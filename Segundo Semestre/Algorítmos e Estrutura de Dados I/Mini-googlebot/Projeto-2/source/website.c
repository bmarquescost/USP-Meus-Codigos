/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goulart 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "website.h"
#include "util.h"

/*
    Dados do website
*/
struct _website {
    char *nome;
    char *url;
    char **palavras_chaves;
    int codigo;
    int relevancia;
    int num_palavras_chave;
};

/*
    Função website_criar
    Não recebe parâmetros, inicia um novo website e seta seus dados para 0
    Retorna o endereço do novo website criado
*/
WEBSITE *website_criar(){
    WEBSITE *novo_site = NULL;
    novo_site = calloc(1,sizeof(WEBSITE));

    novo_site->codigo = 0;
    novo_site->url = NULL;
    //novo_site->palavras_chaves = NULL;
    novo_site->palavras_chaves = calloc(10, sizeof(char *));
    novo_site->relevancia = 0;
    novo_site->nome = NULL;
    novo_site->num_palavras_chave = 0;

    return novo_site;
}

/*
    Função website_deletar
    Recebe como parâmetro o endereço de um ponteiro para o website que vai ser deletado
    Retorna um booleano conforme for verificada a possibilidade de remoção
*/
boolean website_deletar(WEBSITE **site){
    if(site == NULL){
        printf("Site não existe\n");
        return FALSE;
    }
    if(*site == NULL){
        printf("Site sem informações\n");
        return FALSE;
    }

    free((*site)->url);
    (*site)->url = NULL;

    free((*site)->nome);
    (*site)->nome = NULL;
    
    for(int i = 0; i < (*site)->num_palavras_chave; ++i){
        free((*site)->palavras_chaves[i]);
        (*site)->palavras_chaves[i] = NULL;
    }

    free((*site)->palavras_chaves);
    (*site)->palavras_chaves = NULL;
    
    free((*site));
    *site = NULL;

    return TRUE;
}

/*
    Função website_insere_nome
    Recebe como parâmetros o website e o nome que vai ser atribuído a ele
    Retorna um booleano conforme for verificada a possibilidade ou não de inserção
*/
boolean website_insere_nome(WEBSITE *site, char *nome){
    
    if(site == NULL || nome == NULL){
        printf("Impossível inserir no campo nome: site ou nome inexistentes\n");
        return FALSE;
    }
    
    site->nome = nome;

    if(site->nome == NULL) return FALSE;
    
    return TRUE;
}

/*
    Função website_consulta_nome
    Recebe como parâmetro o site cujo nome será consultado
    Retorna uma cadeia de caracteres contendo o nome do site em caso de sucesso ou NULL para um site inexistente
*/
char *website_consulta_nome(WEBSITE *site){
    if(site == NULL){
        printf("Impossível encontrar nome: site inexistente\n");
        return NULL;
    }

    return site->nome;
}

/*
    Função website_insere_url
    Recebe como parâmetros o site e a url que será atribuída a ele
    Retorna um booleano conforme for verificada a possibilidade ou não de inserção
*/
boolean website_insere_url(WEBSITE *site, char *url){
    if(site == NULL || url == NULL){
        printf("Impossível inserir no campo url: site ou url inexistentes\n");
        return FALSE;
    }
        
    site->url = url;
    
    if(site->url == NULL) return FALSE;
    
    return TRUE;
}

/*
    Função *website_consulta_url
    Recebe como parâmetro o site cuja url será consultada
    Retorna uma cadeia de caracteres contendo a url do site em caso de sucesso ou NULL para um site inexistente
*/
char *website_consulta_url(WEBSITE *site){
    if(site == NULL){
        printf("Impossível encontrar url: site inexistente\n");
        return NULL;
    }

    return site->url;
}

/*
    Função website_insere_relevancia
    Recebe como parâmetros o site e a relevância que será atribuída a ele
    Retorna um booleano conforme for verificada a possibilidade ou não de inserção
*/
boolean website_insere_relevancia(WEBSITE *site, int relevancia){
    if(site == NULL){
        printf("Impossível inserir no campo relevancia: site inexistente");
        return FALSE;
    }
    site->relevancia = relevancia;
    return TRUE;
}

