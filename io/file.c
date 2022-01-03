#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file.h"

void printFile(const char* filename){
	FILE* f = fopen(filename, "r");

	while(!feof(f)){
		char c = fgetc(f);
		printf("%c",c);
	}
	printf("\n");

	fclose(f);
}

char* getFileContent(const char* filename) {

	unsigned long size = getFileSize(filename);
	char* content = (char*)malloc(sizeof(char) * size);
	FILE* f = fopen(filename, "r");

	for (int i = 0; i < size; ++i){
		content[i] = fgetc(f);
	}
	fclose(f);

	return content;
}

unsigned long getFileSize(const char* filename) {
    FILE * f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}

void writeToFile(const char* filename, char* content){
	FILE* f = fopen(filename, "w");
	fprintf(f,"%s", content);
	fclose(f);
}

int countWord(const char* filename){

	int cnt = 0;
	char* content = getFileContent(filename);

	for (char* ch = content; *ch != '\0'; ++ch){
		if (isspace(*ch)){
			cnt++;
		}
	}
	free(content);
	return cnt;
}
