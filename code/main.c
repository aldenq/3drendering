#include <SDL2/SDL.h>
#include <sys/time.h>

#include "draw.h"
#include "render.h"
#include "vectors.h"
#include "geometry.h"
#include "objhandler.h"
#define MOUSE_SENSITIVITY 0.04
SDL_Event evt;
int running = 1;
int KEYS[322];
float spf = .01;
float timeScale=.1;
float prev=1;

void benchmark()
{
    VertexBuffer *teapot = getUtah();
    for (int i = 0; i < 1000; i++)
    {

        clearAll();
        loadVertexBuffer(teapot);
        render();
    }
}

void benchmark2()
{
    VertexBuffer *teapot = getUtah();
    loadVertexBuffer(teapot);
    loadVertexBuffer(teapot);

    for (int i = 0; i < 100000; i++)
    {

        // clearAll();

        transformVerts2();
        // printf("%d\n",i);
        // render();
    }
}

void benchmarkrender()
{
    setupCamera();
    VertexBuffer *teapot = loadFromOBJ("CuberpunkCityWithKaws.obj");
    teapot->position = (Vect3f){.x = 0, .y = 2, .z = 5};
    cameraPos.y = -2;
    cameraRot.x -= 3.1415 / 8;

    cameraPos.z = -2;
    teapot->rotation.z = 3.1415;
    loadVertexBuffer(teapot);
    for (int i = 0; i < 200; i++)
    {
        teapot->position = (Vect3f){.x = 0, .y = 2, .z = 5};
        render();
        clearAll();
        loadVertexBuffer(teapot);
        teapot->position.z += 2;
        //loadVertexBuffer(teapot);
    }
}

