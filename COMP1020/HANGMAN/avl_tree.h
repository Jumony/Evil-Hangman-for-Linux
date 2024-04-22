#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "generic.h"
#include "my_string.h"
#include "generic_vector.h"

typedef void* TREE;

typedef struct node Node;

struct node {

    Node* left;
    Node* right;
    MY_STRING key; // ie ---f----f--f
    GENERIC_VECTOR data; // actual dictionary words
    int height;

};

typedef struct avl_tree {

    Node* root;

} AVL_tree;

/*
    The Tree is responsible for holding key-value pair strings in alphabetical order.
*/

// Precondition: None
// Postcondition: Allocate space for an AVL Tree containing a
//  root node that is NULL by default. If unable to allocate memory,
//  returns a NULL tree. Else, it will return the address of the opaque object
TREE avl_tree_init_default(void);

// Precondition: phAVL_tree holds the address of a valid
//  handle to a TREE object.
// Postcondition: "Iteratively" destroys AVL_tree starting with
//  the left-bottom most node and then proceeding to the right
//  bottom most node. The root node is then freed, set to NULL
//  and the memory has been reclaimed by the system.
void avl_tree_destroy(TREE* phAVL_tree);

// Precondition: hAVL_tree is the handle to a valid AVL_tree object.
//  key is the handle to a valid My_string object.
//  value is the handle to a valid My_string object.
// Postcondition: if hAVL_tree is NULL, a new root node is created
//  with the according key-value pair. If hAVL already exists,
//  check the alphabetical value of the key and recursively insert 
//  into tree according to the structure of an AVL tree. If a key
//  already exists, then push the value into the node with the same key
Status avl_tree_push(TREE hAVL_tree, MY_STRING key, MY_STRING value);

Node* createNode(MY_STRING key, MY_STRING value);
Node* insert(Node* node, MY_STRING key, MY_STRING value);

// Precondition: pNode is the address to a Node object
// Postcondition: Successfully destroys nodes in a
//  Recursive manner as a helper recursive function
//  to the avl_tree_destroy function. Returns memory
//  back to system.
// Maybe there is a way to do this without a helper function?
void avl_tree_destroy_recursive_helper(Node* pNode); 

// Precondition: hAVL_tree is a handle to a TREE object.
//  running_total is a number greater than or equal to zero
// Postcondition: Returns a generic vector containing a list of
//  possible words the computer can use to evade the player
GENERIC_VECTOR get_largest_family(TREE hAVL_tree, int running_total);

// Precondition: Root is a pointer to the root of a tree.
//  running_total is an integer greater than or equal to zero.
// Postcondition: Returns a generic vector and is a helper
//  function to the get_largest_family function.
GENERIC_VECTOR get_largest_family_helper(Node* root, int running_total);

#endif