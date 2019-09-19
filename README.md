# SphereBouncingGame
This is a game simulating two spheres bouncing in a fixed sized box. Tha spheres will change derection either intersecting walls or colliding with each other. The functionalities of the game are implemented step by step, and follows is a brief description of functions included. For detailed documentation, please see header files.

void intersects_wall( sphere, width, height, bounce ) computes which walls the sphere intersects. 

simple_ray_sphere_intersect returns true if the ray intersects the sphere, and false otherwise.

simple_render renders/prints an ASCII-art image of size [width x height].

closest_sphere_colour returns the colour of the sphere that intersects the ray and is closest to the ray origin.

void render(seq, width, height, background) renders the sequence of spheres over the provided background to the screen using ASCII characters.

void simulate_one_sphere(sphere, width, height, t, background) renders the scene containing the sphere at time t (after simulating the ball bouncing). 

bool sphere_collision(a, b) returns true if spheres a and b collide using the following method: if distance between (a, b) <= sum of radii then collision.

void simple_move_sphere(sphere, t) moves the sphere to a new position using the following method: new_center = old_center + t * direction.

void simulate_two_spheres(seq, width, height, t, background) renders the scene containing the two spheres at time t (after simulating the ball bouncing). 
