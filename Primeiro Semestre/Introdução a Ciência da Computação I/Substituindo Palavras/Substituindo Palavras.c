/*
    ICMC - Instituto de Ciências matemáticas e de Computação
    Curso: Bacharelado em Ciência da Computação

    Programa: SUBSTITUINDO PALAVRAS
    
    Disciplina: Introdução a Ciência da Computação I
    Aluno: Bernardo Marques Costa
    Número USP: 11795551

    Programa que receberá uma palavra a ser buscada em uma frase, a palavra que ira substituí-la e a frase, e realizará
    a substituição da primeira pela segunda, mostrando a frase modificiada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Função readline: 
    Recebe entradas do standard input, escrevendo com  função fgetc em uma string, retornando-a.
    A alocação dinâmica é feita com a função realloc, ocorrendo de acordo com o aumento da entrada do teclado.
*/
char *readline(FILE *stream){
    char *string = NULL;
    int position = 0;
    do {    
        string = (char*) realloc(string, position + 1);
        string[position] = (char) fgetc(stream);
    } while ( string[position++] != '\n' && string[position+1] != '\r' && !feof(stream));
    string[position - 1] = '\0';
    return string;
}

/*
    Função nearbycheck:
    Recebe como parâmetro sentence(frase inicial), old (palavra a ser mudada), p_sentence (posição em que se encontra, na 
    frase inicial, a análise).
    Retornará a flag, que receberá 0 ou 1:
            1 --> a função identifica que a palavra na frase é identica àquela que se deseja substituir: antes e depois dela
                  existem caracteres válidos, como espaços, pontuações, e não outras letras.
            0 --> a palavra obtida na frase não é identica.
*/
int nearbycheck(char *sentence, char *old, int p_sentence){
    int flag = 0, p_old = 0;        //Declarando a flag que será retornada e a posição na palavra que deseja substituir.
    char next;                      //Declarando variavial next que recebera o caractere seguinte da palavra na frase

    // Repetição reconhece a similaridade do caractere na palavra a ser substituida e na palavra analisada na frase, acrescendo
    // tanto a posição na sentença tanto na palavra antiga. 
    // A repetição termina quando as letras forem diferente ou quando chegamos no fim da palavra antiga.
    while (sentence[p_sentence] == old[p_old] && old[p_old] != '\0'){
        p_sentence++;       
        p_old++;            
    }
    
    // Caso todos caracteres da palavra forem encontrada na outra palavra analisada na frase, teremos valores de p_old e
    // strlen(old) iguais.
    if (p_old == strlen(old)) flag = 1;

    next = (char) sentence[p_sentence];  // next recebera o valor correpondente a letra seguinte da palavra
    
    // Caso a flag seja 1, ainda é necessário analisar o caso da letra seguinte da palavara na frase invalidar o processo.
    if (flag == 1){

        // Caso a letra esteja entre os correspondentes ASCII das letras A,Z ou a,z, então a palavra na frase nao é a mesma,
        // sendo necessario retornar a flag como 0.
        if ((next >= 'a' && next <= 'z') || (next >= 'A' && next <= 'Z')) flag = 0;
    }
    
    return flag;
}

/*
    Função createnewstring:
    recebe como argumentos new (nova palavra), newfullstring (nova frase), nletter (numero de letras que a frase nova
    já possui).
    A iteração ocorre a cada letra da palavra substituta, sendo adicionada à frase na posição equivalente a nletter. 
*/
void createnewstring(char *new, char *newfullstring, int nletter){
    int i;
    for (i = 0; new[i] != '\0'; i++){
        newfullstring[nletter] = new[i];
        nletter++;
    }
}
    
/*
    Função cicle:
    Receberá old (palavra que será substituida), new (palavra que substituirá), sentence (frase inicial que será reformulada).
    O programa inteiro se passa nessa função que chama as funções acima.
    Retorna a frase nova completa para a função main.
*/
char* cicle(char *old, char *new, char *sentence){

    int p_sentence = 0, flag = 0, nletter = 0;  // Declarando inteiras as variáveis p_sentence (posição na frase inicial),
                                                // flag (servindo de boleano para realizar a troca ou não), nletter (posição
                                                // na frase nova, que esta sendo construída).

    char *newfullstring = NULL; // Criando e declarando NULL ('\0') a string que sofrerá reallocs e formara a frase final.

    
    // Laço de repetição em que funcionará o codigo de análise da frase incicial e construção da
    // frase nova.
    // Ocorre enquanto não terminar a frase que estamos analisando.
    while (sentence[p_sentence] != '\0'){
        
        flag = 0;
        // Caso encontre uma letra equivalente a letra inicial da palavra que será substituida, sendo ou a primeira letra da
        // frase ou sendo uma letra que vem apos um espaço, chamaremos a função nearbycheck.
        if  (sentence[p_sentence] == old[0] && (sentence[p_sentence - 1] == ' ' || p_sentence == 0)){
            flag = nearbycheck(sentence, old, p_sentence);
        }
        
        // Caso a flag seja 1 (como verdadeira): newfullstring sofrerá um realloc para nletter (já que sofrerá alterações 
        // durante a repetição while) + strlen(new) (para caber a palavra) + 1 (por descargo de consciencia)
        if (flag){
            newfullstring = (char*)realloc(newfullstring, nletter + strlen(new) + 1);
            createnewstring(new, newfullstring, nletter);   // Chamada da função que preenchera a string como a nova palavra
            nletter += strlen(new);         // Acrescimo de nletter do tamanho da palavra nova para que corresponda sempre ao
                                            // tamanho atual da frase.

            p_sentence += strlen(old);      // Acréscimo de p_sentence para indicar que a palavra antiga ja foi somada, então
                                            // o "cursor" irá mover para frente de acordo com o tamanho da palavra substituida
        }

        // Caso flag seja zero (como falsa): newfullstring sofre realloc de nletter + 1, indicando uma posição a mais,
        if (!(flag)){
            newfullstring = (char*)realloc(newfullstring, nletter+1);
            newfullstring[nletter] = sentence[p_sentence];      // A letra da frase antiga será a letra da frase nova
            nletter++;                  // nletter será acrescido de mais uma unidade
            p_sentence++;               // p_sentece será acerscido de mais uma unidade
        }
    }


    newfullstring = (char*)realloc(newfullstring, nletter);     //Reallocando newfullstring para seu tamanho exato.
    newfullstring[nletter] = '\0';              // Finalizando a string com '\0' ou NULL.
    
    return newfullstring;           // Retornando a frase final
}


int main(int argc, char*argv[]){

    //  Apenas declarando a string newsentence (frase nova)
    //  Declarando e recebendo  da função readline as palavras: oldword (palavara que será substituida), newword (palavra 
    //  substituta), fullsentence (frase antiga).
    char *oldword, *newword, *fullsentence, *newsentence;  
    oldword = (char*) readline(stdin);
    newword = (char*) readline(stdin);
    fullsentence = (char*) readline(stdin);

    // newsentence receberá o retorno da função cicle, que forma a sentença final com as palavras substituidas.
    newsentence = cicle(oldword,newword, fullsentence);

    printf("%s", newsentence);

    // Liberando a memória Heap utilzada para armazenar as strings utilizadas.
    free(oldword);
    free(newword);
    free(fullsentence);
    free(newsentence);

    return 0;
}