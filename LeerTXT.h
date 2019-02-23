#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *proceso;
    int TLlegada;
    int TEjecucion;
    int Tipo;
    int cont;
}

procesos;
procesos *proc = NULL;
void vaciar(char temp[]);
void copiar(char temp[], int i);
procesos *Leer();

procesos *Leer(){
    FILE *f;
    f = fopen("/run/media/josec/Jose Cruz/Documentos/VIMProjects/Proyecto I/Proyecto I/Prueba.txt", "r");
    int cont = 0;
    char temp[50];
    char aux;

    if(f == NULL){
        printf("No se ha podido leer el fichero");
	exit(-1);
    }else{
         while(!feof(f)){
            fgets(temp, 50, f);
            cont++;
        }

        rewind(f);
        proc = (procesos*)malloc(cont*sizeof(procesos)); 

        for(int a = 0; a < cont - 1; a++){
		vaciar(temp);
		aux = '0';
            for(int b = 0; aux != ' '; b++){
		    aux = fgetc(f);
	        if(aux != ' '){
	            temp[b] = aux;
	        }
	    }
	    copiar(temp, a);
	    fgets(temp, 4, f);
	    proc[a].TLlegada = atoi(temp);
	    fgets(temp, 5, f);
	    proc[a].TEjecucion = atoi(temp);
	    fgets(temp, 100, f);
	    proc[a].Tipo = atoi(temp);
        }
    }
    proc[0].cont = cont;
    return proc;
}

void vaciar(char temp[]){
    for(int c = 0; c < 50; c++){
        temp[c] = '\0';
    }
}

void copiar(char temp[], int i){
    int N = strlen(temp) + 1;
    proc[i].proceso = (char*)malloc(N*sizeof(char)-1);
    if(proc[i].proceso == NULL){
        printf("No se ha podido reservar memoria.\n");
	exit(-1);
    }
    strcpy(proc[i].proceso, temp);
    if(proc[i].proceso, temp);
}