#include <stdio.h>
#include <stdlib.h>

void printFile(FILE *input) {
    char currentChar, lastChar;
    int count = 1;

    if (fread(&lastChar, sizeof(char), 1, input) != 1) {
        return;
    }

    while (fread(&currentChar, sizeof(char), 1, input) == 1) {
        if (currentChar == lastChar) {
            count++;
        } else {
            fwrite(&count, sizeof(int), 1, stdout);
            putchar(lastChar);
            count = 1;
            lastChar = currentChar;
        }
    }

    fwrite(&count, sizeof(int), 1, stdout);
    putchar(lastChar);
}

int main(int argc, char *argv[]) {

    if (argc == 1) { // If no files specified.
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *input = fopen(argv[i], "r");
        if (!input) {
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }
        printFile(input);
        fclose(input);
    }

    return 0;
}