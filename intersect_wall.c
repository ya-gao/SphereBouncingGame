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
#include "sphere.h"
#include "intersect_wall.h"



// void intersects_wall( sphere, width, height, bounce ) computes which walls 
// the sphere intersects.  The box has dimensions (0,0,0)x(width,height,100)    
// parameters:  sphere is the sphere used in the intersection test
//              width is the width of the image (and box)
//              height is the height of the image (and box)
//              bounce is a pointer to a struct Bounce, which holds the
//                     information about which walls are intersected
//
// requires:    sphere != NULL 
//              width >= 0
//              height >=0
//              bounce != NULL
// effects:     bounce is updated
void intersects_wall(struct Sphere *sphere, int width,
                     int height, struct Bounce *bounce) {
  assert(sphere != NULL);
  assert(width >= 0);
  assert(height >= 0);
  assert(bounce != NULL);
  struct Point3D center = get_sphere_center(sphere);
  double r = get_sphere_radius(sphere);
  // check if sphere intersects front wall (z = 0)
  
  if ((center.z - r) <= 0) {
    bounce->front = true;
  } else {
    bounce->front = 0;
  }
  // check if sphere intersects back wall (z = 100)
  if ((center.z + r) >= 100) {
    bounce->back = true;
  } else {
    bounce->back = 0;
  }
  // check if sphere intersects top wall
  if ((center.y + r) >= (height - 1)) {
    bounce->top = true;
  } else {
    bounce->top = 0;
  }
  // check if sphere intersects bottom wall
  if ((center.y - r) <= 0) {
    bounce->bottom = true;
  } else {
    bounce->bottom = 0;
  }
  // check if sphere intersects left wall
  if ((center.x - r) <= 0) {
    bounce->left = true;
  } else {
    bounce->left = 0;
  }
  // check if sphere intersects right wall
  if ((center.x + r) >= (width - 1)) {
    bounce->right = true;
  } else {
    bounce->right = 0;
  }
}

