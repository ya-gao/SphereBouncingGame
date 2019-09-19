//////////////////////////////////////////////////////////////////////////////
// test_functions.c
//////////////////////////////////////////////////////////////////////////////
// The testing platform for A5 simple ASCII raycaster.
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////


// INCLUDES
#include "cs136.h"
#include "test_functions.h"
#include "render.h"
#include "sphere_movement.h"
#include "sphere_collision.h"
#include "intersect_wall.h"

// CONSTANTS
const double EPSILON = 0.000001;


// FUNCTION IMPLEMENTATIONS
//////////////////////////////////////////////////////////////////////////////

// void pass_fail(char *msg, bool b)is a simple function to print test 
// results neatly.  Prints the message stored in msg and PASS if b is true, 
// FAIL otherwise
//
// requires: msg != NULL
// effects:  prints results to screen
void pass_fail(char *msg, bool b) {
    if (b) {
        printf("%s PASS\n", msg);
    } else {
        printf("%s FAIL\n", msg);
    }
}



// void test_simple_ray_sphere_intersect(struct Sequence *seq) generates 
// several rays and tests for intersection with EVERY sphere s
// rays go through the top, bottom, left and right of the sphere,
// the middle of the sphere, and TWO rays that do not go through the 
// sphere (upper-right, lower-left).  The .expect file will contain
// a PASS/FAIL list of ray-sphere intersection expectations for each
// sphere.  This is to test Q1.
//
// effects:  prints results to screen
void test_simple_ray_sphere_intersect(struct Sequence *seq) {
    assert(seq != NULL);

    // check EVERY sphere
    int size = length(seq);
    int totalTestsPassed = 0;
    int outOf = 7 * size;

    for (int i = 0; i < size; i ++) {
        struct Sphere *s = item_at(seq, i);

        // get radius
        double r = get_sphere_radius(s);

        // get sphere center
        struct Point3D c = get_sphere_center(s);

        // ray through "middle"
        struct Ray middle = {{c.x, c.y, 0}, {0, 0, 1}};
    
        // rays through top, bottom, left, and right
        struct Ray top = {{c.x, c.y + r, 0}, {0, 0, 1}};
        struct Ray bottom = {{c.x, c.y - r, 0}, {0, 0, 1}};
        struct Ray left = {{c.x - r, c.y, 0}, {0, 0, 1}};
        struct Ray right = {{c.x + r, c.y, 0}, {0, 0, 1}};

        // rays through up/right and down/left
        struct Ray up_right = {{c.x + r, c.y + r, 0}, {0, 0, 1}};
        struct Ray down_left = {{c.x - r, c.y - r, 0}, {0, 0, 1}};

        // perform ray-sphere intersection tests
        bool middle_b = simple_ray_sphere_intersect(s, middle);
        bool top_b = simple_ray_sphere_intersect(s, top);
        bool bottom_b = simple_ray_sphere_intersect(s, bottom);
        bool left_b = simple_ray_sphere_intersect(s, left);
        bool right_b = simple_ray_sphere_intersect(s, right);
        bool up_right_b = simple_ray_sphere_intersect(s, up_right);
        bool down_left_b = simple_ray_sphere_intersect(s, down_left);

        totalTestsPassed += middle_b + top_b + bottom_b + left_b + right_b;
        totalTestsPassed += !up_right_b + !down_left_b;

        // middle, left, right, top, and bottom should be hits
        // upright, downleft should be MISSES
        print_sphere(s);
        pass_fail("    MIDDLE:   ", middle_b);
        pass_fail("    TOP:      ", top_b);
        pass_fail("    BOTTOM:   ", bottom_b);
        pass_fail("    LEFT:     ", left_b);
        pass_fail("    RIGHT:    ", right_b);
        pass_fail("    UP/RIGHT: ", !up_right_b);
        pass_fail("    DOWN/LEFT:", !down_left_b);
    }
    printf("QUESTION 1: %d / %d\n", totalTestsPassed, outOf); 
}



