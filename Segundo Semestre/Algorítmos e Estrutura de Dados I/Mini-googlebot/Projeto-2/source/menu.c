/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goulart 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "menu.h"
#include "website.h"
#include "avl.h"
#include "palavras_chave.h"

// Enumeração para facilitar a chamada das funções
enum comando { INSERIR_SITE = 0, REMOVER, INSERIR_PALAVRA, ATUALIZAR_RELEVANCIA, MOSTRA_LISTA, LER_CSV, BUSCAR_PALAVRA, SUGERIR_SITE,SAIR};

void imprime_menu(){
    printf("\n+---------------------------------------------------------------+\n");
    printf("| Digite o comando desejado de acordo com a seguinte enumeração |\n");
    printf("|\t[0] - Inserir um site na lista                          |\n");
    printf("|\t[1] - Remover um site da lista                          |\n");
    printf("|\t[2] - Inserir palavra-chave para um site                |\n");
    printf("|\t[3] - Atualizar relevância de um site                   |\n");
    printf("|\t[4] - Mostrar a lista obtida ate agora                  |\n");
    printf("|\t[5] - Realizar a leitura de dados a partir de um CSV    |\n");
    printf("|\t[6] - Buscar palavra-chave                              |\n");
    printf("|\t[7] - Sugerir sites                                     |\n");
    printf("|\t[8] - Sair                                              |\n");
    printf("+---------------------------------------------------------------+\n");
}

/*
    Função cria_site_insere_na_lista:
    Recebe como parâmetro a lista e todos os valores necessários para construir uma variável do tipo
    struct WEBSITE.
    Cria um novo site, adicionando-o na lista
    Retorna se a execução foi bem sucedida e falso se houve algum erro durante execução do código.
*/
boolean cria_site_insere_na_arvore(AVL *arvore, int codigo, char *nome,  char *url, int relevancia, char **pc, int n_pc){
    if(arvore == NULL) {
        printf("Lista inexistente\n");
        return FALSE;
    }

    WEBSITE *novo_site = website_criar();
    
    boolean inseriu_codigo = website_insere_codigo(novo_site, codigo);
    boolean inseriu_nome = website_insere_nome(novo_site, nome);
    boolean inseriu_relevancia = website_insere_relevancia(novo_site, relevancia);
    boolean inseriu_url = website_insere_url(novo_site, url);
    boolean inseriu_pc = FALSE;
    
    for(int i = 0; i < n_pc; ++i)
       inseriu_pc += website_insere_palavra_chave(novo_site, pc[i]);

    int inseriu_site = inseriu_codigo + inseriu_nome + inseriu_relevancia + inseriu_url + inseriu_pc;
    if(inseriu_site == n_pc + 4){
        boolean inseriu_avl = avl_inserir_site(arvore, novo_site);

        if(inseriu_avl)
            return TRUE;
    }

    return FALSE;
}

/*
    Função inserir_site:
    Recebe como parâmetro a lista em que será inserido o novo site.
    Recebe pelo stdin todas as informações necessárias para que o usuário insira um novo website na lista.
*/
void inserir_site(AVL *arvore) {
    printf("\n+-------------------------------------------+\n");
    printf("|              INSERIR SITE                 |\n");
    printf("+-------------------------------------------+\n");

    printf("Você escolheu inserir um novo site\n");
    
    printf("Digite o código do site: ");
    
    int codigo;
    codigo = leitura_de_inteiro();

    while(avl_procurar_codigo(arvore, codigo)) {
        printf("Código já existente, não é possível adicionar site com mesmo código.\n");
        printf("Digite um novo código (ou digite -1 para cancelar a inserção): ");
        codigo = leitura_de_inteiro();
        if(codigo == -1) return;
    }

    while(codigo < 0 || codigo >= 10000) {
        printf("O código deve ser um número entre 0 e 9999.\n");
        printf("Digite novamente (-1 para cancelar a inserção):   ");
        codigo = leitura_de_inteiro();
        if(codigo == -1) return;
    }


    printf("Digite o nome do site que será inserido: ");
    char *nome = leitura_de_linha(stdin);

    printf("Digite agora a url do site: ");
    char *url = leitura_de_linha(stdin);

    printf("Digite a relevância do site (deve ser entre 0 e 1000): ");
    
    int relevancia;
    relevancia = leitura_de_inteiro();
    
    while(relevancia < 0 || relevancia > 1000){
        printf("Por favor, digite uma relevancia entre 0 e 1000: ");
        relevancia = leitura_de_inteiro();
    }

    printf("Quantas palavras chave irá relacionar a este site? ");
    
    int num_palavras_chave;
    num_palavras_chave = leitura_de_inteiro();
    
    if(num_palavras_chave > 10) {
        printf("O número máximo de palavras chaves permitido é de 10, permitiremos então 10 palavras\n");
        num_palavras_chave = 10;
    }

    char **palavras_chaves = calloc(num_palavras_chave, sizeof(char*));
    
    for(int i = 0; i < num_palavras_chave; ++i){ 
        printf("> [%d]: ", i);
        palavras_chaves[i] = leitura_de_linha(stdin);
        printf("\n");
    }

    boolean site_inserido = cria_site_insere_na_arvore(arvore, codigo, nome, url, relevancia, palavras_chaves, num_palavras_chave);

    if(site_inserido) 
        printf("Inserção bem sucedida!\n");
    
    else {
        printf("Algum erro ocorreu durante a inserção do site.\n");
        printf("Algum dado pode ter sido perdido.\n");
    }
    
    free(palavras_chaves); // Como perdemos a referência para o ponteiro inicial, devemos dar free

    //Mostrando o site inserido  
    WEBSITE* s = avl_buscar_site(arvore, codigo);
    mostrar_site(s);
    printf("\n");

}

