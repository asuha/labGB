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
const char* GZIP_FILE_NAME="./teste.gz";

void openFile(char* sFilePath);

int main(int argc, const char * argv[]) {
    printf("abriu\n");
    openFile(GZIP_FILE_NAME);
}

void openFile(char* sFilePath){
    printf("openFIle\n");
    int iFile= fopen(sFilePath, "rb");
    
    if (iFile < 0) {
        perror("Não encontrou o arquivo");
        exit(1);
    }
    
    char teste[150] = "";
    
    int res = read(iFile, teste, 150);
    
    printf("%d\n", res);
    printf("%d \n", teste);
}
