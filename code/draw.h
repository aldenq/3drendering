/**
 * @file draw.h
 * @author Alden Quigley (aldenaquigley@gmail.com)
 * @brief responsible for all the 2d side of 3d rendering
 * @version 0.1
 * @date 2022-12-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "vectors.h"
#include "render.h"

#define DRAW_WIDTH RENDER_WIDTH
#define DRAW_HEIGHT RENDER_HEIGHT
#define PIXEL_WIDTH DRAW_WIDTH/RENDER_WIDTH
#define PIXEL_HEIGHT DRAW_HEIGHT/RENDER_HEIGHT
extern SDL_Window *win;
extern SDL_Renderer *rdr;
//buffer that is actually displayed
extern Vect3c pixelBuffer[DRAW_WIDTH][DRAW_HEIGHT];

/**
 * @brief sets up window and pixelbuffer
 * 
 */
void setupDraw();
/**
 * @brief sets the pixels in the pixelbuffer according to 3d data
 * 
 */
void drawBuffer();







