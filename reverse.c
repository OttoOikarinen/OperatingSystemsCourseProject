#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void reverseFile(FILE *input, FILE *output) {
    fprintf(output, "Testiteksti\n");
};

int main(int argc, char *argv[]) {
    if(argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }  

    FILE *input = stdin;
    FILE *output = stdout;

    if (argc == 2) {
        output = stdout;
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        };
    }

    if (argc == 3) {
        printf("Here!\n");
        output = fopen(argv[2], "w");
        if (!output) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
        input = fopen(argv[1], "r");
        printf("HEre!\n");
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        };

        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "error: Input and output file must differ\n");
            fclose(input);
            fclose(output);
            exit(1);
        }
    }

    reverseFile(input, output);

    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }
    
    
    return 0;
}