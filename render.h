#pragma once
#include "vectors.h"
#include "geometry.h"
#define RENDER_WIDTH 500
#define RENDER_HEIGHT 500
#define maxVerts 5000
#define maxFaces 10000
#define FOV 350.0

extern void asm_transformVerts(Vect3f*points,int numVerts, Vect3f*Sin_rotation,Vect3f*Cos_rotation, Vect3f* dest,Vect3f* pos);
// extern float asm_sin(float n);
// extern void SIMD_test(float*n, int* index);
extern Vect3f cameraPos;
extern Vect3f cameraRot;
extern float ZBuffer[RENDER_WIDTH][RENDER_HEIGHT];
extern int indices[8];
void addViewTriangle(Vect3f p1, Vect3f p2, Vect3f p3);
void addGlobalTriangle(Vect3f p1, Vect3f p2, Vect3f p3);
void depthSort();
void clearAll();
void render();
void setupCamera();
void loadVertexBuffer(VertexBuffer* vbuffer);
void transformVerts();
void transformVerts2();



















