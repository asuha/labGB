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

#define _XOPEN_SOURCE = 700;

char* FILE_NAME = "teste.txt.gz";

int openFile(char* fileName);
bool isZippedFile(int fileDescriptor);
int unzipFile(char* fileName);
void executeUnzip(char* fileName);

int main(int argc, const char * argv[]) {
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

        do{
            char buf[15];
            count = read(iFileDescriptor, buf, 14);
            if (count > 0 ) {
                //Check for entered string.
                printf("%s\n", buf);
            }

        } while( count > 0);
    }

    return 0;
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
            char buf[15];
            int count = -1;
            while (count != 0) {
                count = read(pfd[0], buf, 14);
                if (count > 0)
                    printf("%s\n", buf); }
            return 0;
            //read file and search for virus
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
