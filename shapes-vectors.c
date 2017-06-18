#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shapes-vectors.h"

Coord3D newCoord3D(double x, double y, double z)
{

    Coord3D coord3D;

    coord3D.x = x;
    coord3D.y = y;
    coord3D.z = z;

    return coord3D;

}

Coord2D newCoord2D(double x, double y)
{

    Coord2D coord2D;

    coord2D.x = x;
    coord2D.y = y;

    return coord2D;

}

Shape3D newShape3D(int verticesNumb)
{

    int i;
    Shape3D shape3D;

    shape3D.verticesNumb = verticesNumb;

    shape3D.edges = (int**) malloc(verticesNumb * sizeof(int*));
    for (i = 0; i < verticesNumb; ++i)
    {

        shape3D.edges[i] = (int*) calloc(verticesNumb, sizeof(int));

    }

    shape3D.vertices = (Coord3D*) malloc(verticesNumb * sizeof(Coord3D));
    for (i = 0; i < verticesNumb; ++i)
    {

        shape3D.vertices[i] = newCoord3D(0, 0, 0);

    }

    return shape3D;

}

Shape2D newShape2D(int verticesNumb)
{

    int i;
    Shape2D shape2D;

    shape2D.verticesNumb = verticesNumb;

    shape2D.edges = (int**) malloc(verticesNumb * sizeof(int*));
    for (i = 0; i < verticesNumb; ++i)
    {

        shape2D.edges[i] = (int*) calloc(verticesNumb, sizeof(int));

    }

    shape2D.vertices = (Coord2D*) malloc(verticesNumb * sizeof(Coord2D));
    for (i = 0; i < verticesNumb; ++i)
    {

        shape2D.vertices[i] = newCoord2D(0, 0);

    }

    return shape2D;

}

void freeShape2D(Shape2D *s)
{

    int i;

    for (i = 0; i < s->verticesNumb; ++i)
    {
        free(s->edges[i]);
    }
    if (s->verticesNumb > 0)
    {
        free(s->edges);
        free(s->vertices);
    }

}
void freeShape3D(Shape3D *s)
{

    int i;

    for (i = 0; i < s->verticesNumb; ++i)
    {
        free(s->edges[i]);
    }
    if (s->verticesNumb > 0)
    {
        free(s->edges);
        free(s->vertices);
    }

}

void shape2DSetverticesNumb(Shape2D *s, int n)
{
    freeShape2D(s);
    *s = newShape2D(n);
}

double dotProduct(Coord3D vector1, Coord3D vector2)
{

    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);

}

Coord3D crossProduct(Coord3D vector1, Coord3D vector2)
{

    double x, y, z;

    x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

    return newCoord3D(x, y, z);

}

Coord3D scalarMultiplication(Coord3D vector, double scalar)
{

    return newCoord3D(vector.x * scalar, vector.y * scalar, vector.z * scalar);

}

Coord3D vector3DSubtract(Coord3D v1, Coord3D v2)
{

    return newCoord3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);

}

Coord3D vector3DSum(Coord3D v1, Coord3D v2)
{

    return newCoord3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);

}

Coord3D normalizeVector(Coord3D v)
{

    double norm = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
    return newCoord3D(v.x/norm, v.y/norm, v.z/norm);

}
