/*
    CIFRA DE CESAR
    ALUNO: Bernardo Marques Costa
    NÚMEROS USP: 11795551

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char* argv []){
    int escolha, chave;                  //Declarando as variáveis inteiras escolha e chave, a primeira correspondente a escolha do usuário quanto criptrografar ou descriptografar.
                                        //enquanto chave corresponde a chave da cifra.

    char mensagem[100], letra, resposta[100];   //Declarando os caracteres e cadeias de caracteres: mensagem que sera escolhida pelo usuário, letra que será auxiliar e o vetor que armazenará a resposta.

    scanf ("%d %d", &escolha, &chave); //Recebendo os inteiro digitados pelo usuário.
    
    //Iteração para armazenar '\0' (NULL) em todas posiçoes dos vetores.
    for (int i = 0; i < 100; i++){
        resposta[i] = 0;
        mensagem[i] = 0;
    }
    scanf (" %[^\n]", mensagem); //Recebendo a mensagem escrita pelo usuário.
    

    //Ocorrerá agora a diferenciação a partir da escolha do usuário quanto a criptografar ou descriptografar a mensagem enviada.


    // 1 corresponde a criptografar a mensagem: 
    if (escolha == 1){
        //Laço de repetição que funcionará da seguinte forma:

        /*
        CASO A LETRA SEJA MINÚSCULA:
        o inteiro j irá variar de 0 até o tamanho da mensagem enviada (strlen(mensagem)), sendo acrescido de 1 unidade no final
        A cada iteração teremos uma letra que recebera o caractere na posição j do vetor mensagem.
        Se o inteiro correspondente da tabela ASCII da letra for maior que o valor do caractere a (97) e menor que o valor do caractere z (122)
        entraremos então na primeira estrutura condicional: a posição j do vetor resposta receberá então o correspondente da tabela ASCII cujo valor é 
        equivalente à soma da letra + a chave escolhida. Aninhado a este primeiro if, teremos a condição de extrapolar o limite, quando letra + chave resulta
        em um valor na tabela ASCII maior que o valor de z (122), dessa forma, para que retorne ao conjunto das letras minusculas (97 - 122) é necessário subtrair
        26 unidades (correspondente as 26 letras existentes no alfabeto).
        */

        /*
        CASO A LETRA SEJA MAIÚSCULA:
        da mesma forma, teremos a iteração de j equivalente ao caso com as letras minúsculas. Contudo, o intervalo de variação ao qual
        está associado o valor na tabela ASCII da letra é equivalente ao intervalo 65 - 90, sendo A e Z os pontos extremos. 
        O caso aninhado também funcionará de uma maneira semelhante.
        
        */
        for (int j = 0; j < strlen(mensagem); j++){                           
            letra = mensagem[j];
            if (letra <= 'z' && letra >= 'a') {
                resposta[j] = letra + chave;
                if (letra + chave > 'z') resposta[j] = letra + chave - 26;
            }
            else if (letra <= 'Z' && letra >= 'A'){
                resposta[j] = letra + chave; 
                if (letra + chave > 'Z') resposta[j] = letra + chave - 26;
            }
            else resposta[j] = letra;
        }
    }


    // 2 corresponde a descriptografar.
    if (escolha == 2){

        /*
        O seguinte laço de repetição é semelhante ao anterior no processo de criptografia.
        É necessário ressaltar a mais importantes diferenças entre as duas iteraçoes: no caso de descriptografar a chave que deve ser
        utilizada é, na verdade, o valor oposto ao da chave utilizada no processo de criptografia, desta forma --> -1 * chave.
        Outra diferença: como nesse caso ocorre a subtração da chave, teremos que supor, no pior dos casos, que a letra será menor 
        que o valor da tabela ASCII de a ou de A (diferenciando nos dois condicionais) ou seja, 97 ou 65 respectivamente. 
        Para corrigir tal problema é necessário, agora, somar 26 unidades para obter a letra correspondente do alfabeto.
        */
        for (int k = 0; k < strlen(mensagem); k++){
            letra = mensagem[k];
            if (letra <= 'z' && letra >= 'a'){
                resposta[k] = letra - chave;
                if (resposta[k] < 'a') resposta[k] = letra - chave + 26;
            }
            else if (letra <= 'Z' && letra >= 'A'){
                resposta[k] = letra - chave;
                if (resposta[k] < 'A') resposta[k] = letra - chave + 26;
            }   
            else resposta[k] = letra;
        }
    }

    //Imprimindo a solução do problema.
    printf ("%s", resposta);
    return 0;
}