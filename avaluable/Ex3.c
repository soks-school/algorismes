/*Marina Catalan 1752407, Daniel Hurtado 1703664*/
#include<stdio.h>
#include <stdlib.h>

#define NGERRES 3
#define MAXLITRES 10
#define MAXCONF 20

typedef struct{
    unsigned capacitat,contingut;
}gerra;

typedef struct{
    unsigned continguts[NGERRES];
    unsigned origen, desti;
    unsigned anterior;
}configuracio;

configuracio transvasament(int j, int k, configuracio confi, gerra* gerres){
    unsigned l;
    configuracio conf;
    for(l=0; l<NGERRES; l++) {
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

void mostracami ( unsigned num_conf, configuracio * conf){
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
        for(unsigned l=0;l<NGERRES;l++) printf("%u|",conf[conf[cami[i]].anterior].continguts[l]);
        printf("-(%u,%u)-|",conf[cami[i]].origen,conf[cami[i]].desti);
    }
    for(unsigned l=0;l<NGERRES;l++) printf("%u|",conf[cami[no]].continguts[l]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    unsigned i,j,k,l;
    for(i=1; i<=5; i+=2){
        if(atoi(argv[i])<atoi(argv[i+1])){
            printf("Configuració no possible per la gerra %d\n", i/2);
            return 1;
        }
        if(atoi(argv[i])>MAXLITRES){
            printf("Configuració no possible per la gerra %d\n", i/2);
            return 1;
        }
    }
    char estat_config[MAXLITRES+1][MAXLITRES+1][MAXLITRES+1];
    gerra gerres[NGERRES] = {{atoi(argv[1]),atoi(argv[2])},{atoi(argv[3]),atoi(argv[4])},{atoi(argv[5]),atoi(argv[6])}};

    configuracio configuracions[MAXCONF+1];
    printf("Gerres amb capacitats |");
    for(l=0;l < NGERRES; l++) printf("%u|", gerres[l].capacitat);
    printf("\n");
    for(i=0; i<gerres[0].capacitat+1; i++){
        for(j=0; j<gerres[1].capacitat+1; j++){
            for(k=0; k<gerres[2].capacitat+1; k++){
                estat_config[i][j][k] = 0;
            }
        }
    }
    for(l=0; l<NGERRES; l++) configuracions[0].continguts[l]=gerres[l].contingut;
    printf("Configuració inicial  |");
    for(l=0; l<NGERRES; l++) printf("%u|", configuracions[0].continguts[l]); 
    printf("\n");
    estat_config[configuracions[0].continguts[0]] [configuracions[0].continguts[1]] [configuracions[0].continguts[2]]=1;
    int num_conf=1;
    for(i=0; i<num_conf && num_conf<MAXCONF; i++){
        for(j=0; j<NGERRES && num_conf<MAXCONF; j++){
            for(k=0; k<NGERRES && num_conf<MAXCONF; k++){
                if(j==k) continue;
                if(configuracions[i].continguts[j]==0) continue;
                if(configuracions[i].continguts[k]==gerres[k].capacitat) continue;
                                
                configuracions[num_conf] = transvasament(j, k, configuracions[i], gerres);
                if(estat_config[configuracions[num_conf].continguts[0]] [configuracions[num_conf].continguts[1]] [configuracions[num_conf].continguts[2]]==1) continue;

                estat_config[configuracions[num_conf].continguts[0]] [configuracions[num_conf].continguts[1]] [configuracions[num_conf].continguts[2]]=1;
                configuracions[num_conf].anterior = i;
                configuracions[num_conf].origen = j;
                configuracions[num_conf].desti = k;

                mostracami(num_conf, configuracions);
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
