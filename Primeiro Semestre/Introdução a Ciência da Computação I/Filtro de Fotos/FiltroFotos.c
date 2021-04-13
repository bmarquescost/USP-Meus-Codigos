/*
    ICMC - Instituto de Ciências matemáticas e de Computação
    Curso: Bacharelado em Ciência da Computação

    Programa: FILTRO DE FOTOS

    Disciplina: Introdução a Ciência da Computação I
    Aluno: Bernardo Marques Costa
    Número USP: 11795551

    O programa receberá como entrada o nome de um arquivo (sendo necessário o formato bmp) correspondente a uma foto e 
    um inteiro correspondente ao filtro que deverá ser aplicado na imagem.
    1 -> Filtro Negativo
    2 -> Filtro de imagem Preto e Branco
    Cria a imagem com o nome <nome do arquivo><filtro>.bmp
    Ex: paisagem.bmp
        1
    --> paisagemNegativo.bmp

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct que armazena o cabeçalho do arquivo (dados do arquivo)
typedef struct{
    char assinatura[2];
    int tamanho_arquivo;
    int campo_reservado;
    int deslocamento;
} HEADER_ARCHIVE;

// Struct que armazena o cabeçalho do arquivo de imagem (dados do bitmap)
typedef struct {
    int tamanho_header;
    int largura_imagem;
    int altura_imagem;
    short int numero_planos;
    short int bit_per_pixel;
    int compressao;
    int tamanho_imagem;
    int pixel_metro_horizontal;
    int pixel_metro_vertical;
    int numero_cores_usadas;
    int numero_cores_importantes;
} HEADER_BITMAP;

// Paleta de cores da image, guardando valores do RGB e um valor reservado.
typedef struct{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char  reservado;
} RGB_PALET;

// Struct completa dos dados do arquivo de imagens.
typedef struct{
    HEADER_ARCHIVE *h_arquivo;
    HEADER_BITMAP *h_bitmap; 
    RGB_PALET *palette;
    unsigned char **image_matrix;
} HEADER;

char *readline(FILE *);
void readHeader(FILE *, HEADER *);
void initializePalette(RGB_PALET**);
void initializeArchiveStruct(HEADER **);
unsigned char **initializeMatrixImage(HEADER *, int);
void readPalette(FILE *, RGB_PALET *);
void readColorImage(FILE *, HEADER *, int);
char* nameAdd(int, char*);
FILE* createNewFile(char*);
void fillDataFile( HEADER *, FILE *, int , RGB_PALET *);
void fillImageFile(FILE *, HEADER*, int);
void printAllData(HEADER *, RGB_PALET *, int, char *);

int main(int argc, char *argv[]){

    char* new_file_name = NULL;    // Cadeia de caracteres que armazenará o nome do arquivo novo.
    FILE *new_file_pointer = NULL;  // Ponteiro para o arquivo que será criado.
    
    // variável do tipo struct HEADER que contem todos os dados da imagem que serão passados para a imagem nova.
    HEADER *image = NULL;      

    RGB_PALET *palette = NULL; // Paleta de cores do arquivo bmp original.
    
    // Lendo o nome do arquivo, imagem que será aplicado o filtro.
    char *image_name = NULL;
    image_name = readline(stdin);

    // Recebendo o tipo do filtro desejado.
    int type_of_filter;
    scanf("%d", &type_of_filter);
    
    // Verificando se o arquivo de entrada possui extenção .bmp
    int aux = strlen(image_name) - 1;
    if (!(image_name[aux-3] == '.' && image_name[aux-2] == 'b' && image_name[aux-1] == 'm' && image_name[aux] == 'p')){
        printf("Arquivo nao eh do formato BMP\n");
        free(image_name);
        exit(1);
    }

    // Abrindo o arquivo desejado para que seja possível a leitura, sendo executado na forma de leitura binária.
    FILE *filepointer;
    if (!(filepointer= fopen(image_name, "rb"))){
        printf("Erro no arquivo\n");
        free(image_name);
        exit(1);
    }

    // Realizando a comparção da assinatura do arquivo com a string característica de arquivos do tipo .bmp
    // Processo feito para que não seja alocado inutilmente a struct
    char auxiliar[3];
    fread(auxiliar, sizeof(char), 2 , filepointer);
    auxiliar[2] = '\0';
    if (strcmp(auxiliar, "BM") != 0){
        printf("Arquivo nao eh do formato BMP\n");
        free(image_name);
        fclose(filepointer);
        exit(1);
    }
    
    // Retornando o "cursor" para o início do arquivo para a leitura dos dados do cabeçalho
    fseek(filepointer, 0 , SEEK_SET);

    // Função que inicializa a variável do tipo HEADER *, alocando seus campos dinamicamente
    initializeArchiveStruct(&image);    
    // Função que inicializa as paletas de cores, tanto a antiga, quanto a do novo arquivo.
    initializePalette(&palette);
    
    // Realizando a leitura dos cabeçalhos do arquivo de entrada
    readHeader(filepointer, image);

    // Adicionado o padding (caso exista) à largura da imagem, para a alocação da matriz da imagem.
    int padding = 0;
    if (image->h_bitmap->largura_imagem % 4) padding = 4 - image->h_bitmap->largura_imagem % 4;
    
    // Atribuindo o retorno da função (utilizada para inicializar a matriz da imagem) à matriz presente na struct image
    // como um de seus campos.
    image->image_matrix = initializeMatrixImage(image, padding);

    // Leitura da paleta de cores a partir do arquivo de entrada.
    readPalette(filepointer, palette);

    // Leitura da matriz da imagem a partir do arquivo de entrada.
    readColorImage(filepointer, image, padding);

    // Fechando o arquivo, já que não é mais utilizado no programa
    fclose(filepointer);

    // Atribuindo o retorno da função que constrói o nome do arquivo novo.
    new_file_name = nameAdd(type_of_filter, image_name);

    // Atribuindo o retorno da função que cria o ponteiro para o novo arquivo. 
    new_file_pointer = createNewFile(new_file_name);

    // Preenchendo os dados do cabeçalho do novo arquivo binário
    fillDataFile(image, new_file_pointer, type_of_filter, palette);
    
    // Preenchendo os dados da matriz de imagem no novo arquivo binário.
    fillImageFile(new_file_pointer, image, padding);

    //fseek(new_file_pointer, image->h_arquivo->deslocamento, SEEK_SET);  
    // Imprimindo todas as informações: header, paleta de cores original e nova, soma das linhas da matriz de image e o nome 
    // do novo arquivo. 
    printAllData(image, palette, padding, new_file_name);

    // Realizando os free de todas as variáveis que forma dinamicamente alocadas
    // Fechando o arquivo aberto.
    fclose(new_file_pointer);
    free(new_file_name);
    free(image_name);
    free(palette);
    free(image->palette);
    for (int i = 0; i < image->h_bitmap->altura_imagem; i++){
        free(image->image_matrix[i]);
    }
    free(image->image_matrix);
    free(image->h_arquivo);
    free(image->h_bitmap);
    free(image);

    return 0;
}

/*
    Função initializeArchivesStruct:
    Recebe como parâmetro o endereço do ponteiro que aponta para uma struct HEADER, alocando-a dinamicamente na memória
    Heap, em conjunto a seus campos.
*/
void initializeArchiveStruct(HEADER **img){
    (*img) = (HEADER*)calloc(1,sizeof(HEADER));
    (*img)->image_matrix = NULL;
    (*img)->h_arquivo = (HEADER_ARCHIVE*)calloc(1,sizeof(HEADER_ARCHIVE));
    (*img)->h_bitmap = (HEADER_BITMAP*)calloc(1,sizeof(HEADER_BITMAP));
    initializePalette(&(*img)->palette); // Enviando para a função que inicializa paletas de cores.
}

