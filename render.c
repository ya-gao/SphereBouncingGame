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

#include "render.h"

// simple_ray_sphere_intersect returns true if the ray intersects the sphere,
//   and false otherwise.
// requires: The sphere parameter cannot be null.
bool simple_ray_sphere_intersect(struct Sphere *sphere, struct Ray ray) {
  struct Point3D center = get_sphere_center(sphere);
  double r = get_sphere_radius(sphere);
  if (center.z + r < 0) {
    return false;
  } else if ((ray.origin.x - center.x) * (ray.origin.x - center.x) + 
             (ray.origin.y - center.y) * (ray.origin.y - center.y) <= r * r) {
    return true;
  } else {
    return false;
  }
}

// simple_render renders/prints an ASCII-art image of size [width x height].
void simple_render(struct Sphere *sphere, int width,
                   int height, char background){
  int h = 0;
  while (h < height) {
    int w = 0;
    while (w < width) {
      struct Ray ray = {{w, h, 0.0}, {0.0, 0.0, 1.0}};
      if (simple_ray_sphere_intersect(sphere, ray)) {
        char colour = get_sphere_colour(sphere);
        printf("%c", colour);
      } else {
        printf("%c", background);
      }
      w++;
    }
    printf("\n");
    h++;
  }
}

// closest_sphere_colour returns the colour of the sphere that intersects the
//   ray and is closest to the ray origin.
char closest_sphere_colour(struct Sequence *seq, struct Ray ray){
  int len = length(seq);
  int i = 0;
  double min_depth = 10000000.0;
  double depth = 0.0;
  char colour = ' ';
  bool intersect = 0;
  while (i < len) {
    struct Sphere *sphere = item_at(seq, i); 
    if (simple_ray_sphere_intersect(sphere, ray)) {
      intersect = 1;
      depth = min_z_intersection(sphere, ray);
      if (depth < min_depth) {
        min_depth = depth;
        colour = get_sphere_colour(sphere);
      }
    } 
  i++;
  }
  if (intersect == 0) {
    return 0;
  } else {
    return colour;
  }
}

// void render(seq, width, height, background) renders the sequence of spheres
// over the provided background to the screen using ASCII characters
//
// requires: seq != NULL
void render(struct Sequence *seq, int width, int height, char background){
  int h = 0;
  while (h < height) {
    int w = 0;
    while (w < width) {
      struct Ray ray = {{w, h, 0.0}, {0.0, 0.0, 1.0}};
      if (closest_sphere_colour(seq, ray) != 0) {
        char colour = closest_sphere_colour(seq, ray);
        printf("%c", colour);
      } else {
        printf("%c", background);
      }
      w++;
    }
    printf("\n");
    h++;
  }
}

void simulate_one_sphere(struct Sphere *sphere, int width,
                         int height, double t, char background){
  if (t < TIMESTEP) {
    simple_render(sphere, width, height, background);
  } else {
    double cur_t = TIMESTEP;
    while (cur_t < t) {
      struct Bounce bounce;
      intersects_wall(sphere, width-1, height-1, &bounce);
      // if bounced, get new direction of sphere
      if (is_bounce(bounce)) {
        struct Point3D reflected;
        wall_bounce(sphere, bounce, &reflected);
        set_sphere_direction(sphere, reflected.x, reflected.y, reflected.z);
      }
    
      // move the sphere to new position
      simple_move_sphere(sphere, TIMESTEP);
      cur_t += TIMESTEP;
    }
    simple_move_sphere(sphere, TIMESTEP);
    simple_render(sphere, width, height, background);
  }
}

void simulate_two_spheres(struct Sequence *seq, int width, 
                          int height, double t, char background){
  if (t < TIMESTEP) {
    render(seq, width, height, background);
  } else {
    struct Sphere *a = item_at(seq, 0); 
    struct Sphere *b = item_at(seq, 1);
    double cur_t = TIMESTEP;
    while (cur_t < t) {
      // if two spheres bounce off each other
      // new directions of both spheres updated
      struct Point3D bouncea;
      struct Point3D bounceb;
      if (sphere_collision(a, b)) {
        sphere_bounce(a, b, &bouncea, &bounceb);
        set_sphere_direction(a, bouncea.x, bouncea.y, bouncea.z);
        set_sphere_direction(b, bounceb.x, bounceb.y, bounceb.z);
      }
      
      // wall collision check for sphere a
      struct Bounce bounce1;
      intersects_wall(a, width-1, height-1, &bounce1);
      // if bounced, get new direction of sphere a
      if (is_bounce(bounce1)) {
        struct Point3D reflected;
        wall_bounce(a, bounce1, &reflected);
        set_sphere_direction(a, reflected.x, reflected.y, reflected.z);
      }
      
      // wall collision check for sphere b
      struct Bounce bounce2;
      intersects_wall(b, width-1, height-1, &bounce2);
      // if bounced, get new direction of sphere b
      if (is_bounce(bounce2)) {
        struct Point3D reflected;
        wall_bounce(b, bounce2, &reflected);
        set_sphere_direction(b, reflected.x, reflected.y, reflected.z);
      }
    
      // move the sphere to new position
      simple_move_sphere(a, TIMESTEP);
      simple_move_sphere(b, TIMESTEP);
      cur_t += TIMESTEP;
    }
    simple_move_sphere(a, TIMESTEP);
    simple_move_sphere(b, TIMESTEP);
    render(seq, width, height, background);
  }
}
