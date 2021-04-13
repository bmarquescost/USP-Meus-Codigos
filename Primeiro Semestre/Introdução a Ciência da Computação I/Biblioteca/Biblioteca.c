/*
    ICMC - Instituto de Ciências matemáticas e de Computação
    Curso: Bacharelado em Ciência da Computação

    Programa: BIBLIOTECA
    
    Disciplina: Introdução a Ciência da Computação I
    Aluno: Bernardo Marques Costa
    Número USP: 11795551

    Programa que funcionará como um auxilio de uma biblioteca, receberá o numero de livros do acervo, o nome de cada livro 
    seguido do tempo de alguel em dias.
    A operação 1 será chamada para requisitar um livro.
    A operação 2 será chamada para mostrar quais livros estão sobre a posse do usuário, juntamente com o tempo de aluguel.
    A operação 3 retornará um livro.
    A operação 4 finalizará o programa. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// A struct definida como o tipo DADOS armazenará o titulo de cada obra, seu tempo de alguel e seu estado (sendo 1 para alugado
// e 0 para não alugado).
typedef struct {
    char *titulo;
    int tempo;
    int estado;
} DADOS;

// A struct definida como tipo ALUGADOS armazenará cada um dos livros alugados, além do número total de algueis.
typedef struct {
    DADOS *obra;
    int n_alugados;
} ALUGADOS;

/*
    Função readLine:
    Recebe como parâmetro o standart input (teclado), e retorna o ponteiro para o endereço em que se inicia a string na
    memória heap.
*/
char *readLine(FILE *stream){
    char *string = NULL;
    int pos = 0;
    do{
        string = (char*)realloc(string, pos+1);
        string[pos] = fgetc(stream);
        pos++;
    } while(string[pos-1] != '\n' && string[pos-1] != '\r' && !feof(stream));
    string[pos-1] = '\0';
    return string;
}

/*
    Função pegarlivro:
    Recebe como parametros:
        -> acervo: passada como valor; estrutura que armazena os livros da biblioteca, seus estados e tempos de alguel.
        -> alugados: passada por referencia; estrutura que armazena os livros que estão alugados.
        -> nlivros: numero total de livros que a biblioteca possui.
*/
void pegarlivro(DADOS *acervo, ALUGADOS *alugados, int nlivros){
    char *livro_procurado = NULL;       // String que será o livro procurado pelo usuário
    int flag = 0;                       // Variável que indicará a presença ou não do livro
    int encontrado = -1;                // Variável que define qual a posição do livro no vetor acervo.
    printf("Digite o livro que voce procura:\n");
    
    livro_procurado = readLine(stdin);
    
    // Percorrendo o vetor de struct acervo e comparando o titulo de cada um de seus index ao livro procurado
    // Caso flag seja  0 (ou seja, os nomes sejam identicos) encontrado receberá i -> index do livro no acervo.
    for (int i = 0; i < nlivros; i++){
        flag = strcmp(acervo[i].titulo, livro_procurado);
        if (!flag) encontrado = i;
    }

    // Caso haja um livro com tal nome, encotnrado será diferente de -1.
    if (encontrado != -1){
        if (alugados->n_alugados < 10){                     // Assegurando que existem menos de 10 livros alugados
            if(acervo[encontrado].estado == 0){             // Assegurando que o já nao está alugado           
                acervo[encontrado].estado = 1;              // Alterando o estado do livro para alugado.
                printf("%s alugado com sucesso\n", acervo[encontrado].titulo);
                
                // Armazenando no vetor de ponteiro do tipo DADOS em alugados o ponteiro para o livro de acervo que foi alugado
                alugados->obra[alugados->n_alugados] = acervo[encontrado];  
                alugados->n_alugados++;     // Incrementando o número de livros que estão alugados no momentos.
            }
            else printf("Livro ja alugado\n");
        }
        else printf("Voce ja tem 10 livros alugados\n");
    } 
    else printf("Livro nao encontrado na biblioteca\n");

    free(livro_procurado);
}
/*
    Função mostrarAlugados
    Recebe como parâmetro:
        -> livros: estrutura que armazena todos os livros alugados e o número de livros alugados.
*/
void mostrarAlugados(ALUGADOS livros){
    if (livros.n_alugados == 0) printf("Voce nao tem livros alugados\n");
    else {
        printf("Voce tem %d livro(s) alugado(s)\n", livros.n_alugados);
        for(int i = 0; i < livros.n_alugados; i++){             // Percorre o vetor dos livros alugados. 
            printf("Livro nome: %s\n", livros.obra[i].titulo);
            printf("Devolve-lo daqui %d dias\n", livros.obra[i].tempo);
        }
    }
}

