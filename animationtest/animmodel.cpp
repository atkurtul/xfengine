#include "animmodel.h"

mat4 interpolate(const mat4& x, const mat4& y, float t)
{
    quat q0 = x, q1 = y;
    vec3 v0 = x.col[3].xyz;
    vec3 v1 = y.col[3].xyz;
    mat4 re = q0 * (1.f - t) + sign(dot(q0, q1)) * t * q1;
    re.col[3].xyz = v0 + (v1 - v0) * t;
    return re;
}

mat4* frame::getPoseAt(float t) const
{
    mat4* re = 0;
    if (input.empty()) return re;
    if (t <= input[1])
        return re = new mat4(interpolate(output[0], output[1], (t - input[0]) / (input[1] - input[0])));
    for (uint i = 0, j = 1; j < input.size(); ++i, ++j)
    {
        if (input[i] == t) return re = new mat4(output[i]);
        if (input[i] <= t && input[j] > t)
            return re = new mat4(interpolate(output[i], output[j], (t - input[i]) / (input[j] - input[i])));
    }
}

void animation::update()
{
    t += clock::dt * 0.1f;
    if (t >= len) t -= len;
}

void bone::setPose(const animation& animation, const mat4& parentxf)
{
    mat4* pose = animation.frames[id].getPoseAt(animation.t);
    if (!pose) pose = new mat4(bind);
    mat4 bound = parentxf * *pose;
    delete pose;
    anim = bound * inv;
    for (bone* b : children)
        b->setPose(animation, bound);
}

void model::update()
{
    anim.update();
    for (bone* b : bones)
        b->setPose(anim, mat4());
}

void model::handleBones(xfvec<bone*>& v, xfvec<xml_node*>& nodes, xfvec<xfstr>& namearray, xfvec<mat4>& inv)
{
    for (xml_node* n : nodes)
    {
        int id = namearray.find(n->attribs["sid"]) - namearray.begin();
        bone* b = new bone(id, n->attribs["sid"], inv[id], xforms[id], n->getChild("matrix")->readDataAsMat4<float>().front());
        v.push(b);
        auto children = n->getChildren("node", "type", "JOINT");
        handleBones(b->children, children, namearray, inv);
    }
}
model::model(const char* path)
{
    xml_parser p(path);
    //geometry
    auto vertices = p.root.getDescendant("float_array", "id", "mesh-positions-array")->readDataAsVec<float, 3>();
    auto normals = p.root.getDescendant("float_array", "id", "mesh-normals-array")->readDataAsVec<float, 3>();
    auto textures = p.root.getDescendant("float_array", "id", "mesh-map-0-array")->readDataAsVec<float, 2>();
    uint dim = p.root.getDescendant("triangles")->getChildren("input").size();
    auto indices = p.root.getDescendant("p")->readDataAs<uint>();

    //controllers
    auto namearray = p.root.getDescendant("Name_array", "id", "skin-joints-array")->readDataAsStr();
    auto invbinds = p.root.getDescendant("float_array", "id", "skin-bind_poses-array")->readDataAsMat4<float>();
    auto weights = p.root.getDescendant("float_array", "id", "skin-weights-array")->readDataAs<float>();
    auto vcount = p.root.getDescendant("vcount")->readDataAs<uint>();
    auto vs = p.root.getDescendant("v")->readDataAs<uint>();
    auto sorted = sortWeights(weights, vcount, vs);

    //bone hierarchy
    //xforms.resize(namearray.size());
    //auto boneroot = p.root.getDescendant("node", "id", "armature");
    //auto ourbones = boneroot->getChildren("node", "type", "joint");
    //handleBones(bones, ourbones, namearray, invbinds);

    //animation
    //auto animroot = p.root.getDescendant("animation", "id", "action_container");
    //for (xfstr& n : namearray)
    //{
    //    auto in = animroot->getDescendant("float_array", "id", n + "_pose_matrix-input-array");
    //    auto out = animroot->getDescendant("float_array", "id", n + "_pose_matrix-output-array");

    //    if (in && out)
    //    {
    //        uint id = &n - namearray.begin();
    //        auto inv = in->readDataAs<float>();
    //        auto outv = out->readDataAsMat4<float>();
    //        if (inv.back() > anim.len) anim.len = inv.back();
    //        anim.frames[id] = { (xfvec<float>&&)inv, (xfvec<mat4>&&)outv };
    //    }
    //}
    struct layout
    {
        vec3 v;
        vec3 c;
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
                vertices[indices[i]], // color
                normals[indices[i + 1]], // normal
                textures[indices[i + 2]], // uv
                sorted[indices[i]].i, // joint index
                sorted[indices[i]].w // joint weight
            });
    }
    mesh.gen();
    buffer(finalbuffer);
    mesh.attrib(0, 3, 17, 0);
    mesh.attrib(1, 3, 17, 3);
    mesh.attrib(2, 3, 17, 6);
    mesh.attrib(3, 2, 17, 9);
    mesh.attribI(4, 3, 17, 11);
    mesh.attrib(5, 3, 17, 14);
    mesh.size = finalbuffer.size();
}

void model::draw()
{
    update();
    mesh.bind();
    shader::active->uniform("bones", xforms);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size);
}


xfvec<model::vweight> model::sortWeights(const xfvec<float>& weights, const xfvec<uint>& vcount, const xfvec<uint>& v)
{
    {
        xfvec<vweight> re;
        uint current = 0;
        for (uint i : vcount) {
            xfvec<weight> temp;
            for (uint j = 0; j < i * 2; j += 2)
            {
                temp.push({ v[j + current * 2], weights[v[j + 1 + current * 2]] });
            }

            temp.sort();
            temp.reverse();
            vweight t;
            for (uint j = 0; j < 3 && j < temp.size(); ++j)
            {
                t.i[j] = temp[j].i;
                t.w[j] = temp[j].w;
            }
            float l = 1.f / (t.w.x + t.w.y + t.w.z);
            t.w.x *= l;
            t.w.y *= l;
            t.w.z *= l;
            re.push(t);
            current += i;
        }
        return re;
    }
}