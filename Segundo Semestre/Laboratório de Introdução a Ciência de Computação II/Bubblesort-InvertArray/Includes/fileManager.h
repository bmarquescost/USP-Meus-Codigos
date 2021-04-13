#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

char *getFileName(char* dataSize);
int *readVectorDataFile(char *dataSize);
void saveTimeDataIntoFile(int fuctionDescriptor, char * dataSize, double time, int executions);


#endif