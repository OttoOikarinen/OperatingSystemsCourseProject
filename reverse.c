#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void reverseFile(FILE *input, FILE *output) {
    char *row = NULL;
    size_t lenght = 0;
    ssize_t this;

    while ((this = getline(&row, &lenght, input)) != -1) {
        fprintf(output, "%s", row);
    }

    free(row);
};

int main(int argc, char *argv[]) {
    if(argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }  

    FILE *input = stdin;
    FILE *output = stdout;

    if (argc == 2) {
        FILE *output = stdout;
        FILE *input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        };
    }

    if (argc == 3) {
        FILE *output = fopen(argv[2], "w");
        if (!output) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
        FILE *input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        };

        if (input == output) {
            fprintf(stderr, "error: Input and output file must differ\n");
            fclose(input);
            fclose(output);
            exit(1);
        }
    }
    if (argc == 1) {
        FILE *input = stdin;
        FILE *output = stdout;
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