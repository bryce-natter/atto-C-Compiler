// File: main.c
// Contents: Main Driver

#define _CRT_SECURE_NO_WARNINGS
#include "../inc/atto-C.h"
FILE *sourcefile;
FILE *asmfile;


/*
int argc: the number of words on the command line

char **argv: a pointer to a list of strings, one string for each word
             on the command line, ending with a null pointer.
             argv[0] is the command name, argv[1] is the first argument,
             and so on.  argv[argc] is set to a null pointer.
*/
int main(int argc, char **argv) {

    if (!argc == 2) {
        printf("\nMissing source file on command line\n"); exit(0);
    }
    sourcefile = fopen(argv[1], "r"); //Open source file, read-only
    if (sourcefile == NULL) //Error catch
    {
        perror(argv[1]);
        exit(1);
    }

    char asmfilename[100];
    strncpy(asmfilename, argv[1], 95);    // "95" is the max length to copy
    int length;
    length = strlen(asmfilename);

    if (strcmp(asmfilename + length - 2, ".c") != 0)
    {
        printf("Source file does not have a.c extension"); exit(0);
    }
    strcpy(asmfilename + length - 2, ".asm");

    asmfile = fopen(asmfilename, "w"); //Open .asm file in write-mode
    if (asmfile == NULL)
    {
        perror(asmfilename);
        exit(9);
    }
    
    preamble(argv[1]); //Create asm header
    program();
    postamble(); //Add "END" to asm
    return 0;
}
