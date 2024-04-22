#include <stdio.h>
#include <stdlib.h>

#include "generic.h"
#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

TREE avl_tree_init_default(void) {

    AVL_tree* pMy_tree = (AVL_tree*)malloc(sizeof(AVL_tree));

    if (pMy_tree == NULL)
        return NULL;

    pMy_tree->root = NULL;

    return pMy_tree;
}

// The generic_vector IS the associative array (key-value pairs)
// an Associative Array is basically a dictionary (from Python) 
// IMPORTANT TO NOTE, that this is a recursive function and if no
//  node is found with the key given, then it will create its own
//  node with the key
Status avl_tree_push(TREE hAVL_tree, MY_STRING key, MY_STRING value) 
{

    AVL_tree* pMy_tree = (AVL_tree*)hAVL_tree;

    // If the tree is empty, or there is no existing Node,
    //  create a new Node holding a unique key and add
    //  the value into that key
    if (pMy_tree->root == NULL) 
    {

        pMy_tree->root = (Node*)malloc(sizeof(Node));

        if (pMy_tree->root == NULL)
            return FAILURE;

        pMy_tree->root->left = NULL;
        pMy_tree->root->right = NULL;
        pMy_tree->root->key = my_string_init_c_string(my_string_c_str(key));

        // Creates key-VALUE pair
        pMy_tree->root->data = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);
        generic_vector_push_back(pMy_tree->root->data, value);
        return SUCCESS;
    }

    // If the tree already exists, then recursively get to the bottom
    //  by repeatedly checking the children's keys alphabetical value
    if (pMy_tree->root != NULL) 
    {

        int compare = my_string_compare((pMy_tree->root)->key, key);

        // Given key is alphabetically bigger than current key,
        // so traverse to the right.
        if (compare == 1)
        {
            avl_tree_push(&((pMy_tree->root)->right), key, value);
        }

        // Keys are alphabetically the same.
        // Found the the corresponding key so insert value 
        else if (compare == 0)
        {
            generic_vector_push_back((pMy_tree->root)->data, value);
        }

        // Given key is alphatically smaller than current key,
        // so traverse to the left.
        else if (compare == -1) 
        {
            avl_tree_push(&((pMy_tree->root)->left), key, value);
        }

        // something bad happened
        else 
        {
            return FAILURE;
        }

    }
    return SUCCESS;

}

void avl_tree_destroy(TREE* phAVL_tree) {

    AVL_tree* pMy_tree = (AVL_tree*)*phAVL_tree;

    if (pMy_tree->root != NULL) 
    {
        if ((pMy_tree->root)->left != NULL) 
            avl_tree_destroy_recursive_helper((pMy_tree->root)->left);

        if ((pMy_tree->root)->right != NULL) 
            avl_tree_destroy_recursive_helper((pMy_tree->root)->right);

        my_string_destroy(&((pMy_tree->root)->key));
        generic_vector_destroy(&((pMy_tree->root)->data));
        free(pMy_tree->root);
    }

    free(pMy_tree);
    phAVL_tree = NULL;

}

void avl_tree_destroy_recursive_helper(Node* pNode) 
{
    if (pNode == NULL) 
        return;

    if (pNode->key != NULL)
        my_string_destroy(&(pNode->key));

    if (pNode->data != NULL)
        generic_vector_destroy(&(pNode->data));

    avl_tree_destroy_recursive_helper(pNode->left);
    avl_tree_destroy_recursive_helper(pNode->right);

    free(pNode);
}

GENERIC_VECTOR get_largest_family(TREE hAVL_tree, int running_total) 
{
    AVL_tree* pMy_tree = (AVL_tree*)hAVL_tree;
    GENERIC_VECTOR largest_family = NULL;
    GENERIC_VECTOR temp;

    temp = get_largest_family_helper(pMy_tree->root, running_total);
    largest_family = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);

    for (int i = 0; i < generic_vector_get_size(temp); i++) 
        generic_vector_push_back(largest_family, generic_vector_at(temp, i));

    return largest_family;
}

GENERIC_VECTOR get_largest_family_helper(Node* root, int running_total) 
{
    Generic_vector* temp = NULL;

    if (root != NULL)
    {
        if (root->left != NULL) 
        {
            temp = get_largest_family_helper(root->left, running_total);
            if ((temp == NULL) || (generic_vector_get_size(temp) < generic_vector_get_size(root->data)))
                temp = root->data;
        }

        if (root->right != NULL) 
        {
            temp = get_largest_family_helper(root->right, running_total);
            if ((temp == NULL) || (generic_vector_get_size(temp) < generic_vector_get_size(root->data)))
                temp = root->data;
        }

        if ((temp == NULL) || (generic_vector_get_size(temp) < generic_vector_get_size(root->data))) 
            temp = root->data;
    }

    if (running_total) 
    {
        my_string_insertion(root->key, stdout);
        printf(" %d\n", generic_vector_get_size(root->data));
    }
    return temp;
}