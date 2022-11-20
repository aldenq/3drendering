#include "render.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

float ZBuffer[RENDER_WIDTH][RENDER_HEIGHT];
int indices[] = {0,3,6,9,12,15,18,21};
Vect3f globalVerts[maxVerts];
int numGlobalVerts = 0;
Vect3i faces[maxFaces];
int numFaces = 0;

Vect3i clippedFaces[maxFaces];
int numClippedFaces = 0;
Vect3f viewVerts[maxVerts];

Vect3f cameraPos;
Vect3f cameraRot;

void setupCamera()
{
    cameraPos.x = 0;
    cameraPos.y = 0;
    cameraPos.z = 0;
    cameraRot.x = 0;
    cameraRot.y = 0;
    cameraRot.z = 0;
}

Vect3f rotate2D(float x, float y, float r)
{
    Vect3f output = {.x = x * cos(r) - y * sin(r), .y = x * sin(r) + y * cos(r), .z = 0};
    return (output);
}   





Vect3f rotateVert(Vect3f vert, Vect3f rotation)
{

    Vect3f rotateX = rotate2D(vert.y, vert.z, rotation.x);
    //Vect3f output = {.y = y * cos(rx) - z * sin(rx), .z = y * sin(rx) + z * cos(rx), .z = 0};
    
    rotateX.z = rotateX.y;
    rotateX.y = rotateX.x;
    rotateX.x = vert.x;
    
    Vect3f rotateY = rotate2D(rotateX.z, rotateX.x, rotation.y);
    //Vect3f output = {.z = z * cos(ry) - x * sin(ry), .x = z * sin(ry) + x * cos(ry), .z = 0};
    rotateY.z = rotateY.x;
    rotateY.x = rotateY.y;
    rotateY.y = rotateX.y;
    Vect3f rotateZ = rotate2D(rotateY.x, rotateY.y, rotation.z);
    //Vect3f output = {.x = x * cos(rz) - y * sin(rz), .y = x * sin(rz) + y * cos(rz), .z = 0};

    rotateZ.z = rotateY.z;
    // printf("vect0 %.6f,%.6f,%.6f\n", vert.x,vert.y,vert.z);
    // printf("vect1 %.6f,%.6f,%.6f\n", rotateZ.x,rotateZ.y,rotateZ.z);

    return rotateZ;
}

void clipFaces(){
    for (int i =0; i < numFaces; i++){
        Vect3f view_p1 = viewVerts[faces[i].x];
        Vect3f view_p2 = viewVerts[faces[i].y];
        Vect3f view_p3 = viewVerts[faces[i].z];

        if (view_p1.z > 0 && view_p2.z > 0 && view_p3.z > 0){
            clippedFaces[numClippedFaces] = faces[i];
            numClippedFaces +=1;
        }
    }
}


Vect3f transformVert(Vect3f vert)
{

    vert.x -= cameraPos.x;
    vert.y -= cameraPos.y;
    vert.z -= cameraPos.z;

    Vect3f inverseCamera = (Vect3f){.x = cameraRot.x * -1, .y = cameraRot.y * -1, .z = cameraRot.z * -1};
    vert = rotateVert(vert, inverseCamera);
    return (vert);
}

void transformVerts()
{
    Vect3f rot_sin = {.x=sin(-cameraRot.x),.y=sin(-cameraRot.y),.z=sin(-cameraRot.z)};
    Vect3f rot_cos = {.x=cos(-cameraRot.x ),.y=cos(-cameraRot.y),.z=cos(-cameraRot.z)};
    // for (int i = 0; i < numGlobalVerts; i+=8)
    // {
    asm_transformVerts(globalVerts,numGlobalVerts,&rot_sin,&rot_cos,viewVerts,&cameraPos);
        //viewVerts[i] = transformVert(globalVerts[i]);
    // }
}

void transformVerts2()
{
    Vect3f rot_sin = {.x=sin(-cameraRot.x),.y=sin(-cameraRot.y),.z=sin(-cameraRot.z)};
    Vect3f rot_cos = {.x=cos(-cameraRot.x ),.y=cos(-cameraRot.y),.z=cos(-cameraRot.z)};
    for (int i = 0; i < numGlobalVerts; i+=1)
    {
        //asm_transformVerts(globalVerts+i,0,&rot_sin,&rot_cos,viewVerts+i,&cameraPos);
        viewVerts[i] = transformVert(globalVerts[i]);
    }
}

Vect3i getScreenSpace(Vect3f point)
{
    Vect3i output;
    float virtSlope = point.y / point.z;
    float horSlope = point.x / point.z;
    output.x = horSlope * FOV;
    output.y = virtSlope * FOV;
    output.z = FOV;
    return (output);
}

