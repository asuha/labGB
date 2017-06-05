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

char* FILE_NAME = "teste.txt";

int openFile(char* fileName);
bool isZippedFile(int fileDescriptor);

int main(int argc, const char * argv[]) {
    int fileDescriptor = openFile(FILE_NAME);

    unsigned int byte[2];

    int count = read(fileDescriptor, &byte, 2);

    if (count <= 0) {
        printf("read failed\n");
        exit(0);
    }

    if (isZippedFile(byte[0])){
        printf("zipped file");
    }
    //printf("%X\n", byte[0]);

    close(fileDescriptor);

    fileDescriptor = openFile(FILE_NAME);
    do{
        char buf[15];
        count = read(fileDescriptor, buf, 14);
        if (count > 0 ) {
            //Check for entered string.
            printf("%s\n", buf);
        }
    
    } while( count > 0);

    return 0;
}

int openFile(char* fileName){

    int fileDescriptor = open(fileName, O_CLOEXEC | O_RDONLY);

    if (!(fileDescriptor > 0)){
        perror("Error reading file");
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
