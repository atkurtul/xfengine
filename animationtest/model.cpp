#include "model.h"

mat4 interpolate(const mat4& x, const mat4& y, float t)
{
    quat q0 = x, q1 = y;
    mat4 re = q0 * (1.f - t) + sign(dot(q0, q1)) * t * q1;
    re.col[3].xyz = x.col[3].xyz + (y.col[3].xyz - x.col[3].xyz) * t;
    return re;
}

mat4* frame::getPoseAt(float t) const
{
    mat4* re = 0;
    if (input.empty()) return re;
    for (uint i = 1; i < input.size(); ++i)
    {
        if (input[i] > t)
        {
            t = (t - input[i - 1]) / (input[i] - input[i - 1]);
            return re = new mat4(interpolate(output[i - 1], output[i], t));
        }
    }
}

void animation::update() const
{
    t += clock::dt;
    if (t >= len) t -= len;
}

void bone::setPose(const animation& animation, const mat4& parentxf)
{
    mat4* pose = animation.frames[id].getPoseAt(animation.t);
    if (pose)
    {
        mat4 bound = parentxf * *pose;
        delete pose;
        anim = bound * inv;
        for (bone* b : children)
            b->setPose(animation, bound);
        return;
    }
    mat4 bound = parentxf * bind;
    anim = bound * inv;
    for (bone* b : children)
        b->setPose(animation, bound);
}

void a_model::handleBones(xfvec<bone*>& v, xfvec<xml_node*>& nodes, xfvec<xfstr>& namearray, xfvec<mat4>& inv)
{
    for (xml_node* n : nodes)
    {
        xfstr* name = namearray.find(n->attribs["sid"]);
        int id = name - namearray.begin();
        binds[id] = n->getChild("matrix")->readDataAsMat4<float>().front();
        bone* b = new bone(id, *name, inv[id], xforms[id], binds[id]);
        v.push(b);
        auto children = n->getChildren("node", "type", "JOINT");
        handleBones(b->children, children, namearray, inv);
    }
}

void a_model::addAnim(const char* path)
{
    xml_parser p(path);
    //animation
    auto animroot = p.root.getDescendant("animation", "id", "action_container");
    animations.push({});
    animation& anim = animations.back();
    for (xfstr& n : namearray)
    {
        auto in = animroot->getDescendant("float_array", "id", n + "_pose_matrix-input-array");
        auto out = animroot->getDescendant("float_array", "id", n + "_pose_matrix-output-array");

        if (in && out)
        {
            uint id = &n - namearray.begin();
            auto inv = in->readDataAs<float>();
            auto outv = out->readDataAsMat4<float>();
            if (inv.back() > anim.len) anim.len = inv.back();
            anim.frames[id] = { (xfvec<float>&&)inv, (xfvec<mat4>&&)outv };
        }
    }

}

a_model::a_model(const char* path)
{
    xml_parser p(path);
    //geometry
    auto vertices = p.root.getDescendant("float_array", "id", "mesh-positions-array")->readDataAsVec<float, 3>();
    auto normals = p.root.getDescendant("float_array", "id", "mesh-normals-array")->readDataAsVec<float, 3>();
    auto textures = p.root.getDescendant("float_array", "id", "mesh-map-0-array")->readDataAsVec<float, 2>();
    uint dim = p.root.getDescendant("triangles")->getChildren("input").size();
    auto indicesroot = p.root.getDescendant("mesh")->getChildren("triangles");
    xfvec<uint> indices;
    for (auto triangles : indicesroot)
    {
        auto v = triangles->getChild("p")->readDataAs<uint>();
        for (uint u : v) indices.push(u);
    }
    //controllers
    namearray = p.root.getDescendant("Name_array", "id", "skin-joints-array")->readDataAsStr();
    invbinds = p.root.getDescendant("float_array", "id", "skin-bind_poses-array")->readDataAsMat4<float>();
    auto weights = p.root.getDescendant("float_array", "id", "skin-weights-array")->readDataAs<float>();
    auto vcount = p.root.getDescendant("vcount")->readDataAs<uint>();
    auto vs = p.root.getDescendant("v")->readDataAs<uint>();
    auto sorted = sortWeights(weights, vcount, vs);

    //bone hierarchy
    xforms.resize(namearray.size());
    binds.resize(namearray.size());
    auto boneroot = p.root.getDescendant("node", "id", "Armature");
    auto ourBones = boneroot->getChildren("node", "type", "JOINT");
    handleBones(bones, ourBones, namearray, invbinds);
    struct layout
    {
        vec3 v;
        vec3 n;
        vec2 t;
        uvec3 j;
        vec3 w;
    };

    xfvec<layout> finalbuffer;
    for (int i = 0; i < indices.size(); i += dim) {

        finalbuffer.push(
            {
                vertices[indices[i]],
                normals[indices[i + 1]], // normal
                textures[indices[i + 2]], // uv
                sorted[indices[i]].first, // joint index
                sorted[indices[i]].second // joint weight
            });
    }
    mesh.gen();
    buffer(finalbuffer);
    mesh.attrib (0, 3, 14, 0);
    mesh.attrib (1, 3, 14, 3);
    mesh.attrib (2, 2, 14, 6);
    mesh.attribI(3, 3, 14, 8);
    mesh.attrib (4, 3, 14, 11);
    mesh.size = finalbuffer.size();
}

