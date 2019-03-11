#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "/run/media/josec/Jose Cruz/Documentos/VIMProjects/ProyectoI/LosLadrones/LeerTXT.h"
#include "/run/media/josec/Jose Cruz/Documentos/VIMProjects/ProyectoI/LosLadrones/Metodos.h"

typedef struct{
    char *proceso;
    int TLlegada;
    int TEjecucion;
    int Tipo;
    char *Type;
    int cont;
}

procesosT;
procesosT *procT = NULL;
procesos *Leer();
void FCFS(procesos *proc, int cont);
void SJF(procesos *proc, int cont);
void ABP(procesos *proc, int cont);
procesos *OrdenarTL(procesos *proc, int d, int e);

void main(){
    int c = 2;
    int d = 0;
    int cont = 0;
    procT = Leer();
    cont = procT[0].cont;
    printf("Cliente    Tiempo de Llegada:    Tiempo de ejecucion:    Tipo de cliente:");
    for(int a = 0; a < cont - 1; a++){ 
        printf("\n%s               ",procT[a].proceso);
	if(procT[a].TLlegada < 10){
	    printf("   %i                  ",procT[a].TLlegada);
	}else if(procT[a].TLlegada < 100){
	    printf("  %i                  ",procT[a].TLlegada);
	}else{
            printf(" %i                  ",procT[a].TLlegada);
	}
	if(procT[a].TEjecucion < 10){
	    printf("   %i               ",procT[a].TEjecucion);
	}else if(procT[a].TEjecucion < 100){
	    printf("  %i               ",procT[a].TEjecucion);
	}else{
	    printf(" %i               ",procT[a].TEjecucion);
	}
        printf("%s", procT[a].Type);	
    }
    printf("\n");
    FCFS(procT, cont);
    SJF(procT, cont);
    ABP(procT, cont);
}
