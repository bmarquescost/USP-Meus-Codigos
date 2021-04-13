#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

#define _max(a,b) (a >= b ? a : b)

struct _node {
    int content;
    Node *left;
    Node *right;
    int height;
};

struct _avl {
    Node *root;
};

Avl *avl_create(void) {
    Avl *new_avl = calloc(1, sizeof(Avl));
    return new_avl;
}

static void _node_destruct(Node **node) {
    if(*node != NULL) {
        _node_destruct(&(*node)->left);
        _node_destruct(&(*node)->right);
        free(*node);
        *node = NULL;
    }
}

void avl_destruct(Avl **avl_tree) {
    if(*avl_tree == NULL) return;
    _node_destruct(&(*avl_tree)->root);
    free(*avl_tree);
    avl_tree = NULL;
}   

static Node *avl_create_node(int content) {
    Node *new_node = calloc(1,sizeof(Node));
    new_node->content = content;
    new_node->height = -1;

    return new_node;
}

static int avl_discover_height(Node *root) {
    if(root == NULL) return -1;
    int left_height = avl_discover_height(root->left) + 1;
    int right_height = avl_discover_height(root->right) + 1;

    return _max(left_height, right_height);
}

int avl_height(Node *node) {
    if(node == NULL)
        return -1;
    else
        return node->height;
}

static int get_balancing(Node *node) {
    int left_height = avl_height(node->left);
    int right_height = avl_height(node->right);

    return left_height - right_height;
}


static Node *rotate_right(Node *desbalanced) {
    // Rotation
    Node *new_root = desbalanced->left;
    desbalanced->left = new_root->right;
    new_root->right = desbalanced;

    // Updating heights
    desbalanced->height = _max(avl_discover_height(desbalanced->left), avl_discover_height(desbalanced->right)) + 1;
    new_root->height = _max(avl_discover_height(new_root->right), avl_discover_height(new_root->left)) + 1;

    return new_root;
}

static Node *rotate_left(Node *desbalanced) {
    // Rotation
    Node *new_root = desbalanced->right;
    desbalanced->right = new_root->left;
    new_root->left = desbalanced;

    // Updating heights
    desbalanced->height = _max(avl_discover_height(desbalanced->left), avl_discover_height(desbalanced->right)) + 1;
    new_root->height = _max(avl_discover_height(new_root->right), avl_discover_height(new_root->left)) + 1;

    return new_root;
}

static Node *rotate_left_right(Node *desbalanced) {
    desbalanced->left = rotate_left(desbalanced->left);
    return rotate_right(desbalanced);
}

static Node *rotate_right_left(Node *desbalanced) {
    desbalanced->right = rotate_right(desbalanced->right);
    return rotate_left(desbalanced);
}

static Node *_avl_insert(Node *root, int key) {
    if(root == NULL)
        root = avl_create_node(key);
    
    else if(key > root->content) {
        root->right = _avl_insert(root->right, key);

        if(avl_height(root->left) - avl_height(root->right) == -2) {
            if(key > root->right->content)
                root = rotate_left(root);
            else   
                root = rotate_right_left(root);
        }
    }
    else if(key < root->content) {
        root->left = _avl_insert(root->left, key);
        
        if(avl_height(root->left) - avl_height(root->right) == 2) {
            if(key < root->left->content)
                root = rotate_right(root);
            else
                root = rotate_left_right(root);
        }
    }

    root->height = _max(avl_height(root->left), avl_height(root->right)) + 1;

    return root;
}

void avl_insert(Avl *avl_tree, int key) {
    if(avl_tree == NULL)
        return;
    else {
       if(avl_tree) avl_tree->root = _avl_insert(avl_tree->root, key);
        else avl_tree->root = avl_create_node(key);
    }
}

static Node *get_min_value_node(Node *root) {
    Node *current = root;
    
    while(current->left != NULL)
        current = current->left;
    
    return current;
}

static Node *_avl_remove_node(Node *root, int key) {
    if(root == NULL)
        return NULL;
    
    if(key < root->content)
        root->left = _avl_remove_node(root->left, key);
    
    else if(key > root->content)
        root->right = _avl_remove_node(root->right, key);

    else {
        if((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            
            if(temp == NULL) {
                temp = root;
                root = NULL;
            }
            
            else 
                *root = *temp;
            
            free(temp);
        } 
        
        else {
            Node *temp = get_min_value_node(root->right);
            root->content = temp->content;
            root->right = _avl_remove_node(root->right, temp->content);
        }
    }

    if(root == NULL)
        return root;
    
    root->height = _max(avl_height(root->left),avl_height(root->right)) + 1;

    int balancing = get_balancing(root);
    
    if(balancing > 1 && key >= root->left->content)
        return rotate_right(root);
    if(balancing > 1 && key < root->left->content) 
        return rotate_left_right(root);
    if(balancing < -1 && key < root->right->content)
        return rotate_left(root);
    if(balancing < -1 && key >= root->right->content)
        return rotate_right_left(root);

    return root;
}

void avl_remove(Avl *avl_tree, int key) {
    if(avl_tree == NULL)
        return;
    avl_tree->root = _avl_remove_node(avl_tree->root, key);
}

static void avl_print_pre_order(Node *root) {
	if(root != NULL) {
		printf("%d", root->content);
        printf("(");
		avl_print_pre_order(root->left);
		printf(",");
		avl_print_pre_order(root->right);
		printf(")");
	}
	else printf("null");
}

void avl_print(Avl *tree) {
    avl_print_pre_order(tree->root);
    printf("\n");
}