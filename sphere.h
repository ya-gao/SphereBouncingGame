//////////////////////////////////////////////////////////////////////////////
// sphere.h
//////////////////////////////////////////////////////////////////////////////
// The interface for spheres and sphere-related function(s).
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////
#ifndef __SPHERE_H__
#define __SPHERE_H__


// INCLUDES
#include <math.h>
#include "point3d.h"


// STRUCTURES
// struct Sphere is a structure that represents a sphere.  It is opaque
// and all interactions with Sphere must be done via the functions provided
// in this file.
struct Sphere;



// FUNCTION INTERFACES

// struct Sphere * make_sphere(x, y, z, r, c) creates and returns the address 
// of a struct Sphere.  You MUST call this function to create a sphere.
// Parameters: x is the position of the sphere center along the x-axis
//             y is the position of the sphere center along the y-axis
//             z is the position of the sphere center along the z-axis
//            r is the radius of the sphere
//             c is a char that is the sphere's colour
//
// requires:   r >= 0
//             c >= ' '
// effects:  creates a Sphere on the heap
struct Sphere * make_sphere(double x, double y, double z, double r, char c);



// void set_sphere_direction(sphere, x, y, z) sets the direction of the 
// provided sphere.  Note that the direction will be normalized.
// Parameters:  sphere is a pointer to the struct Sphere to be modified
//              x is the x-direction
//              y is the y-direction
//              z is the z-direction
//
// requires:    sphere != NULL
// effects:  modifies a sphere structure
void set_sphere_direction(struct Sphere *sphere, double x, double y, double z);



// void destroy_sphere(sphere)
// Destroys the sphere when we are done with it.
// Parameters:  sphere is a pointer to the struct Sphere to be destroyed
//
// requires:    sphere != NULL
// effects:  modifies a sphere structure
void destroy_sphere(struct Sphere *sphere);



// void copy_sphere(source, dest)
// Copies the center, direction and colour of the source sphere 
// into the destination sphere.  
// Parameters:  source is a pointer to the source Sphere 
//              dest is a pointer to the destination Sphere
//
// requires:    source != NULL
//              dest != NULL
// effects:  modifies a sphere structure
void copy_sphere(struct Sphere *source, struct Sphere *dest);



// void set_sphere_colour(sphere, c) sets the colour of the specified 
// sphere 
// Parameters:  sphere is a pointer to the source Sphere 
//              c is a colour (char)
//
// requires:    sphere != NULL
//              c >= ' '
// effects:  modifies a sphere structure
void set_sphere_colour(struct Sphere *sphere, char c);



// void set_sphere_center(sphere, c ) sets the centerpoint of the 
// specified sphere 
// Parameters:  sphere is a pointer to the source Sphere 
//              c is a Point3D of the new center
//
// requires:    sphere != NULL
// effects:  modifies a sphere structure
void set_sphere_center(struct Sphere *sphere, struct Point3D c);



// void print_sphere(sphere ) prints the sphere position, direction, and 
// colour 
// Parameters:  sphere is a pointer to the source Sphere 
//
// requires:    sphere != NULL
// effects:  prints to the screen
void print_sphere(struct Sphere *sphere);



// struct Point3D get_sphere_center(sphere) gets the center of the sphere 
// and returns it
// Parameters:  sphere is a pointer to the source Sphere 
//
// requires:    sphere != NULL
struct Point3D get_sphere_center(struct Sphere *sphere);



// struct Point3D get_sphere_direction(sphere) gets the direction of 
// the sphere and returns it
// Parameters:  sphere is a pointer to the source Sphere 
//
// requires:    sphere != NULL
struct Point3D get_sphere_direction(struct Sphere *sphere);



// double get_sphere_radius(sphere) gets the radius of the sphere 
// and returns it
// Parameters:  sphere is a pointer to the source Sphere 
//
// requires:    sphere != NULL
double get_sphere_radius(struct Sphere *sphere);



// char get_sphere_colour(sphere) gets the colour (char) of the 
// sphere and returns it
// Parameters:  sphere is a pointer to the source Sphere 
//
// requires:    sphere != NULL
char get_sphere_colour(struct Sphere *sphere);



// min_z_intersection(sphere, ray)
// Computes the z-intersection point between the ray and the sphere.
// This function ASSUMES that the ray intersects the sphere.
// Parameters: sphere is the sphere that intersects the ray
//            ray is the ray which intersects the sphere
//
// requires:   sphere != NULL
//             the radius of the sphere > 0
//             the ray intersects the sphere
double min_z_intersection(struct Sphere *sphere, struct Ray ray);



// void wall_bounce(sphere, bounce, reflected) using the bounce structure to 
// determine which walls a sphere bounced off of, wall_bounce computes 
// the NEW direction of the ball after it has bounced off of the walls.  
// reflected contains the result
// Parameters:  sphere is a pointer to the source Sphere 
//             bounce is a struct Bounce indicating which walls are hit
//              reflected is a pointer to a Point3D used as a return value 
//
// requires:    sphere != NULL
//              reflected != NULL
//              at least ONE field in bounce is true
// effects:     reflected is mutated
void wall_bounce(struct Sphere *sphere, struct Bounce bounce, struct Point3D *reflected);



// void sphere_bounce(a, b, bouncea, bounceb)
// Given two spheres that collide, compute the NEW direction of 
// both spheres after the collision
// Parameters:  a is a pointer to the first sphere
//              b is a pointer to the second sphere
//              bouncea is a pointer to a Point3D used as a return for a
//              bounceb is a pointer to a Point3D used as a return for b
//
// requires:    a != NULL
//              b != NULL
//              bouncea != NULL
//              bounceb != NULL
// effects:     bouncea and bounceb are mutated
void sphere_bounce(struct Sphere *a, struct Sphere *b, 
                    struct Point3D *bouncea, struct Point3D *bounceb);


#endif