/*
    Função remover_site:
    Recebe como parâmetro a lista em que será removido um site a partir de um código especificado pelo 
    usuário.
    Procura pelo código na lista, removendo-o caso o encontre.
*/
void remover_site(AVL *arvore) {
    printf("\n+-------------------------------------------+\n");
    printf("|             REMOVER SITE                  |\n");
    printf("+-------------------------------------------+\n");

    printf("\n\nVocê escolheu remover um site da lista\n");
    printf("Digite o código do site que deseja remover: ");
    
    int codigo;
    codigo = leitura_de_inteiro();

    if(avl_remover_site(arvore, codigo)) {
        printf("Site removido com sucesso.\n\n");
        return;
    }
    printf("Erro ao remover site: código não encontrado\n\n");
}

/*
    Função inserir_palavra_chave:
    Recebe como parâmetro a lista.
    A partir do código fornecido pelo usuário e verificado a existencia de um site com aquela chave, 
    é realizada a inserção da mais uma palavra chave (lembrando do máximo permitido de 10 palavras)
*/
void inserir_palavra_chave(AVL *arvore) {
    printf("\n+-------------------------------------------+\n");
    printf("|        INSERIR PALAVRA-CHAVE              |\n");
    printf("+-------------------------------------------+\n");
    

    printf("Você selecionou inserir uma palavra-chave\n");
    printf("Digite qual o código do site em que deseja inserir a nova palavra: ");
    
    int codigo;
    codigo = leitura_de_inteiro();
    
    if(avl_procurar_codigo(arvore, codigo) == FALSE)
        printf("O código buscado não existe na lista\n");
    
    else {
        WEBSITE *site = avl_buscar_site(arvore, codigo);
        
        if(website_consulta_num_palavras_chave(site) >= 10)
            printf("O site já possui o máximo de palavras chaves (MAX = 10)\n");
        
        else{
            printf("Codigo encontrado para o site com nome: %s\n", website_consulta_nome(site));
            printf("Digite a palavra chave que quer acrescentar: ");
            
            char *palavra_chave = leitura_de_linha(stdin);

            if(website_insere_palavra_chave(site, palavra_chave))
                printf("Palavra chave inserida com sucesso\n");
            else 
                printf("Algum erro ocorreu durante a escrita da palavra chave\n");
        }    
    }
    printf("\n");
}

/*
    Função atualizar_relevancia:
    Recebe como parâmetro a lista.
    A partir do código de um site e verificado a existencia deste na lista, é alterado o valor da relevância
    por um valor desejado pelo usuário.
*/
void atualizar_relevancia(AVL *arvore) {
    printf("\n+-------------------------------------------+\n");
    printf("|           ATUALIZAR RELEVÂNCIA            |\n");
    printf("+-------------------------------------------+\n");

    printf("Você escolheu atualizar a relevância de um site na lista.\n");
    printf("Digite o código do site que deseja atualizar a relevancia: ");
    
    int codigo;
    codigo = leitura_de_inteiro();

    if(avl_procurar_codigo(arvore,codigo) == FALSE) {
        printf("Código inexistente na lista\n\n");
        return;
    }
    
    WEBSITE *site;
    site = avl_buscar_site(arvore, codigo);
    
    int nova_relevancia;
    printf("Digite a nova relevância para o site de nome %s: ", website_consulta_nome(site));
    nova_relevancia = leitura_de_inteiro();

    while(nova_relevancia < 0 || nova_relevancia > 1000) {
        printf("Por favor, digite um valor de relevância entre 0 e 1000: ");
        nova_relevancia = leitura_de_inteiro();
    }

    if(website_insere_relevancia(site, nova_relevancia))
        printf("Relevância do site %s alterada para %d com sucesso\n\n", website_consulta_nome(site), nova_relevancia);
    else
        printf("Falha na inserção da relevância do site desejado\n\n");
}

