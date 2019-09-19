//////////////////////////////////////////////////////////////////////////////
// intersect_wall.h
//////////////////////////////////////////////////////////////////////////////
// The interface for intersect_wall function.
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "sphere.h"

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
void intersects_wall(struct Sphere *sphere, int width, int height, struct Bounce *bounce);



