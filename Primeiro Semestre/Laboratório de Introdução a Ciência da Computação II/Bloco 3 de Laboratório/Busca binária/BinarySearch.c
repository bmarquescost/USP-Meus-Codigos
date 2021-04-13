/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa : BUSCA BINÁRIA

    Aluno : Bernardo Marques Costa
    Número USP: 11795551

    Programa que deve implementar a busca binária, a partir de um vetor não ordenado.
    Deve portanto, fazer a ordenação e informar (caso haja) o index de um elemento procurado no array.

*/


#include <stdio.h>
#include <stdlib.h>

// Definindo a constante que corresponde a -1, representando que não existe o elemento no array.
#define NOT_IN_ARRAY -1

// Função cocktail sort de ordenação.
void cocktailsort(int *v, int size);
// Função binary_search que irá executar a busca binária.
int binary_search(int *v, int key, int pos_start, int pos_end);

int main(int argc, char *argv[]){
    
    int key;    // Inteiro correspondente a chave, elemento procurado no array.
    int size;   // Inteiro correspondente ao tamanho do vetor que será dado como entrado.
    
    scanf("%d %d", &size, &key);
    
    // Declarando, alocando e preenchendo o vetor de valores inteiros no qual será realizado a busca.
    int *vector = (int *)calloc(size,sizeof(int));
    for (int i = 0 ; i < size; i++) scanf("%d", &vector[i]);
    
    // Chamando a função que irá realizar a ordenação. 
    cocktailsort(vector, size);

    // Definindo a variável que corresponde a resposta da procura: -1 caso nao haja o elemento ou o valor do index no vetor.
    int answer = binary_search(vector, key, 0, size - 1);

    // Caso a resposta seja NOT_IN_ARRAY a chave não existe no array.
    if (answer == -1) printf("Chave inexistente\n");

    // Caso contrário, teremos a resposta da posição no vetor que armazena o elemento procurado.
    else printf("%d\n", answer);

    // Desalocando a memória Heap utilizada.
    free(vector);

    return 0;
}

/*
    Função cocktailsort:
    Recebe como parâmetro o vetor e o tamanho dele.
    Realiza a ordenação do vetor para que seja possível a realização da busca binária.
*/
void cocktailsort(int *v, int size){

    int flag = 1;   // flag servindo de booleano : 1 -> não ordenado 0-> ordenado

    int start = 0, end = size -1;  // Inteiro que serão correspondentes ao inicio e ao fim da análise (mudarão conforme o laço)

    int i, aux;  // variáveis auxiliares.
    
    // Enquando flag seja 1, ou seja, o vetor ainda não esteja ordenado.
    while(flag){

        flag = 0; // Resetando a flag para novas análises.
        
        // Do início para o fim, será comparado um elemento com o seu seguinte, ocorrendo um swap caso o anterior seja maior que o seu próximo.
        for (i = 0; i < end; i++){
            if(v[i] > v[i+1]){
                aux = v[i+1];
                v[i+1] =v[i];
                v[i] = aux;
                flag = 1;   // Identificando a ocorrência do swap.
            }
        }
        
        // Caso não tenha entrado em nenhum momento na condicional anterior, flag será 0 e o vetor ja estará ordenado. 
        if (!flag) break;
        
        end--;  // O último elemento ja estará ordenado, sendo possível desconsiderá-lo
        
        flag = 0; // Resetando a flag.

        // Do final para o ínicio do vetor, será feita a mesma comparação.
        for (i = end; i >= start; i--){
            if (v[i] > v[i+1]){
                aux = v[i+1];
                v[i+1] = v[i];
                v[i] = aux;
                flag = 1;
            }
        }
        // O primeiro elemento do vetor ja estará ordenado, sendo possível desconsiderá-lo
        start++;
    }   
}


/*
    Função binary_search:
    Realiza a busca binária.
    Recebe como parâmetro o vetor, a chave buscada, a posição inicial (sendo 0 no começo), e a posição final do vetor (correspondente
    a size - 1).
*/
int binary_search(int *v, int key, int pos_start, int pos_end){
    
    // Enquanto a posição inicial de analise seja menor que a posição final de análise.
    while (pos_start <= pos_end){
        
        // Devemos considerar o elemento intermediário, cuja posição é calculada a seguir.
        int middle = pos_start + (pos_end - pos_start)/2;
        
        // Caso o elemento do vetor na posição intermediária seja a chave, então teremos esta a resposta.
        if (v[middle] == key) return middle;
        
        // Caso o valor do elemento na posição intermediária seja maior que a chave buscada (lembrando que o vetor se encontra
        // ordenado), teremos então que a posição final de análise corresponderá a posição intermediária - 1, desconsiderando
        // todos os elementos de posição maiores, já que são todos inteiros maiores que a chave buscada. 
        else if (v[middle] > key) pos_end = middle - 1;
                
        // Analise semelhante é feita para caso o valor intermediário seja menor.
        // A chave se encontra na outra metade do vetor, sendo necessário deslocar a posição inicial para a posição intermediária + 1;
        else  pos_start = middle+1;
    }

    // Caso após a última comparação, em que chegamos a uma pos_start > pos_end não encontramos ainda o valor, significa que ele nao pertence ao vetor.
    return NOT_IN_ARRAY;
}
