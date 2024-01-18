#include <stdio.h>
#include <stdlib.h>

void unzipFile(FILE *input) {
    int count;
    char character;

    // While characters left in the file, first read a count number.
    while (fread(&count, sizeof(int), 1, input) == 1) {
        fread(&character, sizeof(char), 1, input); // Then read character.
        for (int i = 0; i < count; i++) { // Print characer as many times as count is.
            printf("%c", character);
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc == 1) { // If no files specified, give advice.
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) { // For every parameter.
        FILE *input = fopen(argv[i], "r"); // Open file. 
        if (!input) { // If file opening failed:
            fprintf(stderr, "my-unzip: cannot open file\n");
            exit(1);
        }

        // For every file: unzip it and then close the file before opening next one. 
        unzipFile(input);
        fclose(input);
    }

    return 0;
}