/*
    JOGO DA VELHA
    ALUNO: Bernardo Marques Costa
    NÚMERO USP : 11795551
    ICMC - Bacharelado em Ciências de Computação

    Código do famigerado jogo da velha com alocação dinâmica para guardar a matriz do jogo.
*/

#include <stdio.h>
#include <stdlib.h>

//Função que recebe a matriz que presentado tabuleiro, e printa o tabuleiro na tela toda vez que é chamada, atualizando o jogo.
void printTab (char **tab){
    printf ("%c   |%c   |%c   |\n", tab[0][0], tab[0][1], tab[0][2]);
    printf ("----+----+-----\n");
    printf ("%c   |%c   |%c   |\n", tab[1][0], tab[1][1], tab[1][2]);
    printf ("----+----+-----\n");
    printf ("%c   |%c   |%c   |\n", tab[2][0], tab[2][1], tab[2][2]);
    printf ("----+----+-----\n");
}

//Função que verifica qual é o jogador da vez e recebe o número correspondente de sua jogada, retornando para a função main esta escolha.
int jogada(int vez){
    int escolha;
    if (vez%2 != 0){
        printf ("Escolha um número para jogar, jogador X!\n");
    }
    else printf ("Escolha um número para jogar, jogador O!\n");
    scanf("%d", &escolha);

    return escolha;

}

/* Função checagem:
    Recebe como parâmetros o tabuleiro e a escolha do jogador
    Verifica então se a jogada é possível ou não: se o número pertence ao intervado entre 1 e 9, e se a posição desejada está vaga.
    retorna uma variável boleano_verificar para a main, que representaria de certa forma um true ou false, que permite uma repetição caso os valores
    enviados representem valores invalidos.
*/
int checagem(int escolha, char **tabuleiro){
    int boleano_verificar = 1;
    if (escolha < 1 || escolha > 9) {
        boleano_verificar = 0;
    }
    else if (escolha >= 1 && escolha <= 3){
        if (*(*(tabuleiro + 0) + escolha - 1) == 'X' || *(*(tabuleiro + 0) + escolha - 1) == 'O') boleano_verificar = 0;
    }
    else if (escolha >= 4 && escolha <= 6){
        if (*(*(tabuleiro+ 1) + escolha - 4) == 'X' || *(*(tabuleiro + 1) + escolha - 4) == 'O') boleano_verificar = 0;
    }
    else if (escolha >= 7 && escolha <= 9){
        if (*(*(tabuleiro + 2) + escolha - 7) == 'X' || *(*(tabuleiro + 2) + escolha - 7) == 'O') boleano_verificar = 0;
    }
    return boleano_verificar;
}

/*
    Função newtab:
    Recebe como parâmetros a escolha, o turno (vez de qual jogador) e o próprio tabuleiro.
    A estrutura de repetição serve para que dado o momento que a iteração chegue no elemento da matriz que foi selecionado para colocar o simbolo
    de X ou O, será então feita a troca dos valores em char.
    obs: esc + 48 é resultado de uma conversão da escolha em inteiro para um valor equivalente do tipo char na tabela ASCII ('1' -->  49)
    A função retorna o ponteiro do tipo duplo tabuleiro.
*/
char** newtab(int esc, int vez, char **tabuleiro){
    char simbolo;
    if (vez == 1){
        simbolo = 'X';
    }    
    else simbolo = 'O';

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if ((esc + 48) == tabuleiro[i][j])
                tabuleiro[i][j] = simbolo;
        }
    }
    return tabuleiro;
} 

/*
    Função teste:
    Recebe o tabuleiro como parâmetro
    Verifica horizontalemnte, verticalemnte e diagonalmente se todos os simbolos são iguais.
    Caso algum deste casos seja verdadeiro, a variável temp inicializada com 0 receberá 1 e será retornada a função main para declarar o fim do jogo.
    O aux inicializado com 0 serve para contabilizar o número de jogadas, e para  que assim, ao chegar em 9 (máximo de jogadas), atribui -1 à temp, que será 
    retornada a função declarando que o jogo acabou, dando velha.  
*/
int teste (char **tabuleiro){
    int temp = 1, aux = 0;
    for (int i = 0; i < 3; i++){
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) temp = 0; 
    }
    for (int j = 0; j < 3; j++){
        if (tabuleiro[0][j] == tabuleiro[1][j] && tabuleiro[1][j] == tabuleiro[2][j]) temp = 0;
    }
    if ((tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[2][2] == tabuleiro[1][1]) || ( tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2] )) temp = 0;
    
    if (temp == 0) temp = 0;
    else {
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (tabuleiro[i][j] == 'X' || tabuleiro[i][j] == 'O') aux++;
            }
        }
    }
    if (aux == 9) temp = -1;
    return temp;
}

/*
    Função ganhador:
    Recebe a variável boleano, que representa o resultado do jogo (velha ou vitória de algum dos jogadores).
    Também recebe a variável vez como parâmetro: declarar qual jogador (X ou O) que venceu a partida em caso de não ter acabado em empate.
*/
void ganhador(int bool, int vez){
    char auxiliar;
    if (vez == 1) auxiliar = 'X';
    else auxiliar = 'O';
    
    if (bool == 0) printf ("Fim do jogo! O jogador %c venceu!\n", auxiliar);
    else printf ("Deu velha!");
}



int main(int argc, char* argv []){

    /* 
    Declarando a variável ponteiro duplo do tipo char que será o tabuleiro do jogo 
    O armazenamento desta é feito na memória Heap, sendo feito um laço de iteração para o processo de alocação dinâmica.
    */
    char **tabuleiro;
    tabuleiro = (char **)calloc(3,sizeof(char*));
    for (int i = 0; i < 3; i++){
        tabuleiro[i] = (char*)calloc(3, sizeof(char));
    }
    
    //Preenchendo a matriz com os elementos do tipo char 1,2,3,4,5,6,7,8,9 em suas respectivas posições na matriz. 
    char preencher = '1';
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            tabuleiro[i][j] = preencher;
            preencher ++;
        }
    }

    //Declarando as variáveis que servirão para acompanhar o jogo.
    int vez = 1, boleano = 1, check = 0, escolha, printar_titulo = 0;

    //Estrutura de repetição do jogo, acontece enquanto boleano for 1, o que indica que o jogo ainda está acontecendo.
    while (boleano == 1){
        vez = (vez % 2)? 1 : 2;
        printTab(tabuleiro);
        if (printar_titulo == 0) printf ("Jogo da velha!\n");
        printar_titulo = 1;
        escolha = jogada(vez);
        check = checagem(escolha, tabuleiro);
        if (check == 0){
            while (check == 0){
                    printf ("Jogada inválida! Escolha outra casa.\n");
                    scanf("  %d", &escolha);
                    check = checagem(escolha, tabuleiro);
            }
        }
        newtab (escolha, vez, tabuleiro);
        boleano = teste(tabuleiro);
        vez ++;
    }

    //Subtraindo 1 da variável vez para obter o real vencedor do jogo (caso haja).
    vez--; 

    printTab(tabuleiro);

    //Chamando a função ganhador para printar o resultado final.
    ganhador(boleano, vez);
    

    //Liberando a memória Heap.
    for (int i = 0; i < 3; i++){
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 0;
}