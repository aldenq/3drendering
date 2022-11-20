#pragma once
#include "vectors.h"

typedef struct VertexBuffer
{
    Vect3f position;
    Vect3f rotation;
    int numFace;
    int numVerts;
    Vect3f *verts;
    Vect3i *faces;

} VertexBuffer;


VertexBuffer* getUtah();