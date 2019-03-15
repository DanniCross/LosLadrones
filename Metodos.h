#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

procesos *OrdenarTL(procesos *pro, int a, int b);

//Algoritmo de planificación First Come First Servered
void FCFS(procesos *pro, int cont){
    printf("\nALgoritmo First Come First Servered\n");
    double tp, tf = 0;
    for(int b = 2; b < cont - 1; b++){
        for(int c = 0; c < cont - b; c++){
            if(pro[c].TLlegada > pro[c+1].TLlegada){
                pro = OrdenarTL(pro, c, c);
	    }
	}
    }

    for(int j = 0; j < cont - 1; j++){   
        tf += pro[j].TEjecucion;
	tp = tp + tf;
    	printf("\nCliente %s, terminó su diligencia en %2.1f segundos", pro[j].proceso, tf);
    }

    printf("\n\nLa suma de los tiempos es: %2.1f segundos", tp);
    tp = tp / (cont-1);
    printf("\nTiempo promedio en FCFS fue de: %2.2f segundos\n", tp);
    printf("----------------------------------------------------------\n");
}
//Algoritmo de planificación Shortest Job First
void SJF(procesos *pro, int cont){
    printf("\nAlgoritmo Shortest Job First\n");
    double tp, tf = 0;

    for(int i = 2; i < cont - 1; i++){
        for(int j = 0; j < cont - i; j++){
	    if(pro[j].TLlegada > pro[j+1].TLlegada){
	        pro = OrdenarTL(pro, j, j);
	    }
	}
    }

    for(int d = 2; d < cont - 1; d++){
	tf = 0;
        for(int e = 1; e < cont - d; e++){
            tf += pro[e].TEjecucion;
	    if(pro[e].TEjecucion > pro[e+1].TEjecucion){
		if(tf > pro[e+1].TLlegada){
                    pro = OrdenarTL(pro, e, e);
	        }
	    }
	}
    }

    tf = 0;

    for(int j = 0; j < cont - 1; j++){   
        tf += pro[j].TEjecucion;
	tp = tp + tf;
    	printf("\nCliente %s, terminó su diligencia en %2.1f segundos", pro[j].proceso, tf);
    }

    printf("\n\nLa suma de los tiempos es: %2.1f segundos", tp);
    tp = tp / (cont-1);
    printf("\nTiempo promedio en SJF fue de: %2.2f segundos\n", tp);
    printf("---------------------------------------------------------\n");
}
//ALgoritmo de planificación basado en prioridades.
void ABP(procesos *pro, int cont){
    printf("\nAlgoritmo basado en prioridades\n");
    double tp, tf = 0;

    for(int i = 2; i < cont - 1; i++){
        for(int j = 0; j < cont - i; j++){
            if(pro[j].TLlegada > pro[j+1].TLlegada){
	        pro = OrdenarTL(pro, j, j);
	    }
	}
    }
    
    for(int f = 2; f < cont - 1; f++){
	tf = 0;
        for(int g = 1; g < cont - f; g++){
	    tf += pro[g-1].TEjecucion;
            if(pro[g].Tipo > pro[g+1].Tipo){
	        if(tf > pro[g+1].TLlegada){
		    pro = OrdenarTL(pro, g, g);
		}
	    }else if(pro[g].Tipo == pro[g+1].Tipo){
	        if(pro[g].TLlegada > pro[g+1].TLlegada){
		    pro = OrdenarTL(pro, g, g);
		}
	    }
	    
	}
    }

    tf = 0;

    for(int a = 0; a < cont - 1; a++){
        tf += pro[a].TEjecucion;
        tp = tp + tf;
        printf("\nCliente %s, terminó su diligencia en %2.1f segundos",pro[a].proceso, tf);	
    }

    printf("\n\nLa suma de los tiempos es: %2.1f segundos", tp);
    tp = tp / (cont - 1);
    printf("\nTiempo promedio en ABP fue de: %2.2f segundos\n", tp);
    printf("---------------------------------------------------------\n");
}
//Algoritmo de planificación expulsivo primero el de menor tiempo restante
void SRTF(procesos *pro,int n)
{	printf("\nAlgoritmo SRTF\n");
	int i,ct=0,spi;	//ct->tiempo actual,spi->indice del proceso mas corto
	double tp= 0;
	int tf = 0;
	//Inicializa cada proceso como no ejecutado	
	for(i=0;i<n;i++)
	{
		pro[i].status = 0;
		pro[i].wt=0;		
	}
	
	do
	{
	   spi=shortestProcess(pro,n,ct); //Indice del proceso más corto
           if(spi==-1) //Si no hay ningun proceso menor
           	break;
                 
	   //Aumenta el tiempo de espera de los procesos que han llegado pero no se ejecutan
	   for(i=0;i<n;i++)
		{
                  if(i!=spi && pro[i].status==0 && ct>=pro[i].TLlegada)
                    {                   
                     pro[i].wt = pro[i].wt + 1;
			
                    }
                }
		
	   ct=ct+1;		//actualizando el tiempo actual
	   pro[spi].TEjecucion= pro[spi].TEjecucion - 1; //Actualiza el tiempo de ejecución
                
       	   if(pro[spi].TEjecucion<=0) //Revisa que el proceso haya finalizado
        	{
         	   pro[spi].status=1; //cambia el estado del proceso a ejecutado
            	   pro[spi].ft=ct-pro[spi].TLlegada+pro[spi].wt; //actualiza el tiempo de finalización
	       	}

	}while(ct);

        //Ordena por tiempo de finalización
	for(int d = 1; d < n; d++)
        {
	   for(int e = 0; e < n - d; e++)
           {
	       if(pro[e].ft > pro[e+1].ft)
                {		
                    pro = OrdenarTL(pro, e, e);
	        }
	   }
        }

        tf = 0;
        //Imprimir	
	for(int d = 0; d < n; d++)
         {   
	  tf = pro[d].ft;
       	  tp = tp + tf;
    	  printf("\nCliente %s, terminó su diligencia en %i segundos", pro[d].proceso, tf);
          tf = 0;
         }
	printf("\n\nLa suma de los tiempos es: %2.1f segundos", tp);
    	tp = tp / (n);
    	printf("\nTiempo promedio en SRTF fue de: %2.2f segundos\n", tp);
    	printf("---------------------------------------------------------\n");
}
//Devuel el indice del proceso mas corto que llego antes de the current time ct
int shortestProcess(procesos *pro,int n,int ct)
{
	int i,min_bt=99999,min_index=-1;
	for(i=0;i<n;i++)
	{
		if(pro[i].status==0 && pro[i].TLlegada<=ct)
		{
			if(pro[i].TEjecucion<min_bt)
			{
			    min_bt=pro[i].TEjecucion;
				min_index=i;
			}
		}
	}
	return min_index;
}
//Algoritmo de planificación expulsivo Turno Rotativo
void RoundRobin(procesos *pro, procesos *proT, int cont){
    printf("\nAlgoritmo expulsivo Round Robin\n");
    double tp = 0;
    int Q, n = 0;
    printf("Defina el Quantum para los procesos: ");
    scanf("%d",&Q);
    int pass = 0;

    for(int h = 2; h < cont - 1; h++){
        for(int i = 0; i < cont - h; i++){
	    if(pro[i].TLlegada > pro[i+1].TLlegada){
	        pro = OrdenarTL(pro, i, i);
	    }
	}
    }
    
    for(int l = 0; l < cont - 1; l++){
	pass = 0;
        for(int m = 0; m < cont - 1; m++){
            if(pro[m].TEjecucion > 0 && pro[m].TEjecucion <= Q){
		proT[l].TEjecucion = n + pro[m].TEjecucion;   
	       	proT[l].TLlegada = pro[m].TLlegada;
		proT[l].proceso = pro[m].proceso;
		proT[l].Tipo = pro[m].Tipo;
		proT[l].Type = pro[m].Type;
		n += pro[m].TEjecucion;
		pro[m].TEjecucion = -1;
		pass = 1;
		m = cont - 2;
	    }else if(pro[m].TEjecucion > 0){
	        n += Q;
	        pro[m].TEjecucion = pro[m].TEjecucion - Q;
    		if(n < pro[m+1].TLlegada || m == cont - 2){
	            m = -1;
		}
		/*sleep(1);
		for(int pp = 0; pp < cont - 1; pp++){
		    printf("\n%s , Llega a los %i segundos, va %i segundos, %i",pro[pp].proceso, pro[pp].TLlegada, pro[pp].TEjecucion, n);
		}
		printf("\n");*/
	    }
	    if(m == cont - 2 && pass == 0){
	        l = l - 1;
	    }
	}
    }
    
    for(int n = 0; n < cont - 1; n++){
        tp += proT[n].TEjecucion;
	printf("\nCliente %s, terminó su diligencia en %d segundos",proT[n].proceso, proT[n].TEjecucion);
    }

    printf("\n\nLa suma de los tiempos es: %2.1f segundos",tp);
    tp = tp / (cont - 1);
    printf("\nTiempo promedio en Round Robin fue: %2.2f segundos\n",tp);
    printf("-------------------------------------------------------------\n");
}
//Algoritmo de planificación expulsivo basado en prioridad.
void ABPX(procesos *pro, procesos *proT, int cont){
    printf("\nAlgoritmo expulsivo basado en prioridad.\n");
    double tp = 0;
    int n = 0;

    for(int i = 2; i < cont - 1; i++){
         for(int j = 0; j < cont - i; j++){
	     if(pro[j].TLlegada > pro[j+1].TLlegada){
	         pro = OrdenarTL(pro, j, j);
	     }
	 }
    }

    for(int k = 0; k < cont - 1; k++){
        for(int l = 0; l < cont - 1; l++){
            
	}
    }
}
//Ordenamiento
procesos *OrdenarTL(procesos *pro, int d, int e){
    int Llega;
    int Ejecuta;
    int Tipo;
    char *proceso;
    char *Type;
    int wt;
    int ft;
    int status;
    Llega = pro[d].TLlegada;
    Ejecuta = pro[d].TEjecucion;
    proceso = pro[d].proceso;
    Tipo = pro[d].Tipo;
    Type = pro[d].Type;
    wt = pro[d].wt;
    ft = pro[d].ft;
    status = pro[d].status;
    pro[d].TLlegada = pro[e+1].TLlegada;
    pro[d].TEjecucion = pro[e+1].TEjecucion;
    pro[d].proceso = pro[e+1].proceso;
    pro[d].Tipo = pro[e+1].Tipo;
    pro[d].Type = pro[e+1].Type;
    pro[d].wt = pro[e+1].wt;
    pro[d].ft = pro[e+1].ft;
    pro[d].status = pro[e+1].status;
    pro[e+1].TLlegada = Llega;
    pro[e+1].TEjecucion = Ejecuta;
    pro[e+1].proceso = proceso;
    pro[e+1].Tipo = Tipo;
    pro[e+1].Type = Type;
    pro[e+1].wt = wt;
    pro[e+1].ft = ft;
    pro[e+1].status = status;
    return pro;
}
