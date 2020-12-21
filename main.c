#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestorefile.h"

#define RMIN 1
#define RMAX 100


// Funzioni
int menu();
void guessRandom();
void guessSort();
void leggiRange(int *rmin, int *rmax);
void memoNum();
int leggiNumLen();


int main()
{
    int sc;
    do {
        sc = menu();
        switch(sc) {
        case 1:
            guessRandom();
            system("pause");
            system("cls");
            break;
        case 2:
            guessSort();
            system("pause");
            system("cls");
            break;
        case 3:
            memoNum();
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    } while(sc != 4);
    return 0;
}


//Funzioni
int menu()
{
    int sc;
    printf("1) Numeri random\n"
           "2) Numeri in ordine\n"
           "3) Memorizza numero\n"
           "4) Esci\n");
    do {
        printf("Scelta: ");
        scanf("%d", &sc);
        fflush(stdin);
    } while (sc < 1 || sc > 4);
    return sc;
}

void guessRandom()
{
    int rmin, rmax, n; // valore minimo range, valore massimo range, numero di numeri randomici da mostrare
    char word[20], lista[1000][21]; // [NUMBER_OF_STRINGS][STRING_LENGTH+1]
    bool arr[1000] = {0};

    puts("\n----- Indovina le parole random -----");

    leggiRange(&rmin, &rmax);
    if (apriFile("parole.txt", "r")) {
        // File aperto
        leggiFile(lista);

        // Leggi n
        unsigned int n;
        int max = (rmax - rmin) + 1;

        printf("Quanti numeri vuoi? ");
        scanf("%u", &n);
        fflush(stdin);

        while (n > max) {
            printf("Errore: il valore supera il numero massimo di numeri random (%d).\nRiscrivi: ", max);
            scanf("%u", &n);
            fflush(stdin);
        }

        // Calcola e stampa numeri random
        srand(time(0));
        int r;
        for (int i = 0; i < n; ++i) {
            r = rmin + rand() % max;
            if(!arr[r]) {
                printf("- %d: ", r);
                scanf("%20s", word);
                fflush(stdin);

                // Verifica parola
                int res = strcmp(word, lista[r-1]);
                if (res != 0) {
                    // Parole diverse
                    printf("\tSbagliato. Parola esatta: %s\n", lista[r-1]);
                }
            } else {
                i--;
            }
            arr[r] = 1;
        }

        chiudiFile(fPtr);
    } else {
        // Errore apertura file
        printf("Errore: file 'parole.txt' non trovato\n");
    }
}

void guessSort()
{
    int rmin, rmax;
    char word[20], lista[1000][21]; // [NUMBER_OF_STRINGS][STRING_LENGTH+1]
    char ris;

    puts("\n----- Indovina le parole -----");

    leggiRange(&rmin, &rmax);
    if (apriFile("parole.txt", "r")) {
        // File aperto
        leggiFile(lista);

        do {
            for (int i = rmin-1; i < rmax; i++) {
                printf("\n- %d: ", i + 1);
                scanf("%20s", word);
                fflush(stdin);

                // Verifica parola
                int res = strcmp(word, lista[i]);
                if (res != 0) {
                    // Parole diverse
                    printf("\tSbagliato. Parola esatta: %s\n", lista[i]);
                }
            }
            printf("\nRipetere [y/n]? ");
            scanf("%c", &ris);
        } while (ris == 'y' || ris == 'Y');

        chiudiFile(fPtr);
    } else {
        // Errore apertura file
        printf("Errore: file non aperto\n");
    }
}

void leggiRange(int *rmin, int *rmax)
{
    printf("Inserisci il range di numeri [1 - 100] separati da uno spazio: ");
    scanf("%d %d", rmin, rmax);
    fflush(stdin);

    while((*rmin < RMIN || *rmax > RMAX) || (*rmin > *rmax || *rmax < *rmin)) {
        printf("Valori non validi. Riscrivi: ");
        scanf("%d %d", rmin, rmax);
        fflush(stdin);
    }
    //printf("OK");
}

void memoNum()
{
    char numero[100];

    puts("\n----- Memorizza il numero -----");

    int numLen = leggiNumLen();

    // Genera numero randomico
    srand(time(0));
    int r; // Numero randomico 1-9 / 0-9
    char buffer; // Numero randomico ma in char

    // Scrivi prima cifra != 0
    r = 1 + rand() % 9;    // min + rand() % (max - min + 1)
    buffer = r + '0';   // int to char
    numero[0] = buffer;

    // Scrivi cifre restanti
    for (int i = 1; i < numLen; i++) {
        r = rand() % 10;    // min + rand() % (max - min + 1)
        buffer = r + '0';   // int to char

        numero[i] = buffer;
    }

    // Stampa numero
    puts("");
    for (int i = 0; i < numLen; i++)
        printf("%c", numero[i]);
    printf("\n\n");

    // Pulisci console
    system("PAUSE");    // Press any key
    system("cls");      // Pulisci console

    // Richiesta numero
    char temp[100];
    printf("Inserisci il numero memorizzato: \n");
    printf("? ");
    scanf("%s", temp);

    // Verifica numero
    if(strcmp(numero, temp) == 0) {
        printf("\nBrevo\n");
    } else {
        printf("\nHai errorato\n");
    }
}

int leggiNumLen() {
    int numLen;

    printf("Inserisci la lunghezza del numero: ");
    scanf("%d", &numLen);
    fflush(stdin);

    while(numLen < 1 || numLen > 100) {
        printf("Valore non valido. Riscrivi: ");
        scanf("%d", &numLen);
        fflush(stdin);
    }
    return numLen;
}
