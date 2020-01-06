#include "cam.h"

terrain::terrain(float xx, float yy, uint div) : size(xx, yy), div(div), t("assets/textures/empty.png"){
    float dx = xx / div;
    float dy = yy / div;
    int co = 0;
    xfvec<vec2> tex;
    xfvec<vec3> colors;
    for (uint i = 0; i < div + 1; i++)
    {
        uint row = (div + 1) * i;
        float y = i * dy;
        for (uint j = 0; j < div + 1; j++)
        {
            float x = j * dx;
            float z = ranf() * 0.2f;
            vertices.emplace(x, z, y);
            vec3 cc = { ranf(), ranf(), ranf() };
            colors.emplace(~cc);
            tex.emplace(i * dx / xx, j * dy / yy);
            if (i != div && j != div)
            {
                indices.emplace(j + row, j + 1 + row, j + div + 1 + row);
                indices.emplace(j + div + 2 + row, j + div + 1 + row, j + 1 + row);
            }
        }
    }
    mesh.gen();
    vbo = buffer(vertices, GL_ARRAY_BUFFER);
    mesh.attrib(0, 3, 0, 0);
    buffer(tex, GL_ARRAY_BUFFER);
    mesh.attrib(2, 3, 0, 0);
    buffer(colors, GL_ARRAY_BUFFER);
    mesh.attrib(3, 3, 0, 0);
    buffer(indices, GL_ELEMENT_ARRAY_BUFFER);
    drawsize = indices.size() * 3;
}
void terrain::draw() {
    mesh.bind();
    t.bind();
    shader::active->uniform("xform", xform);
    glDrawElements(GL_TRIANGLES, drawsize, GL_UNSIGNED_INT, 0);
}

float terrain::height(vec3 pos)
{
    if (pos.x < 0 || pos.z < 0 || pos.x > size.x || pos.z > size.y) return 0;
    vec2 loc = (pos.xz) / size * div;
    uvec2 grid = loc;
    vec2 f = loc - (vec2)grid;
    uvec3 is = indices[(grid.y * div + grid.x) * 2 + int(f.x + f.y)];  // index
    vec3 normal = cross(vertices[is.y] - vertices[is.x], vertices[is.z] - vertices[is.x]);
    float h = (dot(normal, vertices[is.x]) - dot(normal.xz, pos.xz)) / normal.y;
    return h;
}

void terrain::highlight(vec3 pos, const vec3& ray)
{
    if (in(key::E))
    {
        pos -= ray * pos.y / ray.y;
        if (pos.x < 0 || pos.z < 0 || pos.x > size.x || pos.z > size.y) return;
        vec2 loc = (pos.xz) / size * div;
        uvec2 grid = loc;
        vec2 f = loc - (vec2)grid;
        uvec3 is = indices[(grid.y * div + grid.x) * 2 + int(f.x + f.y)];  // index
        vertices[is.x].y += clock::dt * 20.f;
        vertices[is.y].y += clock::dt * 20.f;
        vertices[is.z].y += clock::dt * 20.f;
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, is.x * 12 + 4, 4, &vertices[is.x].y);
        glBufferSubData(GL_ARRAY_BUFFER, is.y * 12 + 4, 4, &vertices[is.y].y);
        glBufferSubData(GL_ARRAY_BUFFER, is.z * 12 + 4, 4, &vertices[is.z].y);
    }
}

void fpscam::look()
{
    mat3 mup = axAng(0, 1, 0, mouse::delta.x * dt);
    right = right * mup;
    dir = dir * mup;
    up = up * mup;
    mat3 mright = axAng(right, mouse::delta.y * dt);
    vec3 td = dir * mright;
   // if (absl(td.y) < 0.98f)
    {
        dir = td;
        up = up * mright;
    }
}
void fpscam::move(terrain& t)
{
    if (in(key::D)) pos += right * dt * speed;
    if (in(key::A)) pos -= right * dt * speed;
    if (in(key::W)) pos -= dir * dt * speed;
    if (in(key::S)) pos += dir * dt * speed;

    //pos.y = t.height(pos) + 3.f;
}
void fpscam::update(terrain& t)
{
    if (!mouse::status)
    {
        ray = dir;
        look();
    }
    move(t);
    view.row[3].x = -dot(pos, right);
    view.row[3].y = -dot(pos, up);
    view.row[3].z = -dot(pos, dir);
    static mat4 invprj = perspective(90.f, window::size.y / window::size.x, 0.1f, 10000.f).xpos().inv();
    if(mouse::status)
    {
        vec4 eye = invprj * mouse::normalized();
        ray = -~(vec4(eye.xy, -1.f, 0.f) * view.inv()).xyz;          
    }
}

void tpscam::look()
{
    if (in(key::Q)) radius += clock::dt;
    if (in(key::E) && radius > 3) radius -= clock::dt;
    if (in(key::Right)) {
        mouse::hide();
        mat3 mup = axAng(0, 1, 0, mouse::delta.x * dt);
        right = right * mup;
        mat3 mright = axAng(right, mouse::delta.y * dt);
        up = up * mup * mright;
        dir = dir * mup * mright;
        right = cross(up, dir);
        up = cross(dir, right);
    }
    else mouse::show();
}
void tpscam::move()
{
    if (in(key::D)) ppos.xz += right.xz * dt;
    if (in(key::A)) ppos.xz -= right.xz * dt;
    if (in(key::W)) ppos.xz -= dir.xz * dt;
    if (in(key::S)) ppos.xz += dir.xz * dt;
}
void tpscam::updateRay()
{
    vec2 m = (mouse::pos / window::size) * 2.f - 1.f;
    vec2 a = { atanf(-m.x * window::size.x / window::size.y * tanf(45.f * ct::rad)), atanf(m.y * tanf(45.f * ct::rad)) };
    quat q = axAng(up, a.x);
    vec3 tright = q * right;
    vec3 tdir = q * dir;
    ray = tdir * axAng(tright, a.y);
}
void tpscam::update()
{
    look();
    move();
    ppos.y = 0.5f;
    pos = ppos + dir * radius;

    updateRay();
    view.row[3].x = -dot(pos, right);
    view.row[3].y = -dot(pos, up);
    view.row[3].z = -dot(pos, dir);
    {
        shader::active->uniform("xform", xform);
        character.bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}


shooter::prj::prj(const vec3& p, const vec3& d) 
    : dir(d* axAng(ranf()*0.01f, 1, ranf() * 0.01f, ranf() * 0.01f))
{ 
    pos = p; 
}

void shooter::prj::draw() {
    y -= clock::dt * 0.05f;
    pos -= dir * clock::dt * 150.f;
    pos.y += y;
    shader::active->uniform("xform", xform);
}

bool shooter::prj::ttd() 
{ 
    ++f;  
    return f > 1000 || pos.y < -10; 
}
void shooter::update(const cam& cam)
{
    if (in(key::Left)) projectiles.emplace(cam.pos, cam.ray);
    v.bind();
    xfvec<pptr*> erases;
    for (pptr& p : projectiles)
    {
        if (p.p->ttd()) erases.push(&p);
        p.p->draw();
        glDrawArrays(GL_TRIANGLES, 0, v.size);
        //glDrawElements(window::render_mode, 36, GL_UNSIGNED_INT, 0);
    }
    for (pptr* p : erases) projectiles.erase(p);
}