// void test_simple_render(struct Sequence *seq, WIDTH, HEIGHT) renders each 
// sphere separately.  Each rendering is separated by a line of dashes
// so that it is easy to separate images.  The .expect file contains the
// rendered scenes for each sphere.  This function is to test Q2.
//
// effects:  prints results to screen
void test_simple_render(struct Sequence *seq, int WIDTH, int HEIGHT) {
    assert(seq != NULL);

    // image size and background colour
    int width = WIDTH;
    int height = HEIGHT;
    char background = '.';

    // sequence length
    int size = length(seq);

    // render each sphere
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < size; i ++) {
        simple_render(item_at(seq, i), width, height, background);
        printf("----------------------------------------------------------------------\n"); 
    }
}



// void test_closest_sphere_colour(struct Sequence *seq) generates a 
// sphere behind and in-front of each in seq and tests visibility of
// those spheres.  The .expect file contains PASS/FAIL results for
// each sphere's expected visibility. This function is for testing Q3.
//
// effects:  prints results to screen
void test_closest_sphere_colour(struct Sequence *seq) {
    assert(seq != NULL);

    // check EVERY sphere
    int size = length(seq);
    int totalTestsPassed = 0;
    int outOf = 0;

    for (int i = 0; i < size; i ++) {
        struct Sphere *s = item_at(seq, i);
        
        // get radius
        double r = get_sphere_radius(s);

        // test the MIDDLE ray for all
        // get sphere center
        struct Point3D c = get_sphere_center(s);

        // Make sphere in front and in back
        struct Sphere *copy = make_sphere(c.x, c.y, c.z, r, 'x');
        copy_sphere(s, copy);
        set_sphere_colour(copy, 'x');

        struct Sphere *front = make_sphere(c.x, c.y, 
            ((c.z - r) <= 0) ? (c.z - r + 1) : (c.z - r), 1, 'f');
        struct Sphere *behind = make_sphere(c.x, c.y, c.z + r, r + 2, 'b');

        // Create the sequence of spheres
        struct Sequence *tmp_seq = make_sequence();
        insert_at(tmp_seq, front, 0);
        insert_at(tmp_seq, behind, 1);
        insert_at(tmp_seq, copy, 2);

        // Make rays
        struct Ray raym = {{c.x, c.y, 0}, {0, 0, 1}};
        struct Ray rayt = {{c.x, c.y + r, 0}, {0, 0, 1}};
        struct Ray rayb = {{c.x, c.y - r, 0}, {0, 0, 1}};
        struct Ray rayl = {{c.x - r, c.y, 0}, {0, 0, 1}};
        struct Ray rayr = {{c.x + r, c.y, 0}, {0, 0, 1}};
        struct Ray rayur = {{c.x + r, c.y + r, 0}, {0, 0, 1}};
        struct Ray raydl = {{c.x - r, c.y - r, 0}, {0, 0, 1}};

        // calculate
        bool m = (closest_sphere_colour(tmp_seq, raym) == 'f') ? 1 : 0;
        bool t = (closest_sphere_colour(tmp_seq, rayt) == 'x') ? 1 : 0;
        bool b = (closest_sphere_colour(tmp_seq, rayb) == 'x') ? 1 : 0;
        bool l = (closest_sphere_colour(tmp_seq, rayl) == 'x') ? 1 : 0;
        bool rt = (closest_sphere_colour(tmp_seq, rayr) == 'x') ? 1 : 0;
        bool ur = (closest_sphere_colour(tmp_seq, rayur) != 'x') ? 1 : 0;
        bool dl = (closest_sphere_colour(tmp_seq, raydl) != 'x') ? 1 : 0;

        // For small radii, only test MIDDLE, UR and DL
        if (r <= 4) {
            totalTestsPassed += m + ur + dl;
            outOf += 3;
        } else {
            totalTestsPassed += m + t + b + l + rt + ur + dl;
            outOf += 7;        
        }

        print_sphere(s);
        pass_fail("    MIDDLE:   ", m);
        if (r > 4) {
            pass_fail("    TOP:      ", t);
            pass_fail("    BOTTOM:   ", b);
            pass_fail("    LEFT:     ", l);
            pass_fail("    RIGHT:    ", rt);
        }
        pass_fail("    UP/RIGHT: ", ur);
        pass_fail("    DOWN/LEFT:", dl);

        destroy_sequence(tmp_seq);
    }
    printf("QUESTION 4: %d / %d\n", totalTestsPassed, outOf);         
}



