/**
 * @file render.h
 * @author Alden Quigley (aldenaquigley@gmail.com)
 * @brief all the code for 3d parts of 3d rendering
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "vectors.h"
#include "geometry.h"
#define RENDER_WIDTH 600
#define RENDER_HEIGHT 600
#define maxVerts 200000
#define maxFaces 200000
#define FOV 700.0 // distance between camera and plane

/**
 * @brief SIMD optimized code for transforming vertices
 *
 * @param points pointer to vertices
 * @param numVerts number of vertices
 * @param Sin_rotation precached sin and cos for performance
 * @param Cos_rotation
 * @param dest where to write transformed points back to
 * @param pos camera position
 */
extern void asm_transformVerts(Vect3f *points, int numVerts, Vect3f *Sin_rotation, Vect3f *Cos_rotation, Vect3f *dest, Vect3f *pos);

extern Vect3f cameraPos; // camera position
extern Vect3f cameraRot; // camera rotation
extern float ZBuffer[RENDER_WIDTH][RENDER_HEIGHT];
extern int faceIndex[RENDER_WIDTH][RENDER_HEIGHT]; // stores indices for which face is being shown at a given point in the zbuffer
extern Vect3f normals[maxFaces];                   // stores the normals for each face

/**
 * @brief adds a triangle directly to camera space(should only be used for debugging)
 *
 * @param p1 point in triangle
 * @param p2 point in triangle
 * @param p3 point in triangle
 */
void addViewTriangle(Vect3f p1, Vect3f p2, Vect3f p3);
/**
 * @brief adds a triangle into world space
 *
 * @param p1 point in triangle
 * @param p2 point in triangle
 * @param p3 point in triangle
 */
void addGlobalTriangle(Vect3f p1, Vect3f p2, Vect3f p3);

/**
 * @brief generates the zbuffer
 *
 */
void depthSort();

/**
 * @brief empties out the zbuffer and all the vertices/faces
 *
 */
void clearAll();
/**
 * @brief wrapper for a couple of function used to render
 *
 */
void render();
/**
 * @brief sets up the camera, just used in init
 *
 */
void setupCamera();
/**
 * @brief takes in a vertex buffer and adds it so it can be rendered
 *
 * @param vbuffer pointer to VertexBuffer which should be added
 */
void loadVertexBuffer(VertexBuffer *vbuffer);
/**
 * @brief transforms verts into camera space using SIMD optimized code
 *
 */
void transformVerts();
/**
 * @brief transforms verts into camera space using C implimentation
 *
 */
void transformVerts2();
