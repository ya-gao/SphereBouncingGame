//////////////////////////////////////////////////////////////////////////////
// test_functions.h
//////////////////////////////////////////////////////////////////////////////
// Tests for the sphere renderer.
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "sequence.h"



// FUNCTION INTERFACE
// void pass_fail(char *c, bool b) prints the message stored in c and PASS 
// if b is true, FAIL otherwise
//
// effects:  prints results to screen
void pass_fail(char *c, bool b);



// void test_simple_ray_sphere_intersect(struct Sequence *seq) generates 
// several rays and tests for intersection with EVERY sphere s
// rays go through the top, bottom, left and right of the sphere,
// the middle of the sphere, and TWO rays that do not go through the 
// sphere (upper-right, lower-left).  The .expect file will contain
// a PASS/FAIL list of ray-sphere intersection expectations for each
// sphere.  This is to test Q1.
//
// effects:  prints results to screen
void test_simple_ray_sphere_intersect(struct Sequence *seq);



// void test_simple_render(struct Sequence *seq, WIDTH, HEIGHT) renders each 
// sphere separately.  Each rendering is separated by a line of dashes
// so that it is easy to separate images.  The .expect file contains the
// rendered scenes for each sphere.  This function is to test Q2.
//
//effects:  prints results to screen
void test_simple_render(struct Sequence *seq, int WIDTH, int HEIGHT);



// void test_closest_sphere_colour(struct Sequence *seq) generates a 
// sphere behind and in-front of each in seq and tests visibility of
// those spheres.  The .expect file contains PASS/FAIL results for
// each sphere's expected visibility. This function is for testing Q3.
//
// effects:  prints results to screen
void test_closest_sphere_colour(struct Sequence *seq);



// void test_render(struct Sequence *seq, WIDTH, HEIGHT) renders the 
// scene with preset params.  The .expect file will contain the 
// rendered image.  This is for testing Q4.
//
// effects:  prints results to screen
void test_render(struct Sequence *seq, int WIDTH, int HEIGHT);



// void test_simple_move_sphere(struct Sequence *seq)
// Tests the movement of spheres by moving each along a pre-determined 
// direction for a fixed time unit and comparing the results.  The 
// .expect file will contain PASS/FAIL for each sphere/direction/time
// combination. This is the test for Q5.
//
// effects:  prints results to screen
void test_simple_move_sphere(struct Sequence *seq);



// void test_intersects_wall(WIDTH, HEIGHT) generates a few simple spheres
// that test for wall intersection.  One sphere will intersect nothing, 
// another intersects all but one wall, and the final sphere encompasses
// the whole world. The .expect file indicates if the expected intersections
// match the ones discovered with PASS/FAIL.  This is the test for Q6.
//
// effects:  prints results to screen
void test_intersects_wall(int WIDTH, int HEIGHT);



// void test_simulate_one_sphere(struct Sequence *seq, WIDTH, HEIGHT)
// Simulates one sphere, at a time, bouncing around.  Two time steps are 
// rendered per sphere, each separated by a line of dashes.  This is the
// test for Q7.
//
// effects:  prints results to screen
void test_simulate_one_sphere(struct Sequence *seq, int WIDTH, int HEIGHT);



// void test_sphere_collision(struct Sequence *seq) generates new spheres
// for each in seq that do and do not intersect.  The .expect file contains
// PASS/FAIL for each combination. This is the test for Q8.
// 
// effects:  prints results to screen
void test_sphere_collision();



// void test_simulate_two_spheres(seq, WIDTH, HEIGHT) simulates two spheres, 
// bouncing around in the box.  If seq contains more than two spheres, only
// the first two in the sequence will be used.  All other spheres will be
// ignorned.  The simulation will be displayed for two timesteps, separated
// by a line of dashes.  This is the test for Q9.
//
// effects:  prints results to screen
void test_simulate_two_spheres(struct Sequence *seq, int WIDTH, int HEIGHT);