// void test_render(struct Sequence *seq, WIDTH, HEIGHT) renders the scene with 
// preset params.  The scene contains all spheres in the seq.
//
// effects:  prints results to screen
void test_render(struct Sequence *seq, int WIDTH, int HEIGHT) {
    assert(seq != NULL);

    // image size and background colour
    int width = WIDTH;
    int height = HEIGHT;
    char background = '.';

    // render scene
    printf("----------------------------------------------------------------------\n");
    render(seq, width, height, background);
    printf("----------------------------------------------------------------------\n"); 
}


// void test_simple_move_sphere(struct Sequence *seq)
// Tests the movement of spheres by moving each along a pre-determined 
// direction for a fixed time unit and comparing the results.  The 
// .expect file will contain PASS/FAIL for each sphere/direction/time
// combination. This is the test for Q5.
//
// effects:  prints results to screen
void test_simple_move_sphere(struct Sequence *seq) {
    assert(seq != NULL);

    // sequence length
    int size = length(seq);
    int totalTestsPassed = 0;
    int outOf = 6 * size;

    // render each sphere
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < size; i ++) {
        struct Sphere * s = item_at(seq, i);
        struct Point3D oldv = get_sphere_direction(s); // OLD velocity
        struct Point3D v = {1, 0, 0};
        struct Point3D c = get_sphere_center(s);


        set_sphere_direction(s, 1, 0, 0); // set a NEW velocity

        // t = 0
        simple_move_sphere(s, 0); 
        struct Point3D newc = get_sphere_center(s);
        bool t_zero = (fabs(c.x - newc.x)<= EPSILON && 
                        fabs(c.y - newc.y)<= EPSILON &&
                        fabs(c.z - newc.z)<= EPSILON)? 1 : 0;

        // t = 1
        simple_move_sphere(s, 1);
        newc = get_sphere_center(s);
        bool t_one = false;
        if ((newc.x - (c.x + v.x)) <= EPSILON &&
             (newc.y - (c.y + v.y)) <= EPSILON &&
             (newc.z - (c.z + v.z)) <= EPSILON) {
            t_one = true;
        }

        // t = 10
        set_sphere_center(s, c);
        simple_move_sphere(s, 10);
        newc = get_sphere_center(s);
        bool t_ten = false;
        if ((newc.x - (c.x + 10 * v.x)) <= EPSILON &&
             (newc.y - (c.y + 10 * v.y)) <= EPSILON &&
             (newc.z - (c.z + 10 * v.z)) <= EPSILON) {
            t_ten = true;
        }

        set_sphere_center(s, c);
        set_sphere_direction(s, oldv.x, oldv.y, oldv.z);

        // calculate score
        totalTestsPassed += t_zero + t_one + t_ten;

        print_sphere(s);
        pass_fail("d=(1,0,0), t = 0:    ", t_zero);
        pass_fail("d=(1,0,0), t = 1:    ", t_one);
        pass_fail("d=(1,0,0), t = 10:   ", t_ten);

        // A NEW direction
        set_sphere_direction(s, 0, -1, 0); // set a NEW velocity
        v.x = 0;
        v.y = -1;
        v.z = 0;


        // t = 0
        simple_move_sphere(s, 0); 
        newc = get_sphere_center(s);
        t_zero = (fabs(c.x - newc.x)<= EPSILON && 
                        fabs(c.y - newc.y)<= EPSILON &&
                        fabs(c.z - newc.z)<= EPSILON)? 1 : 0;

        // t = 1
        simple_move_sphere(s, 1);
        newc = get_sphere_center(s);
        t_one = false;
        if ((newc.x - (c.x + v.x)) <= EPSILON &&
             (newc.y - (c.y + v.y)) <= EPSILON &&
             (newc.z - (c.z + v.z)) <= EPSILON) {
            t_one = true;
        }

        // t = 10
        set_sphere_center(s, c);
        simple_move_sphere(s, 10);
        newc = get_sphere_center(s);
        t_ten = false;
        if ((newc.x - (c.x + 10 * v.x)) <= EPSILON &&
             (newc.y - (c.y + 10 * v.y)) <= EPSILON &&
             (newc.z - (c.z + 10 * v.z)) <= EPSILON) {
            t_ten = true;
        }

        set_sphere_center(s, c);
        set_sphere_direction(s, oldv.x, oldv.y, oldv.z);

        // calculate score
        totalTestsPassed += t_zero + t_one + t_ten;

        pass_fail("d=(0,-1,0), t = 0:    ", t_zero);
        pass_fail("d=(0,-1,0), t = 1:    ", t_one);
        pass_fail("d=(0,-1,0), t = 10:   ", t_ten);
    }
    printf("QUESTION 5: %d / %d\n", totalTestsPassed, outOf);             
}



