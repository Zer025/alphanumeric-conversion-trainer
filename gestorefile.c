#include "gestorefile.h"


bool apriFile(char* filename, char* modo)
{
    fPtr = fopen(filename, modo);

    return (fPtr != NULL);
}

void leggiFile(char lista[][21])
{
    char str[20];
    int i = 0;
    while(!feof(fPtr)) {
        fscanf(fPtr, "%s\n", str);
        //lista[i] = str;
        strcpy(lista[i], str);
        i++;
    }

    /*while(!feof(fPtr)) {
      fgets(lista, sizeof(lista), fPtr);
    }*/
}

void chiudiFile(FILE* ptr)
{
    fclose(ptr);
}

/*bool verificaFileVuoto()
{
    fseek(fPtr, 0, SEEK_END);
    long size = ftell(fPtr);

    return (size == 0);
}*/
