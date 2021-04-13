/*
    Aluno : Bernardo Marques Costa
    Número USP : 11795551   
    Programa: BANCO DE DADOS
*/

#include "SuportSGBD.h"

/*
    Função readline:
    Realiza a leitura de um buffer, até o \n.
    Retorna a string formada.
*/
char *readline(FILE *stream){
    char *string = NULL;
    int pos = 0;
    do{
        string = (char*)realloc(string, pos+1);
        string[pos] = (char) fgetc(stream);
        if (string[pos] != '\r') pos++; 
    }while(string[pos-1] != '\n' && !feof(stream));
    string[pos-1] = '\0';
    string = (char*)realloc(string, pos);
    return string;
}

/*
    Função initializeArchiveInfo:
    Inicializa os campos da struct do tipo ARCHIVE_INFO, retornando um bloco alocado na memória heap.
*/
ARCHIVES_DATA *initializeArchiveInfo(){
    ARCHIVES_DATA *data;
    data = (ARCHIVES_DATA*)calloc(1, sizeof(ARCHIVES_DATA));
    data->offset = sizeof(int);
    data->number_of_fields = 0;
    data->insertion_counter = 0;
    data->register_file_name = NULL;
    data->key_type = NULL;
    data->key_name = NULL;
    data->idx_file_name = NULL;
    data->data_file_name = NULL;
    return data;
}

/*
    Função separaString:
    Recebe como parâmetro uma cadeia de caracteres, e realiza uma separação desta string de acordo com o token de separação
    filename: registros.reg --> registros.reg
*/
void separateString(char *string){
    char *auxiliar = NULL;
    int pos_string = 0, pos_token = 0, pos_auxiliar = 0;

    while (string[pos_token] != TOKEN)
        pos_token++;

    pos_string = pos_token + 2;
    
    do{
        auxiliar = (char*)realloc(auxiliar, pos_auxiliar + 1);
        auxiliar[pos_auxiliar] = string[pos_string];
        pos_auxiliar++;
        pos_string++;
    } while(string[pos_string - 1] != '\0' && string[pos_string - 1] != '\n');
    
    int length = strlen(auxiliar);
    for ( int i = 0; i < pos_auxiliar; i++)
        string[i] = auxiliar[i];
    
    string[length] = '\0';
    
    free(auxiliar);
}

/*
    Função separateByToken:
    Função que redireciona todas strings que seguem o padrão do token para a função que efetua o particionamento da string.
*/
void separateByToken(ARCHIVES_DATA *data, FIELD *fields){
    separateString(data->register_file_name);
    separateString(data->key_name);
    separateString(data->key_type);
    for (int i = 0; i < data->number_of_fields; i++){
        separateString(fields[i].field_name);
        separateString(fields[i].field_type);
    }
}

/*
    Função stringSizeReturn:
    Recebe como parâmetro uma string, que deve estar no formato char[<NUMERO>]
    Retorna o valor inteiro correspondente ao número de bytes desta cadeia de caracteres.
*/
int stringSizeReturn(char *string){
    int pos = 0, aux_integer = 0;
    char *integer_in_char = NULL;
    while(string[pos] != '[') pos++;
    pos++;
    while(string[pos] != ']'){
        integer_in_char = (char*)realloc(integer_in_char, aux_integer + 1);
        integer_in_char[aux_integer] = string[pos];
        pos++;
        aux_integer++;
    }
    integer_in_char = (char*)realloc(integer_in_char, aux_integer + 1);
    integer_in_char[aux_integer] = '\0';
    
    int size = atoi(integer_in_char);

    free(integer_in_char);

    return size;
}

/*
    Função findType:
    Recebe como parâmetro o número de campos existentes no arquivo de metadados lidos e a struct que armazena as informações deste campo.
    Adiciona o tamanho em bytes daquele campo, sendo diferenciado em int, float, double e char[<inteiro>] 
*/
void findType(ARCHIVES_DATA *data, FIELD *field_data){
    for (int i = 0; i < data->number_of_fields; i++){
        if (field_data[i].field_type[0] == 'i') field_data[i]. bytes_size = sizeof(int);
        else if(field_data[i].field_type[0] == 'f') field_data[i].bytes_size = sizeof(float);
        else if(field_data[i].field_type[0] == 'c') field_data[i].bytes_size = sizeof(char) * stringSizeReturn(field_data[i].field_type);
        else if(field_data[i].field_type[0] == 'd') field_data[i].bytes_size = sizeof(double);
    }
}