/*
    Função initializePalette:
    Recebe como parâmetro o endereço da paleta de cores que se deseja alocar dinamicamente na memória Heap, realizando a 
    alocação de 256 blocos de memórias do tamanho da struct RGB_PALET.
*/
void initializePalette(RGB_PALET **palette){
    *palette = (RGB_PALET*)calloc(256, sizeof(RGB_PALET));
}

/* 
    Função initializeMatrixImage:
    Recebe como parâmetros o padding da imagem e a struct para que possa acessar os dados da largura e altura da imagem.
    Aloca dinamicamente uma matriz de unsigned char de dimensões Altura * (Largura + padding).
*/
unsigned char** initializeMatrixImage(HEADER *img, int padding){
    unsigned char **matrix;
    matrix = (unsigned char**)calloc(img->h_bitmap->altura_imagem, sizeof(unsigned char*));
    for (int i = 0 ; i < img->h_bitmap->altura_imagem; i++)
        matrix[i] = (unsigned char *)calloc(img->h_bitmap->largura_imagem + padding, sizeof(unsigned char));
    
    // Retorando o ponteiro para a matriz alocada na Heap.
    return matrix;
}

/*
    Função readHeader:
    Realiza a leitura de todo o cabeçalho do arquivo original, atribuindo ao respectivo campo na variável do tipo
    struct HEADER. 
*/
void readHeader(FILE *filepointer, HEADER *img){
    
    // LENDO HEADER DO ARQUIVO
    fread(img->h_arquivo->assinatura, sizeof(char), 2, filepointer); 
    fread(&img->h_arquivo->tamanho_arquivo, sizeof(int), 1, filepointer); 
    fread(&img->h_arquivo->campo_reservado, sizeof(int), 1, filepointer); 
    fread(&img->h_arquivo->deslocamento, sizeof(int), 1, filepointer);

    //  LENDO HEADER DE DADOS DA IMAGEM
    fread(&img->h_bitmap->tamanho_header, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->largura_imagem, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->altura_imagem, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->numero_planos, sizeof(short int), 1, filepointer);
    fread(&img->h_bitmap->bit_per_pixel, sizeof(short int), 1, filepointer);
    fread(&img->h_bitmap->compressao, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->tamanho_imagem, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->pixel_metro_horizontal, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->pixel_metro_vertical, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->numero_cores_usadas, sizeof(int), 1, filepointer);
    fread(&img->h_bitmap->numero_cores_importantes, sizeof(int), 1, filepointer);
}

