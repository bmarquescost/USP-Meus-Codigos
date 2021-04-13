/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa : MISTURA DE CORES

    Aluno : Bernardo Marques Costa
    Número USP: 11795551

    Programa que receberá dados de uma matriz correspondente a uma palleta de cores, sendo cada linha uma cor.
    Receberá também quais cores serão misturadas e ainda a linha que ocorrerá a mistura, sendo necessário somar a metadade 
    de cada um dos elementos das colunas e cujas linhas sejam equivalente e correspondentes a cada uma das cores.
    A soma será feita também ao valor que ja existe nas posições da linha em que será feita a mistura. 
*/


#include <stdio.h>
#include <stdlib.h>

void receivedata(int **pallete);
void printpallete(int **pallete, int flag);
void changedata(int **pallete, int firstcolor, int seccolor, int palleteline);


int main(int argc, char *argv[]){
    
    int firstcolor;     // Declarando a primeira escolha de cor
    int seccolor;       // Declarando a segudna escolha de cor
    int palleteline;    // Declarando a linha em que ocorrerá a mistura. 
    scanf("%d %d %d", &firstcolor, &seccolor, &palleteline);    // Recebendo os dados.

    int i;
    
    // Declarando a alocando a matriz que contem 6 linhas (6 cores) e cada cor possui 3 colunas (RGB).
    int **pallete = (int**)calloc(6, sizeof(int*));
    for (i = 0; i < 6; i++) pallete[i] = (int*)calloc(3,sizeof(int));

    // Função que recebe os dados da matriz.
    receivedata(pallete);
    
    // Flag que indicará qual a matriz (inicial ou resultante) que deverá ser impressa.
    int flag = 0;
    // Função que imprime os dados.
    printpallete(pallete, flag);
    
    // Função que altera dos dados, misturando as cores.
    changedata(pallete, firstcolor, seccolor, palleteline);
    
    printf("\n");
    flag = 1;
    // Novamente pritando, mas agora a matriz resultante.
    printpallete(pallete,flag);

    // Desalocando a memória Heap utilizada.
    for (i = 0; i < 6; i++) free(pallete[i]);
    free(pallete);

    return 0;
}


/*
    Função receivedata:
    Recebe como parâmetro a matriz.
    Realiza a atribuição de dados elemento a elemento na matriz.
*/
void receivedata(int **pallete){
    int i, j;
    for (i = 0; i < 6; i++){
        for (j = 0 ; j < 3; j++){
            scanf("%d", &pallete[i][j]);
        }
   }
}


/*
    Função printpallete:
    Recebe como parâmetro a matriz das cores e a flag.
    Caso a flag seja 0 -> indicará que é o Start (Matriz inicial);
    Caso a flag seja 1 -> indicará que é o Result (Matriz resultante);
*/
void printpallete(int **pallete, int flag){
    int i;
    if (!flag) printf("Start:\n");
    else printf("Result:\n");
    for(i = 0; i < 6 ; i++){
        printf("Color(%d): [\t%d\t%d\t%d\t]\n", i, pallete[i][0], pallete[i][1], pallete[i][2]);
    }
}


/*
    Função changedata:
    Recebe como parâmetro a matriz, a primeira cor e a segunda cor (correspondentes as respectivas linhas) e a linha em que
    deve ocorrer a mistura.
*/
void changedata(int **pallete, int firstcolor, int seccolor, int palleteline){
    int i;
    for (i = 0; i < 3; i++){
        // Para cada elemento da coluna será adicionada a metadade de cada elemento desta mesma coluna, mas das linhas
        // correspondentes a primeira e a segunda cor selecionadas. 
        pallete[palleteline][i] += pallete[firstcolor][i]/2 + pallete[seccolor][i]/2;
        if (pallete[palleteline][i] > 255) pallete[palleteline][i] = 255;
    }
}