int minInt(int a, int b, int c)
{
    int t = (a < b) ? a : b;
    return (t < c) ? t : c;
}

int maxInt(int a, int b, int c)
{
    int t = (a > b) ? a : b;
    return (t > c) ? t : c;
}

float computeDepth(int face, Vect3i pixel)
{

    Vect3f view_p1 = viewVerts[clippedFaces[face].x];
    Vect3f view_p2 = viewVerts[clippedFaces[face].y];
    Vect3f view_p3 = viewVerts[clippedFaces[face].z];

    Vect3f vect;
    vect.x = pixel.x / (float)FOV;
    vect.y = pixel.y / (float)FOV;
    vect.z = 1;

    float out = pow(((pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2)) * pow(view_p3.x * view_p2.y * view_p1.z - view_p2.x * view_p3.y * view_p1.z - view_p3.x * view_p1.y * view_p2.z + view_p1.x * view_p3.y * view_p2.z + view_p2.x * view_p1.y * view_p3.z - view_p1.x * view_p2.y * view_p3.z, 2)) /
                        pow(-(view_p1.x * view_p2.y * vect.z) + view_p1.x * view_p3.y * vect.z + vect.x * view_p2.y * view_p1.z - vect.x * view_p3.y * view_p1.z + view_p1.x * vect.y * view_p2.z - vect.x * view_p1.y * view_p2.z + vect.x * view_p3.y * view_p2.z + view_p3.x * (-(view_p1.y * vect.z) + view_p2.y * vect.z + vect.y * view_p1.z - vect.y * view_p2.z) - view_p1.x * vect.y * view_p3.z +
                                vect.x * view_p1.y * view_p3.z - vect.x * view_p2.y * view_p3.z + view_p2.x * (view_p1.y * vect.z - view_p3.y * vect.z - vect.y * view_p1.z + vect.y * view_p3.z),
                            2),
                    0.5);

    return out;
    // Vect3f side1;
    // side1.x = view_p2.x - view_p1.x;
    // side1.y = view_p2.y - view_p1.z;
    // side1.z = view_p2.z - view_p1.z;

    // Vect3f side2;
    // side1.x = view_p2.x - view_p1.x;
    // side1.y = view_p2.y - view_p1.z;
    // side1.z = view_p2.z - view_p1.z;

    // Vect3f normal;
    // normal.x = (side1.y*side2.z - side1.z*side2.y);
    // normal.y = (side1.x*side2.z - side1.z*side2.x);
    // normal.z = (side1.x*side2.y - side1.y*side2.x);
}

int hit(Vect3i p1, Vect3i p2, Vect3i p3, Vect3i tp)
{
    float out = abs(p1.y * p2.x - p1.x * p2.y - p1.y * p3.x + p2.y * p3.x + p1.x * p3.y - p2.x * p3.y) - abs(p1.y * p2.x - p1.x * p2.y - p1.y * tp.x + p2.y * tp.x + p1.x * tp.y - p2.x * tp.y) -
                abs(p1.y * p3.x - p1.x * p3.y - p1.y * tp.x + p3.y * tp.x + p1.x * tp.y - p3.x * tp.y) - abs(p2.y * p3.x - p2.x * p3.y - p2.y * tp.x + p3.y * tp.x + p2.x * tp.y - p3.x * tp.y);
    // printf("%9.6f   %i\n",out,(int)(abs(out) < .000001));
    return (int)(abs(out) < .000001);
}

int clamp(int val, int min, int max)
{
    val = (val > min) ? val : min;
    val = (val < max) ? val : max;
    return val;
}