// void test_intersects_wall(WIDTH, HEIGHT) generates a few simple spheres
// that test for wall intersection.  One sphere will intersect nothing, 
// another intersects all but one wall, and the final sphere encompasses
// the whole world. The .expect file indicates if the expected intersections
// match the ones discovered with PASS/FAIL.  This is the test for Q6.
//
// effects:  prints results to screen
void test_intersects_wall(int WIDTH, int HEIGHT) {
    assert(WIDTH >= 0);
    assert(HEIGHT >= 0);
    assert(WIDTH == HEIGHT);

    // new center
    double c_x = (double)(WIDTH - 1.0) / 2.0;
    double c_y = (double)(HEIGHT - 1.0) / 2.0;
    double c_z = c_x;
    double c_r = c_x;

    // First sphere should intersect everything EXCEPT the back wall
    struct Sphere * s1 = make_sphere(c_x, c_y, c_z, c_r, 'x');
    struct Bounce bounce;

    intersects_wall(s1, WIDTH - 1, HEIGHT - 1, &bounce);


    int outOf = 18;
    int totalTestsPassed = 0;
    totalTestsPassed = bounce.top + bounce.bottom + bounce.left + bounce.right +
                       bounce.front + !bounce.back;

    print_sphere(s1);
    pass_fail("    TOP:      ", bounce.top);
    pass_fail("    BOTTOM:   ", bounce.bottom);
    pass_fail("    LEFT:     ", bounce.left);
    pass_fail("    RIGHT:    ", bounce.right);
    pass_fail("    FRONT:    ", bounce.front);
    pass_fail("    BACK:     ", !bounce.back);
    

    // second sphere should intersect nothing
    struct Sphere * s2 = make_sphere(c_x, c_y, 25, 1, 'x');  
    intersects_wall(s2, WIDTH-1, HEIGHT-1, &bounce);
    totalTestsPassed += !bounce.top + !bounce.bottom + !bounce.left + !bounce.right +
                        !bounce.front + !bounce.back;

    print_sphere(s2);
    pass_fail("    TOP:      ", !bounce.top);
    pass_fail("    BOTTOM:   ", !bounce.bottom);
    pass_fail("    LEFT:     ", !bounce.left);
    pass_fail("    RIGHT:    ", !bounce.right);
    pass_fail("    FRONT:    ", !bounce.front);
    pass_fail("    BACK:     ", !bounce.back);

    struct Sphere * s3 = make_sphere(c_x, c_y, 25, WIDTH+HEIGHT, 'x');
    intersects_wall(s3, WIDTH-1, HEIGHT-1, &bounce);
    totalTestsPassed += bounce.top + bounce.bottom + bounce.left + bounce.right +
                       bounce.front + ((25 + WIDTH + HEIGHT >= 100) ? bounce.back : !bounce.back);

    print_sphere(s3);
    pass_fail("    TOP:      ", bounce.top);
    pass_fail("    BOTTOM:   ", bounce.bottom);
    pass_fail("    LEFT:     ", bounce.left);
    pass_fail("    RIGHT:    ", bounce.right);
    pass_fail("    FRONT:    ", bounce.front);
    pass_fail("    BACK:     ", ((25 + WIDTH + HEIGHT >= 100) ? bounce.back : !bounce.back));


    printf("QUESTION 6: %d / %d\n", totalTestsPassed, outOf);

    destroy_sphere(s1);
    destroy_sphere(s2);
    destroy_sphere(s3);
}




