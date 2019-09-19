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


// bool sphere_collision(a, b) returns true if spheres a and b collide using 
// the following method:
//     if distance between (a, b) <= sum of radii then collision    
// Parameters:  a is the first sphere
//              b is the second sphere
//
// requires:    a != NULL 
//              b != NULL
bool sphere_collision(struct Sphere *a, struct Sphere *b){
  struct Point3D center_a = get_sphere_center(a);
  struct Point3D center_b = get_sphere_center(b);
  double r_a = get_sphere_radius(a);
  double r_b = get_sphere_radius(b);
  double dis = distance(center_a, center_b);
  if (dis <= (r_a + r_b)) {
    return true;
  } else {
    return false;
  }
}