void handleInput()
{
    Vect3f forward = {0, 0, 0};
    forward.z = cos(cameraRot.y);
    forward.x = sin(cameraRot.y);
    Vect3f across = {0, 0, 0};
    across.z = -sin(cameraRot.y);
    across.x = cos(cameraRot.y);

    if (KEYS[SDL_SCANCODE_W] == 1)
    {
        cameraPos.z += forward.z * .1 *timeScale;
        cameraPos.x += forward.x * .1 *timeScale;
    }
    if (KEYS[SDL_SCANCODE_S] == 1)
    {
        cameraPos.z += forward.z * -.1 * timeScale;
        cameraPos.x += forward.x * -.1 * timeScale;
    }
    if (KEYS[SDL_SCANCODE_A] == 1)
    {
        cameraPos.z += across.z * .1 * timeScale;
        cameraPos.x += across.x * .1* timeScale;
    }
    if (KEYS[SDL_SCANCODE_D] == 1)
    {
        cameraPos.z += across.z * -.1 * timeScale;
        cameraPos.x += across.x * -.1 * timeScale;
    }
    if (KEYS[SDL_SCANCODE_SPACE] == 1)
    {
        cameraPos.y += -.1 * timeScale;
    }
    if (KEYS[SDL_SCANCODE_LSHIFT] == 1)
    {
        cameraPos.y += .1 * timeScale;
    }
}
void normalRun()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    setupDraw();
    setupCamera();
    float state = 1;
    for (int i = 0; i < 322; i++)
    {
        KEYS[i] = 0;
    }
    Vect3f p1 = {.x = 1, .y = 0, .z = 5};
    Vect3f p2 = {.x = 0, .y = 0, .z = 5};
    Vect3f p3 = {.x = 0, .y = 2, .z = 0};

    Vect3f p4 = {.x = -100, .y = 0, .z = 25};
    Vect3f p5 = {.x = 0, .y = 120, .z = 5};
    Vect3f p6 = {.x = 100, .y = 0, .z = 25};

    // addViewTriangle(p1,p2,p3);
    // addViewTriangle(p4,p5,p6);
    VertexBuffer *teapot = loadFromOBJ("CuberpunkCityWithKaws.obj");

    teapot->position = (Vect3f){.x = 0, .y = 2, .z = 5};
    teapot->rotation.z = 3.1415;
    char *out;
    cameraPos.y = -2;
    cameraRot.x -= 3.1415 / 4;
    int status = SDL_CaptureMouse(SDL_TRUE);
    out = SDL_GetError();
    printf("%d %s\n", status, out);

    while (running)
    {
        clearAll();
        state += .005;

        // teapot->rotation.y = state;
        //  teapot->rotation.x = state;

        // cameraPos.z = -2;
        p4 = (Vect3f){.x = 2, .y = 2, .z = 5 };
        p5 = (Vect3f){.x = 0, .y = 0, .z = 5};
        p6 = (Vect3f){.x = -2 , .y = 2, .z = 5};

        // p1 = (Vect3f){.x = 40 * sin(state+3.14159/2), .y= -30, .z=40*cos(state+3.14159/2) + 150};
        // p2 = (Vect3f){.x = 50 * sin(state+3.14159/2), .y= 30, .z= 50*cos(state+3.14159/2) + 150};
        // p3 = (Vect3f){.x = 60 * sin(state+3.14159/2), .y= -30, .z=60*cos(state+3.14159/2) + 150};

        // cameraRot=(Vect3f){0,0,state};
        // cameraPos=(Vect3f){0,0,0};

        //  cameraRot.x = 3.1415 * sin(state)/6;
        //  printf("%.6f\n", cameraRot.x);
        // addGlobalTriangle(p4,p5,p6);

        // p1 = (Vect3f){-1.759013,-0.239987,6.033576};
        // p2 = (Vect3f){-1.536003,-0.243114,5.914171};
        // p3 = (Vect3f){-1.507330,-0.226033,5.970282};
        // // addGlobalTriangle(p1, p2, p3);
        // // addGlobalTriangle(p1, p2, p3);
        // // addGlobalTriangle(p1, p2, p3);
        //addGlobalTriangle(p4, p5, p6);
        int mx, my;

        loadVertexBuffer(teapot);
        render();
        drawBuffer();
        // printf("draw\n");
        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (evt.type == SDL_WINDOWEVENT)
            {
                if (evt.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                {
                    out = SDL_CaptureMouse(SDL_TRUE);
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                    printf("cap%d\n", out);
                }
                else if (evt.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                {
                    SDL_CaptureMouse(SDL_FALSE);
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                    printf("loss\n");
                }
            }
            else if (evt.type == SDL_KEYDOWN)
            {
                int num = evt.key.keysym.scancode;
                if (num < 322)
                {
                    KEYS[evt.key.keysym.scancode] = 1;
                }
                /* code */
            }
            else if (evt.type == SDL_KEYUP)
            {
                int num = evt.key.keysym.scancode;
                if (num < 322)
                {
                    KEYS[evt.key.keysym.scancode] = 0;
                }
                /* code */
            }
        }
        handleInput();

        SDL_GetMouseState(&mx, &my);

        float normalizedMX = ((float)mx) / RENDER_WIDTH - .5;
        float normalizedMY = ((float)my) / RENDER_HEIGHT - .5;
        cameraRot.y = -normalizedMX * 3.1415 * 2 * MOUSE_SENSITIVITY;
        cameraRot.x = -normalizedMY * 3.1415 * 2 * MOUSE_SENSITIVITY;

        // if (cameraRot.x < -3.141/2)
        // {
        //     cameraRot.x = -3.141/2;

        //     SDL_WarpMouseInWindow(win,mx,3500);
        // }
        // else if (cameraRot.x > 3.141/2)
        // {
        //     /* code */
        //     //printf("%d\n",my);
        //     cameraRot.x = 3.141/2;
        //     SDL_WarpMouseInWindow(win,mx, -3451);
        // }
        // if (cameraRot.y<0 || cameraRot.y > 6.141){
        //     cameraRot.y=0;
        // }

        //printf("rot %f %f %f\n", cameraRot.x, cameraRot.y, cameraRot.z);
        // printf("pos %f %f %f\n", cameraPos.x, cameraPos.y, cameraPos.z);
        // pixelBuffer[5][5].x = 255*state;
        // printf("%9.6f  %9.6f\n\n", p4.x,p6.x);
        // printf("%9.6f\n", p4.x+p6.x);
        // state = !state;
        gettimeofday(&end, NULL);
        spf=((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec)/1000000.0;
        start=end;
        timeScale = (spf/(1.0/60.0));
        // printf("%f\n",spf);

    }
    // // //benchmark();
}

int main()
{
    //     int indexs[] = {0*3,1*3,2*3,3*3,4*3,5*3,6*3,7*3};

    //     float a[] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0,24.0};
    //     SIMD_test(a,indexs);

// VertexBuffer *teapot = loadFromOBJ("teapot.obj");
//    VertexBuffer *teapot2 = getUtah();

//     for (int vert = 0; vert < teapot->numFace; vert++)
//     {
//         printf("%d %d %d\n",teapot->faces[vert].x, teapot->faces[vert].y, teapot->faces[vert].z);
//         printf("%d %d %d\n\n", teapot2->faces[vert].x, teapot2->faces[vert].y, teapot2->faces[vert].z);
//     }

    // benchmark2();
    //benchmarkrender();
    normalRun();
    // Vect3f points[] = {
    // {.x = 10, .y = 11, .z = 12},
    // {.x = 20, .y = 21, .z = 22},
    // {.x = 30, .y = 31, .z = 32},
    // {.x = 40, .y = 41, .z = 42},
    // {.x = 50, .y = 51, .z = 52},
    // {.x = 60, .y = 61, .z = 62},
    // {.x = 70, .y = 71, .z = 72},
    // {.x = 80, .y = 81, .z = 82},
    // {.x = 90, .y = 91, .z = 92}
    // };
    // float rx=0;
    // float ry=0;
    // float rz=0;
    // Vect3f rot_sin = {.x=sin(rx),.y=sin(ry),.z=sin(rz)};
    // Vect3f rot_cos = {.x=cos(rx),.y=cos(ry),.z=cos(rz)};
    // Vect3f pos = {.x=0,.y=0,.z=0};
    // asm_transformVerts(points, 8, &rot_sin, &rot_cos,points,&pos);
}