/*
    Função readPalette:
    Recebe como parâmetro o ponteiro para o arquivo original e a paleta de cores em que será armazenado os dados.
*/
void readPalette(FILE *filepointer, RGB_PALET *palette){
    for (int i = 0; i < 256; i++){
        fread(&palette[i].blue, 1, 1, filepointer);
        fread(&palette[i].green, 1, 1, filepointer);
        fread(&palette[i].red, 1, 1, filepointer);
        fread(&palette[i].reservado, 1, 1, filepointer);
    }
}

/*
    Função readColorImage:
    Recebe como parâmetro o ponteiro para o arquivo original, a variável do tipo struct HEADER e o padding.
    Realiza a leitura desde o final do cabeçalho e dos dados da paleta até o final do arquivo, coletando as informações
    da matriz e atribuindo-o ao campo da struct como matriz de unsigned char alocada dinamicamente.
*/
void readColorImage(FILE *filepointer, HEADER *img, int padding){  
    fseek(filepointer, img->h_arquivo->deslocamento, SEEK_SET);
    for (int i = 0; i < img->h_bitmap->altura_imagem; i++){
        for(int j = 0; j < img->h_bitmap->largura_imagem + padding; j++){
            fread(&img->image_matrix[i][j], 1, 1, filepointer);
        }
    }
}

/*
    Função nameAdd:
    Recebe como parâmetros a flag (correspondente ao tipo do filtro desejado) e a cadeia de caracteres correspondentes
    ao nome original do arquivo.
    Retorna o ponteiro para o bloco de memória do nome final, armazenado na memória heap.
*/
char* nameAdd(int flag, char* img_name){

    // Ponteiro para o do arquivo final que será retornado
    char *newfile = NULL;
    int aux = 0, pos = 0;

    // FILTRO NEGATIVO
    if (flag == 1){
        // Utilizando uma mariável do tipo char armazenado na stack para acrescentá-lo ao nome final.
        char add[] = "Negativo";
        // Alocando o espaço necessário na memória Heap para armazenar o nome do novo arquivo.
        newfile = (char*)calloc(strlen(img_name)+ strlen(add) + 1, sizeof(char));
        // Copiando o nome do arquivo antigo.
        while(img_name[aux] != '.'){
            newfile[pos] = img_name[aux];
            pos++;
            aux++;
        }
        aux = 0;
        // Copiando o nome do filtro desejado.
        while(add[aux] != '\0'){
            newfile[pos] = add[aux];
            aux++;
            pos++;   
        }
        // Acrescentado a extensão do arquivo
        newfile[pos++] = '.';
        newfile[pos++] = 'b';
        newfile[pos++] = 'm';
        newfile[pos++] = 'p'; 
    }

    // FILTRO PRETO E BRANCO
    else if(flag == 2){
        char add[] = "PretoBranco";
        newfile = (char*)calloc(strlen(img_name)+strlen(add)+1, sizeof(char));
        while(img_name[aux] != '.'){
            newfile[pos] = img_name[aux];
            pos++;
            aux++;
        }
        aux = 0;
        while(add[aux] != '\0'){
            newfile[pos] = add[aux];
            aux++;
            pos++;
        }
        newfile[pos++] = '.';
        newfile[pos++] = 'b';
        newfile[pos++] = 'm';
        newfile[pos++] = 'p'; 
    } 
    
    // Acrescentando o delimitador do final da cadeia de caracteres.
    newfile[pos] = '\0';
    
    return newfile;
}

