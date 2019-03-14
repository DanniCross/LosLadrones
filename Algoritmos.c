#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "/run/media/josec/Jose Cruz/Documentos/VIMProjects/ProyectoI/LosLadrones/LeerTXT.h"
#include "/run/media/josec/Jose Cruz/Documentos/VIMProjects/ProyectoI/LosLadrones/Metodos.h"

typedef struct{
    char *proceso;
    int TLlegada;
    int TEjecucion;
    int Tipo;
    char *Type;
    int cont;
    int wt = 0;
    int ft = 0;
    int status = 0;
}

procesosT;
procesosT *procT = NULL;
procesosT *procT2 = NULL;
procesos *Leer();
void Hora();
int menu();
void FCFS(procesos *proc, int cont);
void SJF(procesos *proc, int cont);
void ABP(procesos *proc, int cont);
void SRTF(procesos *proc, int cont);
void RoundRobin(procesos *proc, procesos *proT, int cont);

void main(){
    int c = 2;
    int d = 0;
    int cont = 0;
    int p = 1;
    procT = Leer();
    procT2 = procT;
    for(int w = 0; w < cont - 1; w++){
        procT2[w].proceso = " ";
	procT2[w].TLlegada = 0;
	procT2[w].TEjecucion = 0;
	procT2[w].Tipo = 0;
	procT2[w].Type = " ";
	procT2[w].cont = 0;
	procT2[w].wt = 0;
	procT2[w].ft = 0;
	procT2[w].status = 0;
    }
    cont = procT[0].cont;
    while(p){
        Hora();
        int n = menu();
        printf("                         TABLA DE PROCESOS                               \n");
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
	if(n == 1){
            FCFS(procT, cont);
	}else if(n == 2){
            SJF(procT, cont);
	}else if(n == 3){
            ABP(procT, cont);
	}else if(n == 4){
	    SRTF(procT, cont);
	}else if(n == 5){
            RoundRobin(procT, procT2, cont);
	}else{
	    printf("Dato erroneo, intente nuevamente.\n");
	}
	printf("¿Desea probar otro simulador?(1:Si o 2:No): ");
	scanf("%i", &p); 
	if(p != 1){
	    p = 0;
	}
    }
}

void Hora(){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    printf("         BIENVENIDO AL SIMULADOR DEL BANCO LOSLA DRONES LTDA.\n");
    char output[128];
    strftime(output,128,"%d/%m/%y   %H:%M:%S",tlocal);
    printf("%s\n",output);
}

int menu(){
    int n = 0;
    printf("Simuladores:\n");
    printf("1).Simulador algoritmo no expulsivo primero en llegar primero en ejecutarse(FCFS).\n");
    printf("2).Simulador algoritmo no expulsivo primero el trabajo más corto(SJF).\n");
    printf("3).Simulador algoritmo no expulsivo planificación basada en prioridades.\n");
    printf("4).Simulador algoritmo expulsivo primero el de menor tiempo restante(SRTF).\n");
    printf("5).Simulador algoritmo expulsivo turno rotativo(Round Robin).\n");
    printf("6).Simulador algoritmo expulsivo planificación expulsiva basada en prioridades.\n");
    printf("7).Simulador algoritmo propio.\n");
    printf("Elija simulador a utilizar: ");
    scanf("%i", &n);
    return n;
}
