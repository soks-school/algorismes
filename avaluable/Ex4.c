/*Marina Catalan 1752407, Daniel Hurtado 1703664*/
#include<stdio.h>
#include <stdlib.h>

// #define NGERRES 3
// #define MAXLITRES 10
#define MAXCONF 20

typedef struct{
    unsigned capacitat,contingut;
}gerra;

typedef struct{
    unsigned *continguts;
    unsigned origen, desti;
    unsigned anterior;
}configuracio;

configuracio transvasament(int j, int k, configuracio confi, gerra* gerres, int ngerres){
    unsigned l;
    configuracio conf;
    for(l=0; l<ngerres; l++) {
        conf.continguts[l]=confi.continguts[l];
    }

    conf.continguts[k]=conf.continguts[k]+conf.continguts[j];

    conf.continguts[j]=0;

    if(conf.continguts[k]>gerres[k].capacitat){
        conf.continguts[j]=conf.continguts[k]-gerres[k].capacitat;

        conf.continguts[k]=gerres[k].capacitat;
    }
    return conf;
}

void mostracami ( unsigned num_conf, configuracio * conf, int ngerres){
    int no = 0;
    int i = num_conf;
    while (i != 0) {
        i = conf[i].anterior;
        no++;
    }
    int* cami = (int*)malloc((no+1)*sizeof(int));

    i = num_conf;
    int j = no;
    while (i != 0) {
        cami[j] = i;
        i = conf[i].anterior;
        j--;
    }
    for(i=1; i<no+1; i++){
        // printf("De configuració %u a %u: |",conf[cami[i]].anterior,cami[i]);
        for(unsigned l=0;l<ngerres;l++) printf("%u|",conf[conf[cami[i]].anterior].continguts[l]);
        printf("-(%u,%u)-|",conf[cami[i]].origen,conf[cami[i]].desti);
    }
    for(unsigned l=0;l<ngerres;l++) printf("%u|",conf[cami[no]].continguts[l]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    unsigned i,origen,desti,l;
    int ngerres = atoi(argv[1]);
    gerra* gerres = malloc(sizeof(gerra)*(argc-1));

    if(gerres==NULL){
        printf("No s'ha pogut alocar la memoria necessaria\n");
        return 1;
    }

    for(i=2; i<=ngerres*2-1; i+=2){
        if(atoi(argv[i])<atoi(argv[i+1])){
            printf("Configuració no possible per la gerra %d\n", i/2);
            return 1;
        }        
        gerres[i].capacitat=atoi(argv[i]);
        gerres[i].contingut=atoi(argv[i+1]);

        // if(atoi(argv[i])>MAXLITRES){
        //     printf("Configuració no possible per la gerra %d\n", i/2);
        //     return 1;
        // }
    }
    char* estat_config = calloc(ngerres,sizeof(char));
    if(estat_config==NULL){
        printf("No s'ha pogut alocar la memoria necessaria\n");
        return 1;
    }

    configuracio configuracions[MAXCONF+1];
    printf("Gerres amb capacitats |");
    for(l=0;l < ngerres; l++) printf("%u|", gerres[l].capacitat);
    printf("\n");

    for(l=0; l<ngerres; l++) configuracions[0].continguts[l]=gerres[l].contingut;
    printf("Configuració inicial  |");
    for(l=0; l<ngerres; l++) printf("%u|", configuracions[0].continguts[l]); 
    printf("\n");
    int num_conf=1;
    estat_config[configuracions[num_conf].continguts[0]] [configuracions[num_conf].continguts[1]] [configuracions[num_conf].continguts[2]]=1;
    for(i=0; i<num_conf && num_conf<MAXCONF; i++){
        for(origen=0; origen<ngerres && num_conf<MAXCONF; origen++){
            for(desti=0; desti<ngerres && num_conf<MAXCONF; desti++){
                if(origen==desti) continue;
                if(configuracions[i].continguts[origen]==0) continue;
                if(configuracions[i].continguts[desti]==gerres[desti].capacitat) continue;
                                
                configuracions[num_conf] = transvasament(origen, desti, configuracions[i], gerres, ngerres);
                if(estat_config[configuracions[num_conf].continguts[0]] [configuracions[num_conf].continguts[1]] [configuracions[num_conf].continguts[2]]==1) continue;

                estat_config[configuracions[num_conf].continguts[0]] [configuracions[num_conf].continguts[1]] [configuracions[num_conf].continguts[2]]=1;
                configuracions[num_conf].anterior = i;
                configuracions[num_conf].origen = origen;
                configuracions[num_conf].desti = desti;

                mostracami(num_conf, configuracions, ngerres);
                num_conf++;
            }
        }
    }
    if(num_conf==MAXCONF){
        printf("Hem arribat al màxim de configuracions i pot ser no s'han fet totes\n");
        return 1;
    }
    printf("S'han trobat %u configuracions possibles\n",num_conf);
    // mostracami(15, configuracions);
    return 0;
}
