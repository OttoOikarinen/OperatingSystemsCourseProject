#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void printFile(FILE *input) {
    char* pLine = NULL;
    size_t iLineLenght = 0;
    ssize_t nread;

    // For every line in file the program will just print it.
    while ((nread = getline(&pLine, &iLineLenght, input)) != -1) {
        printf("%s", pLine);
    }
}

int main(int argc, char *argv[]) {

    if (argc == 1) { // No no files specified, just stop.
        exit(0);
    } 

    for (int i = 1; i < argc; i++) { // For every parameter given.
        FILE *input = fopen(argv[i], "r"); // Opens input to chosen file.
        if (!input) { // If fopen did not succeed:
            fprintf(stderr, "my-cat: cannot open file\n", argv[i]);
            exit(1);
        };

        // Print file and close it.
        printFile(input);
        fclose(input);
    }
    return 0;
}