#include "avl.h"

int main() {
	AVL pe_de_maconha = avl_create();


	avl_insert(pe_de_maconha, 8);
	avl_print_in_order(pe_de_maconha);

	avl_insert(pe_de_maconha, 5);
	avl_print_in_order(pe_de_maconha);

	avl_insert(pe_de_maconha, 3);
	avl_print_in_order(pe_de_maconha);

	avl_insert(pe_de_maconha, 12);
	avl_print_in_order(pe_de_maconha);

	avl_insert(pe_de_maconha, 15);
	avl_print_in_order(pe_de_maconha);

	avl_insert(pe_de_maconha, 5);
	avl_print_in_order(pe_de_maconha);

	avl_delete(pe_de_maconha);

	return 0;
}