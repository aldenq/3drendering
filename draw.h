#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "vectors.h"
#include "render.h"

#define DRAW_WIDTH 500
#define DRAW_HEIGHT 500
#define PIXEL_WIDTH DRAW_WIDTH/RENDER_WIDTH
#define PIXEL_HEIGHT DRAW_HEIGHT/RENDER_HEIGHT
extern SDL_Window *win;
extern SDL_Renderer *rdr;
extern Vect3c pixelBuffer[DRAW_WIDTH][DRAW_HEIGHT];

void setupDraw();
void drawBuffer();