/*
    Função standartOffset:
    Calcula qual o offset padrão a partir dos tipos de cada campo, informados pelo arquivo de metadados.
    Somatoria de todos os valores de bytes dos campos.
*/
void standarOffset(ARCHIVES_DATA *data, FIELD *field_data){
    for(int i = 0; i < data->number_of_fields; i++){
        data->offset += field_data[i].bytes_size;
    }
}


/*  
    Função readMetadata:
    Recebe como parâmetro o ponteiro para uma struct do tipo ARCHIVES_DATA, preenchendo cada um de seus campos.
*/
FIELD *readMetadata(ARCHIVES_DATA *data){
    FIELD *fields = NULL;

    data->data_file_name = readline(stdin);
    
    FILE *data_filepointer = NULL;
    
    if(!(data_filepointer = fopen(data->data_file_name, "r"))){
        free(data->data_file_name);
        free(data);
        printf("Erro na abertura do arquivo .dat\n");
        exit(1);
    }

    data->register_file_name = readline(data_filepointer);
    data->key_name = readline(data_filepointer);
    data->key_type = readline(data_filepointer);

    
    while(!feof(data_filepointer)){
        fields = (FIELD*)realloc(fields, (data->number_of_fields + 1)*sizeof(FIELD));
        fields[data->number_of_fields].field_name = readline(data_filepointer);
        // Eventuais linhas vazias e a mais no arquivo .dat deverão ser corrigidas. 
        if(fields[data->number_of_fields].field_name[0] == '\0'){
            free(fields[data->number_of_fields].field_name);
            fields = (FIELD*)realloc(fields, (data->number_of_fields) * sizeof(FIELD));
            continue;
        } 
        fields[data->number_of_fields].field_type = readline(data_filepointer);
        data->number_of_fields++;
    }

    fclose(data_filepointer);
    
    return fields;
}

/*
    Função creadIdxName:
    Recebe como parâmetro a cadeia de caracteres que corresponde ao nome do arquivo inicial.
    Retorna o nome do arquivo no formato .idx
*/
char *createIdxName(char *file_name){
    char *name = NULL;
    int dot_pos = 0;
    while (file_name[dot_pos] != '.')
        dot_pos++;

    int size = 4 + dot_pos;
    name = (char *)calloc(size+1, sizeof(char));
    
    for(int j = 0; j <= dot_pos; j++)
        name[j] = file_name[j];
    
    name[dot_pos+1] = 'i';
    name[dot_pos+2] = 'd';
    name[dot_pos+3] = 'x';
    name[dot_pos+4] = '\0';

     return name;
}   


/*
    Função decodeInstruction:
    Recebe como parâmetro a cadeia de caracteres correspondente ao comando desejado.
    Retorna um inteiro representado por meio de uma enumeração estabelecida arbitrariamente.
*/
int decodeInstruction(char *instruction){
    int pos = 0;
    char *auxiliar = NULL;
    do {
        auxiliar = (char*)realloc(auxiliar, pos + 1);
        auxiliar[pos] = (instruction[pos] == ' ') ? '\0': instruction[pos];
        pos++;
    } while(auxiliar[pos - 1] != '\0');

    if (!strcmp(auxiliar, "insert")){
        free(auxiliar);
        return INSERT_MODE;
    }
    else if (!strcmp(auxiliar, "search")){
        free(auxiliar);
        return SEARCH_MODE;
    } 
    else if (!strcmp(auxiliar, "index")){
        free(auxiliar);
        return INDEX_MODE;
    }
    else if (!strcmp(auxiliar, "exit")){
        free(auxiliar);
        return EXIT;
    } 
    else{ 
        free(auxiliar);
        return -1;
    }
}


/*
    Função takeKey:
    Recebe como parâmetro o ponteiro para o bloco de memória em que será armazenada a chave que será encontrada na função, além 
    da string correspondente ao comando.
    Possui como retorno o indice em que a chave foi encontrado, sendo útil em alguns casos para prosseguir na análise da linha de comando.
*/
int takeKey(unsigned int *key, char *command){

    int pos_ins = 0;
    char *auxiliar = NULL;
    int pos_aux = 0;
    while(command[pos_ins] != ' ') pos_ins++;
    pos_ins++;

    while(command[pos_ins] != SEPARATOR && command[pos_ins] != '\0' && command[pos_ins] != '\n' && command[pos_ins] != '\r'){
        auxiliar = (char*)realloc(auxiliar, pos_aux + 1);
        auxiliar[pos_aux] = command[pos_ins];
        pos_aux++;
        pos_ins++;
    }
    
    auxiliar = (char*)realloc(auxiliar, pos_aux + 1);
    
    auxiliar[pos_aux] = '\0';
    
    *key = atoi(auxiliar);
    
    free(auxiliar);

    return pos_ins;
}     


