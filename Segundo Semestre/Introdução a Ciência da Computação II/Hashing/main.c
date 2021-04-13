/*
    ICMC - Instituto de Ciências Matemáticas e de Computação 
    Disciplina: Introdução a Ciência da Computação II
    
    Professor: Moacir Ponti
    Aluno: Bernardo Marques Costa - 11795551

    Hashing de alunos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student STUDENT;
typedef struct _hash_table HASH;

// Struct de estudantes 
struct _student {
    char *name; // Guarda o nome dos estudantes
    int hash;   // Guarda a soma ou hashing modular dos estudantes
};

// Struct da hash table
struct _hash_table {
    STUDENT **sitted_students; // Guarda um ponteiro para os estudantes, ou seja, a situação dos estudantes nas cadeiras
    int num_chairs;  // Numero total de cadeiras
    int num_students; // Numero de estudantes na sala
};

// Retorna o hash de um aluno a partir do seu nome e do numero N de cadeiras
int hash_student(char *name, int M) {
    int sum = 0;
    
    for(int i = 0; name[i] != '\0'; ++i)
        sum = (sum + name[i]) % M;
    
    return sum;
}

// Dado um estudantes, adiociona-o na hash table
void sit_student(STUDENT *s, HASH *hash_table) {
    int wait_something_wrong = s->hash;
    int hash = s->hash;

    do {
        if(hash_table->sitted_students[hash] == NULL) {
            hash_table->sitted_students[hash] = s;
            return;
        }
        hash = (hash + 1) % hash_table->num_chairs;
    } while(hash != wait_something_wrong);
}

// Remove um aluno da hash table a partir de seu nome
void stand_up(HASH *hash_table, char *student_name) {
    int hash = hash_student(student_name, hash_table->num_chairs);
    int wait_something_wrong = hash;

    // Verificamos se de cara sua posição esta vazia
    if(hash_table->sitted_students[hash] == NULL)
        return;
    
    // Caso nao esteja vazia, temos que verifica-la, assim como a seguintes ate retornarmos a ela (dando a volta no arrays)
    do { 
        if(hash_table->sitted_students[hash] != NULL) {
            if(strcmp(hash_table->sitted_students[hash]->name, student_name) == 0) {
                hash_table->sitted_students[hash] = NULL;
                return;
            }
        }   
        
        hash = (hash + 1) % hash_table->num_chairs;
    } while(hash != wait_something_wrong);
} 


// Verificamos se um alunos esta sentado, ou seja, se esta na hash table (retornamos a struct com os dados deste aluno 
// alem de retornar por referencia qual a sua posição)
STUDENT *is_sitted(HASH *hash_table, char *student_name, int *position) {
    
    int hash = hash_student(student_name, hash_table->num_chairs);
    int wait_something_wrong = hash;
    
    do {
        if(hash_table->sitted_students[hash] != NULL) {
            if(strcmp(hash_table->sitted_students[hash]->name, student_name) == 0) {
                *position = hash;
                return hash_table->sitted_students[hash];
            }
        } 
        hash = (hash + 1) % hash_table->num_chairs;

    } while(hash != wait_something_wrong);

    return NULL;
}

// Imprimindo a configuração da hash table
void print_chairs_situation(HASH *hash_table) {
    for(int i = 0; i < hash_table->num_chairs; ++i)
        printf("%d: %s\n", i, hash_table->sitted_students[i] != NULL ? hash_table->sitted_students[i]->name : "XXXX");
    
    printf("\n");
}

// Leitura de buffer
char *readline(FILE *stream) {
    char *string = NULL, character;
    int pos = 0;
    do {
        string = realloc(string, pos + 1);
        character = fgetc(stream);
        
        if(character != '\r') 
            string[pos++] = character;
    
    } while(character != '\n' && !feof(stream));

    string[pos - 1] = '\0';

    return string;
}

// Leitura de inteiro
int readint(FILE *stream) {
    char *string_int = readline(stream);
    int value = atoi(string_int);
    free(string_int);
    return value;
}

int main(int argc, char *argv[]) {
    
    int N = readint(stdin);
    int M = readint(stdin);

    STUDENT *students = calloc(M, sizeof(STUDENT));
    
    // Criando a hash table
    HASH *hash_table = calloc(1, sizeof(HASH));
    
    hash_table->sitted_students = calloc(N, sizeof(STUDENT *));
    hash_table->num_chairs = N;
    hash_table->num_students = M;
    
    // Criando as estruturadas dos alunos e adicionando-os a hash table
    for(int i = 0; i < M; ++i) {
        students[i].name = readline(stdin);
        students[i].hash = hash_student(students[i].name, N);
        sit_student(&students[i], hash_table);
    }
    // Imprimindo a configuração inicial
    print_chairs_situation(hash_table);
    
    // Fazendo remoção de alunos
    int R = readint(stdin);
    for(int i = 0; i < R; ++i) {
        char *student_removed = readline(stdin);
        stand_up(hash_table, student_removed);
        free(student_removed);
    }

    // Buscando alunos na hash table
    int K = readint(stdin);
    char **searched_students = calloc(K, sizeof(char *));
    
    for(int i = 0; i < K; ++i) 
        searched_students[i] = readline(stdin);
    
    for(int i = 0; i < K; ++i) {
        int position = 0;
        STUDENT *student = is_sitted(hash_table, searched_students[i], &position);
        
        if(student != NULL) printf("%s esta presente no lugar %d\n", student->name, position);
        else printf("%s nao esta presente\n", searched_students[i]);
    }

    // Liberando a memoria utilizada pelo programa
    // - Nomes buscados: 
    for(int i = 0; i < K; ++i) 
        free(searched_students[i]);
    free(searched_students);

    // - Desalocando o vetor de estudantes
    for(int i = 0; i < hash_table->num_students; ++i) free(students[i].name);
    free(students);

    // Desalocando os ponteiro restantes alocados pela hash table (o bloco de STUDENTS * ja sofreu liberação, logo nao precisamos desaloca-lo)
    free(hash_table->sitted_students);
    free(hash_table);

    return 0;
}