/*
	ICMC - INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
	BCC - Bacharelado em Ciências de Computação
	
	ICC II - Moacir Ponti
	Aluno: Bernardo Marques Costa
	Número: 11795551

	Programa para revisão de memória Heap, Recursão e arquivos.
	Resolução de um labirinto do formato:
	# # # # #	
	# * # . .	# -> obstáculos
	# . # . #	. -> caminhos possiveis
	# . # . #	* -> caminhos já percorridos
	# . . . #
	# # # # #

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _lab{
	char **structure;		// Armazena a estrutura do labirinto
	int numberOfColumns;	// número de colunas do labirinto
	int numberOfRows;       // número de linhas do labirinto
	int position_i;         // posição i na matriz, correspondente à linha
	int position_j;         // posição j na matriz, correspondente à coluna
	int possibleWay;        // número total de caminhos possíveis (.)
	int passedBy;			// número total de caminhos passados (*)
	int annoyingRelatives;  // número total de obstáculos (#)
} MAZE;

// Struct nó: armazena dados de cada ponto de retorno quando existe bifurcações, escolhas de mais de um
// caminho possível.
typedef struct _node{
	int i;				// armazena a linha do nó	
	int j;				// armazena a coluna do nó
	int timesPassed;	// armazena o número de vezes em que foi retornado para esse nó
	int numberOfWay;	// número caminhos possiveis a partir deste nó.
} NODE;


char *readLine(FILE *);
void readMaze(FILE *, MAZE*);
void printMaze(MAZE *);
MAZE *solveMaze(MAZE *,int, int, NODE **, int *);
int countAllCharacter(MAZE *, char );
MAZE* initializeMazeStruct();

int main(int argc, char *argv[]){
	char *filename = NULL;
	filename = readLine(stdin);

	FILE *filepointer = NULL;

	// abertura do arquivo
	if (!(filepointer = fopen(filename, "r+"))){
		printf("Erro na abertura do arquivo do labirinto\n");
		exit(1);
	}


	MAZE *maze = initializeMazeStruct(); 
	readMaze(filepointer, maze);

	NODE *nodes = NULL;
	int numberOfNodes = 0;

	maze = solveMaze(maze, maze->position_i, maze->position_j, &nodes, &numberOfNodes);

	maze->passedBy = countAllCharacter(maze, '*');

	printMaze(maze);
	printf("Voce escapou de todos! Ninguem conseguiu te segurar!\n");
	printf("Veja abaixo os detalhes da sua fuga:\n");
	printf("----Pessoas te procurando: %d\n", maze->annoyingRelatives);
	printf("----Numero total de caminhos validos:   %d\n", maze->possibleWay);
	printf("----Numero total de caminhos visitados: %d\n", maze->passedBy);
	
	double percentage = (maze->passedBy * 100/ maze->possibleWay);
	printf("----Exploracao total do labirinto: %.1lf%%\n", percentage); 
	
	free(filename);
	fclose(filepointer);
	for(int i = 0; i < maze->numberOfRows; i++)
		free(maze->structure[i]);
	free(maze->structure);
	free(maze);
	free(nodes);

	return 0;
}

/*
	Função readLine:
	- Realiza a leitura de caracteres a partir de uma stream até que se encontre uma
	nova linha (\n), \r ou que encontre o final da stream (EOF). 
	- Retorna a string obtida.
*/
char *readLine(FILE *stream){
	char *string = NULL;
	int pos = 0;
	do{
		string = realloc(string, pos+1);
		string[pos] = fgetc(stream);
		pos++;
	}while(string[pos - 1] != '\n' && string[pos - 1] != '\r' && !feof(stream));
	string[pos-1] = '\0';
	return string;
}

MAZE *initializeMazeStruct(){
	MAZE *maze = NULL;
	maze = calloc(1, sizeof(MAZE));

	maze->numberOfColumns = 0;
	maze->numberOfRows = 0;
	maze->passedBy = 0;
	maze->possibleWay = 0;
	maze->annoyingRelatives = 0;
	maze->position_i = 0;
	maze->position_j = 0;
	maze->structure = NULL;
	
	return maze;
}

/*
	Função readMaze:
	Realiza a leitura a partir do arquivo dado de entrada, armazenando os dados em 
	uma estrutura do tipo MAZE *.
	Retorna a estrutura obtida.
*/
void readMaze(FILE *fp, MAZE *maze){
	
	fscanf(fp, "%d %d\n%d %d", &maze->numberOfRows, &maze->numberOfColumns , 
				&maze->position_i, &maze->position_j);
	
	maze->structure = calloc(maze->numberOfRows, sizeof(char*));
	for(int i = 0; i < maze->numberOfRows; i++) 
		maze->structure[i] = calloc(maze->numberOfColumns + 1, sizeof(char));

	for(int i = 0; i < maze->numberOfRows; i++)
		fscanf(fp, "%s[^\n]", maze->structure[i]);
		// fread(maze->structure[i], sizeof(char), maze->numberOfColumns, fp);

	maze->possibleWay = countAllCharacter(maze, '.');
	maze->annoyingRelatives = countAllCharacter(maze, '#');
	maze->structure[maze->position_i][maze->position_j] = '*';

}