/*
    Função createNewFile:
    Recebe como parâmetro o ponteiro para o nome do do arquivo novo.
    Abre o arquivo no modo binário de escrita, apagando caso um arquivo com tal nome já exista.
    Retorna o ponteiro do arquivo.
*/
FILE *createNewFile(char *newfile){
    FILE * newfilepointer = NULL;
    if (!(newfilepointer = fopen(newfile, "wb+"))){
        printf("Não foi possível criar o novo arquivo\n");
        exit(1);
    }
    return newfilepointer;
}

/*
    Função fillDataFile:
    Recebe como parâmetro a variável do tipo struct HEADER, o ponteiro para o novo arquivo, o filtro utilziado e 
    a paleta de cores original.
*/
void fillDataFile(HEADER *img, FILE *newfilepointer, int filter, RGB_PALET *palette){
    
    // COPIANDO HEADER DOS DADOS DO ARQUIVOS
    fwrite(img->h_arquivo->assinatura, sizeof(char), 2, newfilepointer); 
    fwrite(&img->h_arquivo->tamanho_arquivo, sizeof(int), 1, newfilepointer); 
    fwrite(&img->h_arquivo->campo_reservado, sizeof(int), 1, newfilepointer); 
    fwrite(&img->h_arquivo->deslocamento, sizeof(int), 1, newfilepointer);

    //  LENDO HEADER DE DADOS DA IMAGEM
    fwrite(&img->h_bitmap->tamanho_header, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->largura_imagem, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->altura_imagem, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->numero_planos, sizeof(short int), 1, newfilepointer);
    fwrite(&img->h_bitmap->bit_per_pixel, sizeof(short int), 1, newfilepointer);
    fwrite(&img->h_bitmap->compressao, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->tamanho_imagem, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->pixel_metro_horizontal, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->pixel_metro_vertical, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->numero_cores_usadas, sizeof(int), 1, newfilepointer);
    fwrite(&img->h_bitmap->numero_cores_importantes, sizeof(int), 1, newfilepointer);

    // CASO NEGATIVO -> subtrai de 255 (maior valor da paleta possível) do valor inicial de cada tom de RGB.
    if (filter == 1){
        for (int i = 0; i < 256; i++){
            img->palette[i].red = 255 - palette[i].red;
            img->palette[i].blue = 255 - palette[i].blue;
            img->palette[i].green = 255 - palette[i].green; 
        }
    }
    // CASO PRETO E BRANCO -> realiza a média dos valores presentes dos tons de RGB, atribuindo-o à paleta final.
    else if(filter == 2){
        unsigned int aux = 0;
        for(int i = 0; i < 256; i++){
            aux = (palette[i].red + palette[i].green + palette[i].blue)/3;
            img->palette[i].red = aux;
            img->palette[i].green = aux;
            img->palette[i].blue = aux;
        }
    }

    // Escreveno no arquivo final a paleta de cores resultante.
    for (int i = 0; i < 256; i++){
        fwrite(&img->palette[i].blue, 1, 1, newfilepointer);
        fwrite(&img->palette[i].green, 1, 1, newfilepointer);
        fwrite(&img->palette[i].red, 1, 1, newfilepointer);
        fwrite(&img->palette[i].reservado, 1, 1, newfilepointer);
    }
}

