#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numOfArgs 4
#define Flag 1
#define InFileArg 2
#define OutFileArg 3

//France Le
//FL193361
//LAB: Wed 4:15


int main(int argc, char *argv[])
{
    FILE *infileptr;
    FILE *outfileptr;

    //need to use stderr
    if(argc != numOfArgs){
        printf("Enter [./executable] [flag: -v,-b,-f][inputfilename] [outputfilename]");
        fflush(stdout);
        exit(1);
    }

    char *ip;
    char *op;
    //adds .mal to file name
    ip = (char*)malloc (sizeof(strlen(argv[InFileArg] +5)));
    op = (char*)malloc(sizeof(strlen(argv[OutFileArg]+5)));
    strcpy(ip, argv[InFileArg]);
    strcpy(op, argv[OutFileArg]);
    strcat(ip,".mal");
    strcat(op, ".txt");

    if((infileptr = (FILE*)(fopen(ip,"r")))==NULL){
        printf("Could not open %s file. Closing program.\n", argv[InFileArg]);
        fflush(stdout);
        exit(1);
    }

    if((outfileptr = (FILE*)(fopen(op,"w")))==NULL){
        printf("Could not open %s file. Closing program.\n", argv[OutFileArg]);
        fflush(stdout);
        exit(1);
    }



    //closes files
    if(fclose(infileptr) == EOF){
        printf("Error in closing input file.");
        fflush(stdout);
    }

    if(fclose(outfileptr) == EOF){
        printf("Error in closing output file.");
        fflush(stdout);
    }

    free(ip);
    free(op);
    return 0;










    return 0;
}