/*
    Função takeField:
    A função recebe o vetor de struct de todas instruções realizadas no programa, o índice deste vetor, o comando realizado,
    a posição inicial de análise e o índice de inserção correspondente à qual campo de metadados está sendo lido. 
    Retorna o indice na linha de comando em que haverá prosseguimento da leitura.
*/
int takeField(INSERTION **insert, int index, char *command, int starting_pos, int insertion_index){
    
    char *auxiliar = NULL;
    int pos_aux = 0;
    while(command[starting_pos] != SEPARATOR && command[starting_pos] != '\n' && command[starting_pos] != '\r' && command[starting_pos] != '\0'){
        auxiliar = (char*)realloc(auxiliar, pos_aux + 1);
        auxiliar[pos_aux] = command[starting_pos];
        pos_aux++;
        starting_pos++; 
    }

    auxiliar = (char*)realloc(auxiliar, pos_aux + 1);
    auxiliar[pos_aux] = '\0';

    int pos_data = 0;

    (*insert)[index].inserted[insertion_index] = (char*)calloc(strlen(auxiliar) + 1, sizeof(char));

    do{
        (*insert)[index].inserted[insertion_index][pos_data] = auxiliar[pos_data];
        pos_data++;
    }while(auxiliar[pos_data - 1] != '\0');

    free(auxiliar);
    // o retorno é de 2 posições a mais que o fim obtido nesta função, para começar a nova análise exatamente na próxima info
    // Considerando o padrão : <informação>, <nova informação>   <informação>, <nova informação> 
    //                                     |  <- onde para                     | <- posição retornada. 
    return (starting_pos + 2);
}


/*
    Função stringPattern:
    Ao receber uma informação do tipo string, no formato "<string>", a função stringPattern é chamada 
    para converter a cadeia para <string>, retirando as aspas duplas.
*/
void stringPattern(char *string){
    int pos = 1;
    char *auxiliar = NULL;
    if (string) auxiliar = (char*)calloc(strlen(string) - 1, sizeof(char));
    
    while(string[pos] != STRING_PATTERN){
        auxiliar[pos-1] = string[pos];
        pos++;
    }

    auxiliar[pos - 1] = '\0';

    pos = 0;
    
    do{
        string[pos] = auxiliar[pos];
        pos++;
    }while(auxiliar[pos-1] != '\0');
    
    free(auxiliar);
}

/*
    Função insertFunction:
    Recebe como parâmetro a struct que armazena as informações gerais dos arquivos cridos pelo programa, a struct dos campos,
    o vetor de instruções por referência e a linha de comando.
    A cada inserção realizada pelo usuário, a função é chamada de modo a acrescentar ao vetor de inserções, que contem nele
    uma matriz de strings, a chave e o offset destes novos dados.
*/
void insertFunction(ARCHIVES_DATA *data, FIELD *field, INSERTION **insert_data, char *command){
    
    int index = data->insertion_counter;
    
    *insert_data = (INSERTION *)realloc(*insert_data, (index + 1) * sizeof(INSERTION));
    
    (*insert_data)[index].offset_insertion = data->offset * index;

    int index_new_info = 2 + takeKey(&(*insert_data)[index].key, command); // a nova informação estará deslocada em 2 posições a frente do separador ','.

    (*insert_data)[index].inserted = (char**)calloc(data->number_of_fields, sizeof(char*));
    
    // O laço preenche para cada campo de metadados, a informação obtida, sendo armazenada como uma cadeia de caracteres indiferenciadamente. 
    for (int i = 0; i < data->number_of_fields; i++){
        (*insert_data)[index].inserted[i] = NULL;
        index_new_info = takeField(insert_data, index, command, index_new_info, i);
        if(field[i].field_type[0] == 'c') stringPattern((*insert_data)[index].inserted[i]);
    }

}

