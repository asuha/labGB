/*
 ============================================================================
 Name        : antivirus.c
 Author      : Julio Renner
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char* virusSignature;
const char* FILE_NAME="./teste.txt";
const char* GZIP_FILE_NAME="./teste.txt.gz";

FILE* openFile(const char* sFilePath);

int main(int argc, const char * argv[]) {
    printf("abriu\n");
	FILE* fp = openFile(GZIP_FILE_NAME);
	char buff[255];

	//fread(buff,2,1,fp);

	//printf("%d %d", buff[0], buff[1]);
	//fgetc(fp);

	char byte;
	while( (byte=fgetc(fp)) != EOF){
		printf("%d\t", byte);
	}

	//int array[2] = {3,5};
	//int idx = 1;

	//printf("%d\n", idx[array]);
}

FILE* openFile(const char* sFilePath){
	printf("openFIle\n");


    FILE* fp = (FILE*)malloc(sizeof(FILE));
    fp = fopen(sFilePath, "r");

    if (!fp) {
    	perror("Não encontrou o arquivo");
    	exit(1);
    }

    return fp;

/*    char teste[150] = "";

    int res = read(iFile, teste, 150);

    printf("%d\n", res);
    printf("%d \n", teste);*/
}