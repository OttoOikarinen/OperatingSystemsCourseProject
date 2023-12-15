#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void grepFile(FILE *input, char *cSearchTerm) {
    char* pLine = NULL;
    size_t iLineLenght = 0;
    ssize_t nread;

    if (input == stdin) {
        printf("Write your inputs. When you want to stop, write 'quit'.\n");

    }

    // For every line in file the program will just print it.
    while ((nread = getline(&pLine, &iLineLenght, input)) != -1) {
        char *result = strstr(pLine, cSearchTerm);
        // If user writes 'quit' in terminal, stops getting inputs.
        if (input == stdin && strcmp(pLine, "quit\n") == 0) {
            printf("Stopping.\n");
            break;
        }
        if (result != NULL) {
            printf("%s", pLine);
        }
    }

    free(pLine);
}

int main(int argc, char *argv[]) {

    if (argc == 1) { // If no arguments, give advice.
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    } 

    char *cSearchTerm = argv[1];

    if (argc == 2) {
        grepFile(stdin, cSearchTerm);
    } else {
        for (int i = 2; i < argc; i++) { // For every parameter given.
        FILE *input = fopen(argv[i], "r"); // Opens input to chosen file.
        if (!input) { // If fopen did not succeed:
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        };

        // Search the terms in this file.
        grepFile(input, cSearchTerm);
        fclose(input);
    }
    }// searchterm for testing :D
    return 0;
}