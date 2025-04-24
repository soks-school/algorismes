/*Marina Catalan 1752407, Daniel Hurtado 1703664*/
# include <stdio.h>
# include <stdlib.h>

typedef struct Dada{
    int niu;
    float notes[5];
    struct Dada * seg;
} Alu;

float mitjana(float [],int );
void imprimirllista(Alu* inicill);
void inserir(Alu* actual, Alu** inicill);
void esborrar(int niu, Alu** inicill);
void imprimirenordre(Alu** index, int n);
int comparaciomitjana ( const void* a, const void* b);
Alu* cercabinarianiu( Alu** index, int niu, int n);

int main(){
    FILE *dades;
    int n,i,lrg=0;
    
    Alu *inicill=NULL, *actual = NULL;
    
    dades=fopen("Llista.txt","r");
    if(dades==NULL){
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    
    while(!(fscanf(dades,"%i;",&n)==EOF)){
        if((actual=(Alu *)malloc(sizeof(Alu)))==NULL){
            printf("Problema assignant espai de memoria\n");
            return 2;
        }
        lrg++;
        actual->niu=n;
        for(i=0;i<4;i++){
            fscanf(dades,"%f",&actual->notes[i]);
            fgetc(dades);//llegeix i descarta els ; i el \n
        }
        actual->notes[4]=mitjana(actual->notes,4);

        inserir(actual, &inicill);
    }
    fclose(dades);
    imprimirllista(inicill);
    printf("\nS'ha llegit informacio de %d linies.\n\n",lrg);

    if((actual=(Alu *)malloc(sizeof(Alu)))==NULL)
    {
        printf("Problema assignant espai de memoria\n");
        return 2;
    }
    lrg++;
    actual->niu = 1234567;
    actual->notes[0] = 5.6;
    actual->notes[1] = 6.2;
    actual->notes[2] = 4.3;
    actual->notes[3] = 8.6;
    actual->notes[4] = mitjana(actual->notes, 4);
    inserir(actual, &inicill);
    imprimirllista(inicill);
    printf("\nS'ha afegit una dada\n");

    esborrar(1000961, &inicill);
    esborrar(1110847, &inicill);
    esborrar(3900285, &inicill);
    esborrar(3989795, &inicill);
    imprimirllista(inicill);
    printf("\nS'ha eliminat una dada\n");

    lrg -= 4;
    Alu** adrecesordremitjana;
    Alu** indexmitjana;
    if((adrecesordremitjana = (Alu**)malloc(sizeof(Alu*) * lrg))==NULL){
        printf("Problema assignant espai de memoria\n");
        return 2;
    }
    if((indexmitjana = (Alu**)malloc(sizeof(Alu*) * lrg))==NULL){
        printf("Problema assignant espai de memoria\n");
        return 2;
    }
    actual = inicill;
    for(i=0; i<lrg; i++){
        if(actual != NULL){
            adrecesordremitjana[i] = actual;
            indexmitjana[i] = actual;
            actual = actual->seg;
        }
    }
    imprimirenordre(adrecesordremitjana, lrg);
    printf("\nImprés desde index\n");
    qsort(adrecesordremitjana, lrg, sizeof(Alu*), comparaciomitjana);
    imprimirenordre(adrecesordremitjana, lrg);
    printf("\nImprés per mitjana\n");

    printf("Dades alumne: ");
    Alu* alumne = cercabinarianiu(indexmitjana, 1829476, lrg);
    printf("%d | ", alumne->niu);
    for (int i = 0; i < 4; i++) {
        printf("%5.1f", alumne->notes[i]);
    }
    printf(" |%6.2f", alumne->notes[4]);
    printf("\n");


    return 0;
}

float mitjana(float dades[],int n){
    int i;
    float m=0.;
    for(i=0;i<n;i++) {
        m+=dades[i];
    }
    return m/n;
}

void imprimirllista(Alu* inici) {
    while(!(inici==NULL)){
        printf("%d | ",inici->niu);
        for(int i=0;i<4;i++){
            printf("%5.1f",inici->notes[i]);
        }
        printf(" |%6.2f",inici->notes[4]);
        printf("\n");
        inici=inici->seg;
    }
}

void inserir(Alu* actual, Alu** inicill){
    Alu* anterior;
    if(*inicill==NULL){
        actual->seg=NULL;
        *inicill=actual;
    }
    else{
        if (actual->niu < (*inicill)->niu){
            actual->seg = *inicill;
            *inicill=actual;
        }
        else{
            anterior=*inicill;
            while(anterior->seg != NULL && (anterior->seg)->niu < actual->niu){
                anterior = anterior->seg;
            }
            actual->seg = anterior->seg;
            anterior->seg = actual;
        }
    }
}

void esborrar(int niu, Alu** inicill){
    Alu* actual = *inicill;
    Alu* anterior;
    if((*inicill)->niu==niu){
        *inicill = (*inicill)->seg;
        return;
    }
    while(!(actual==NULL)){
        anterior = actual;
        actual=actual->seg;
        if(actual != NULL && actual->niu == niu){
            anterior->seg = actual->seg;
            free(actual);
            return;
        }
    }
}

void imprimirenordre(Alu** index, int n) {
    for (int j = 0; j < n; j++) {
        if(index[j]==NULL){
            printf("NULL\n");
            fflush(stdout);
            exit(1);
        }
        printf("%d | ", index[j]->niu);
        for (int i = 0; i < 4; i++) {
            printf("%5.1f", index[j]->notes[i]);
        }
        printf(" |%6.2f", index[j]->notes[4]);
        printf("\n");
    }
};

int comparaciomitjana ( const void* a, const void* b){
    if ((*(Alu**)a)->notes[4] > (*(Alu**)b)->notes[4]) return 1;
    else return -1;
}

Alu* cercabinarianiu( Alu** index, int niu, int n) {
    int lower = 0;
    int upper = n-1;
    int mid;

    while (lower <= upper) {
        mid = lower + (upper - lower)/2;

        if (index[mid]->niu == niu) {
            return index[mid];
        }
        if (index[mid]->niu < niu) {
            lower = mid+1;
        }else {
            upper = mid-1;
        };
    }
    return NULL;
}
