/*
    Aluno: Bernardo Marques Costa
    Número USP: 11795551
*/
#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

double getExecutionTime(time_t startTime, time_t endTime);
char **read_file(char *file_name, int *num_words);
char *readline(FILE *stream);
void saveTimeDataIntoFile(int functionDescriptor, char* dataSize, double time, int executions);

#endif