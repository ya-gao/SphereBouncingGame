//////////////////////////////////////////////////////////////////////////////
// main.c
//////////////////////////////////////////////////////////////////////////////
// Test routines.
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////


// LIBRARY INCLUDES
#include "cs136.h"

// PROJECT INCLUDES
#include "test_functions.h"

// GLOBAL DEFAULT VALUES
int WIDTH = 20;
int HEIGHT = 20;

struct Sequence *seq = NULL;


 // int read_scene() reads from STDIN a scene description.  The description 
 // has the following format, which must be followed exactly (note that 
 // NO error checking is performed).  The test number is returned.
 //
 // FORMAT:
 // TESTNUM               // an integer indicating which test to run
 // WIDTH HEIGHT          // integers for the width and height of the image
 // NUMSPHERES            // an integer indicating the number of spheres
 // X Y Z DX DY DZ R C    // the sphere description - one sphere PER LINE
 //                       //       X, Y, Z, DX, DY, DZ, R are integers
 //                       //       C is a character
 //
 // requires:  global seq is NULL
 // effects:   a global sequence is created and populated with spheres
 //            the global WIDTH and HEIGHT values are set 
int read_scene() {
    assert(seq == NULL);

    // make the sequence
    seq = make_sequence();

    int num_spheres = 0;
    int test_num = 0;

    // get the test number
    scanf("%d", &test_num);

    // width and height
    scanf("%d%d", &WIDTH, &HEIGHT);

    // number of spheres
    scanf("%d", &num_spheres);

    // read spheres
    for (int i = 0; i < num_spheres; i ++) {

        int x = 0;
        int y = 0; 
        int z = 0;
        int dx = 0;
        int dy = 0;
        int dz = 0; 
        int r = 0;
        char c = 0;
        
        scanf("%d %d %d %d %d %d %d %c", &x, &y, &z, &dx, &dy, &dz, &r, &c);
        
        // create sphere
        struct Sphere *s = make_sphere(x, y, z, r, c);
        set_sphere_direction(s, dx, dy, dz);

        // insert into sequence
        insert_at(seq, s, i);
    }

    // Uncomment this line to verify spheres read correctly
    // print_sequence(seq);
    
    return test_num;
}



// main!
int main() {
    // read scene information
    int test = read_scene();
    
    // run the specified test; number corresponds to question number
    if (test == 1) {
        test_simple_ray_sphere_intersect(seq);
    } else if (test == 2) {
        test_simple_render(seq, WIDTH, HEIGHT);
    } else if (test == 3) {
        test_closest_sphere_colour(seq);
    } else if (test == 4) {
        test_render(seq, WIDTH, HEIGHT);
    } else if (test == 5) {
        test_simple_move_sphere(seq);
    } else if (test == 6) {
        test_intersects_wall(WIDTH, HEIGHT);
    } else if (test == 7) {
        test_simulate_one_sphere(seq, WIDTH, HEIGHT);
    } else if (test == 8) {
        test_sphere_collision(seq);
    } else if (test == 9) {
        test_simulate_two_spheres(seq, WIDTH, HEIGHT);
    }

    // cleanup
    destroy_sequence(seq);
    return 0;
}
