// Aluno: Bernardo Marques Costa - 11795551

#include <stdio.h>
#include <stdlib.h>

#include "Pokemon.h"
#include "PokeType.h"
#include "PokeDex.h"

#include "avl.h"

// Define de uma função estatica que simplesmente retorna o maior entre dois numeros
#define _max(a,b) (a >= b ? a : b)

struct _node {
    pokemon_t *pokemon;
    NODE *left;
    NODE *right;
    int height;
};

struct _avl {
    NODE *root;
    int num_pokemons;
};

// Função de criação da avl
AVL *avl_create(void) {
    AVL *new_tree = calloc(1, sizeof(AVL));
    return new_tree;
}

// Criação de um nó para a avl
static NODE *_node_create(pokemon_t *pokemon) {
    NODE *newnode = calloc(1, sizeof(NODE));
    newnode->pokemon = pokemon;
    newnode->height = -1;

    return newnode;
}

// Deletar recursivamente os nos da avl
static void _avl_delete_nodes(NODE **root) {
    if(*root != NULL) {
        _avl_delete_nodes(&(*root)->left);
        _avl_delete_nodes(&(*root)->right);
        
        free(*root);
        *root = NULL;
    }
}

// Função de destruição da avl inteira
void avl_delete(AVL **tree) {
    if(*tree != NULL) {
        _avl_delete_nodes(&(*tree)->root);
        free(*tree);
        *tree = NULL;
    }
}

// Função de calculo da altura de um nó
static int _avl_node_height(NODE *root) {
    if(root == NULL) return -1;
    int left_height = _avl_node_height(root->left) + 1;
    int right_height = _avl_node_height(root->right) + 1;

    return _max(left_height, right_height);
}

// Função que retorna a altura de um nó
int avl_height(NODE *root) {
    if(root == NULL) return -1;
    return root->height;
} 

// Função que informa o fator de balanceamento de um nó 
static int _avl_balance_factor(NODE *root) {
    if(root == NULL) return 0;

    int left_height = avl_height(root->left);
    int right_height = avl_height(root->right);

    return left_height - right_height;
}

// Rotação para a direita
static NODE *_avl_rotate_to_right(NODE *desb) {
    NODE *new_root = desb->left;
    desb->left = new_root->right;
    new_root->right = desb;

    desb->height = _max(_avl_node_height(desb->left), _avl_node_height(desb->right)) + 1;
    new_root->height = _max(_avl_node_height(new_root->left), _avl_node_height(new_root->right)) + 1;

    return new_root;
}

// Rotação para a esquerda
static NODE *_avl_rotate_to_left(NODE *desb) {
    NODE *new_root = desb->right;
    desb->right = new_root->left;
    new_root->left = desb;

    desb->height = _max(_avl_node_height(desb->right), _avl_node_height(desb->left)) + 1;
    new_root->height = _max(_avl_node_height(new_root->right), _avl_node_height(new_root->left)) + 1;

    return new_root;
}

// Rotação para a esquerda e logo em seguida para a direita
static NODE *_avl_rotate_left_right(NODE *desb) {
    desb->left = _avl_rotate_to_left(desb->left);
    return _avl_rotate_to_right(desb);
}

// Rotação para a direita e logo em seguida para a esquerda
static NODE *_avl_rotate_right_left(NODE *desb) {
    desb->right = _avl_rotate_to_right(desb->right);
    return _avl_rotate_to_left(desb);
}

// Função de recursiva inserção de pokemons na avl, leva em consideração o HP dos pokemons (HPs unicos)
static NODE *_avl_insert_recursive(NODE *root, pokemon_t *pokemon, int *insert) {
    if(root == NULL) {
        root = _node_create(pokemon);
        *insert = 1;
    }

    if(pokemon->hp > root->pokemon->hp) {
        root->right = _avl_insert_recursive(root->right, pokemon, insert);

        if(_avl_balance_factor(root) < -1) {
            if(pokemon->hp > root->right->pokemon->hp) root = _avl_rotate_to_left(root);
            else root = _avl_rotate_right_left(root);
        }
    }
    
    else if(pokemon->hp < root->pokemon->hp) {
        root->left = _avl_insert_recursive(root->left, pokemon, insert);

        if(_avl_balance_factor(root) > 1) {
            if(pokemon->hp < root->left->pokemon->hp) root = _avl_rotate_to_right(root);
            else root =_avl_rotate_left_right(root);
            
        }
    }

    root->height = _max(_avl_node_height(root->left), _avl_node_height(root->right)) + 1;

    return root;
}

// Função base de inserção
void avl_insert_pokemon(AVL *tree, pokemon_t *pokemon) {
    if(tree == NULL || pokemon == NULL) return;

    int insert = 0;
    tree->root = _avl_insert_recursive(tree->root, pokemon, &insert);
    if(insert) tree->num_pokemons++;

}

// Print em recursao pre ordem da avl
static void _avl_print_pre_order(NODE *root) {
    if(root != NULL) {
        printPokemon(root->pokemon);
        _avl_print_pre_order(root->left);
        _avl_print_pre_order(root->right);
    }
}

// Função base poara print em pre ordem da avl
void avl_print_pre_order(AVL *poketree) {
    if(poketree != NULL) 
        _avl_print_pre_order(poketree->root);
}

// Print em recursao em ordem
static void _avl_print_in_order(NODE *root) {
    if(root != NULL) {
        _avl_print_in_order(root->left);
        printPokemon(root->pokemon);
        _avl_print_in_order(root->right);
    }
}

// FUnção base para print em ordem
void avl_print_in_order(AVL *poketree) {
    if(poketree != NULL) 
        _avl_print_in_order(poketree->root);
}

// Print em recursao pos ordem
static void _avl_print_pos_order(NODE *root) {
    if(root != NULL) {
        _avl_print_pos_order(root->left);
        _avl_print_pos_order(root->right);
        printPokemon(root->pokemon);
    }
}

// Função base para print em pos ordem
void avl_print_pos_order(AVL *poketree) {
    if(poketree != NULL) 
        _avl_print_pos_order(poketree->root);
}