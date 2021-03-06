//
//  main.c
//  antivirus
//
//  Created by Júlio Renner on 03/06/17.
//  Copyright © 2017 RENNERJ. All rights reserved.
//

#define _XOPEN_SOURCE 700
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

const int SIZE = 11;
char* signature;
int numberOfFilesWithVirus = 0;
int numberOfFiles = 0;
char* filesWithVirus[];

bool isZippedFile(int fileDescriptor);
bool lookForVirus(int iFileDescriptor);
int openFile(char* fileName);
int unzipFile(char* fileName);
bool hasVirus(char* buffer, int* verifica, int res);
void executeUnzip(char* fileName);

int main(int argc, const char * argv[]) {

    char sFile[30];
    while( (scanf("%30[^\n]%*c",sFile) != EOF) ){

        signature = argv[1];

        int fileDescriptorToCheckType = openFile(sFile);

        unsigned int byte[2];

        int count = read(fileDescriptorToCheckType, &byte, 2);

        if (count <= 0) {
            printf("read failed\n");
            exit(0);
        }

        close(fileDescriptorToCheckType);

        int iFileDescriptor;

        if (isZippedFile(byte[0])){

            unzipFile(sFile);

        } else {

            iFileDescriptor = openFile(sFile);
        	numberOfFiles++;

            if(lookForVirus(iFileDescriptor))
            	dprintf(1, "%s\n", sFile);

        }
    };

    dprintf(2, "Número de arquivos lidos: %d\n", numberOfFiles);
    dprintf(2, "Número de arquivos com vírus: %d\n", numberOfFilesWithVirus);

    return 0;
}

bool lookForVirus(int iFileDescriptor){
    int res = 0;
    int offset = 0;
    bool virus = false;

    do{
        char buffer[SIZE];
        for(int i = 0; i < SIZE; i++)
            buffer[i] = 0;

        res = read(iFileDescriptor, buffer, SIZE);

        if(res < 0){
            perror("Erro no read");
            return EXIT_FAILURE;
        }

        if(res == 0){
        	//EOF
        }

        else {

            if (hasVirus(buffer, &offset, res) == true){
            	numberOfFilesWithVirus++;
            	virus = true;
                break;
            }
        }

    } while( res > 0);

    return virus;
}

bool hasVirus(char* buffer, int* offset, int res){
    int j = 0;
    for(int i = 0; i < res; i++){

        if(buffer[i] == signature[j + *(offset)]){
            j++;
        } else {
            j = 0;
            *(offset) = 0;
        }

        if ( (j + *(offset)) == strlen(signature)){
            return true;
        }
    }

    *(offset) = j;

    return false;
}

int openFile(char* fileName){

    int fileDescriptor = open(fileName, O_CLOEXEC | O_RDONLY);

    if (!(fileDescriptor > 0)){
        perror("Error reading file\n");
        exit(0);
    }

    return fileDescriptor;

}

bool isZippedFile(int value) {

    if (( value == 35615 ))
        return true;

    return false;

}

int unzipFile(char* fileName){
    int pfd[2];

    if (pipe(pfd) != 0){
        perror("error setting pipe\n");
        exit(EXIT_FAILURE);
    };

    switch (fork()){
        case -1:
            perror("fork error\n");
            exit(EXIT_FAILURE);
        case 0:
            close(pfd[0]);
            dup2(pfd[1], STDOUT_FILENO);
            executeUnzip(fileName);
        default:
            close(pfd[1]);
            lookForVirus(pfd[0]);
            return EXIT_SUCCESS;
    }

}

void executeUnzip(char* fileName){
    execlp("gzip",
           "gzip",
           "-d"  ,
           "-c"  ,
           fileName,
           NULL );
}
