/**
 * @file geometry.h
 * @author your name (you@domain.com)
 * @brief describes how geometry data is stored
 * @version 0.1
 * @date 2022-12-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "vectors.h"
/**
 * @brief describes how geometry data is stored
 * 
 */
typedef struct VertexBuffer
{
    Vect3f position;
    Vect3f rotation;
    int numFace;
    int numVerts;
    Vect3f *verts;
    Vect3i *faces;

} VertexBuffer;

/**
 * @brief gets a Vertex buffer containing data for utah teapot
 * 
 * @return VertexBuffer*
 */
VertexBuffer* getUtah();