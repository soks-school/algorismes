#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *nom;
    char *estacio ;
    int alt;
    float tmtj ,tmxm ,tmnm ,tmx ,tmn ;
} MetCom ;

int main(){
    FILE *meteo;
    MetCom *comarca;
    unsigned i=0,numcom=0,ll;
    
    if ((meteo=fopen("MeteoCat2023.txt","r"))==NULL){
        printf("No es pot obrir el fitxer\n");
        return 1;
    }
    
    while((ll=fgetc(meteo)) != EOF){
        if (ll=='\n'){numcom++;}
    }
    printf("\nDades de %d comarques\n",numcom);
    
    rewind(meteo);
    printf("meteo");
    if((comarca = (MetCom *) malloc(numcom * sizeof(MetCom))) == NULL){
        printf ("\nNo es possible assignar la memoria necessaria...\n\n");
        return 1;
    }

    printf( "his malloc");
    char temp_name [35];
    for(i=0;i<numcom;i++){
        int name_size = fscanf(meteo, "%19[a-zA-Z'. -];", temp_name);
        comarca[i].nom = malloc(( name_size+1 )*sizeof(char));
        strcpy(comarca[i].nom, temp_name);

        printf("my malloc");
        name_size = fscanf(meteo, "%34[a-zA-Z'. -];", temp_name);
        comarca[i].estacio = malloc(( name_size+1 )*sizeof(char));
        strcpy(comarca[i].estacio, temp_name);
        fscanf(meteo, "%d;", &comarca[i].alt);
        fscanf(meteo, "%f;", &(comarca[i].tmtj));
        fscanf(meteo, "%f;", &(comarca[i].tmxm));
        fscanf(meteo, "%f;", &(comarca[i].tmnm));
        fscanf(meteo, "%f;", &(comarca[i].tmx));
        fscanf(meteo, "%f\n", &(comarca[i].tmn));
    }
    printf("Fi de la lectura.....\n\n");
    
    fclose(meteo);

    printf("   Comarca              Estacio                             Max\n");
    printf("================================================================\n");
    float smx = 0, smn = 0;
    for(i=0;i<numcom;i++){
        printf("%2u ",i+1);
        printf("%-20s ",comarca[i].nom);
        printf("%-35s ",comarca[i].estacio);
        printf("%-.1f",comarca[i].tmx);
        printf("\n");
        smx += comarca[i].tmx;
        smn += comarca[i].tmn;
    }
    printf("La mitjana maxima es: %g\n", smx/numcom);
    printf("La mitjana minima es: %g", smn/numcom);
 
    return 0;
}
