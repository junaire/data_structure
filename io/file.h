#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

void printFile(const char* filename);

char* getFileContent(const char* filename);

unsigned long getFileSize(const char* filename);

void writeToFile(const char* filename, char* content);

#endif
