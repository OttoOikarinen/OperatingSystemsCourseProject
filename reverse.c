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


// Function to free the memory which was reserved for the linked list
// and for the lines.
void freeList(LIST *pHead) {
    LIST *pCurrent = pHead;
    while (pCurrent != NULL) {
        LIST *pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        free(pTemp->pString);
        free(pTemp);
    }
}

void printList(LIST *pHead, FILE *output) {
    int first = 0;

    printf("Printing the list to the chosen output.\n\n");
    LIST *pCurrent = pHead;

    // Goes to the end of the linked list.
    while (pCurrent->pNext != NULL) {
        pCurrent = pCurrent->pNext;
    }

    // Travels the linked list in reverse order and prints the lines.
    while (pCurrent != NULL) {
        fprintf(output, "%s", pCurrent->pString);
        if (first == 0 && output != stdout) { // The last line (which is now first) needs
            fprintf(output, "\n");            // a linechange after it.
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

    // Gives advice when writing inputs on the terminal.
    if (input == stdin) {
        printf("Write your inputs. When you want to stop, write 'quit'.\n");

    }

    // Read input line by line and saves it in linked list.
    while ((nread = getline(&pLine, &dLineLenght, input)) != -1) {
        printf("Retrieved line of length %zd.\n", nread);

        // If user writes 'quit' in terminal, stops getting inputs.
        if (output == stdout && strcmp(pLine, "quit\n") == 0) {
            printf("Stopping.\n\n");
            break;
        }
        
        // Reserves memory for the new node which will be added to the linked list.
        LIST *newNode = (LIST *)malloc(sizeof(LIST));
        if (newNode == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        newNode->pString = strdup(pLine);  // Copies the line to the linkedlist.
        if (newNode->pString == NULL) {
            fprintf(stderr, "Memory allocation error when using strdup.\n");
            free(newNode);
            exit(1);
        }

        if (pHead == NULL) { // If first node.
            pHead = newNode;
            pCurrent = newNode;
        } else {
            pCurrent->pNext = newNode;
            newNode->pPrevious = pCurrent;
            pCurrent = newNode;
        }
    }
    printList(pHead, output);

    // Freeing memory.
    free(pLine);
    freeList(pHead);

}


int main(int argc, char *argv[]) {
    if(argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }  

    // Defining input and output with assumption, that they will be stdout and stdin.
    FILE *input = stdin;
    FILE *output = stdout;

    if (argc == 2) {
        input = fopen(argv[1], "r"); // Changes the input to chosen file.
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        };
    }

    if (argc == 3) {
        output = fopen(argv[2], "w"); // Changes output to chosen file.
        if (!output) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
        input = fopen(argv[1], "r"); // Changes input to chosen file.
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        };

        if (strcmp(argv[1], argv[2]) == 0) { // If input and output are the same file. 
            fprintf(stderr, "error: Input and output file must differ\n");
            fclose(input);
            fclose(output);
            exit(1);
        }
    }

    reverseFile(input, output); // Let's do the file reversing.

    // Closing files. 
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }
    
    return 0;
}