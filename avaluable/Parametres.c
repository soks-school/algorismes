/* Programa d'exemple amb paràmetres al main.
 * Tots els paràmetres s'intepreten com a cadenes.
 * Podem convertir les cadenes a altres tipus de dades amb les instruccions:
 * n = atoi(c) // converteix la cadena c a enter i la guarda a n.
 * x = atof(c) // converteix la cadena c a double i la guarda a x.
 * n = atol(c) // converteix la cadena c a long integer i la guarda a n.
 * n = atoi(c) // converteix la cadena c a enter i la guarda a n.
 
 
 */
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    printf("Hem rebut %d parametres.\n",argc);
    for(int i=0;i<argc;i++){
        printf("El parametre %d conté la cadena \"%s\"\n",i,argv[i]);
    }
    return 0;
}
