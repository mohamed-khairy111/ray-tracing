#include <iostream>
#include <cmath>
#include "SDL2/SDL.h"
#undef main

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_RAY 0xfcba03
#define M_PI 3.14159265358979323846
#define RAYS_NUMBER 100

using namespace std;

struct Circle
{
    double x;
    double y;
    double r;
};

struct Ray
{
    double x_start, y_start;
    double angle;
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
void generate_Rays(Circle circle, Ray rays[RAYS_NUMBER])
{
    for (int i = 0; i < RAYS_NUMBER; i++)
    {
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
    }
}

void FillRays(SDL_Surface *surface, Ray rays[RAYS_NUMBER], Uint32 color, Circle circle)
{
    double radius_squared = pow(circle.r, 2);
    for (int i = 0; i < RAYS_NUMBER; i++)
    {
        Ray ray = rays[i];

        int end_of_screen = 0;
        int object_hit = 0;
        int step = 1;
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;
        while (!end_of_screen && !object_hit)
        {

            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);
            SDL_Rect pixel = {static_cast<int>(round(x_draw)), static_cast<int>(round(y_draw)), 3, 3};
            SDL_FillRect(surface, &pixel, color);
            if (x_draw < 0 || x_draw > WIDTH)
                end_of_screen = 1;
            if (y_draw < 0 || y_draw > HEIGHT)
                end_of_screen = 1;

            double distance_squared = pow(x_draw - circle.x, 2) + pow(y_draw - circle.y, 2);
            if (distance_squared < radius_squared)
            {
                break;
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
    Ray rays[RAYS_NUMBER];
    generate_Rays(circle, rays);
    double obstacel_speed_y = 1;
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
                generate_Rays(circle, rays);
            }
        }
        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface, circle, COLOR_WHITE);
        FillCircle(surface, shadow_circle, COLOR_WHITE);
        FillRays(surface, rays, COLOR_RAY, shadow_circle);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
}