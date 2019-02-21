#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char *proceso;
    int TLlegada;
    int TEjecucion;
    char *tipo;
}

procesos;
procesos *proc = NULL;
void vaciar(char temp[]);
void copiar(char temp[], int i);

void main(){
    double tp, tf = 0;
    int np = 0;
    char temp[50];
    char aux;
    int cont = 0;
    FILE *f;
    int men = 0;
    int men1 = 0;
    char *men2;
    f = fopen("/home/josec/Documentos/VIMProjects/Proyecto I/Prueba.txt" , "r");
    if(f == NULL){
        printf("No se ha podido abrir el fichero.\n");
	exit(1);
    }

    while(!feof(f)){
        fgets(temp, 50,f);
	cont++;
    }

    int pro[cont-1];
    rewind(f);
    proc = (procesos*)malloc(cont*sizeof(procesos));
    
    if(proc == NULL){
        printf("No se ha podido reservar la memoria.\n");
	exit(1);
    }
    
    printf("Nombre de usuario:    Tiempo de llegada:    Tiempo de ejecución:    Tipo de usuario:\n"); 

    for(int i = 0; i< cont-1; i++){
        vaciar(temp);
        aux = '0';
	for(int j = 0; aux != ' '; j++){
	    aux = fgetc(f);
            if(aux != '-'){
	        temp[j] = aux;
	    }
	}
	copiar(temp, i);
	fgets(temp, 3, f);
	proc[i].TLlegada = atoi(temp);
	fgets(temp, 3, f);
	proc[i].TEjecucion = atoi(temp);
	fgets(temp, 20, f);
	proc[i].tipo = temp;
	printf("%s                    %i                     %i                    %s\n", proc[i].proceso, proc[i].TLlegada, proc[i].TEjecucion, proc[i].tipo);
    }
    for(int k = 0; k < cont; k++){
        for(int m = k; m < cont-2; m++){
	    if(proc[m].TLlegada > proc[m+1].TLlegada){
	        men = proc[m].TLlegada;
		men1 = proc[m].TEjecucion;
		men2 = proc[m].proceso;
		proc[m].TLlegada = proc[m+1].TLlegada;
		proc[m].TEjecucion = proc[m+1].TEjecucion;
		proc[m].proceso = proc[m+1].proceso;
		proc[m+1].TLlegada = men;
		proc[m+1].TEjecucion = men1;
		proc[m+1].proceso = men2;
	    } 
	}
    }

    //Algoritmo FCFS
    printf("\nALgoritmo First Come First Servered\n");
    for(int j = 0; j < cont-1; j++){
        tf += proc[j].TEjecucion;
	tp = tp + tf;
    	printf("\nCliente %s, terminó su diligencia en %2.1f segundos\n", proc[j].proceso, tf);
    }

    printf("\n-------------------------------");
    printf("\nLa suma de los tiempos es: %2.1f segundos", tp);
    tp = tp / (cont-1);
    printf("\n\nTiempo promedio en FCFS fue de: %2.2f segundos\n", tp);
}

void vaciar(char temp[]){
    for(int i = 0; i < 50; i++){
        temp[i] = '\0';
    }
}

void copiar(char temp[], int i){
    int N = strlen(temp) + 1;
    proc[i].proceso = (char*)malloc(N*sizeof(char)-1);
    if(proc[i].proceso == NULL){
        printf("No se ha podido reservar memoria.\n");
        exit(1);
    }
    strcpy(proc[i].proceso, temp);
    if(proc[i].proceso, temp);
}
