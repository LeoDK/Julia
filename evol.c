#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "complex.h"

void function (Complex *z, Complex *c)
{
    cplxPow(z, 2, z);
    addCplx(z, c, z);
}

int calcPoint (Complex *z, Complex *c, unsigned int limit)
{
    int n=0;
    while (z->mod <= 2 && n < limit-1)
    {
        function(z, c); 
        n++;
    }
    return n;
}

void calcSet ( float x1, float y1, float x2, float y2, 
                unsigned int width, unsigned int height, Complex *c,
                unsigned int limit,
                unsigned int *buf)
{
    float prec_x = (float) abs(x1-x2);
    float prec_y = (float) abs(y1-y2);
    prec_x /= width;
    prec_y /= height;

    Complex *z = __new__Complex(0.0, 0.0);
    int x;
    int y;
    for (x=0; x<width; x++)
    {
        for (y=0; y<height; y++)
        {
            addCplx2(z, x1 + x*prec_x, y1 + y*prec_y, z); // Point coordinates
            *(buf + x*height + y) = calcPoint(z, c, limit);
            zero(z);
        }
    }
}
 

void plotSet (  unsigned int *set, unsigned int width, unsigned int height,
                unsigned int limit, SDL_Surface *screen )
{
    int colors[limit][3];
    int i;
    for (i=0; i<limit; i++)
    {
        colors[i][0] = 255*i/limit;
        colors[i][1] = 150*i/limit;
        colors[i][2] = 10*i/limit;
    }

    SDL_Rect pos;
    SDL_Surface *point = NULL;
    point = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);

    int x;
    int y;
    for (x=0; x<width; x++)
    {
        for (y=0; y<height; y++)
        {
            int *color = colors[*((set + x*(height)) + y)];
            pos.x = x;
            pos.y = height-y;
            SDL_FillRect(point, NULL, SDL_MapRGB(screen->format, color[0], color[1], color[2]));
            SDL_BlitSurface(point, NULL, screen, &pos);
        }
    }

    SDL_FreeSurface(point);
    SDL_Flip(screen);
}

int main (int argc, char **argv)
{
    if (argc != 10)
    {
        printf("Usage : ./evol x1 y1 x2 y2 Re(c) Im(c) width height limit\n");
        return 0;
    }

    float x1 = strtof(argv[1], NULL);
    float y1 = strtof(argv[2], NULL);
    float x2 = strtof(argv[3], NULL);
    float y2 = strtof(argv[4], NULL);
    Complex *c = __new__Complex(strtof(argv[5],NULL), strtof(argv[6],NULL));
    unsigned int width = strtol(argv[7], NULL, 10);
    unsigned int height = strtol(argv[8], NULL, 10);
    unsigned int limit = strtol(argv[9], NULL, 10);

    SDL_Surface *screen;
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        printf("Error with SDL.\n");
        exit(EXIT_FAILURE);
    }
    screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
    SDL_Event event;
 
    unsigned int set[width][height];
    int i;
    for(i=2; i<=limit; i++)
    {
        calcSet(x1, y1, x2, y2, width, height, c, i, &set[0][0]);
        plotSet(&set[0][0], width, height, i, screen);
        SDL_Delay(50);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                i=limit;
            }
        }
    }

    SDL_Quit();
    free(c);

    return 0;
}
