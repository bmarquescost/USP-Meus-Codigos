/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa: BANCO DE DADOS

    Aluno : Bernardo Marques Costa
    Número USP : 11795551

    Programa que deve funcionar como um banco de dados.                 | filename : <nome do arquivo>   |
                                                                        | key-name: <nome da chave>      |
    Deverá ler um arquivo de metadados, contendo a seguinte estrutura:  | key-type: <tipo da chave>      |
                                                                        | field-name: <nome do campo>    |
                                                                        | field-type: <tipo do campo>    |
                                                                        |               ...              |
    
    Após lê-lo, deverá considerar as seguinte instruções na linha de comando:

    insert -> inserir em um arquivo dados de acordo com os campos obtidos no arquivo de metadados, e que possuirá o nomed
              dado pelo primeira linha do arquivo .dat.
    search -> procurar um registro de acordo com a chave desejada.
    index  -> criar um arquivo .idx, que armazena em ordem crescente (de acordo com o valor da chave de cada inserção) a inserção
              e o offset desta inserção no arquivo .reg.
    exit   -> sair do programa. 

*/

#include "SuportSGBD.h"

int main(int argc, char *argv[]){
    
    ARCHIVES_DATA *data = NULL;
    
    INSERTION *inserts = NULL;
    
    FIELD *field_data = NULL;
    
    data = initializeArchiveInfo(); // inicializando os dados.
    field_data = readMetadata(data); // Recebendo os dados.
    separateByToken(data, field_data); 
    findType(data, field_data);
    standarOffset(data, field_data);
    data->idx_file_name = createIdxName(data->register_file_name);
    
    int index_counter = 0;

    // Declarando a matrix de strings, responsável por armazenar cada uma das linhas de instruções executadas pelo usuário do programa.
    char **command_matrix = NULL;
    int command_counter = 0;
    int command_enum = 0;
    command_matrix = (char**)realloc(command_matrix, (command_counter + 1)*sizeof(char*));
    command_matrix[command_counter] = readline(stdin);
    command_enum = decodeInstruction(command_matrix[command_counter]);
    
    // Laço em que ocorre todo o programa, até que o usuário digite o comando exit.
    while(command_enum != EXIT){
        if(command_enum == INSERT_MODE){
            // Laço de repetição para construir um vetor de instruções sequencial, minimizando o número de vezes em que se é necessário
            // abrir o arquivo para inserção dos dados.
            while(command_enum == INSERT_MODE){
                insertFunction(data, field_data, &inserts, command_matrix[command_counter]);
                command_counter++;
                data->insertion_counter++;
                command_matrix = (char**)realloc(command_matrix, (command_counter + 1) * sizeof(char*));
                command_matrix[command_counter] = readline(stdin);
                command_enum = decodeInstruction(command_matrix[command_counter]);
            }
            // Criando e preenchendo o arquivo.
            // OBS: caso o programa já tenha recebido a instrução de insert, mas tenha sido interrompido e posteriormente acrescentada outra inserção,
            //      o vetor de instruções será acrescido, e um novo arquivo será construído, reescrevendo tanto os dados anteriores quanto os novos.
            createFileRegister(data, field_data, inserts);
        }

        if(command_enum == SEARCH_MODE && data->insertion_counter){
            if(!(index_counter)) createIdxFile(data, inserts);  // Caso não seja criado um arquivo idx, será necessário criá-lo para realizar a busca.
            searchFunction(data, field_data, inserts, command_matrix[command_counter]);
        }

        else if(command_enum == INDEX_MODE){
            createIdxFile(data, inserts);
            index_counter++;
        }
        // Realocando e recebendo a nova linha de comando do usuário.
        command_counter++;
        command_matrix = (char**)realloc(command_matrix, (command_counter + 1)*sizeof(char*));
        command_matrix[command_counter] = readline(stdin);
        command_enum = decodeInstruction(command_matrix[command_counter]);
    }

    //No fim, haverá um comando (exit) desconsiderado, então é necessário contabilizado posteriormente.
    command_counter++;
    
    // Realizando os frees necessários.
    if(command_counter) freeMatrix(&command_matrix, command_counter);
    if(data->insertion_counter && data->number_of_fields) freeInsertions(&inserts, data->insertion_counter, data->number_of_fields);
    if(data->number_of_fields) freeFields(&field_data, data->number_of_fields);
    if(data) freeDataSruct(&data);

    return 0;
}