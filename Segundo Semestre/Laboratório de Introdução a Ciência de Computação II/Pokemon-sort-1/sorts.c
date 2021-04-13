// Bernardo Marques Costa - 11795551
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "sorts.h"

// Função auxiliar de comparaçao entre os pokemons, passando qual campo sera a referencia
static int compare(pokemon_t *poke1, pokemon_t *poke2, char *field_compared) {
    if(strcmp(field_compared, "dexNumber") == 0)
        return poke1->dexNumber - poke2->dexNumber;

    else if(strcmp(field_compared, "atk") == 0)
        return poke1->atk - poke2->atk;

    else if(strcmp(field_compared, "mainType") == 0)
        return poke1->mainType - poke2->mainType;

    return -404;
} 

static void max_heapify(pokemon_t **pokelist, int index, int N, char *field_compared) {
    int largest = index;
    int left_child = index * 2 + 1;
    int right_child = index * 2 + 2;

    if(left_child < N && compare(pokelist[left_child], pokelist[largest], field_compared) > 0)
        largest = left_child;
    
    if(right_child < N && compare(pokelist[right_child], pokelist[largest], field_compared) > 0)
        largest = right_child;

    if(largest != index) {
        pokemon_t *tmp = pokelist[index];
        pokelist[index] = pokelist[largest];
        pokelist[largest] = tmp;

        max_heapify(pokelist, largest, N, field_compared);
    }
}

static void heapsort(pokemon_t **pokelist, int num_pokemons, char *field_compared) {
    for(int i = num_pokemons/2 - 1; i >= 0; --i) 
        max_heapify(pokelist, i, num_pokemons, field_compared);

    
    for(int i = num_pokemons - 1; i >= 0; --i) {
        pokemon_t *tmp = pokelist[0];
        pokelist[0] = pokelist[i];
        pokelist[i] = tmp;

        max_heapify(pokelist, 0, i, field_compared);
    }
}

static int random_pivot(int low, int high) {
    return (int) (rand()%(high - low) + low);
}

static void quicksort(pokemon_t **pokelist, int low, int high, char *field_compared) {
    if(low >= high) return;

    int pivot = random_pivot(low, high);

    // Swaping pivot to first position
    pokemon_t *tmp = pokelist[pivot];
    pokelist[pivot] = pokelist[low];
    pokelist[low] = tmp;

    pivot = low;
    int i = low + 1;
    int j = high;

    while(i <= j) {
        while(i <= high && compare(pokelist[i], pokelist[pivot], field_compared) <= 0) ++i;
        while(compare(pokelist[j], pokelist[pivot], field_compared) > 0) --j;

        if(j >= i) {
            tmp = pokelist[i];
            pokelist[i] = pokelist[j];
            pokelist[j] = tmp;
        }
    }

    tmp = pokelist[pivot];
    pokelist[pivot] = pokelist[j];
    pokelist[j] = tmp;

    pivot = j;
    
    quicksort(pokelist, low, pivot - 1, field_compared);
    quicksort(pokelist, pivot + 1, high, field_compared);
}

static void insertion_sort(pokemon_t **pokelist, int low, int high, char *field_compared) {
    for(int i = low + 1; i <= high; ++i) {
        pokemon_t *tmp = pokelist[i];
        int j = i - 1;
        while(j >= low && compare(tmp, pokelist[j], field_compared) < 0) {
            pokelist[j + 1] = pokelist[j];
            j--;
        }

        pokelist[j + 1] = tmp;
    }
}

void merge(pokemon_t **pokelist, int low, int mid, int high, char *field_compared) {
    int left_size = mid - low + 1;
    int right_size = high - mid;

    pokemon_t **left = malloc(left_size * sizeof(pokemon_t *));
    pokemon_t **right = malloc(right_size * sizeof(pokemon_t *));

    for(int i = 0; i < left_size; ++i)
        left[i] = pokelist[low + i];
    
    for(int i = 0; i < right_size; ++i)
        right[i] = pokelist[mid + i + 1];
    
    int i = 0;
    int j = 0;
    int k = low;

    while(i < left_size && j < right_size) {
        if(compare(left[i], right[j], field_compared) <= 0) 
            pokelist[k] = left[i++];
        
        else 
            pokelist[k] = right[j++];
        
        ++k;
    }
    

    while(i < left_size)
        pokelist[k++] = left[i++];
    
    while(j < right_size)
        pokelist[k++] = right[j++];

    free(left);
    free(right);
}


int min(int first_value, int second_value) {
    if(first_value < second_value)
        return first_value;
    return second_value;
}


static void timsort(pokemon_t **pokelist, int num_pokemons, char *field_compared) {
    for(int i = 0; i < num_pokemons; i += 32)
        insertion_sort(pokelist, i, min( i + 31, num_pokemons - 1), field_compared);

    for(int size = 32; size < num_pokemons; size = 2 * size) {
       
        for(int left_size = 0; left_size < num_pokemons; left_size += 2 * size) {
            int mid = left_size + size - 1;
            int right = min((left_size + 2 * size - 1), num_pokemons - 1);

            merge(pokelist, left_size, mid, right, field_compared);
        }
    }

}

// Função de chamada para que a lista de pokemons seja ordenada, passando qual campo será comparado e qual o algoritmo de comparação será executado
void pokelist_sort(pokemon_t **pokelist, int num_pokemons, int sort_algoritm, char *field_compared) {
    if(field_compared == NULL || pokelist == NULL) return;

    
    if(sort_algoritm == 1)
        quicksort(pokelist, 0, num_pokemons - 1, field_compared); 
    
    else if(sort_algoritm == 2)
        heapsort(pokelist, num_pokemons, field_compared);

    else if(sort_algoritm == 3)
        timsort(pokelist, num_pokemons, field_compared);
}