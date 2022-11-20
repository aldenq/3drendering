#include <SDL2/SDL.h>
#include "draw.h"
#include "render.h"
#include "vectors.h"
#include "geometry.h"

SDL_Event evt;
int running = 1;

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

    for (int i = 0; i < 80000; i++)
    {

        // clearAll();
        
        transformVerts2();
        // render();
    }
}





void normalRun(){

    setupDraw();
    setupCamera();
    float state = 1;
    Vect3f p1 = {.x = -10 + 5, .y = 1.5, .z = 5};
    Vect3f p2 = {.x = 10 + 5, .y = 1.5, .z = 5};
    Vect3f p3 = {.x = -10 + 5, .y = 1.5, .z = 0};

    Vect3f p4 = {.x = -100, .y = 0, .z = 25};
    Vect3f p5 = {.x = 0, .y = 120, .z = 5};
    Vect3f p6 = {.x = 100, .y = 0, .z = 25};

    // addViewTriangle(p1,p2,p3);
    // addViewTriangle(p4,p5,p6);
    VertexBuffer *teapot = getUtah();

    teapot->position = (Vect3f){.x = 0, .y = 2, .z = 5};
    teapot->rotation.z = 3.1415;

    cameraPos.y = -2;
    cameraRot.x -= 3.1415 / 8;
    while (running)
    {
        state += .005;
        clearAll();
        teapot->rotation.y = state;

        cameraPos.z = -2;
        // p4 = (Vect3f){.x = 40 * sin(state), .y= -60, .z=40*cos(state) + 150};
        // p5 = (Vect3f){.x = 0, .y= 60, .z=150};
        // p6 = (Vect3f){.x = 40 * sin(state+3.14159), .y= -60, .z=40*cos(state+3.14159) + 150};

        // p1 = (Vect3f){.x = 40 * sin(state+3.14159/2), .y= -30, .z=40*cos(state+3.14159/2) + 150};
        // p2 = (Vect3f){.x = 50 * sin(state+3.14159/2), .y= 30, .z= 50*cos(state+3.14159/2) + 150};
        // p3 = (Vect3f){.x = 60 * sin(state+3.14159/2), .y= -30, .z=60*cos(state+3.14159/2) + 150};

        // cameraRot.y = 3.1415 * sin(state)/6;
        //  cameraRot.x = 3.1415 * sin(state)/6;
        //  printf("%.6f\n", cameraRot.x);
        //  addGlobalTriangle(p4,p5,p6);
        //addGlobalTriangle(p1, p2, p3);

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
        }

        // pixelBuffer[5][5].x = 255*state;
        // printf("%9.6f  %9.6f\n\n", p4.x,p6.x);
        // printf("%9.6f\n", p4.x+p6.x);
        // state = !state;
    }
    // // //benchmark();
}







int main()
{
//     int indexs[] = {0*3,1*3,2*3,3*3,4*3,5*3,6*3,7*3};

//     float a[] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0,24.0};
//     SIMD_test(a,indexs);

    benchmark2();   

    //normalRun();
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