/*
    Função website_consulta_relevancia
    Recebe como parâmetro o site cuja relevância será consultada
    Retorna um inteiro contendo a relevância do site em caso de sucesso ou FALSE para um site inexistente
*/
int website_consulta_relevancia(WEBSITE *site){
    if(site == NULL){
        printf("Impossível encontrar relevância: site inexistente\n");
        return FALSE;
    }
    return site->relevancia;
}

/*
    Função website_insere_codigo
    Recebe como parâmetros o website e o código que será atribuído a ele
    Retorna um booleano conforme for verificada a possibilidade ou não de inserção
*/
boolean website_insere_codigo(WEBSITE *site, int codigo){

    if(site == NULL){
        printf("Website inexsitente\n");
        return FALSE;
    }
    site->codigo = codigo;
    return TRUE;
}

/*
    Função website_consulta_codigo
    Recebe como parâmetro o website cujo código será consultado
    Retorna um inteiro contendo o código do site em caso de sucesso ou ERRO para um site inexistente
*/
int website_consulta_codigo(WEBSITE *site){
    if(site == NULL){
        printf("Impossível buscar código do site (site inexistente)\n");
        return ERRO;
    }
    return site->codigo;
}

/*
    Função website_insere_palavra_chave
    Recebe como parâmetros o website e a palavra chave que será atribuída a ele
    Retorna um booleano conforme for verificada a possibilidade ou não de inserção
*/
boolean website_insere_palavra_chave(WEBSITE *site, char *palavra_chave){   
    if(site == NULL || palavra_chave == NULL){
        printf("Impossível inserir palavra chave no site solicitado\n");
        return FALSE;
    }
    if(site->num_palavras_chave < 10){
        //site->palavras_chaves = realloc(site->palavras_chaves, (site->num_palavras_chave + 1) * sizeof(char*));
        
        site->palavras_chaves[site->num_palavras_chave] = palavra_chave;    
        
        ++site->num_palavras_chave;
        
        return TRUE;
    }

    printf("Número de palavras chave não pode ser maior que 10\n");
    return FALSE;
}

/*
    Função website_consulta_num_palavras_chave
    Recebe como parâmetro o website cujo número de palavras-chaves será consultado
    Retorna um inteiro contendo o número de palavras-chaves em caso de sucesso ou FALSE
*/
int website_consulta_num_palavras_chave(WEBSITE *site){
    if(site == NULL){
        printf("Site inexistente, não é possível acessar o número de palavras chave\n");
        return FALSE;
    }
    return site->num_palavras_chave;
}

char **website_consulta_palavras_chave(WEBSITE *site) {
    if(site == NULL) {
        printf("Site inexistente, não existe palavras chave\n");
        return NULL;
    }
    int num_palavras_chave = website_consulta_num_palavras_chave(site);

    if(num_palavras_chave == 0) {
        printf("Não existe palavras chaves no site\n");
        return NULL;
    }

    return site->palavras_chaves;
}

/*
*/
boolean verifica_palavra_chave(WEBSITE *website, char *palavra_chave) {
    if(website == NULL || palavra_chave == NULL) return FALSE;
    
    for(int i = 0; i < website->num_palavras_chave; ++i) {
        if(strcmp(website->palavras_chaves[i], palavra_chave) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/*
    Função mostrar_site
    Recebe como parãmetro o website a ser mostrado e imprime os dados desse website
*/
void mostrar_site(WEBSITE *site){
    if(site == NULL)
        printf("Site inexistente, não existe informações a serem mostradas.\n");
    else {
        printf("\n");
        //printf("---------------------------------------------------------------\n");   
        printf("| Dados de %s:\n", site->nome);
        printf("| Nome: %s\n", site->nome);
        printf("| URL: %s\n", site->url);
        printf("| Código: %d\n", site->codigo);
        printf("| Relevância: %d\n", site->relevancia);
        printf("| Palavras-chave:\n");
        
        for(int i = 1; i <= site->num_palavras_chave; i++)
            printf("| \t[%d] - %s\n", i, site->palavras_chaves[i - 1]);
        //printf("---------------------------------------------------------------\n");   
    }
    printf("\n");
}