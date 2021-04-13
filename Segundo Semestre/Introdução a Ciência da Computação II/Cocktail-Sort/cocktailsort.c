/*
	ICMC - Instituto de Ciências Matemáticas e de Computação
	Aluno: Bernardo Marques Costa
	Número USP: 11795551
	
	COCKTAIL SORT 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_BUFFER 64

typedef struct _person PERSON;
typedef struct _data DATA;
typedef struct _seach_data SEARCH;

/* Struct que armazena dados de uma pessoa: nome e cidade*/
struct _person {
	char *name;
	char *city;
};

/* Struct que armazena a lista das pessoas e o total de indivíduos*/
struct _data{
	PERSON *list_of_person;
	int num;
};

/* Struct que armazena os nomes buscados e o contador de indivíduos*/
struct _seach_data{
	char **names;
	int num_searchs;
};

/* Função readline: realiza a leitura de uma string a partir de uma stream
   Utilizaremos pra realizar a leitura do stdin.*/
char *readline(FILE *stream){
	char *string = NULL;
	int pos = 0, multiplier = 1;
	char character;

	do{
		character = fgetc(stream);
		
		if(character != '\r'){
			
			if(pos % MIN_BUFFER == 0)
				string = realloc(string, (multiplier++) * MIN_BUFFER);
			
			string[pos++] = character;
		}

	}while(string[pos - 1] != '\n' && !feof(stream));
	
	string = realloc(string, pos);
	
	string[pos-1] = '\0';
	
	return string;
}

/*
	Função create_person_register: 
	Recebe como parâmetro uma string no seguinte formato:
	<nome>. <cidade>
	Realiza o particionamento da string, retornando o registro correspondente a pessoa.
*/
PERSON create_person_register(char *string){
	PERSON data;

	int name_end = 0;

	while(string[name_end] != '.')
		++name_end;

	data.name = calloc((++name_end) + 1, sizeof(char));

	for(int i = 0; i < name_end; ++i)
		data.name[i] = string[i];

	data.name[strlen(data.name)] = '\0';
	
	int city_index = name_end + 1;

	data.city = calloc(strlen(string) - city_index + 1, sizeof(char));

	for(int i = 0, j = city_index; j < strlen(string); ++i, ++j){
		data.city[i] = string[j];
		
		if(data.city[i] == '.') data.city[i] = '\0';
	}

	return data;
}

/*
	Função fill_register:
	A partir dos dados do stdin, realiza a leitura e retorna o registro correspondente 
*/
DATA *fill_register(){
	
	DATA *new_register = calloc(1, sizeof(DATA));

	scanf("%d ", &new_register->num);

	new_register->list_of_person = calloc(new_register->num, sizeof(PERSON));

	char **names_matrix = calloc(new_register->num, sizeof(char*));

	for(int i = 0; i < new_register->num; ++i){
		names_matrix[i] = readline(stdin);
		new_register->list_of_person[i] = create_person_register(names_matrix[i]);
	}

	for(int i = 0; i < new_register->num; ++i)
		free(names_matrix[i]);
	
	free(names_matrix);

	return new_register;
}


void cocktail_sort(PERSON *list, int num_inputs){
	
	PERSON tmp_person; // Criando a variável temporária que servirá para a realização de um swap (rearranjar a ordem dos dados).

	int i, start = 0, is_sorted = 1; // start será variável que corresponde ao inicio da operação, sendo ajustada conforme o laço se repete.
                                   	 // is_sorted será uma flag que indicará 0 para ordenação completa e 1 para não ordenada.
	
	int end = num_inputs - 1;
	
    while(is_sorted){
        is_sorted = 0; 

        // Do início até o fim, são rearranjadas as variáveis do tipo struct DATA de acordo com o campo da string
        // Caso uma posição seja maior que a seguinte, ocorrerá um swap.
        for(i = start; i < end; i++){
            // A função strcmp retorna um número > 0 caso a primeira string seja alfabeticamente maior que a segunda (esteja
            // depois em ordem alfabetica)
            if(strcasecmp(list[i].name, list[i+1].name) > 0){
                tmp_person = list[i+1];
                list[i+1] = list[i];
                list[i] = tmp_person;
                is_sorted = 1;
            }
        }
        // Caso is_sorted seja 0, é entendido que não ocorreu alteração no laço de repetição anterior: o vetor ja está ordernado.
        if(!is_sorted) break;

        is_sorted = 0;

        end -= 1;   // Diminuindo em 1 o final : o último elemento já está ordenado depois do laço anterior.
        
        // Laço de repetição que ocorre do final para o começo do vetor de strings.
        // A forma de operação é semelhante ao laço 'for' anterior.
        for(i = end - 1; i >= start; i--){
            if(strcasecmp(list[i].name, list[i+1].name) > 0){
                tmp_person = list[i+1];
                list[i+1] = list[i];
                list[i] = tmp_person;
                is_sorted = 1;
            }
        }
        ++start; // Acrescendo start, pois a primeiro elemento ja está ordenado depois do último laço.
    }

}

/* Função fill_search_data:
   Realiza o preenchimento do registro de dados buscados com a matriz de nomes e a quantidade de nomes buscados*/
SEARCH* fill_search_data(){
	
	SEARCH *new_data = calloc(1,sizeof(SEARCH));

	scanf("%d ", &new_data->num_searchs);
	
	new_data->names = calloc(new_data->num_searchs, sizeof(SEARCH));

	for(int i = 0; i < new_data->num_searchs; ++i){
		new_data->names[i] = readline(stdin);
		int dot_pos = strlen(new_data->names[i]);
		new_data->names[i][dot_pos] = '\0';
	}

	return new_data;
}

/* Função analyse_search:
	Realiza a análise da busca de cada uma dos nomes buscados printando ao encontrar o nome buscado se a pessoa
	mora em são carlos (1) ou não mora (0)*/
void analyse_search(DATA *registers, SEARCH *search){
	
	int live_in_sc = 0;
	
	for(int i = 0; i < search->num_searchs; ++i){
		char *searched_name = search->names[i];
		for(int j = 0; j < registers->num; ++j){
			char *analysed_name = registers->list_of_person[j].name;
			if(!strcmp(searched_name, analysed_name)){
				if(!strcmp(registers->list_of_person[j].city, "Sao Carlos"))
					live_in_sc = 1;
				
				else
					live_in_sc = 0;
			}
		}
		
		printf("%d\n", live_in_sc);	
	}
}

/* Imprime os nomes, uma vez ordenado */
void print_sorted_list(DATA *registers){
	for(int i = 0; i < registers->num; ++i)
		printf("%s\n", registers->list_of_person[i].name);
}

/* Libera a memória relativa às variáveis da struct SEARCH */
void free_search(SEARCH* search){
	for(int i = 0; i < search->num_searchs; ++i)
		free(search->names[i]);
	free(search->names);
	free(search);
}

/* Libera a memória relativa as variáveis da struct DATA */
void free_register(DATA *registers){
	for(int i = 0; i < registers->num; ++i){
		free(registers->list_of_person[i].name);
		free(registers->list_of_person[i].city);
	}
	free(registers->list_of_person);
	free(registers);
}

int main(int argc, char *argv[]){
	
	DATA* registers = NULL;
	registers = fill_register();

	cocktail_sort(registers->list_of_person, registers->num);

	print_sorted_list(registers);

	SEARCH *search_register = NULL;
	search_register = fill_search_data();

	analyse_search(registers, search_register);

	free_register(registers);
	free_search(search_register);

	return 0;
}