/*
    Função ordenateIndex:
    Recebe como parâmetros os dados e o vetor de inserções.
    Ao criar e preencher um vetor de ordenação de forma crescente, definimos que cada elemento, em cada posição, corresponde a um indice.
    exemplo
    vetor       [0] [1] [2] [3] [4] ...
    elementos    2   1   3   4   0  ...
    Temos então que a ordem crescente para um outro vetor será vetor[2] < vetor[1] < vetor[3] < vetor[4] < vetor[0] ...      
*/
int *ordenateIndex(ARCHIVES_DATA *data, INSERTION *insertion){
    int *v_order = (int*)calloc(data->insertion_counter, sizeof(int));
    
    for(int i = 0; i < data->insertion_counter; i++) v_order[i] = i;

    // Bubble sort em relação as chaves dos elementos do vetor do tipo vetor struct INSERTION.
    for(int k = 0; k < data->insertion_counter; k++){
        for (int i = 0; i < data->insertion_counter; i++){
            if(insertion[v_order[k]].key < insertion[v_order[i]].key) {
                
                // Swap em relação ao vetor de ordenação.
                int aux = v_order[k];    
                v_order[k] = v_order[i];
                v_order[i] = aux;
            }
        }
    }
    return v_order;
}


/*
    Função createIdxFile:
    Recebe como parâmetro os dados do arquivo e as toda inserções feitas até dado momentos.
    Após criar e abrir o arquivo com extensão idx no formato de escrita binária, é realizada a ordenação do vetor de ordem, a partir 
    das chaves de todas inserções.
    Por fim, preenche o arquivo seguindo a ordem crescente das chaves das inserções. 
*/
void createIdxFile(ARCHIVES_DATA *data, INSERTION *insertion){
    
    FILE *idx_filepointer = NULL;
    if(!(idx_filepointer = fopen(data->idx_file_name, "wb"))){
        freeInsertions(&insertion, data->insertion_counter, data->number_of_fields);
        freeDataSruct(&data);
        exit(1);
    }

    int *v_order = NULL;
    v_order = ordenateIndex(data, insertion);
  
    for (int i = 0; i < data->insertion_counter; i++){
        fwrite(&insertion[v_order[i]].key, sizeof(int), 1, idx_filepointer);
        int auxiliar = insertion[v_order[i]].offset_insertion;
        fwrite(&auxiliar, sizeof(int), 1, idx_filepointer);
    }
    
    free(v_order);

    fclose(idx_filepointer);
}


/*
    Função binarySearch:
    Realiza uma busca binária em relação a chave das inserções, retornando o indice correspondente, caso encontrado.
    Lembrando: a busca binária é feita a partir dos dados obtidos pelo .idx, uma vez que as inserções ja estão ordenadas de acordo com suas chaves.
*/
int binarySearch(SEARCH_DATA *insert, int left, int right, int key){
    if (right >= left){
        int middle = left + (right - left)/2;
        if(insert[middle].key == key) return middle;
        if(insert[middle].key > key) return binarySearch(insert, left, middle - 1, key);
        else return binarySearch(insert, middle + 1, right, key);
    }
    else return -1;
}

/*
    Função searchFunction:
    Responsável por realizar a busca de um registro, a partir de uma chave dada pelo usuário na linha de comando.
    Realiza a abertura do arquivo idx, consultando e preenchendo o vetor de struct do tipo SEARCH_DATA, no qual serão
    armazenadas as chaves e os offsets das inserções.
*/
void searchFunction(ARCHIVES_DATA *data, FIELD *field, INSERTION *insert, char *command){
    
    FILE *idx_filepointer = NULL;
    
    if(!(idx_filepointer = fopen(data->idx_file_name, "rb"))){
        free(command);
        freeInsertions(&insert, data->insertion_counter, data->number_of_fields);
        freeFields(&field, data->number_of_fields);
        freeDataSruct(&data);
        exit(1);
    }

    SEARCH_DATA *idx_data = NULL;
    idx_data = (SEARCH_DATA*)calloc(data->insertion_counter, sizeof(SEARCH_DATA));
    
    unsigned int key = 0;
    takeKey(&key, command);

    // Preenchendo os dados.
    for(int i = 0; i < data->insertion_counter; i++){
        fread(&idx_data[i].key, sizeof(unsigned int), 1, idx_filepointer);
        fread(&idx_data[i].offset, sizeof(unsigned int), 1, idx_filepointer);
    }
    
    fclose(idx_filepointer);

    // Realizando as busca binária no vetor dos dados obtidos pelo idx, uma vez que já se encontram ordenados pela chave.
    int index_key = binarySearch(idx_data, 0, data->insertion_counter, key);

    if(index_key != -1){

        int index_in_reg = 0;  // indice no arquivo .reg (correspondente ao indice na ordem em que foi feito os inserts.
        index_in_reg = idx_data[index_key].offset / data->offset;
        
        printf("%s: %d\n", data->key_name, insert[index_in_reg].key);

        for(int i = 0; i < data->number_of_fields; i++){
            if(field[i].field_type[0] == 'f') printf("%s: %.2f\n", field[i].field_name, atof(insert[index_in_reg].inserted[i]));
            
            else if(field[i].field_type[0] == 'd') printf("%s: %.2lf\n", field[i].field_name, strtod(insert[index_in_reg].inserted[i], NULL));
        
            else printf("%s: %s\n", field[i].field_name, insert[index_in_reg].inserted[i]);
        }
        printf("\n");
    }

    free(idx_data);
}