/*
    Função fillImageFile:
    Recebe como parâmetro o ponteiro para o novo arquivo, o endereço da struct HEADER e o padding da imagem.
    Escreve no arquivo binário os dados da matriz de forma contínua.
*/
void fillImageFile(FILE* newfp, HEADER *img, int padding){
    // Alterando o cursos para o inicio dos dados da matriz da imagem.
    fseek(newfp, img->h_arquivo->deslocamento, SEEK_SET);
    for(int i = 0; i < img->h_bitmap->altura_imagem; i++){
        for(int k = 0; k < img->h_bitmap->largura_imagem + padding; k++){
            fwrite(&img->image_matrix[i][k], sizeof(unsigned char), 1, newfp);
        }
    }
}

/*
    Função printAllData:
    Recebe como parâmetro a struct HEADER, a paleta de cores original, o padding e o nome do novo arquivo.
*/
void printAllData(HEADER *img, RGB_PALET *palette, int padding, char* newfile){
    // Imprimindo os dados do cabeçalho do arquivo
    printf("CABECALHO:\n");
    printf("Iniciais: %s\n", img->h_arquivo->assinatura);
    printf("Tamanho do arquivo: %d\n", img->h_arquivo->tamanho_arquivo);
    printf("Reservado: %d\n", img->h_arquivo->campo_reservado);
    printf("Deslocamento, em bytes, para o inicio da area de dados: %d\n",img->h_arquivo->deslocamento); 
    // Imprimindo os dados do cabeçalho do bitmap.
    printf("Tamanho em bytes do segundo cabecalho: %d\n", img->h_bitmap->tamanho_header);
    printf("Resolucao: %d x %d\n",img->h_bitmap->largura_imagem, img->h_bitmap->altura_imagem);
    printf("Numero de planos: %hi\n",img->h_bitmap->numero_planos);
    printf("Bits por pixel: %hi\n",img->h_bitmap->bit_per_pixel);
    printf("Compressao usada: %d\n", img->h_bitmap->compressao);
    printf("Tamanho imagem: %d\n",img->h_bitmap->tamanho_imagem);
    printf("Resolucao horizontal: %d pixel por metro\n", img->h_bitmap->pixel_metro_horizontal);
    printf("Resolucao Vertical: %d pixel por metro\n", img->h_bitmap->pixel_metro_vertical);
    printf("Numero de cores usadas: %d\n", img->h_bitmap->numero_cores_usadas);
    printf("Numero de cores importantes: %d\n", img->h_bitmap->numero_cores_importantes);
    // Imprimindo os dados da paleta original.
    printf("PALETA ORIGINAL:\n");
    for(int i = 0; i < 256; i++){
        printf("Paleta[%d]: R:%u G:%u B:%u\n", i, palette[i].red, palette[i].green, palette[i].blue);
    }
    // Imprimindo os dados da paleta nova.
    printf("PALETA NOVA:\n");
    for (int i = 0; i < 256; i++){
        printf("Paleta[%d]: R:%u G:%u B:%u\n", i, img->palette[i].red, img->palette[i].green, img->palette[i].blue);
    }
    
    long long soma = 0;
    // Imprimindo a soma de cada linha (lembrando que a primeira linha seria a última na realidade).
    for(int i = img->h_bitmap->altura_imagem - 1; i >= 0 ; i--){
        for(int j = 0; j < img->h_bitmap->largura_imagem; j++)
            soma += (long long) img->image_matrix[i][j]; 
        soma -= padding;
        printf("Soma linha %d: %lld\n", img->h_bitmap->altura_imagem - 1 - i, soma);
        soma = 0;
    }
    // Imprimindo o nome do novo arquivo.
    printf("%s\n", newfile);
}   

/*
    Função readline:
    Recebe como parâmetro o ponteiro para  o arquivo em que será lidos os dados.
    Retorna a string construída.
*/
char *readline(FILE *stream){
    char *string = NULL;
    int pos = 0;
    do{
        string = (char*) realloc(string, pos+1);
        string[pos++] = fgetc(stream);
    }while(string[pos-1] != '\n' && string[pos-1] != '\r' && !feof(stream));
    string[pos-1] = '\0';
    string = (char*)realloc(string, pos);
    return string;
}