/*
    Função carrega_dados_csv:
    Realiza a leitura de dados a partir de um arquivo no formato CSV fornecido pelo usuário, carregando
    as informações obtidas para a lista.
*/
void carrega_dados_csv(AVL *arvore) {
    printf("\n+-------------------------------------------+\n");
    printf("|            CARREGAR DADOS CSV             |\n");
    printf("+-------------------------------------------+\n\n");

    printf("\nVocê escolheu ler dados de um arquivo CSV\n");
    printf("Digite o nome do arquivo CSV para realizar a leitura: ");
    
    char *nome_arquivo_csv = leitura_de_linha(stdin);

    preenche_lista_dados_csv(arvore, nome_arquivo_csv);
    
    free(nome_arquivo_csv);    
}

void buscar_palavra(AVL *arvore) {
    printf("\n+-------------------------------------------+\n");
    printf("|  BUSCAR PALAVRA-CHAVE NA LISTA DE SITES   |\n");
    printf("+-------------------------------------------+\n\n");
    printf("Você escolheu buscar uma palavra-chave na lista de sites.\n");
    printf("Digite a palavra-chave que deseja buscar: ");

    char *palavra_buscada = leitura_de_linha(stdin);
    
    LISTA_SITES *sites_encontrados = avl_buscar_palavra_chave(arvore, palavra_buscada);    

    lista_sites_ordenar(sites_encontrados);

    printar_lista_encontrada(sites_encontrados);
    

    lista_sites_deletar(&sites_encontrados);

    free(palavra_buscada);
}

void sugerir_sites(AVL *arvore) {
    printf("\n+-------------------------------------------+\n");
    printf("|                 SUGERIR SITES             |\n");
    printf("+-------------------------------------------+\n\n");
    printf("Você escolheu sugerir sites a partir de uma palavra-chave.\n");
    printf("Digite a palavra-chave que deseja iniciar sua busca: ");

    char *palavra_chave_inicial = leitura_de_linha(stdin);

    LISTA_SITES *sites_com_palavra_chave = avl_buscar_palavra_chave(arvore, palavra_chave_inicial);

    if(sites_com_palavra_chave == NULL || lista_sites_consulta_num_sites(sites_com_palavra_chave) == 0) { 
        printf("Não existem sites com a palavra chave %s!!\n", palavra_chave_inicial);
        free(palavra_chave_inicial);
        return;
    }

    TRIE *palavras_chave = construir_trie_com_lista_sites(sites_com_palavra_chave);
    
    LISTA_SITES *sugestoes = verificar_sites_para_sugestao(arvore, palavras_chave);

    lista_sites_ordenar(sugestoes);

    printar_lista_encontrada(sugestoes);

    trie_deletar(&palavras_chave);
    lista_sites_deletar(&sites_com_palavra_chave);
    lista_sites_deletar(&sugestoes);
    free(palavra_chave_inicial);
}

/*
    Função executa_programa:
    Realiza o loop do programa inteiro.
    Indica as funcionalidade disponíveis para o usuário: inserção, remoção, adicionar palavra chave, 
    atualiar relevancia, mostrar a lista, ler csv e sair do programa
*/
void executa_programa(AVL *arvore) {
    int escolha = 0;
   
    while(1) {
        imprime_menu();
        printf("> Digite o comando: ");
        escolha = leitura_de_inteiro();
      
        while(!(escolha >= 0 || escolha <= 5)){
            printf("Por favor, escolha corretamente o comando desejado\n");
            imprime_menu();
            printf("> Digite o comando: ");
            escolha = leitura_de_inteiro();
        }

        if(escolha == INSERIR_SITE)
           inserir_site(arvore);
        
        else if(escolha == REMOVER)
            remover_site(arvore);
        
        else if(escolha == INSERIR_PALAVRA)
            inserir_palavra_chave(arvore);
        
    
        else if(escolha == ATUALIZAR_RELEVANCIA)
             atualizar_relevancia(arvore);
    

        else if(escolha == MOSTRA_LISTA){
            printf("\n\nVocê escolheu mostrar os sites:\n");
            avl_imprimir_em_ordem(arvore);
        }

        else if(escolha == LER_CSV)
            carrega_dados_csv(arvore);

        else if(escolha == BUSCAR_PALAVRA)
            buscar_palavra(arvore);

        else if(escolha == SUGERIR_SITE)
            sugerir_sites(arvore);
        
        else if(escolha == SAIR) {
            printf("\n+-------------------------------------------+\n");
            printf("|            ENCERRANDO O PROGRAMA          |\n");
            printf("+-------------------------------------------+\n");

            printf("Obrigado por usar o programa. Saindo...\n");
            break;
        }
    }

}