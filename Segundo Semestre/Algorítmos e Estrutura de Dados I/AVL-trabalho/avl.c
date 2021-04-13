#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avl.h"

#define _max(a, b) (a >= b ? a : b) 

typedef struct node * Node;
struct node {
	int content;
	Node left;
	Node right;
};

struct avl {
	Node root;
};

static Node _node_create(int content) {
	Node new_node = malloc(sizeof(struct node));

	new_node->content = content;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

static void _node_delete(Node node) {
	free(node);
}

AVL avl_create() {
	AVL new_avl = malloc(sizeof(struct avl));
	new_avl->root = NULL;

	return new_avl;
}

static void _avl_delete(Node cur_node) {
	if (cur_node == NULL) return;

	_avl_delete(cur_node->left);
	_avl_delete(cur_node->right);

	_node_delete(cur_node);
}

void avl_delete(AVL tree) {
	assert(tree != NULL);

	_avl_delete(tree->root);
	free(tree);
}

static int _avl_get_height(Node root) {
	if (root == NULL) return -1;

	int l_height = _avl_get_height(root->left) + 1;
	int r_height = _avl_get_height(root->right) + 1;

	return _max(l_height, r_height);
}

static int _node_get_balancing(Node cur_node) {
	int l_height = _avl_get_height(cur_node->left);
	int r_height = _avl_get_height(cur_node->right);

	return l_height - r_height;
}

static Node _left_rotate(Node node) {
	Node new_root = node->right;
	Node left_sub_tree = new_root->left;

	new_root->left = node;
	node->right = left_sub_tree;

	return new_root;
}

static Node _right_rotate(Node node) {
	Node new_root = node->left;
	Node right_sub_tree = new_root->right;

	new_root->right = node;
	node->left = right_sub_tree;

	return new_root;
}

static Node _left_right_rotate(Node node) {
	node->left = _left_rotate(node->left);
	return _right_rotate(node);
}

static Node _right_left_rotate(Node node) {
	node->right = _right_rotate(node->right);
	return _left_rotate(node);
}

static Node _avl_balance(Node cur_node, int item, int balancing) {
	if (balancing > 1 && item < cur_node->left->content) {
		return _right_rotate(cur_node);
	}
	else if (balancing < -1 && item > cur_node->right->content) {
		return _left_rotate(cur_node);
	}
	else if (balancing > 1 && item > cur_node->left->content) {
		return _left_right_rotate(cur_node);
	}
	else if (balancing < -1 && item < cur_node->right->content) {
		return _right_left_rotate(cur_node);
	}

	return cur_node;
}

static Node _avl_insert(Node cur_node, int item) {
	if (cur_node == NULL) return _node_create(item);

	if (item < cur_node->content) cur_node->left = _avl_insert(cur_node->left, item);
	else if (item > cur_node->content) cur_node->right = _avl_insert(cur_node->right, item);

	int balancing = _node_get_balancing(cur_node);
	if (balancing < -1 || balancing > 1) return _avl_balance(cur_node, item, balancing);

	return cur_node;
}

void avl_insert(AVL tree, int item) {
	assert(tree != NULL);

	if (tree->root) tree->root = _avl_insert(tree->root, item);
	else tree->root = _node_create(item);
}

// void avl_remove(AVL tree, int item) {
// 	assert(tree != NULL);

// }

// bool avl_search(AVL tree, int item) {
// 	assert(tree != NULL);

// }

static void _node_print(Node node) {
	printf("%d ", node->content);
}

static void _avl_print_pre_order(Node cur_node) {
	if (cur_node == NULL) return;

	_node_print(cur_node);
	_avl_print_pre_order(cur_node->left);
	_avl_print_pre_order(cur_node->right);
}

void avl_print_pre_order(AVL tree) {
	assert(tree != NULL);

	printf("[ ");
	_avl_print_pre_order(tree->root);
	printf("]\n");
}

// static void _avl_print_in_order(Node cur_node) {
// 	if (cur_node == NULL) return;

// 	_avl_print_in_order(cur_node->left);
// 	_node_print(cur_node);
// 	_avl_print_in_order(cur_node->right);
// }

void imprimir_arvore(Node raiz) {
	if(raiz != NULL) {
		printf("%d", raiz->content);
		printf("(");
		imprimir_arvore(raiz->left);
		printf(",");
		imprimir_arvore(raiz->right);
		printf(")");
	}
	else printf("null");
}

void avl_print_in_order(AVL tree) {
	assert(tree != NULL);

	imprimir_arvore(tree->root);
	printf("\n");
}

static void _avl_print_pos_order(Node cur_node) {
	if (cur_node == NULL) return;

	_avl_print_pos_order(cur_node->left);
	_avl_print_pos_order(cur_node->right);
	_node_print(cur_node);
}

void avl_print_pos_order(AVL tree) {
	assert(tree != NULL);

	printf("[ ");
	_avl_print_pos_order(tree->root);
	printf("]\n");
}