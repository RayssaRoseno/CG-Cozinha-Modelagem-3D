#include "pch.h"
#include "window.hpp"
#include "vec.hpp"
#include "reader.hpp"
#include "light.hpp"

static camera cam {
    {0.0f, 0.0f, 5.0f},
    {0.0f, 0.0f, -3.0f},
    {0.0f, 1.0f, 0.0f},
};

float door_rotate = 0.0f;
float window_rotate = 0.0f;
float last_frame = 0.0f, dt = 0.0f;
float speed = 9.6f * 2.0f; // camera speed

float rot_angle = 0.0f;
float sun_rot_angle = 0.0f;
float clock_rot = 0.0f;
bool rotate_sun = true;

static void idle()
{
    float current_frame = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    dt = current_frame - last_frame;
    last_frame = current_frame;

    float rotation_speed = 60.0f * 2.0f;
    rot_angle += rotation_speed * dt;
    
    rot_angle -= 360.0f * (rot_angle >= 360.0f);

    clock_rot += rotation_speed * dt / 8.0f;
   
    clock_rot -= 360.0f * (clock_rot >= 360.0f);

    if (rotate_sun)
    {
        sun_rot_angle += (rotation_speed / 4.0f) * dt;
        sun_rot_angle -= 360.0f * (sun_rot_angle >= 360.0f);
    }

    glutPostRedisplay();
}

static std::unordered_map<const char*, obj_file> models;

material mat1 {{1.0f, 1.0f, 1.0f}, {0.8f, 0.8f, 0.8f}, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, 255.0f};
material black {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0.0f};

material mat_sol {{1.0f, 1.0f, 1.0f}, {1.0f, 0.3f, 0.3f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.5f, 0.0f}, 0.0f};

material mat_lua {{1.0f, 1.0f, 1.0f}, {0.3f, 0.3f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.3f, 0.3f, 1.0f}, 0.0f};

