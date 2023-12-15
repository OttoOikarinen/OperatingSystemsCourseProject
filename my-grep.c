#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grepFile(FILE *input, char *cSearchTerm) {
    printf("%s\n", cSearchTerm);
}

int main(int argc, char *argv[]) {

    if (argc == 1) { // If no arguments, give advice.
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    } 

    char *cSearchTerm = argv[1];

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
    return 0;
}