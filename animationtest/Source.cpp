#include "cam.h"
#include "model.h"

int main()
{
    window::init(800, 600);
    shader main("assets/shaders/main.vs", "assets/shaders/main.frag");
    main.uniform("prj", perspective(90.f, window::size.y / window::size.x, 0.1f, 10000.f));
    shader anim("assets/shaders/anim.vs", "assets/shaders/anim.frag");
    anim.uniform("prj", perspective(90.f, window::size.y / window::size.x, 0.1f, 10000.f));
    terrain t(800, 800, 800);
    ui ui("assets/shaders/text.vs", "assets/shaders/text.frag", "assets/fonts/arial.ttf");
    fpscam cam;
    mouse::hide();
    shooter s;
    crosshair cs;
    vao mp5k = obj()("assets/models/mp5k2.obj");
    texture mp5kt("assets/textures/MP5K.png");
    //a_model m("char.dae");
    //m.addAnim("char.dae");
    a_model m("girl.dae");
    m.addAnim("girl.dae");
    texture tauren("girl.png");
    while (window::runs()) {

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        main.use();
        cam.update(t);
        static float zoom = 55.f;
        mat4 prj = perspective(zoom, window::size.y / window::size.x, 0.1f, 10000.f);
        main.uniform("view", cam.view); 
        main.uniform("prj", prj);
        if (in(key::Right) && zoom >= 55.f)  zoom -= clock::dt * 400.f;
        else if (!in(key::Right) && zoom <= 90.f) zoom += clock::dt * 400.f;
        s.update(cam);
        tauren.bind();
        t.draw();
        
        t.highlight(cam.pos, cam.ray);
        cs.draw();
        {
            mp5kt.bind();
            mp5k.bind();
            float sss = clock::dt * 0.1f;
            mat4 id;
            id.row[3].xyz = vec3(-.486f, 0.204f, 0.206f) * (1.f - (zoom - 55.f)/35.f);
            main.uniform("xform", id);
            glDrawArrays(GL_TRIANGLES, 0, mp5k.size);
        } 
        anim.use();
        anim.uniform("prj", prj);
        anim.uniform("view", cam.view);
        tauren.bind();
        m.draw();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        ui.render(tostr(clock::fps), 0, 0.9f * window::size.y);
        ui.render(tostr(mouse::pos), 0, 0.8f * window::size.y);
        ui.render(tostr(mouse::normalized()), 0, 0.7f * window::size.y);
        ui.render(tostr(cam.ray), 0, 0.6f * window::size.y);
        ui.render(tostr(s.projectiles.size()), 0, 150);
        ui.render(tostr(cam.right), 0, 120);
        ui.render(tostr(cam.up), 0, 80);
        ui.render(tostr(cam.dir), 0, 40);
        ui.render(tostr(cam.pos), 0, 0);

        {
            static float t = 0.2f;
            t -= clock::dt;
            if (in(key::SPACE) && t < 0.f) mouse::toggle(), t = 0.2f;
        }
    }
}