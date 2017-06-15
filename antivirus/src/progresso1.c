//
//  main.c
//  antivirus
//
//  Created by Júlio Renner on 03/06/17.
//  Copyright © 2017 RENNERJ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

#define _XOPEN_SOURCE 700
#define _GNU_SOURCE

char* FILE_NAME = "teste.txt.gz";

const int SIZE = 10;
char* assinatura;

int openFile(char* fileName);
bool isZippedFile(int fileDescriptor);
int unzipFile(char* fileName);
void executeUnzip(char* fileName);
int processaArquivo(char* buffer, int verifica);

int main(int argc, const char * argv[]) {
	assinatura = argv[1];

    int fileDescriptorToCheckType = openFile(FILE_NAME);

    unsigned int byte[2];

    int count = read(fileDescriptorToCheckType, &byte, 2);

    if (count <= 0) {
        printf("read failed\n");
        exit(0);
    }

    close(fileDescriptorToCheckType);

    int iFileDescriptor;

    if (isZippedFile(byte[0])){

        printf("zipped file\n");
        iFileDescriptor = unzipFile(FILE_NAME);

    } else {

        iFileDescriptor = openFile(FILE_NAME);
        int res = 0;
        int offset = 0;

        do{
            char buffer[SIZE];
            	for(int i = 0; i < SIZE; i++)
            		buffer[i] = 0;

        	res = read(iFileDescriptor, buffer, SIZE);

        	if(res < 0){
        		perror("Erro no read");
        		return EXIT_FAILURE;
        	}

        	if(res == 0)
        		printf("EOF\n");

        	else{
        		int processa = processaArquivo(buffer, offset);

        		if (processa == 0){
        			printf("POSSUI!!\n");
        			offset = 0;
        		}
        		else if (processa > 0)
        			offset = processa;
        		else
        			offset = 0;
        	}

        } while(res > 0);
    }

    return 0;
}

int processaArquivo(char* buffer, int offset){
	int verifica = -1;
	int teste = 0;

	for(int i = 0, j = 0; i < strlen(buffer); i++){
		if(buffer[i] == assinatura[j + offset]){
			teste++;
			j++;
		}
	}

	if((teste == strlen(assinatura)) | (teste == strlen(assinatura) - offset))
		verifica = 0;
	else if((teste == 0) | (teste > strlen(assinatura)))
		verifica = -1;
	else
		verifica = teste;

	return verifica;
}


int openFile(char* fileName){

    int fileDescriptor = open(fileName, O_CLOEXEC | O_RDONLY);

    if (!(fileDescriptor > 0)){
        perror("Error reading file\n");
        exit(0);
    }

    /*unsigned int byte[2];

    int teste = read(fileDescriptor, &byte, 1);
    int v1 = byte[0];
    teste = read(fileDescriptor, &byte, 1);
    int v2 = byte[0];
    printf("%i\n", teste);

    if ( byte[0] == "0x8b1f" ) {
        printf("worked\n");
    }

    unsigned int teste1 = byte[0];

    printf("%x\n", byte[0]);
    //printf("%s\t", byte[1]);
*/
    return fileDescriptor;
}

bool isZippedFile(int value) {

    if (( value == 35615 ))
        return true;

    return false;

}


void executeUnzip(char* fileName){
    execlp("gzip",
           "gzip",
           "-d"  ,
           "-c"  ,
           fileName,
           NULL );
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

            int res = 0;
            int offset = 0;

            do{
                char buffer[SIZE];
                	for(int i = 0; i < SIZE; i++)
                		buffer[i] = 0;

            	res = read(pfd[0], buffer, SIZE);

            	if(res < 0){
            		perror("Erro no read");
            		return EXIT_FAILURE;
            	}

            	if(res == 0)
            		printf("EOF\n");

            	else{
            		int processa = processaArquivo(buffer, offset);

            		if (processa == 0){
            			printf("POSSUI!!\n");
            			offset = 0;
            		}
            		else if (processa > 0)
            			offset = processa;
            		else
            			offset = 0;
            	}

            } while(res > 0);

            return 0;
            //read file and search for virus
    }

}
