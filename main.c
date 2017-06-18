#include <stdio.h>
#include <stdlib.h>
#include "shapes-vectors.h"
#include <SDL2/SDL.h>


#define SCALE 50
#define DISPLACEMENT 250
#define WINDOW_H 500
#define WINDOW_W 500
#define WINDOW_X 500
#define WINDOW_Y 500


const double ROTATION_ANGLE = 0.05;


void rotate(Shape3D *obj, Coord3D custom, double angulo);
void projectOn3DPlane(Shape3D shape3D, Shape2D *shape2D, Coord3D xAxis, Coord3D yAxis);
Shape3D generateCube();
void startSDL(SDL_Window **w, SDL_Renderer **r);
void quitSDL(SDL_Window **w, SDL_Renderer **r);

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int i, j, x1, y1, x2, y2, quit = 0;
    Coord3D xAxis, yAxis, mouseMotion;
    Shape2D cubeProj;
    Shape3D cube;


    startSDL(&window, &renderer);
    yAxis = newCoord3D(1, 0, 0);
    xAxis = newCoord3D(0, 1,0);
    cube = generateCube();
    cubeProj = newShape2D(0);


    projectOn3DPlane(cube, &cubeProj, xAxis, yAxis);


    while(!quit)
    {
        //Limpa tela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//preto
        SDL_RenderClear(renderer);

        //Desenha linhas do cubeProj
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//branco
        for(i = 0; i < cubeProj.verticesNumb; ++i)
        {
            for (j = 0; j < cubeProj.verticesNumb; ++j)
            {
                if (cubeProj.edges[i][j] == 1)
                {
                    x1 = round(cubeProj.vertices[i].x * SCALE);
                    y1 = round(cubeProj.vertices[i].y * SCALE);
                    x2 = round(cubeProj.vertices[j].x * SCALE);
                    y2 = round(cubeProj.vertices[j].y * SCALE);

                    y1 *= -1;
                    y2 *= -1;

                    x1 += DISPLACEMENT;
                    y1 += DISPLACEMENT;
                    x2 += DISPLACEMENT;
                    y2 += DISPLACEMENT;


                    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
                }
            }
        }

        //Trata eventos
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                if (event.motion.state == SDL_BUTTON_LMASK)
                {
                    mouseMotion = newCoord3D(event.motion.xrel,event.motion.yrel,0);
                    mouseMotion = normalizeVector(mouseMotion);
                    rotate(&cube, mouseMotion, ROTATION_ANGLE);
                    projectOn3DPlane(cube, &cubeProj, xAxis, yAxis);

                }
                break;

            case SDL_QUIT:
                quit = 1;
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    quit = 1;
                }
                break;

            default:
                break;
            }
        }
    }

    quitSDL(&window, &renderer);
    freeShape2D(&cubeProj);
    freeShape3D(&cube);

    return 0;
}

void projectOn3DPlane(Shape3D shape3D, Shape2D *shape2D, Coord3D xAxis, Coord3D yAxis)
{
    int i, j;


    shape2DSetverticesNumb(shape2D, shape3D.verticesNumb);
    yAxis = normalizeVector(yAxis);
    xAxis = normalizeVector(xAxis);

    for (i = 0; i < shape3D.verticesNumb; ++i)
    {
        shape2D->vertices[i].x = dotProduct(shape3D.vertices[i], xAxis);
        shape2D->vertices[i].y = dotProduct(shape3D.vertices[i], yAxis);

        shape2D->vertices[i].x = dotProduct(shape3D.vertices[i], xAxis);
        shape2D->vertices[i].y = dotProduct(shape3D.vertices[i], yAxis);

        for (j = 0; j < shape3D.verticesNumb; ++j)
        {
            shape2D->edges[i][j] = shape3D.edges[i][j];
        }
    }
}

void rotate(Shape3D *obj, Coord3D axis, double angle)
{
    int i;

    double dao,can;
    Coord3D cao, soc, scs, sad, css, ssc;

    axis = scalarMultiplication(axis,-1);
    axis = normalizeVector(axis);

    for(i = 0; i < obj->verticesNumb; ++i)
    {
        /* Variáveis auxiliares para reduzir comprimento
           da linha onde é feita operação de rotação */
        can = 1 - cos(angle);
        soc = scalarMultiplication(obj->vertices[i], cos(angle));
        cao = crossProduct(axis, obj->vertices[i]);
        scs = scalarMultiplication(cao, sin(angle));
        css = vector3DSum(soc,scs);
        dao = dotProduct(axis, obj->vertices[i]);
        sad = scalarMultiplication(axis,dao);
        ssc = scalarMultiplication(sad,can);

        obj->vertices[i] = vector3DSum(css, ssc);//Operação de rotação
    }
}

void startSDL(SDL_Window **w, SDL_Renderer **r)
{
    SDL_Init(SDL_INIT_VIDEO);
    *w = SDL_CreateWindow("3DTo2D", WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    *r = SDL_CreateRenderer(*w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void quitSDL(SDL_Window **w, SDL_Renderer **r)
{
    SDL_DestroyRenderer(*r);
    SDL_DestroyWindow (*w);
    SDL_Quit();
}

Shape3D generateCube()
{
    int i;
    Shape3D cube = newShape3D(8);


    cube.vertices[0] = newCoord3D(0, 0, 0);
    cube.vertices[1] = newCoord3D(1, 0, 0);
    cube.vertices[2] = newCoord3D(1, 1, 0);
    cube.vertices[3] = newCoord3D(0, 1, 0);
    cube.vertices[4] = newCoord3D(0, 0, 1);
    cube.vertices[5] = newCoord3D(1, 0, 1);
    cube.vertices[6] = newCoord3D(1, 1, 1);
    cube.vertices[7] = newCoord3D(0, 1, 1);

    cube.edges[0][1] = 1;
    cube.edges[1][2] = 1;
    cube.edges[2][3] = 1;
    cube.edges[3][0] = 1;
    cube.edges[4][5] = 1;
    cube.edges[5][6] = 1;
    cube.edges[7][6] = 1;
    cube.edges[4][7] = 1;
    cube.edges[5][1] = 1;
    cube.edges[6][2] = 1;
    cube.edges[7][3] = 1;
    cube.edges[4][0] = 1;

    for(i = 0; i < cube.verticesNumb; ++i)
    {
        cube.vertices[i].x -= 0.5;
        cube.vertices[i].y -= 0.5;
        cube.vertices[i].z -= 0.5;
    }

    return cube;
}