clight light[2];

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cam.look_at();

    for (auto &li: light)
    {
        li.dist_position();
    }

    // Parte do codigo para o sol e lua

    float sun_distance = 400.0f;

    glPushMatrix();
        glRotatef(sun_rot_angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(sun_distance, 0.0f, 0.0f);
        mat_sol.apply_material();
        glutSolidSphere(4.0f, 10.0f, 10.0f);
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(sun_rot_angle - 180.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(sun_distance, 0.0f, 0.0f);
        mat_lua.apply_material();
        glutSolidSphere(8.0f, 10.0f, 10.0f);
    glPopMatrix();

    // Parte do codigo para objetos

    glPushMatrix();//cozinha
        glTranslatef(0.0f, -5.0f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(5.0f, 5.0f, 5.0f);
        models["base cozinha"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//janela01
        glTranslatef(-5.5f + (window_rotate / (10.0f)), -4.0f, 33.80f);
        glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
        glScalef(4.0f, 6.0f, 4.0f);
        models["janela"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//janela02_nao se move
        glTranslatef(5.5f, -4.0f, 33.90f);
        glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
        glScalef(4.0f, 6.0f, 4.0f);
        models["janela"].draw_mat_mesh();
    glPopMatrix(); 

    glPushMatrix();//janela03_nao se move
        glTranslatef(13.2f, -4.0f, 33.90f);
        glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
        glScalef(4.0f, 6.0f, 2.5f);
        models["janela"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//cadeira
        glTranslatef(-13.0f, -4.7f, 2.5f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glScalef(4.5f, 4.9f, 4.9f);
        models["cadeira"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//pia
        glTranslatef(5.5f, -4.7f, 22.0f);
        glRotatef(180.0f, 0.0f, -1.0f, 0.0f);
        glScalef(4.0f, 4.0f, 4.0f);
        models["pia"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//mesa
        glTranslatef(0.0f, -4.7f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(4.5f, 4.5f, 4.5f);
        models["mesa de jantar"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//cadeira
        glTranslatef(15.0f, -4.7f, -2.5f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(4.5f, 4.9f, 4.9f);
        models["cadeira"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//porta
        glTranslatef(24.7f, -5.0f, -14.0f);
        glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
        glRotatef(door_rotate, 0.0f, -1.0f, 0.0f);
        glTranslatef(6.3f, 0.0f, 0.0f);
        glScalef(7.0f, 6.5f, 2.0f);
        models["porta cozinha"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//luminaria
        glTranslatef(0.0f, 4.2f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(3.0f, 3.0f, 3.0f);
        models["luminaria de mesa"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();//quadro
        glTranslatef(0.0f, -5.0f, -20.0f);
        glRotatef(90.0f, 0.0f, -5.0f, 0.0f);
        glScalef(5.0f, 5.0f, 5.0f);
        models["quadro"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix(); // ventilador
        glTranslatef(0.0f, 19.85f, 1.5f);
        glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
        glScalef(0.5f, 0.5f, 0.5f);
        models["ventiladorc"].draw_mat_mesh();
        glTranslatef(0.0f, -0.9f, 0.45f);
        glRotatef(rot_angle, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        models["ventiladorh"].draw_mat_mesh();
    glPopMatrix();

    black.apply_material();
    glPushMatrix();
        glTranslatef(0.0f, 18.0f, -20.8f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(5.0f, 5.0f, 5.0f);

        glPushMatrix(); // relogio ponteiros horas
            glRotatef(clock_rot, 0.0f, -1.0f, 0.0f);
            glTranslatef(0.25f, 0.1f, 0.0f);
            glScalef(0.5f, 0.1f, 0.1f);
            glutSolidCube(1.0f);
        glPopMatrix();
        
        glPushMatrix(); // relogio ponteiros minutos
            glRotatef(sun_rot_angle, 0.0f, -1.0f, 0.0f);
            glTranslatef(0.25f, 0.1f, 0.0f);
            glScalef(0.5f, 0.1f, 0.1f);
            glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix(); // relogio ponteiros segundos
            glRotatef(rot_angle, 0.0f, -1.0f, 0.0f);
            glTranslatef(0.25f, 0.1f, 0.0f);
            glScalef(0.5f, 0.1f, 0.1f);
            glutSolidCube(1.0f);
        glPopMatrix();

        mat1.apply_material();
        glPushMatrix(); // relogio corpo
            glScalef(1.0f, 0.1f, 1.0f);
            glutSolidCube(1.0f);
        glPopMatrix();
    glPopMatrix();


    glPushMatrix(); // geladeira
        glTranslatef(22.0f, 6.0f, 20.0f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(1.4f, 2.4f, 2.4f);

        glPushMatrix();
            glTranslatef(1.8f, 1.2f, 0.0f);
            glScalef(2.0f, 0.8f, 3.0f);
            glutSolidCube(1.0f);
        glPopMatrix();

        glScalef(4.0f, 5.0f, 10.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-17.6f, 4.0f, -5.0f);
        glScalef(3.0f, 3.0f, 3.0f);
        models["armario"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30.0f, -4.8f, -75.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(4.0f, 4.0f, 4.0f);
        models["area externa"].draw_mat_mesh();
    glPopMatrix();

    glPushMatrix(); // piso
        glTranslatef(0.0f, -5.2f, 0.0f);
        glScalef(200.0f, 0.3f, 200.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    glutSwapBuffers();
}

window mwindow; // declaração de janela no opengl

void reshape(int width, int height)
{
    mwindow.set_dimensions_values(width, height);
    mwindow.run_perspective();
}

void motion(int x, int y)
{
    cam.motion(x, y, 0.22f);
}



bool light_on = true;

void keyboard(unsigned char key, int x, int y)
{
    float cam_speed = speed * dt;
    switch (key)
    {
        case 'w':
            cam.pos += cam.front * cam_speed / 2.0f;
        break;
        case 's':
            cam.pos -= cam.front * cam_speed / 2.0f;
        break;
        case 'a':
            cam.pos -= cam.side_vector() * cam_speed;
        break;
        case 'd':
            cam.pos += cam.side_vector() * cam_speed;
        break;
        case ' ':
            cam.pos += cam.up * cam_speed;
        break;
        case 'b':
            cam.pos -= cam.up * cam_speed;
        break;
        case 'o':
            if (door_rotate <= 85.0f)
            {
                door_rotate += 5.0f;
            }
        break;
        case 'p':
            if (door_rotate >= 5.0f)
            {
                door_rotate -= 5.0f;
            }
        break;
        case 'm':
            if (window_rotate >= 5.0f)
            {
                window_rotate -= 5.0f;
            }
        break;
        case 'l':
            if (window_rotate <= 85.0f)
            {
                window_rotate += 5.0f;
            }
        break;
        case 'i':
            rotate_sun = !rotate_sun;
            break;
        case 'r':
            static GLenum mode = GL_LINE;
            glPolygonMode(GL_FRONT_AND_BACK, mode);
            mode = mode == GL_LINE ? GL_FILL : GL_LINE;
        break;
        case 'k':
            if (light_on)
            {
                light[1].disable();
                light_on = false;
            }
            else
            {
                light[1].enable();
                light_on = true;
            }
        break;
        case 'u':
            printf("%f %f %f\n", cam.pos.x, cam.pos.y, cam.pos.z);
            printf("%f %f %f\n", cam.front.x, cam.front.y, cam.front.z);
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == 3) // wheel up
    {
    }
    else if (button == 4) // wheel down
    {
    }
}

#ifndef TEST

int main(int argc, char **argv)
{
    mwindow.init(argc, argv, "CG Cozinha AB2", 1080, 900);

    glEnable(GL_DEPTH_TEST);
    /* lightning  */
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    light[0] = clight(
        0,
        {0.488164f, 3.054233f, 6.129874f, 0.0f}, // position
        {0.0f, 0.0f, 0.0f, 0.0f}, // direction
        {0.0f, 0.0f, 0.0f, 1.0f}, // ambient
        {0.5f, 0.5f, 0.5f, 1.0f}, // diffuse
        {1.0f, 1.0f, 1.0f, 1.0f}, // specular
        0.0f, 0.0f, clight::type::point_light
    );

    light[1] = clight(
        1,
        {2.337596f, -20.059727f, 3.531517f, 1.0f}, // position
        {-0.409779f, 21.274517f, 1.932557f, 1.0f},   // direction
        {1.2f, 1.2f, 1.2f, 1.0f},   // ambient
        {2.0f, 2.2f, 2.0f, 2.0f},   // diffuse
        {1.5f, 1.5f, 1.5f, 1.0f},   // specular
        30.0f, 10.0f, clight::type::spot_light
    );

    for (auto &li: light)
    {
        li.enable();
        li.apply_color();
    }

    mwindow.set_display_func(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(motion);

    cam.center_camera_angle(mwindow);
   
    models["base cozinha"]      = obj_file("objs/baseCozinhateste.obj");
    models["cadeira"]           = obj_file("objs/cadeira.obj");
    models["janela"]            = obj_file("objs/janela.obj");
    models["mesa de jantar"]    = obj_file("objs/mesadejantar.obj");
    models["pia"]               = obj_file("objs/piateste.obj");
    models["porta cozinha"]     = obj_file("objs/portacozinha.obj");
    models["luminaria de mesa"] = obj_file("objs/luminariademesa.obj");
    models["quadro"]            = obj_file("objs/quadro.obj");
    models["ventiladorc"]       = obj_file("objs/ventilador_corpo.obj");
    models["ventiladorh"]       = obj_file("objs/ventilador_helice.obj");
    
    models["area externa"]      = obj_file("objs/area.obj");
    models["armario"]           = obj_file("objs/armario.obj");

    mwindow.run();
    return 0;
}

#endif
