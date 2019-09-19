//////////////////////////////////////////////////////////////////////////////
// point3d.h
//////////////////////////////////////////////////////////////////////////////
// The interface for 3D points, rays, and assorted math functions
// ... ideas borrowed from C++ class Point3D from CS488
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "point3d.h"


// CONSTANTS
const double NEARZERO = 0.000001;


// FUNCTION IMPLEMENTATIONS

// print_Point3D(p) prints Point3D p on the screen.
// Parameters: p is a Point3D
//
// effects:   data is printed on the screen
void print_Point3D(struct Point3D p) {
    printf("[%f, %f, %f]\n", p.x, p.y, p.z);
}



// normalize(p) normalizes the "vector" p.  If p's magnitude is <= EPSILON,
// we assume p has length 0 and the vector is NOT normalized.
// Parameters: p is the vector to normalize
//
// requires:   p != NULL       
// effects:    modifies p
void normalize(struct Point3D *p) {
    assert(p != NULL);

    double d = dot(*p, *p);
    d = sqrt(d);

    if (d > NEARZERO) {
        p->x /= d;
        p->y /= d;
        p->z /= d;
    } else {
        p->x = 0;
        p->y = 0;
        p->z = 0;
    }
}



// add(a, b) adds b to a.
// Parameters: a is the point to add to
//             b is the point to add
//
// requires:   a != NULL
// effects:    modifies a
void add(struct Point3D *a, struct Point3D b) {
    assert(a != NULL);

    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}



// sub(a, b) subtracts b from a.
// Parameters: a is the point to subtract from
//             b is the point to subtract
//
// requires:   a != NULL
// effects:    modifies a
void sub(struct Point3D *a, struct Point3D b) {
    assert(a != NULL);

    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}



// dot(a, b) computes and returns the dot product of a and b.
// Parameters: a and b are vectors
double dot(struct Point3D a, struct Point3D b) {
    double d = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

    return d;
}



// scalar(a, s) multiplies point a by scalar s.
// Parameters: a is the point
//             s is the scalar
//
// requires:   a != NULL
// effects:    modifies a
void scalar(struct Point3D *a, double s) {
    assert(a != NULL);
    a->x *= s;
    a->y *= s;
    a->z *= s;
}


// distance(a, b) computes and returns the distance between a and b.
// Parameters: a is the first point
//             b is the second point
double distance(struct Point3D a, struct Point3D b) {
    double x = a.x - b.x;
    double y = a.y - b.y;
    double z = a.z - b.z;

    double dist = sqrt((x * x) + (y * y) + (z * z));
    return dist;
}


// reflect(v, n, reflected) given velocity (direction) vector and surface normal, 
// computes the reflected vector.
// Parameters: v is the velocity/direction
//             n is the surface normal at the point of interseciton
//             reflected is the direction after bouncing
//
// requires:   reflected != NULL
// effects:    modifies reflected
void reflect(struct Point3D v, struct Point3D n, struct Point3D *reflected) {
    assert(reflected != NULL);
    double n_dot_v = 2 * dot(n, v);

    // bounce dir = v DOT n
    struct Point3D r = {n_dot_v * n.x - v.x,
                        n_dot_v * n.y - v.y,
                        n_dot_v * n.z - v.z};

    // normalize reflected
    normalize(&r);

    *reflected = r;
}



// is_bounce(bounce) returns true if any of the fields of bounce are true.
// Which implies that at the sphere intersected at least ONE wall.
// Parameters: bounce is the wall intersection indicator
bool is_bounce(struct Bounce bounce) {
    if (!(bounce.top || bounce.bottom || bounce.front ||
          bounce.left || bounce.right || bounce.back)) {
        return false;
    }

    return true;
}



// print_bounce(b) prints bounce b on the screen.
// Parameters: b is a bounce struct
//
// effects:   data is printed on the screen
void print_bounce(struct Bounce b) {
    printf("Bounce - top(%d), bottom(%d)\n", b.top, b.bottom);
    printf("         front(%d), back(%d)\n", b.front, b.back);
    printf("         left(%d), right(%d)\n", b.left, b.right);
}


