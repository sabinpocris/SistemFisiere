/*
 * Pocris Sabin - 312CB
 */

#include "IO.h"

int getCommand(FILE *inputFile) {
  char *tempStr = NULL;  // storing the input

  readStringFrom(inputFile, &tempStr);

  if (!tempStr) return NOT_A_COMMAND;

  if (strcmp(tempStr, "touch") == 0) {
    free(tempStr);
    return TOUCH;
  }

  if (strcmp(tempStr, "mkdir") == 0) {
    free(tempStr);
    return MKDIR;
  }

  if (strcmp(tempStr, "ls") == 0) {
    free(tempStr);
    return LS;
  }

  if (strcmp(tempStr, "rmdir") == 0) {
    free(tempStr);
    return RMDIR;
  }

  if (strcmp(tempStr, "rm") == 0) {
    free(tempStr);
    return RM;
  }

  if (strcmp(tempStr, "cd") == 0) {
    free(tempStr);
    return CD;
  }

  if (strcmp(tempStr, "pwd") == 0) {
    free(tempStr);
    return PWD;
  }

  if (strcmp(tempStr, "find") == 0) {
    free(tempStr);
    return FIND;
  }

  free(tempStr);
  return NOT_A_COMMAND;  // not the right input
}

void readStringFrom(FILE *inputFile, char **destination) {
  int bufferSize = 0;
  int maxBufferSize = 0;
  signed char tempChar = 0;

  if (!destination) {
    fprintf(stderr, "The adress of the string is null!\n");
    return;
  }

  if ((*destination)) {
    fprintf(stderr, "The pointer to the string is not null!\n");
    return;
  }

  (*destination) = malloc(MIN_STRING_SIZE);
  maxBufferSize = MIN_STRING_SIZE;
  if (!(*destination)) {
    fprintf(stderr, "Can't allocate the memory!\n");
    return;
  }

  // delete white spaces from input
  while ((tempChar = getc(stdin)) == ' ' || tempChar == '\n' ||
         tempChar == '\t' || tempChar == '\r')
    ;

  if (tempChar == EOF) {
    free((*destination));
    (*destination) = NULL;  // check if the free makes the pointer NULL
    return;
  }

  ungetc(tempChar, stdin);

  // reading the string and storing it into the destination
  while ((tempChar = getc(stdin)) != ' ' && tempChar != '\n' &&
         tempChar != '\t' && tempChar != '\r' && tempChar != EOF) {
    // do we need more memory??
    if (bufferSize + 1 > maxBufferSize) {
      maxBufferSize *= 2;
      (*destination) = realloc((*destination), maxBufferSize);

      if (!(*destination)) return;
    }

    // assign and increment the buffer size
    (*destination)[bufferSize++] = tempChar;
  }

  // mark the end of the string
  (*destination)[bufferSize] = '\0';
}