void a_model::update()
{
    animations[activeAnimation].update();
    for (bone* b : bones)
        b->setPose(animations[activeAnimation], m4id);
}

void a_model::draw()
{
    update();
    mesh.bind();
    shader::active->uniform("xform", xform);
    shader::active->uniform("bones", xforms);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size);
}


xfvec<xfcouple<uvec3, vec3>> a_model::sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v)
{
    struct weight
    {
        uint i;
        float w;
        bool operator <= (const weight& W) { return w <= W.w; }
    };
    xfvec<xfcouple<uvec3, vec3>> re;
    uint current = 0;
    for (uint i : vcount) {
        xfvec<weight> temp;
        for (uint j = 0; j < i * 2; j += 2)
        {
            temp.push({ v[j + current * 2], weights[v[j + 1 + current * 2]] });
        }

        temp.sort();
        temp.reverse();
        xfcouple<uvec3, vec3> t;
        for (uint j = 0; j < 3 && j < temp.size(); ++j)
        {
            t.first[j] = temp[j].i;
            t.second[j] = temp[j].w;
        }
        float l = 1.f / (t.second.x + t.second.y + t.second.z);
        t.second.x *= l;
        t.second.y *= l;
        t.second.z *= l;
        re.push(t);
        current += i;
    }
    return re;
}

model::model(const char* path)
{
    xml_parser p(path);
    //geometry
    auto vertices = p.root.getDescendant("float_array", "id", "mesh-positions-array")->readDataAsVec<float, 3>();
    cout << vertices.size() << "\n";
    auto normals = p.root.getDescendant("float_array", "id", "mesh-normals-array")->readDataAsVec<float, 3>();
    auto textures = p.root.getDescendant("float_array", "id", "mesh-map-0-array")->readDataAsVec<float, 2>();
    uint dim = p.root.getDescendant("triangles")->getChildren("input").size();
    auto indicesroot = p.root.getDescendant("mesh")->getChildren("triangles");
    xfvec<uint> indices;
    for (auto triangles : indicesroot)
    {
        auto v = triangles->getChild("p")->readDataAs<uint>();
        for (uint u : v) indices.push(u);
    }
    struct layout
    {
        vec3 v;
        vec3 n;
        vec2 t;
    };
    xfvec<layout> finalbuffer;
    for (int i = 0; i < indices.size(); i += dim) {

        finalbuffer.push(
            {
                vertices[indices[i]],
                normals[indices[i + 1]], // normal
                textures[indices[i + 2]], // uv
            });
    }
    mesh.gen();
    buffer(finalbuffer);
    mesh.attrib(0, 3, 8, 0);
    mesh.attrib(1, 3, 8, 3);
    mesh.attrib(2, 2, 8, 6);
    mesh.size = finalbuffer.size();
}

void model::draw()
{
    mesh.bind();
    shader::active->uniform("xform", xform);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size);
}

