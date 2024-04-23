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

int get_height(Node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int get_max(int a, int b)
{
    return (a > b) ? a : b;
}

int get_balance_factor(Node* node)
{
    if (node == NULL)
        return 0;
    
    return get_height(node->left) - get_height(node->right);
}

Node* right_rotate(Node* y) {
    Node* x = y->left;
    Node* T2;

    // Check if x (y->left) is NULL
    if (x == NULL)
        return y;

    T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = get_max(get_height(y->left), get_height(y->right)) + 1;
    x->height = get_max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}

Node* left_rotate(Node* x){  
    Node* y = x->right;  
    Node* T2 = y->left;  
   
    y->left = x;  
    x->right = T2;  
   
    x->height = get_max(get_height(x->right), get_height(x->left)) + 1;  
    y->height = get_max(get_height(y->right), get_height(y->left)) + 1;  
   
    return y;  
}  

Node* createNode(MY_STRING key, MY_STRING value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
        return NULL;

    newNode->key = my_string_init_c_string(my_string_c_str(key));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    newNode->data = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);
    if (newNode->data == NULL)
    {
        my_string_destroy(&(newNode->key));
        free(newNode);
        return NULL;
    }
    generic_vector_push_back(newNode->data, value);

    return newNode;
}


Status avl_tree_push(TREE hAVL_tree, MY_STRING key, MY_STRING value) 
{
    AVL_tree* pMy_tree = (AVL_tree*)hAVL_tree;

    // If the tree is empty, or there is no existing Node,
    // create a new Node holding a unique key and add
    // the value into that key
    if (pMy_tree->root == NULL) 
    {
        pMy_tree->root = createNode(key, value);
        if (pMy_tree->root == NULL)
            return FAILURE;
        return SUCCESS;
    }

    // If the tree already exists, then recursively get to the bottom
    // by repeatedly checking the children's keys alphabetical value
    pMy_tree->root = insert(pMy_tree->root, key, value);
    if (pMy_tree->root == NULL)
        return FAILURE;

    return SUCCESS;
}

// Helper function to insert a new node into the AVL tree
Node* insert(Node* node, MY_STRING key, MY_STRING value)
{
    // If the current node is NULL, create a new node
    if (node == NULL)
        return createNode(key, value);

    // Compare the keys to determine the insertion direction
    int compare = my_string_compare(node->key, key);

    // Perform recursive insertion based on comparison
    if (compare > 0)
        node->left = insert(node->left, key, value);
    else if (compare < 0)
        node->right = insert(node->right, key, value);
    else
        generic_vector_push_back(node->data, value);

    // Update height of the current node
    node->height = 1 + get_max(get_height(node->left), get_height(node->right));

    // Check and perform rotations if necessary to maintain AVL balance
    int bf = get_balance_factor(node);

    // Left Left Case
    if (bf > 1 && my_string_compare(key, node->left->key) < 0)
        return right_rotate(node);

    // Right Right Case
    if (bf < -1 && my_string_compare(key, node->right->key) > 0)
        return left_rotate(node);

    // Left Right Case
    if (bf > 1 && my_string_compare(key, node->left->key) > 0) 
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left Case
    if (bf < -1 && my_string_compare(key, node->right->key) < 0) 
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void avl_tree_destroy(TREE* phAVL_tree) 
{
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

GENERIC_VECTOR get_largest_family(TREE hAVL_tree, int running_total) {
    AVL_tree* pMy_tree = (AVL_tree*)hAVL_tree;
    GENERIC_VECTOR largest_family = NULL;
    GENERIC_VECTOR temp;

    temp = get_largest_family_helper(pMy_tree->root, running_total);
    largest_family = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);

    for (int i = 0; i < generic_vector_get_size(temp); i++)
        generic_vector_push_back(largest_family, generic_vector_at(temp, i));

    generic_vector_destroy(&temp); // Deallocate the temporary vector

    return largest_family;
}

GENERIC_VECTOR get_largest_family_helper(Node* root, int running_total) {
    GENERIC_VECTOR largest_family = NULL;
    GENERIC_VECTOR temp;
    MY_STRING largest_key = NULL;

    if (root != NULL) {
        if (root->left != NULL) {
            temp = get_largest_family_helper(root->left, running_total);
            if (largest_family == NULL || (generic_vector_get_size(temp) > generic_vector_get_size(largest_family)) ||
                (generic_vector_get_size(temp) == generic_vector_get_size(largest_family) && my_string_compare(root->left->key, largest_key) < 0)) {
                if (largest_family != NULL)
                    generic_vector_destroy(&largest_family); // Deallocate the previous largest_family
                largest_family = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);
                for (int i = 0; i < generic_vector_get_size(temp); i++)
                    generic_vector_push_back(largest_family, generic_vector_at(temp, i));
                largest_key = root->left->key;
            }
            generic_vector_destroy(&temp); // Deallocate the temporary vector
        }

        if (root->right != NULL) {
            temp = get_largest_family_helper(root->right, running_total);
            if (largest_family == NULL || (generic_vector_get_size(temp) > generic_vector_get_size(largest_family)) ||
                (generic_vector_get_size(temp) == generic_vector_get_size(largest_family) && my_string_compare(root->right->key, largest_key) < 0)) {
                if (largest_family != NULL)
                    generic_vector_destroy(&largest_family); // Deallocate the previous largest_family
                largest_family = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);
                for (int i = 0; i < generic_vector_get_size(temp); i++)
                    generic_vector_push_back(largest_family, generic_vector_at(temp, i));
                largest_key = root->right->key;
            }
            generic_vector_destroy(&temp); // Deallocate the temporary vector
        }

        temp = root->data;
        if (largest_family == NULL || (generic_vector_get_size(temp) > generic_vector_get_size(largest_family)) ||
            (generic_vector_get_size(temp) == generic_vector_get_size(largest_family) && my_string_compare(root->key, largest_key) < 0)) {
            if (largest_family != NULL)
                generic_vector_destroy(&largest_family); // Deallocate the previous largest_family
            largest_family = generic_vector_init_default((void*)my_string_assignment, my_string_destroy);
            for (int i = 0; i < generic_vector_get_size(temp); i++)
                generic_vector_push_back(largest_family, generic_vector_at(temp, i));
            largest_key = root->key;
        }
    }

    if (running_total && root != NULL) {
        my_string_insertion(root->key, stdout);
        printf(" %d\n", generic_vector_get_size(root->data));
    }

    return largest_family;
}