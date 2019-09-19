//////////////////////////////////////////////////////////////////////////////
// point3d.h
//////////////////////////////////////////////////////////////////////////////
// The interface for 3D points, rays, and assorted math functions
// ... ideas borrowed from C++ class Point3D from CS488
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////
#ifndef __POINT3D_H__
#define __POINT3D_H__


// INCLUDES
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


// STRUCTURES
// struct Point3D is used to store a 3D point with (x,y,z) coordinates
struct Point3D {
    double x;
    double y;
    double z;
};

// struct Ray is a line that has an origin and a direction of travel
struct Ray {
    struct Point3D origin;
    struct Point3D direction;   
};


// struct Bounce is used to store which of the six walls of a cube
// the sphere intersects.  Each wall is a bool and is false if there
// is no intersection.
struct Bounce {
    bool top;
    bool bottom;
    bool front;
    bool back;
    bool left;
    bool right;
};


// FUNCTION INTERFACES

// normalize(p) normalizes the "vector" p.  If p's magnitude is <= EPSILON,
// we assume p has length 0 and the vector is NOT normalized.
// Parameters: p is the vector to normalize
//
// requires:   p != NULL       
// effects:    modifies p
void normalize(struct Point3D *p);


// dot(a, b) computes and returns the dot product of a and b.
// Parameters: a and b are vectors
double dot(struct Point3D a, struct Point3D b);


// sub(a, b) subtracts b from a.
// Parameters: a is the point to subtract from
//             b is the point to subtract
//
// requires:   a != NULL
// effects:    modifies a
void sub(struct Point3D *a, struct Point3D b);


// add(a, b) adds b to a.
// Parameters: a is the point to add to
//             b is the point to add
//
// requires:   a != NULL
// effects:    modifies a
void add(struct Point3D *a, struct Point3D b);


// distance(a, b) computes and returns the distance between a and b.
// Parameters: a is the first point
//             b is the second point
double distance(struct Point3D a, struct Point3D b);


// scalar(a, s) multiplies point a by scalar s.
// Parameters: a is the point
//             s is the scalar
//
// requires:   a != NULL
// effects:    modifies a
void scalar(struct Point3D *a, double s);


// reflect(v, n, reflected) given velocity (direction) vector and surface normal, 
// computes the reflected vector.
// Parameters: v is the velocity/direction
//             n is the surface normal at the point of interseciton
//             reflected is the direction after bouncing
//
// requires:   reflected != NULL
// effects:    modifies reflected
void reflect(struct Point3D v, struct Point3D n, struct Point3D *reflected);


// is_bounce(bounce) returns true if any of the fields of bounce are true.
// Which implies that at the sphere intersected at least ONE wall.
// Parameters: bounce is the wall intersection indicator
bool is_bounce(struct Bounce bounce);


// print_Point3D(p) prints Point3D p on the screen.
// Parameters: p is a Point3D
//
// effects:   data is printed on the screen
void print_Point3D(struct Point3D p);


// print_bounce(b) prints bounce b on the screen.
// Parameters: b is a bounce struct
//
// effects:   data is printed on the screen
void print_bounce(struct Bounce b);

#endif
