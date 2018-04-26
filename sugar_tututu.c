#include <stdio.h> //standard input/output
#include <pthread.h> //para usar threads

#include <unistd.h>     // para hacer sleep
#include <stdlib.h>     // para libreria de numeros random: srand, rand 
#include <time.h>       // para tomar el tiempo 
#include <semaphore.h>

sem_t semaf1;
sem_t semaf2;
sem_t semaf3;
sem_t semaf4;
unsigned int value=0;
#define NUM_THREADS 4

//cada funcion tocar_movimiento_i toca una parte de la melodia
void* tocar_movimiento_1 (void* parametro)
{ 	
	sem_post(&semaf1);
	while(1){
	   	system("echo Start; mplayer -really-quiet part1_SugarSugar.mp3");
	}
	sleep(16);
	sem_wait(&semaf2);
   	pthread_exit(NULL);
	
}

void* tocar_movimiento_2 (void* parametro)
{
    
	while(1){
	   	system("mplayer -really-quiet part2_SugarSugar.mp3");
		printf("F2");
	}
   	pthread_exit(NULL);
}

void* tocar_movimiento_3 (void* parametro)
{   
	while(1){
	   	system("mplayer -really-quiet part3_SugarSugar.mp3");
	}   
   	pthread_exit(NULL);
}

void* tocar_movimiento_4 (void* parametro)
{   
	while(1){
	   	system("mplayer -really-quiet part4_SugarSugar.mp3");
	}   
   	pthread_exit(NULL);
}


int main ()
{
	sem_init(&semaf1,0,0);
	sem_init(&semaf2,0,0);
	sem_init(&semaf3,0,0);
	sem_init(&semaf4,0,0);
   	pthread_t threads[NUM_THREADS]; //una variable de tipo pthread_t sirve para identificar cada hilo que se cree
                                   //la variable threads es una array de pthread_t
                                   //comparar con char data[100], un array de char                                           
	
	//genero los threads y los lanzo, observar que sin semaforos se ejecutan los 4 casi al mismo tiempo
	//y no se reconoce la melodía   	
	int rc;
   	rc = pthread_create(&threads[1], NULL, tocar_movimiento_2, NULL );
   	rc = pthread_create(&threads[0], NULL, tocar_movimiento_1, NULL );
   	rc = pthread_create(&threads[3], NULL, tocar_movimiento_4, NULL );
   	rc = pthread_create(&threads[2], NULL, tocar_movimiento_3, NULL );
   	

	//esperar a que los threads terminen para terminar el programa principal
	int i;
    	for(i = 0 ; i < NUM_THREADS ; i++)
    	{
        	pthread_join(threads[i] , NULL);
    	}
    	
	pthread_exit(NULL);
	return EXIT_SUCCESS;

	sem_destroy(&semaf1);
	sem_destroy(&semaf2);
	sem_destroy(&semaf3);
	sem_destroy(&semaf4);
}

//Para compilar:   gcc sugar_tututu.c -o sugar_tututu -lpthread
//Para ejecutar:   ./sugar_tututu






