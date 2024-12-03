#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global Variables
symbols symbol, relation;
char token[TOKEN_SIZE];
FILE* fp = NULL;

void generateCode(char* rot, char* command) {
  if (fp == NULL) {
    fp = fopen("MEPA", "w");
  }

  if (rot == NULL) {
    fprintf(fp, "    %s\n", command);
    fflush(fp);
  } else {
    fprintf(fp, " %s:%s\n", rot, command);
    fflush(fp);
  }
}

void closeMEPAFile() { fclose(fp); }

void printError(char* error) {
  fprintf(stderr, "Erro na linha %d - %s\n", nl, error);
  exit(-1);
}