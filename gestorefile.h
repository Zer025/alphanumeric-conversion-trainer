#ifndef GESTOREFILE_H_INCLUDED
#define GESTOREFILE_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>

static FILE *fPtr;

bool apriFile(char* filename, char* modo);
void leggiFile(char lista[][21]);
void chiudiFile(FILE* ptr);

//bool verificaFileVuoto();

#endif