// void test_simulate_one_sphere(struct Sequence *seq, WIDTH, HEIGHT)
// Simulates one sphere, at a time, bouncing around.  Two time steps are 
// rendered per sphere, each separated by a line of dashes.  This is the
// test for Q7.
//
// effects:  prints results to screen
void test_simulate_one_sphere(struct Sequence *seq, int WIDTH, int HEIGHT) {
    // image size and background colour
    int width = WIDTH;
    int height = HEIGHT;
    char background = '.';

    // sequence length
    int size = length(seq);

    // render each sphere
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < size; i ++) {
        simulate_one_sphere(item_at(seq, i), width, height, 0, background);
        printf("\n");
        simulate_one_sphere(item_at(seq, i), width, height, 10, background);
        printf("----------------------------------------------------------------------\n"); 
    }
}




// void test_sphere_collision(struct Sequence *seq) generates new spheres
// for each in seq that do and do not intersect.  The .expect file contains
// PASS/FAIL for each combination. This is the test for Q8.
// 
// effects:  prints results to screen
void test_sphere_collision(struct Sequence *seq) {
    // sequence length
    int size = length(seq);

    int totalTestsPassed = 0;
    int outOf = size * 2;
    for (int i = 0; i < size; i ++) {
        // get this sphere
        struct Sphere *s = item_at(seq, i);

        // get its center and radius
        struct Point3D c = get_sphere_center(s);
        double r = get_sphere_radius(s);

        // create a sphere that DOES intersect
        struct Sphere *does = make_sphere(c.x, c.y, c.z, r / 2, 'Y');
        
        // create a sphere that DOES NOT intersect
        struct Sphere *doesNot = make_sphere(c.x + 2 * r, c.y + 2 * r, c.z + 2 * r, 1, 'N');

        bool does_b = sphere_collision(s, does);
        bool does_not_b = sphere_collision(s, doesNot);

        totalTestsPassed += does_b + !does_not_b;

        // check collisions
        print_sphere(s);
        pass_fail("    COLLIDE:   ", does_b);
        pass_fail("    NO COLLIDE:", !does_not_b);

        destroy_sphere(does);
        destroy_sphere(doesNot);
    }
    printf("QUESTION 8: %d / %d\n", totalTestsPassed, outOf);         
}



// void test_simulate_two_spheres(seq, WIDTH, HEIGHT) simulates two spheres, 
// bouncing around in the box.  If seq contains more than two spheres, only
// the first two in the sequence will be used.  All other spheres will be
// ignorned.  The simulation will be displayed for two timesteps, separated
// by a line of dashes.  This is the test for Q9.
//
// effects:  prints results to screen
void test_simulate_two_spheres(struct Sequence *seq, int WIDTH, int HEIGHT) {
    assert(seq != NULL);

    // image size and background colour
    int width = WIDTH;
    int height = HEIGHT;
    char background = '.';

    // sequence length
    int size = length(seq);

    if (size < 2) {
        printf("Insufficient Spheres to test Q9\n");
        return;
    }

    // render the FIRST two spheres of the sequence
    printf("----------------------------------------------------------------------\n");
    simulate_two_spheres(seq, width, height, 0, background);
    printf("\n" );
    simulate_two_spheres(seq, width, height, 10, background);
    printf("----------------------------------------------------------------------\n"); 
}