Vect3i clampScreen(Vect3i pixel)
{
    pixel.x = clamp(pixel.x, -RENDER_WIDTH / 2, RENDER_WIDTH / 2);
    pixel.y = clamp(pixel.y, -RENDER_HEIGHT / 2, RENDER_HEIGHT / 2);
    return pixel;
}
void depthSort()
{
    for (int i = 0; i < numClippedFaces; i++)
    {
        Vect3f view_p1 = viewVerts[clippedFaces[i].x];
        Vect3f view_p2 = viewVerts[clippedFaces[i].y];
        Vect3f view_p3 = viewVerts[clippedFaces[i].z];

        Vect3i screen_p1 = getScreenSpace(view_p1);
        Vect3i screen_p2 = getScreenSpace(view_p2);
        Vect3i screen_p3 = getScreenSpace(view_p3);

        // printf("p1 %i %i %i\n",screen_p1.x,screen_p1.y,screen_p1.z);
        // printf("p2 %i %i %i\n",screen_p2.x,screen_p2.y,screen_p2.z);
        // printf("p3 %i %i %i\n",screen_p3.x,screen_p3.y,screen_p3.z);
        Vect3i TLbound;
        TLbound.x = minInt(screen_p1.x, screen_p2.x, screen_p3.x);
        TLbound.y = minInt(screen_p1.y, screen_p2.y, screen_p3.y);
        TLbound = clampScreen(TLbound);
        Vect3i BRbound;
        BRbound.x = maxInt(screen_p1.x, screen_p2.x, screen_p3.x);
        BRbound.y = maxInt(screen_p1.y, screen_p2.y, screen_p3.y);
        BRbound = clampScreen(BRbound);

        Vect3i currentPixel;
        for (int x = TLbound.x; x <= BRbound.x; x++)
        {
            for (int y = TLbound.y; y <= BRbound.y; y++)
            {
                currentPixel.x = x;
                currentPixel.y = y;

                int indexX = x + RENDER_WIDTH / 2;
                int indexY = y + RENDER_HEIGHT / 2;
                // printf("p1 %i %i %i\n",screen_p1.x,screen_p1.y,screen_p1.z);
                // printf("p2 %i %i %i\n",screen_p2.x,screen_p2.y,screen_p2.z);
                // printf("p3 %i %i %i\n",screen_p3.x,screen_p3.y,screen_p3.z);
                // ZBuffer[indexX][indexY] = 100;

                if (indexX > 0 && indexX < RENDER_WIDTH && indexY > 0 && indexY < RENDER_HEIGHT)
                {
                    if (hit(screen_p1, screen_p2, screen_p3, currentPixel))
                    {

                        float depth = computeDepth(i, currentPixel);
                        if (depth < ZBuffer[indexX][indexY] || ZBuffer[indexX][indexY] == 0)
                        {
                            ZBuffer[indexX][indexY] = depth;
                            // printf("%9.6f \n",depth);
                        }
                        // printf("p %i %i\n",indexX,indexY);
                        // ZBuffer[indexX][indexY] = 255;
                    }
                }
            }
        }
    }
}

void clearZbuffer()
{
    for (int x = 0; x < RENDER_WIDTH; x++)
    {
        for (int y = 0; y < RENDER_HEIGHT; y++)
        {
            ZBuffer[x][y] = 0;
        }
    }
}
void addViewTriangle(Vect3f p1, Vect3f p2, Vect3f p3) // for debug only
{
    Vect3i newTriangle;
    int base = numGlobalVerts;
    viewVerts[numGlobalVerts] = p1;
    viewVerts[numGlobalVerts + 1] = p2;
    viewVerts[numGlobalVerts + 2] = p3;
    newTriangle.x = base;
    newTriangle.y = base + 1;
    newTriangle.z = base + 2;

    numGlobalVerts += 3;
    faces[numFaces] = newTriangle;
    numFaces += 1;
}

void addGlobalTriangle(Vect3f p1, Vect3f p2, Vect3f p3) // for debug only
{
    Vect3i newTriangle;
    int base = numGlobalVerts;
    globalVerts[numGlobalVerts] = p1;
    globalVerts[numGlobalVerts + 1] = p2;
    globalVerts[numGlobalVerts + 2] = p3;
    newTriangle.x = base;
    newTriangle.y = base + 1;
    newTriangle.z = base + 2;

    numGlobalVerts += 3;
    faces[numFaces] = newTriangle;
    numFaces += 1;
}

void clearAll()
{
    numFaces = 0;
    numGlobalVerts = 0;
    numClippedFaces=0;
    clearZbuffer();
}

void render()
{
    transformVerts();
    clipFaces();
    depthSort();
}
void pushVertex(Vect3f vertex){
    globalVerts[numGlobalVerts] = vertex;
    numGlobalVerts+=1;
}

void pushFace(Vect3i face){
    faces[numFaces] = face;
    numFaces+=1;
}

void loadVertexBuffer(VertexBuffer* vbuffer){
    int vertexOffset = numGlobalVerts;
    for(int i =0; i< vbuffer->numVerts; i++){
        Vect3f vert = vbuffer->verts[i];
        vert = rotateVert(vert,vbuffer->rotation);
        vert.x = vert.x + vbuffer->position.x;
        vert.y = vert.y + vbuffer->position.y;
        vert.z = vert.z + vbuffer->position.z;
        pushVertex(vert);
    }

    for(int i =0; i< vbuffer->numFace; i++){
        Vect3i face = vbuffer->faces[i];
        face.x = face.x + vertexOffset;
        face.y = face.y + vertexOffset;
        face.z = face.z + vertexOffset;
        pushFace(face);
    }

    




}
