//////////////////////////////////////////////////////////////////////////////
// sequence.h
//////////////////////////////////////////////////////////////////////////////
// A numbered sequence of spheres.
//
// Created:  Feb 1, 2019.
//////////////////////////////////////////////////////////////////////////////
#ifndef __SEQUENCE__
#define __SEQUENCE__


// INCLUDES
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "sphere.h"


// STRUCTURES

// struct Sequence is a sequence (numbered, like an array)
// of struct Sphere.
struct Sequence;


// FUNCTION INTERFACE

// struct Sequence * make_sequence() creates and returns the 
// address of a struct Sequence.
//
// effects:  creates a Sequence on the heap
struct Sequence * make_sequence();


// destroy_sequence(seq) destroys the sequence and all the 
// spheres contained within it.
// Parameters:  seq is the sequence to destroy
//
// requires:   seq != NULL
// effects:  destroys the Sequence on the heap
void destroy_sequence(struct Sequence *seq);


// struct Sphere * item_at(seq, i) returns the address of a 
// Sphere at position i in the sequence.
// Parameters:  seq is the sequence 
//              i is the index of the item
//
// requires:   seq != NULL
//             i >= 0 && i < sequence length
struct Sphere * item_at(struct Sequence *seq, int i);


// insert_at(seq, sphere, i) inserts the sphere into the 
// sequence at position i.
// Parameters:  seq is the sequence 
//              sphere is the item to insert
//              i is the index of the item
//
// requires:   seq != NULL
//             i >= 0
// effects:    adds item to sequence
void insert_at(struct Sequence *seq, struct Sphere *sphere, int i);


// remove_at(seq, i) remove the sphere at position i.
// Parameters:  seq is the sequence 
//              i is the index of the item
//
// requires:   seq != NULL
//             i >= 0 && i < sequence length
// effects:    removes item from sequence
void remove_at(struct Sequence *seq, int i);


// int length(seq) returns the number of elements in the 
// sequence.
// Parameters:  seq is the sequence 
//
// requires:   seq != NULL
int length(struct Sequence *seq);



// print_sequence( seq ) display the sequence and its
// contents.
// Parameters:  seq is the sequence 
//
// requires:   seq != NULL
// effects:    prints sequence onto the screen
void print_sequence( struct Sequence * seq );

#endif
