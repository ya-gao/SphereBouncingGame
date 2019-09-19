//////////////////////////////////////////////////////////////////////////////
// sphere_collision.h
//////////////////////////////////////////////////////////////////////////////
// The interface for sphere collision function.
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "sphere.h"


// bool sphere_collision(a, b) returns true if spheres a and b collide using 
// the following method:
//     if distance between (a, b) <= sum of radii then collision    
// Parameters:  a is the first sphere
//              b is the second sphere
//
// requires:    a != NULL 
//              b != NULL
bool sphere_collision(struct Sphere *a, struct Sphere *b);


