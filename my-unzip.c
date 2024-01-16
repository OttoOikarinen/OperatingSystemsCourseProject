#include <stdio.h>
#include <stdlib.h>

void printFile(FILE *input) {
    int count;
    char character;

    while (fread(&count, sizeof(int), 1, input) == 1) {
        fread(&character, sizeof(char), 1, input);
        for (int i = 0; i < count; i++) {
            printf("%c", character);
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc == 1) { // If no files specified.
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *input = fopen(argv[i], "r");
        if (!input) {
            fprintf(stderr, "my-unzip: cannot open file\n");
            exit(1);
        }
        printFile(input);
        fclose(input);
    }

    return 0;
}