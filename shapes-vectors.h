typedef struct coord3D {

    double x, y, z;

} Coord3D;

typedef struct coord2D {

    double x, y;

} Coord2D;

typedef struct shape3D {

    int verticesNumb, **edges;
    Coord3D *vertices;

} Shape3D;

typedef struct shape2D {

    int verticesNumb, **edges;
    Coord2D *vertices;

} Shape2D;

Coord3D newCoord3D(double x, double y, double z);
Coord2D newCoord2D(double x, double y);
Shape3D newShape3D(int verticesNumb);
Shape2D newShape2D(int verticesNumb);

void freeShape2D(Shape2D *s);
void freeShape3D(Shape3D *s);

double dotProduct(Coord3D vector1, Coord3D vector2);
Coord3D crossProduct(Coord3D vector1, Coord3D vector2);
Coord3D scalarMultiplication(Coord3D vector, double scalar);
Coord3D vector3DSubtract(Coord3D v1, Coord3D v2);
Coord3D vector3DSum(Coord3D v1, Coord3D v2);
Coord3D normalizeVector(Coord3D v);
void shape2DSetverticesNumb(Shape2D *s, int n);