/*
    Função devolverLivro:
    Recebe como parâmetro:
        -> livros: estrutura com os livros algados.
        -> nlivros: número total de livros na bilbioteca.
*/
void devolverLivro(ALUGADOS *livros, DADOS *acervo, int nlivros){
    
    char *retornado = NULL;     // String que armazena o livro que se deseja retornado.
    int flag = 0;
    printf("Digite o livro que deseja devolver:\n");
    retornado = readLine(stdin);
    int i = 0;

    // Percorrendo todos os titulos dos livros alugados e comparando com a obra procurada, recebendo 1 e parando caso
    // encontrada a obra que se deseja devolver
    for (i = 0; i < livros->n_alugados; i++){
        if (strcmp(retornado, livros->obra[i].titulo) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) printf("Voce nao possui esse livro\n");
    else{
        printf("Livro %s foi devolvido com sucesso\n", livros->obra[i].titulo);
        
        livros->obra[i].estado = 0;        // Alterando o estado do livro que acaba de ser retornado para 0

        for(int i = 0; i < nlivros; i++){
            if (strcmp(retornado, acervo[i].titulo) == 0){
                acervo[i].estado = 0;
                break;
            }
        }

        // Refazedo o vetor dos livros alugados, mantendo a ordem dos que haviam sido alugado antes do livros retornado
        // e passando uma unidade para frente os livros que foram alugados posteriormente.
        for(int i = 0, j = 0; i < livros->n_alugados; i++){
            if(livros->obra[i].estado == 1) {
                livros->obra[j] = livros->obra[i];
                j++;
            }
        }
        livros->n_alugados--;  // Diminuindo o numero total de livros alugados.
    }   
    free(retornado);    // Liberando o espaço na memória Heap que foi utilizado para a string do livro retornado.
}


int main(int argc, char *argv[]){
    
    int numero_livros = 0; 
    scanf("%d\r\n", &numero_livros);  // Lendo o numero de livros da biblioteca e excluindo do buffer o \r e o \n.

    DADOS *acervo;
    acervo = (DADOS*)calloc(numero_livros, sizeof(DADOS));      // Alocando na heap o espaço para todos os livros e seus dados.

    // Recebendo as entradas dos nomes e seus tempos de alguel.
    for (int i = 0; i<numero_livros; i++){
        acervo[i].titulo = readLine(stdin);
        scanf("%d\r\n", &acervo[i].tempo);
    }

    // Criando e alocando a variável livros_alugados (com o tamanho maximo de 10) que armazena uma string de DADOS, possuindo
    // entao todos dados cada livro, alem do numero de livros alugados.  
    ALUGADOS livros_alugados;
    livros_alugados.obra = (DADOS*)calloc(10,sizeof(DADOS));
    livros_alugados.n_alugados = 0;
    
    int comando = 0;
    do {
        scanf("%d\r\n", &comando); //Recebendo o comando, que rege a operação a ser seguida.
        switch (comando){
            case 1: 
                pegarlivro(acervo, &livros_alugados, numero_livros);
                break;
            case 2: 
                mostrarAlugados(livros_alugados);
                break;
            case 3: 
                devolverLivro(&livros_alugados, acervo, numero_livros);
                break;
            case 4: 
                printf("Programa finalizado\n");
                break;
        }
    }while(comando != 4);  // O programa finaliza quando a entrada é 4.

    // Liberando espaço da memória Heap de todas variáveis que utilizaram-na.
    for (int i = 0; i < numero_livros; i++){
        free(acervo[i].titulo);
    }
    free(acervo);
    free(livros_alugados.obra);

    return 0;
}