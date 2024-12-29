#include <iostream>
#include <cmath>
#include "SDL2/SDL.h"
#undef main

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000

using namespace std;

struct Circle
{
    double x;
    double y;
    double r;
};

void FillCircle(SDL_Surface *surface, Circle circle, Uint32 color)
{
    double radius_squared = pow(circle.r, 2);
    for (double x = circle.x - circle.r; x <= circle.x + circle.r; x++)
    {
        for (double y = circle.y - circle.r; y <= circle.y + circle.r; y++)
        {
            double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if (distance_squared < radius_squared)
            {

                SDL_Rect pixel = {static_cast<int>(round(x)), static_cast<int>(round(y)), 1, 1};

                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    Circle circle = {200, 200, 80};
    Circle shadow_circle = {650, 300, 140};
    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};
    int simulation_running = 1;
    SDL_Event event;
    while (simulation_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                simulation_running = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
            }
        }
        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface, circle, COLOR_WHITE);
        FillCircle(surface, shadow_circle, COLOR_WHITE);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
}