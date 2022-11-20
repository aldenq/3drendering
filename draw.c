#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "vectors.h"
#include "render.h"

SDL_Window *win;
SDL_Renderer *rdr;
Vect3c pixelBuffer[DRAW_WIDTH][DRAW_HEIGHT];

void setupDraw()
{

    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Rect", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DRAW_WIDTH, DRAW_HEIGHT, 0);
    rdr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void drawBuffer()
{
    SDL_Rect drawRect;
    drawRect.h = DRAW_HEIGHT / RENDER_HEIGHT;
    drawRect.w = DRAW_WIDTH / RENDER_WIDTH;

    for (int x = 0; x < RENDER_WIDTH; x++)
    {
        for (int y = 0; y < RENDER_HEIGHT; y++)
        {
            // SDL_RenderClear(rdr);

            int dist = 255 - ZBuffer[x][y]*25;
            int color = dist;

            if (dist >= 255 || dist<0)
            {
                color = 0;
            }

            pixelBuffer[x][y].x = color;
            pixelBuffer[x][y].y = color;
            pixelBuffer[x][y].z = color;
            // SDL_SetRenderDrawColor(rdr,color,color,color,255);

            // drawRect.x = drawRect.w*x;
            // drawRect.y = drawRect.h*y;
            // SDL_RenderFillRect(rdr,&drawRect);
        }
    }

    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void *)pixelBuffer,
                                                    RENDER_WIDTH,
                                                    RENDER_HEIGHT,
                                                    3 * 8,            // bits per pixel = 24
                                                    RENDER_WIDTH * 3, // pitch
                                                    0x0000FF,         // red mask
                                                    0x00FF00,         // green mask
                                                    0xFF0000,         // blue mask
                                                    0);               // alpha mask (none)


    SDL_Texture* texture = SDL_CreateTextureFromSurface(rdr,surface);
    SDL_Rect dstrect;
    dstrect.x = (RENDER_WIDTH - RENDER_HEIGHT) / 2 - 1;
    dstrect.y = (RENDER_HEIGHT - RENDER_WIDTH) / 2;
    dstrect.w = RENDER_HEIGHT;
    dstrect.h = RENDER_WIDTH;
    SDL_RenderCopyEx(rdr, texture, NULL, &dstrect, 90, NULL, SDL_FLIP_NONE);
    SDL_Surface *screen = SDL_GetWindowSurface(win);
    // SDL_BlitSurface(surface, NULL, screen, NULL);
    SDL_FreeSurface(surface);
    // SDL_UpdateWindowSurface(win);
    
    SDL_RenderPresent(rdr);
    SDL_DestroyTexture(texture);
}