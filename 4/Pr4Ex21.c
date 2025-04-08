/*Marina Catalan 1752407, Daniel Hurtado 1703664*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct Dada {
    int niu;
    float notes[5];
} Alu;

float mitjana(float[], int);
void imprimirtaula(struct Dada *, int n);

int niu_gran(const void *, const void *);
void ordenataula(struct Dada *, struct Dada *, int);

int comparacioapartirdindex ( const void* a, const void* b);
void imprimirdesdindex(Alu** index, int n);

int main() {
    FILE *dades, *line_counter;
    int n, i, j, lrg = 0, no_alumnes = 0;

    // 2.1.1
    line_counter = fopen("Llista.txt", "r");
    if (line_counter == NULL) {
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    for (char c = getc(line_counter); c != EOF; c = getc(line_counter))
        if (c == '\n') // Increment count if this character is newline
            no_alumnes = no_alumnes + 1;
    Alu* alumnes = malloc(sizeof(Alu) * no_alumnes);
    Alu** indexmitjanes = malloc(sizeof(Alu*) * no_alumnes);

    dades = fopen("Llista.txt", "r");
    if (dades == NULL) {
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }

    while (!(fscanf(dades, "%i;", &n) == EOF)) {
        indexmitjanes[lrg] = &alumnes[lrg];
        alumnes[lrg].niu = n;
        for (i = 0; i < 4; i++) {
            fscanf(dades, "%f", &alumnes[lrg].notes[i]);
            fgetc(dades); // llegeix i descarta els ; i el \n
        }
        alumnes[lrg].notes[4] = mitjana(alumnes[lrg].notes, 4);
        lrg++;
    }
    fclose(dades);
    for (j = 0; j < lrg; j++) {
        printf("%d | ", alumnes[j].niu);
        for (i = 0; i < 4; i++) {
            printf("%5.1f", alumnes[j].notes[i]);
        }
        printf(" |%6.2f", alumnes[j].notes[4]);
        printf("\n");
    }
    printf("\nS'ha llegit informacio de %d linies.\n\n", lrg);

    // 2.1.2
    no_alumnes++;
    alumnes = (Alu*)realloc(alumnes, sizeof(Alu) * no_alumnes);
    indexmitjanes = (Alu**)realloc(indexmitjanes, sizeof(Alu*) * no_alumnes);
    for (int j=0; j<=no_alumnes; j++){
        indexmitjanes[j] = &alumnes[j];
    }
    Alu nou_alumne = {1234567, {5.6, 6.2, 4.3, 8.6, 6.175}};
    alumnes[no_alumnes - 1] = nou_alumne;
    indexmitjanes[no_alumnes - 1] = &alumnes[no_alumnes - 1];

    // 2.1.3
    printf("\nTaula després d'afegir una dada\n");
    imprimirdesdindex(indexmitjanes, no_alumnes);

    // 2.1.4
    qsort(indexmitjanes, no_alumnes, sizeof(Alu*), comparacioapartirdindex);
    printf("\nTaula ordenada per nota\n");
    imprimirdesdindex(indexmitjanes, no_alumnes);


    /*qsort(alumnes, no_alumnes, sizeof(Alu), comparacioniu);*/
    /*printf("\nTaula ordenada per niu\n");*/
    /*imprimirtaula(alumnes, no_alumnes);*/
    return 0;
}
int comparacioapartirdindex ( const void* a, const void* b)
{
    if ((*(Alu**)a)->notes[4] > (*(Alu**)b)->notes[4]) return 1;
    else return -1;
}

float mitjana(float dades[], int n) {
    int i;
    float m = 0.;
    for (i = 0; i < n; i++) {
        m += dades[i];
    }
    return m / n;
}
void imprimirdesdindex(Alu** index, int n) {
    for (int j = 0; j < n; j++) {
        printf("%d | ", index[j]->niu);
        for (int i = 0; i < 4; i++) {
            printf("%5.1f", index[j]->notes[i]);
        }
        printf(" |%6.2f", index[j]->notes[4]);
        printf("\n");
    }
};
int niu_gran(const void *a, const void *b) {
    return (*(Alu *)a).niu - (*(Alu *)b).niu;
}


