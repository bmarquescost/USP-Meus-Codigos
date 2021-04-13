/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaencadeada.h"
#include "website.h"
#include "util.h"

/*
    Função leitura_de_linha:
    Recebe como parâmetro o buffer em que será lido a cadeia de caracteres, realizando a leitura até
    encontra um '\n' ou o final do buffer (EOF).
    Retorna o ponteiro para a cadeia de caracteres armazenada na memória Heap.
*/
char *leitura_de_linha(FILE *stream){
    char *linha = NULL;
    int pos = 0, multi = 1;
    char caractere;
    do{
        if(pos % TAM == 0) linha = realloc(linha, (multi++)*TAM); 
        caractere = (int) fgetc(stream);
        if(caractere != '\r') {    // Desconsiderando o caractere '\r'
            linha[pos] = caractere;
            pos++;
        }
    }while(caractere != '\n' && !feof(stream)); 

    linha = realloc(linha, pos);
    
    linha[pos - 1] = '\0'; 
    
    return linha;
}

/*
    Função particiona_string_pelo_token:
    Recebe com parâmetro a linha inteira que será analisada, um inteiro correspondente ao indice de
    onde essa análise será feita e um valor boleano recebido por referência, que será alterado para 
    TRUE caso encontramos o final da linha.
    Retorna a string obtida do inicio da análise até encontra o TOKEN (',') ou o final da linha.
*/
char *particiona_string_pelo_token(char *linha_inteira, int inicio, boolean *acabou){
    
    int final = inicio;    

    while(linha_inteira[final] != TOKEN && linha_inteira[final] != '\0')
        final++;

    if(linha_inteira[final] == '\0') *acabou = TRUE;

    int tamanho_auxiliar = final - inicio + 1;

    char *auxiliar = calloc(tamanho_auxiliar, sizeof(char));
    
    for(int i = inicio, j = 0; i < final; ++i, ++j)
        auxiliar[j] = linha_inteira[i]; 

    return auxiliar;
}

/*
    Função cria_website_pelos_dados:
    Recebe uma linha obtida pela leitura do CSV.
    A partir do particionamento da string com a função acima, passa os dados do CSV para a struct 
    que contem os dados do site.
    Retorna o ponteiro para a struct WEBSITE construído na função.
*/
WEBSITE *cria_website_pelos_dados(char *linha_inteira){
    
    if(linha_inteira == NULL) return NULL;

    WEBSITE *novo_site = website_criar();
    
    int inicio = 0;
    boolean final_da_linha = FALSE;
    
    // Código do site
    char *codigo_string = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(codigo_string) + 1; // Colocando o índice na posição correta após a virgula.
    int codigo = atoi(codigo_string);
    website_insere_codigo(novo_site, codigo);

    // Nome do site
    char *nome = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(nome) + 1;
    website_insere_nome(novo_site, nome);

    // Relevância do site
    char *relevancia_string = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(relevancia_string) + 1;
    int relevancia = atoi(relevancia_string);
    website_insere_relevancia(novo_site, relevancia);

    // URL do site    
    char *url = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(url) + 1;
    website_insere_url(novo_site, url);
    
    // Palavras chave do site
    int num_chaves = 0;
    char **palavras_chave = NULL;
    
    while(final_da_linha == FALSE && num_chaves < 10){
        // Realocando o vetor de strings para que seja possível armazenar mais uma palavra chave.
        palavras_chave = realloc(palavras_chave,(num_chaves+1) * sizeof(char*));
        palavras_chave[num_chaves] = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
        
        website_insere_palavra_chave(novo_site, palavras_chave[num_chaves]);

        inicio += strlen(palavras_chave[num_chaves]) + 1;

        ++num_chaves;
    }    

    // Ao igualar ponteiros, perdemos a referência do ponteiro na stack que aponta para o ínicio da matriz de dados,
    // mas nao perdemos a referência para cada uma de suas linhas, portando podemos e devemos dar free nesta região.
    free(palavras_chave); 
    
    free(codigo_string);
    free(relevancia_string);

    return novo_site;
}

/*
    Função leitura_csv:
    Recebe como parâmetro o nome do arquivo csv que será lido e o endereço de uma variável que armazenará o número
    de linhas deste arquivo.
    Retorna um vetor de palavras, sendo a quantidade de linhas equivalente ao número de sites que serão inseridos
    a partir do arquivo CSV.
*/
char **leitura_csv(char *nome_csv, int *num_linhas){
    
    FILE *ponteiro_csv = NULL;
    
    printf("Realizando a leitura do arquivo %s\n",nome_csv);
   
    if(!(ponteiro_csv = fopen(nome_csv, "r"))){
        printf("Erro na abertura do arquivo CSV\n");
        return NULL;
    }
    
    char caracter;
    int numero_linhas = 0;
    while(!feof(ponteiro_csv)){
        caracter = fgetc(ponteiro_csv);
        if(caracter == '\n') // É necessário uma quebra de linha ao final de cada um dos dados que desejamos armazenar.
            ++numero_linhas;
    }

    char **dados_csv = NULL;
    dados_csv = calloc(numero_linhas, sizeof(char* ));
    
    fseek(ponteiro_csv, 0, SEEK_SET);

    for(int i = 0;i < numero_linhas; ++i)
        dados_csv[i] = leitura_de_linha(ponteiro_csv);

    *num_linhas = numero_linhas;
    
    fclose(ponteiro_csv);
    
    return dados_csv;    
}
/*
    Função preenche_lista_dados_csv:
    Recebe como parâmetro a lista em que será inserido os nós do site e o nome do arquivo csv.
    Redireciona para cada uma das funções necessárias, obtendo a struct correspondente ao site e armazenando
    este na lista de acordo com seu código (não é acrescentado dados com relevância menor que 0 ou maior que 1000
    e também não são inseridos dados com mesmo valor de código).
*/
void preenche_lista_dados_csv(LISTA *l, char *arquivo_csv){
    if(l == NULL) return;
    
    int num_linhas = 0;
    char **dados_csv = leitura_csv(arquivo_csv, &num_linhas);
    
    WEBSITE *site_auxiliar;

    for(int i = 0; i < num_linhas; ++i){
        site_auxiliar = cria_website_pelos_dados(dados_csv[i]);
        int relevancia = website_consulta_relevancia(site_auxiliar);
        
        // Checando a validade do código (verificando se não está repetido na lista)
        if(lista_procurar_codigo(l, website_consulta_codigo(site_auxiliar))){
            printf("!! Leitura de codigos semelhantes no arquivo CSV !!\n");
            website_deletar(&site_auxiliar);
        }
        // Checando a validade da relevância
        else if(relevancia < 0 || relevancia > 1000){
            printf("!! Leitura de relevancia inválida (relevancia deve ser maior que 0 e menor que 1000) !!\n");
            website_deletar(&site_auxiliar);
        }
        
        else lista_inserir(l, site_auxiliar);
    }
        
    for(int i = 0; i < num_linhas; ++i)
        free(dados_csv[i]);
    free(dados_csv);
}