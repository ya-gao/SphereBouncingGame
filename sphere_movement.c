/////////////////////////////////////////////////////////////////////////////
// INTEGRITY INSTRUCTIONS

// Explicitly state the level of collaboration on this question
// Examples:
//   * I discussed ideas with classmate(s) [include name(s)]
//   * I worked together with classmate(s) in the lab [include name(s)]
//   * Classmate [include name] helped me debug my code
//   * I consulted website [include url]
//   * None
// A "None" indicates you completed this question entirely by yourself
// (or with assistance from course staff)
/////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT:
// I received help from the following sources:



// Name: Ya Gao
// login ID: y347gao
/////////////////////////////////////////////////////////////////////////////


// INCLUDES
#include "sphere_movement.h"


// IMPLEMENT THIS FUNCTION 
// void simple_move_sphere(sphere, t) moves the sphere to a new position 
// using the following method:
//      new_center = old_center + t * direction
// Parameters:  sphere is the sphere to be moved
//              t is the number of time units the sphere was "moving"
//
// requires:    sphere != NULL
//              t >= 0
// effects:     sphere is mutated; the center is changed
void simple_move_sphere(struct Sphere *sphere, double t) {
  assert(sphere != NULL);
  assert(t >= 0);
  struct Point3D center = get_sphere_center(sphere);
  struct Point3D di = get_sphere_direction(sphere);
  scalar(&di, t);
  add(&center, di);
  set_sphere_center(sphere, center);
}