/*  
    Função createFileRegister:
    A função recebe os dados gerais do arquivos armazenados na struct, os campos e todas inserções.
    Cria o arquivo no formado de escrita binária, preenchendo (de acordo com o tipo de cada campo) os dados obtidos pelo 
    comando de inserção, já tratados e armazenados no vetor de struct INSERTION insert_data.
*/
void createFileRegister(ARCHIVES_DATA *data, FIELD *field_data, INSERTION *insert_data){
   
    FILE *filepointer = NULL;

    if (!(filepointer = fopen(data->register_file_name, "wb"))){
        freeInsertions(&insert_data, data->insertion_counter, data->number_of_fields);
        freeFields(&field_data, data->number_of_fields);
        freeDataSruct(&data);
        exit(1);
    }

    for(int i = 0; i < data->insertion_counter; i++){
        fwrite(&insert_data[i].key, sizeof(int), 1, filepointer);
        
        // Escrevendo no arquivo cada campo, realizando a conversão para cada tipo (int, double, float ou char).
        for(int j = 0; j < data->number_of_fields; j++){
            
            if (field_data[j].field_type[0] == 'i'){
                int aux = atoi(insert_data[i].inserted[j]);
                fwrite(&aux, sizeof(int), 1, filepointer);
            }
            else if (field_data[j].field_type[0] == 'f'){
                float aux = atof(insert_data[i].inserted[j]);
                fwrite(&aux, sizeof(float), 1, filepointer);
            }
            else if (field_data[j].field_type[0] == 'd'){
                double aux = strtod(insert_data[i].inserted[j], NULL);
                fwrite(&aux, sizeof(double), 1, filepointer);
            }
            else if (field_data[j].field_type[0] == 'c'){
                char *aux = NULL;
                int pos = 0;
                aux = (char*)calloc(field_data[j].bytes_size, sizeof(char));
                do{
                    aux[pos] = insert_data[i].inserted[j][pos];
                    pos++;
                }while(insert_data[i].inserted[j][pos-1] != '\0');

                fwrite(aux, sizeof(char), field_data[j].bytes_size, filepointer);
                free(aux);
            }
        }
    }

    fclose(filepointer);
}

// Função freeMatrix: realiza a desalocação da matriz de comandos executados pelo usuário
void freeMatrix(char ***matrix, unsigned int size){
    for(int i = 0; i < size; i++)
        free((*matrix)[i]);
    free(*matrix);
    *matrix = NULL;
}

// Função freeFields: realiza a desalocação dos campos.
void freeFields(FIELD **field, unsigned int size){
    for(int i = 0; i < size; i++){
        free((*field)[i].field_name);
        free((*field)[i].field_type);
    }
    free(*field);
    *field = NULL;
}

// Função freeInsertions: desaloca todas as inserções executadas.
void freeInsertions(INSERTION **insertion, unsigned int size, unsigned int n_fields){
    for (int i = 0; i < size; i++){
        for(int j = 0; j < n_fields; j++)
            free((*insertion)[i].inserted[j]); 
        free((*insertion)[i].inserted);
    }   
    free(*insertion);
    *insertion = NULL;
}

// Função freeDataStruct: desaloca todos os dados.
void freeDataSruct(ARCHIVES_DATA **data){
    free((*data)->data_file_name);
    free((*data)->register_file_name);
    free((*data)->idx_file_name);
    free((*data)->key_name);
    free((*data)->key_type);
    free(*data);
    *data = NULL;
}