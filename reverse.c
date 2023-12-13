#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct list {
    struct list *pPrevious;
    char *pString;
    struct list *pNext;
} LIST;

void printList(LIST *pHead, FILE *output) {
    int first = 0;

    printf("Printing the list to the chosen output.\n\n");
    LIST *pCurrent = pHead;
    while (pCurrent->pNext != NULL) {
        pCurrent = pCurrent->pNext;
    }
    while (pCurrent != NULL) {
        fprintf(output, "%s", pCurrent->pString);
        if (first == 0 && output != stdout) {
            fprintf(output, "\n");
            first = 1;
        }
        pCurrent = pCurrent->pPrevious;
    }
    printf("\n");
}

void reverseFile(FILE *input, FILE *output) {
    char *pLine = NULL;
    size_t dLineLenght = 0;
    ssize_t nread;

    LIST *pHead = NULL;
    LIST *pCurrent = NULL;

    while ((nread = getline(&pLine, &dLineLenght, input)) != -1) {
        printf("Retrieved line of length %zd.\n", nread);

        if (output == stdout && strcmp(pLine, "quit\n") == 0) {
            printf("Stopping.\n");
            break;
        }
        
        LIST *newNode = (LIST *)malloc(sizeof(LIST));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(1);
        }

        newNode->pString = strdup(pLine);
        if (newNode->pString == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            free(newNode);
            exit(1);
        }

        if (pHead == NULL) {
            pHead = newNode;
            pCurrent = newNode;
        } else {
            pCurrent->pNext = newNode;
            newNode->pPrevious = pCurrent;
            pCurrent = newNode;
        }
    }
    printList(pHead, output);
}


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