/*
 * Pocris Sabin - 312CB
 */

#ifndef _IO_
#define _IO_

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MIN_STRING_SIZE 16
#define TEST 0
#define TOUCH 1
#define MKDIR 2
#define LS 3
#define RM 4
#define RMDIR 5
#define CD 6
#define PWD 7
#define FIND 8
#define NOT_A_COMMAND 420

// it reads a string from the inputFile
// and returns which 'command' it is
int getCommand(FILE *inputFile);

// It reads a string from the input file
// and stores it into the destination.
// Destination must be NULL/freed.
// It alocates the memory dinamically!
// If the value of the destination is NULL
// it means it got an error or an EOF..
void readStringFrom(FILE *inputFile, char **destination);

#endif