# Project documentation. 

Written by: Otto Oikarinen (otto.oikarinen@student.lut.fi)
Last edited: 13.5.2024
Code has been written by me. ChatGPT has been used for explaining different functions and helping to debug the code. 

## Project 1: reverse.c

This is the Project 1: Warmup to C and Unix programming. 
It consist of 1 file, reverse.c which includes the whole program. 

The goal of the program is to reverse lines in a given input source and print them to given output. Inputs can be taken from a file or from terminal. Output can be another file or the terminal.

The file includes main-function and several other functions, which together handle the program. Main function is mainly concerned with ensuring the program has been called properly (only maxmimum two parameters after the name of the program) and deciding correct inputs and outputs. Then it calls reverseFile-function which takes in the input and output. 

reverseFile-function is the function which is responsible with reading the inputs, taking the lines and storing them to a linked list. This is done with the help of getline, malloc and other basic commands. There is a spesific struct called LIST, which stores pointers to previous and next nodes as well as pointer to the line. 

After storing the lines to a list, printList-function is called. It travels to the end of the list and then back to the beginning while printing all lines to the chosen output. 

After that memory is freed in freeList-function and main function returns 0.

## Project 2:

Project 2 includes programs my-cat, my-grep, my-zip and my-unzip. This is documentation for them. 

### my-cat.c

my-cat.c is a simple application which purpose is to print the files which are given in the parameters. For example calling:
./my-cat file1 file2 file3

would print the insides of file1, file2 and file3. If no parameters are given, my-cat will just exit without error. 

The program consists of two functions:
main-function is responsible for checking, if there are any parameters. If parameters are found, it will open the file and call printFile-function. After that, it will close the file and open another one, if there are more parameters left. If not, it will stop the program.

printFile-function is actually responsible for the printing part. It reads a line with getline() and then prints it immediately after that. It stops when all the files have been read.

### my-grep.c

my-grep is used to find a searchterm from the input given to it. The inputs can be files or it can be the standard input. The program is called for example:
./my-grep searchterm [file ...]

The searchterm is mandatory, without it the main-function will print advice to using the program and exit with error. The file-part is voluntary and there can be as many files as the user wishes.

The program consists of two functions:
main-function is responsible for checking the parameters. If there are none, it will give advice and exit with error. If there is only one parameter (so a searchterm), it will call the grepFile-function and give it stdin as input and the only parameter as a cSearchTerm. If there are more parameters, the function will try to open them and pass them as inputs to the grepFile-function one by one. 

The grepFile-function is responsible for searching for the term. If the input is stdin, it prints information to the user, that they can stop the program by writing 'quit'. It will read a line from the input using getline(). Then it will search the line for the searchterm using strstr(). If a match is found, it will be printed. Function returns when no more lines can be found or user writes 'quit'.

### my-zip.c

my-zip is used to compress one or more files. It gets the files as parameters when running the program. The program is called like:
./my-zip file1 [file2 ...]

One file is mandatory, but users can use as many files as they wish. 

The program consists of two functions:
main-function is responsible for checking the parameters. If no files are specified when running the program, it will print advice about the usage of the program and then exit with error. If there are one or more files, the function will try to open them and then pass them as an input to the zipFile-function. After that, the function will close the file and open another one, if there are parameters left. 

The zipFile-function is responsible for compressing the file. If the file is empty, it returns nothing. Otherwise it will read characters from the file. If there are multiple same characters back to back, it will count the characters. Then when there are no more same characters, it will print the count and the character. 

### my-unzip.c

my-unzip is used to decompress the files compressed with my-zip. It gets files as parameters when starting the program. The program is called like:
./my-unzip file1 [file2 ...]

One file is mandatory, but users can use as many files as they wish.

The program consists of two functions:
main-function is responsible for checking the parameters. If no files are specified when running the program, it will print advice about the usage of the program and then exit with error. If there are one or more files, the function will try to open them and then pass them as an input to the unzipFile-function. After that, the function will close the file and open another one, if there are parameters left. 

The unzipFile-function is responsible for decompressing the data. It will first read a number and then a character. Then it will print as many characters as the number tells is. This continues as long as there are new characters.


## Project 4: Kernel Hacking

To add a system call for getreadcount() to this xv6-kernel, I made the following changes to the code: 

### In `syscall.c` line 106:
```
extern int sys_getreadcount(void);
```
and line 131: 
```
[SYS_getreadcount]  sys_getreadcount,
```

### In `syscall.h` line 23:
```
#define SYS_getreadcount 22   // For assignment
```

### In `sysproc.c` line 94-98:
```
// This whole function was added for assingment
// It returns the readcount. 
int sys_getreadcount(void) {
  return myproc()->readcount;  
}
```
### In `proc.h` line 52:

 ```
 int readcount;               // For assignment task. 
 ```

 ### In `usys.S` line 32:
 ```
 SYSCALL(getreadcount)
 ```

### In `user.h` line 26:
```
int getreadcount(void);
```

### I then added a new file `getreadcount.c`:
It is the function that the user is able to call to check what the read count is at the moment. It is accessible on the command line using 
`getreadcount`.

It has the following code:
```
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {

    printf(1, "Read count at the moment is: %d\n", getreadcount);
    exit();
}
```


## Running xv6 kernel:

You can run the xv6 kernel by downloading the source code from my CourseProject repository. Then you can run the kernel by using terminal and command:
`sudo make qemu`. This requires you have qemu installed. 