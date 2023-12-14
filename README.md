# Project documentation. 

Written by: Otto Oikarinen (otto.oikarinen@student.lut.fi)
Last edited: 14.12.2023

## reverse.c

This is the Project 1: Warmup to C and Unix programming. 
It consist of 1 file, reverse.c which includes the whole program. 

The goal of the program is to reverse lines in a given input source and print them to given output. Inputs can be taken from a file or from terminal. Output can be another file or the terminal.

The file includes main-function and several other functions, which together 
handle the program. Main function is mainly concerned with ensuring the program has been called properly (only maxmimum two parameters after the name of the program) and deciding correct inputs and outputs. Then it calls reverseFile-function which takes in the input and output. 

reverseFile-function is the function which is responsible with reading the inputs, taking the lines and storing them to a linked list. This is done with the help of getline, malloc and other basic commands. There is a spesific struct called LIST, which stores pointers to previous and next nodes as well as pointer to the line. 

After storing the lines to a list, printList-function is called. It travels to the end of the list and then back to the beginning while printing all lines to the chosen output. 

After that memory is freed in freeList-function and main function returns 0.

