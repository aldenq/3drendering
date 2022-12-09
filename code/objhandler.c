#include "geometry.h"
#include "vectors.h"
#include "objhandler.h"
#include <stdio.h>
#include <stdlib.h>
VertexBuffer *loadFromOBJ(char *filepath)
{
    VertexBuffer *out = malloc(sizeof(VertexBuffer));
    FILE *objFile = fopen(filepath, "r");
    int numVerts = 0;
    int numFaces = 0;
    int lines = 0;
    char inptBuffer[128];

    char *done = 1;
    while (done)
    {

        done = fgets(inptBuffer, 128, objFile);

        if (inptBuffer[0] == 'v' && inptBuffer[1] == ' ')
        {
            numVerts += 1;
            // printf("%s", inptBuffer);
        }
        else if (inptBuffer[0] == 'f' && inptBuffer[1] == ' ')
        {
            numFaces += 1;
            // printf("%s", inptBuffer);
        }

        lines += 1;
    }
    rewind(objFile);
    out->numVerts = numVerts;
    out->verts = (Vect3f *)malloc(sizeof(Vect3f) * numVerts);
    out->faces = (Vect3i *)malloc(sizeof(Vect3i) * numFaces);
    out->numFace = numFaces;

    //printf("verts %d\nfile lines:%d\n faces%d\n", numVerts, lines, numFaces);
    int vertIndex = 0;
    int faceIndex = 0;
    done = 1;
    while (done)
    {

        done = fgets(inptBuffer, 128, objFile);

        if (inptBuffer[0] == 'v' && inptBuffer[1] == ' ')
        {
            sscanf(inptBuffer, "v %f %f %f", &out->verts[vertIndex].x, &out->verts[vertIndex].y, &out->verts[vertIndex].z);
            // printf("v %f %f %f\n",out->verts[vertIndex].x,out->verts[vertIndex].y,out->verts[vertIndex].z);
            vertIndex += 1;
            // printf("%s", inptBuffer);
        }
        else if (inptBuffer[0] == 'f' && inptBuffer[1] == ' ')
        {
            char *first = strchr(inptBuffer, ' ');
            char *second = strchr(first+1, ' ');
            char *third = strchr(second+1, ' ');

            //printf("%lx %lx %lx\n",first,second,third);
            sscanf(first, "%d", &out->faces[faceIndex].x);
            sscanf(second, "%d", &out->faces[faceIndex].y);
            sscanf(third, "%d", &out->faces[faceIndex].z);
            out->faces[faceIndex].x-=1;
            out->faces[faceIndex].y-=1;
            out->faces[faceIndex].z-=1;

            //printf("f %d %d %d\n", out->faces[faceIndex].x, out->faces[faceIndex].y, out->faces[faceIndex].z);
            faceIndex += 1;
        }

        lines += 1;
    }

    return (out);
}