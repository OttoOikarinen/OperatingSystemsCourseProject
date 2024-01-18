#include <stdio.h>
#include <stdlib.h>

void zipFile(FILE *input) {
    char currentChar, lastChar;
    int count = 1;

    // If file is empty, just stop.
    if (fread(&lastChar, sizeof(char), 1, input) != 1) {
        return;
    }

    // While there are characters left in the file:
    while (fread(&currentChar, sizeof(char), 1, input) == 1) {
        if (currentChar == lastChar) { 
            count++; // If characters are same, raise the count by 1.
        } else { // If characters differ:
            // Write the number of characters and then the character itself.
            fwrite(&count, sizeof(int), 1, stdout);
            putchar(lastChar);
            count = 1; // Reset counter.
            lastChar = currentChar;
        }
    }

    // When file is empty, write last character and its count.
    fwrite(&count, sizeof(int), 1, stdout);
    putchar(lastChar);
}

int main(int argc, char *argv[]) {

    if (argc == 1) { // If no files specified, give advice.
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) { // For every parameter:
        FILE *input = fopen(argv[i], "r"); // Open file. 
        if (!input) { // If opening failed.
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }

        // Zip file and close it before opening next one.
        zipFile(input);
        fclose(input);
    }

    return 0;
}