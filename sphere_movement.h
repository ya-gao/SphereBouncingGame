//////////////////////////////////////////////////////////////////////////////
// sphere_movement.h
//////////////////////////////////////////////////////////////////////////////
// The interface for sphere movement function(s).
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "sphere.h"


// void simple_move_sphere(sphere, t) moves the sphere to a new position 
// using the following method:
//      new_center = old_center + t * direction
// Parameters:  sphere is the sphere to be moved
//              t is the number of time units the sphere was "moving"
//
// requires:    sphere != NULL
//              t >= 0
// effects:     sphere is mutated; the center is changed
void simple_move_sphere(struct Sphere *sphere, double t);