/*
	Função countPossibleWays:
	- Recebe como parâmetro a struct e as coordenadas na estrutura da matriz.
	- Realiza a análise identificando quantos caminhos (bifurcações, etc) existem nesta posição.
	- Retorna a quantidade de caminhos possíveis.
*/
int countPossibleWays(MAZE *maze, int pos_i, int pos_j){
	int ways = 0;

	if(pos_i - 1 >= 0)
		if(maze->structure[pos_i - 1][pos_j] == '.') ways++;
	if(pos_j + 1 <= maze->numberOfColumns)
		if(maze->structure[pos_i][pos_j + 1] == '.') ways++;
	if(pos_i + 1 < maze->numberOfRows)	
		if(maze->structure[pos_i + 1][pos_j] == '.') ways++;
	if(pos_j - 1 >= 0)
		if(maze->structure[pos_i][pos_j - 1] == '.') ways++;

	return ways;
}

/*
	Função createNode:
	- Inicializa um nó com os dados das coordenadas [i][j] deste nó na matriz, quantas vezes foi
	passado (inicializado sempre como 1, uma vez que o proximo passo resulta em um proximo caminho) 
	e o número de caminhos possíveis.
	- Retorna o nó.
*/
NODE createNode(int i, int j, int timesPassed, int ways){
	
	NODE nodeData;
	nodeData.i = i;
	nodeData.j = j;
	nodeData.timesPassed = timesPassed;
	nodeData.numberOfWay = ways;

	return nodeData;
}

/*
	Função solveMaze:
	- Função recursiva que realiza a resolução do labirinto.
	- A cada passo recursivo, recebe as coordenadas [i][j] dentro do labirinto.
	Verificado a não resolução, realizamos a seguinte ordem de análise para prosseguir 
	a uma nova posição: cima -> direita -> baixo -> esquerda.
	- Verificamos se tal posição constitui um nó, sendo necessário considera-lo caso seja necessário
	voltar para ele em algum momento.
	- Quando não há mais caminho possível, voltamos ao nó superior, descendo o vetor até que seja 
	encontrado caminhos alternativos.
	- Retornamos a estrutura final, sendo o resultado do labirinto 
*/
MAZE *solveMaze(MAZE *maze, int pos_i, int pos_j, NODE **nodeArray, int *nodesCounter){	
	
	// Conferindo sucesso.
	if(pos_i == 0 || pos_j == 0 || pos_i == maze->numberOfRows - 1 || pos_j == maze->numberOfColumns - 1)
		return maze;	

	int paths = countPossibleWays(maze, pos_i, pos_j);

	// Criando nó
	if(paths > 1){
		(*nodeArray) = realloc(*nodeArray, sizeof(NODE) * (*nodesCounter + 1));
		(*nodeArray)[*nodesCounter] = createNode(pos_i, pos_j, 1, paths);
		(*nodesCounter)++;
	}

	// Cima
	if(maze->structure[pos_i - 1][pos_j] == '.'){
		maze->structure[pos_i - 1][pos_j] = '*';
		return solveMaze(maze, pos_i - 1, pos_j, nodeArray, nodesCounter);
	}

	// Direita
	if(maze->structure[pos_i][pos_j + 1] == '.'){
		maze->structure[pos_i][pos_j + 1] = '*';
		return solveMaze(maze, pos_i, pos_j + 1, nodeArray, nodesCounter);	
	}

	// Baixo	
	if(maze->structure[pos_i + 1][pos_j] == '.'){
		maze->structure[pos_i + 1][pos_j] = '*';
		return solveMaze(maze, pos_i + 1, pos_j, nodeArray, nodesCounter);
	}
	
	// Esquerda
	if(maze->structure[pos_i][pos_j - 1] == '.'){
		maze->structure[pos_i][pos_j - 1] = '*';
		return solveMaze(maze,pos_i, pos_j - 1, nodeArray, nodesCounter);
	}

	// Situação de bloqueio, retornando ao último nó.
	if(*nodeArray != NULL){
		
		int previous_i = (*nodeArray)[*nodesCounter - 1].i;
		int previous_j = (*nodeArray)[*nodesCounter - 1].j;
		
		// Caso o número de caminhos inicais possíveis a partir deste nó seja equuivalente ao número de vezes
		// em que retornamos para ele (significando que tentamos todas possibilidades dele), devemos voltar ao
		// nó anterior à ele, no índice abaixo do vetor. 
		if((*nodeArray)[*nodesCounter - 1].timesPassed == (*nodeArray)[*nodesCounter - 1].numberOfWay)
			(*nodeArray) = realloc(*nodeArray, sizeof(NODE) * ((*nodesCounter)--));
		
		else (*nodeArray)[*nodesCounter - 1].timesPassed++;
		
		return solveMaze(maze,previous_i, previous_j, nodeArray, nodesCounter);
	}

	return NULL;
}


/*
	Função countAllCharacter:
	- Retorna a contagem de um caracter, passado como parâmetro, na estrutura do labirinto.
*/
int countAllCharacter(MAZE *maze, char character){
	int counter = 0;

	for(int i = 0; i < maze->numberOfRows; i++){
		for(int j = 0; j < maze->numberOfColumns; j++)
			if(maze->structure[i][j] == character) counter++;
	}

	return counter;
}

// Função printMaze: imprime o labirinto.
void printMaze(MAZE *maze){
	for(int i = 0; i < maze->numberOfRows; i++){
		printf("%s\n", maze->structure[i]);
	}
	printf("\n");
}