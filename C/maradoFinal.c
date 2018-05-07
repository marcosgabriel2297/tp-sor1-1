#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t semMa;
sem_t semRa;
sem_t semDo;
int cantidad;

void *imprimirMa ()
{
    for(int i=0; i<cantidad; i++)
    {
        sem_wait(&semMa);       
        printf("Ma ");
        sem_post(&semRa);  
    }
    pthread_exit(NULL);
}
void *imprimirRa ()
{
    for(int i=0; i<cantidad; i++)
    {
        sem_wait(&semRa);
        printf("ra ");
        sem_post(&semDo);   
    }
    pthread_exit(NULL);
}
void *imprimirDo ()
{
    for(int i=0; i<cantidad; i++)
    {
        sem_wait(&semDo);       
        printf("dooooooooooo..... ♪ ♪  \n");
        sem_post(&semMa); 
        sleep(1);  
    }
    pthread_exit(NULL);
}

void *Sem(){
    sem_init(&semMa,0,1);
    sem_init(&semRa,0,0);
    sem_init(&semDo,0,0);
}

void *hilos()
{
    pthread_t hiloMa,hiloRa,hiloDo;

    pthread_create(&hiloMa, NULL, imprimirMa, NULL);
    pthread_create(&hiloRa, NULL, imprimirRa, NULL);
    pthread_create(&hiloDo, NULL, imprimirDo, NULL);
    

    pthread_join(hiloMa, NULL);
    pthread_join(hiloRa, NULL);
    pthread_join(hiloDo, NULL);
    
}

void *destruirSem()
{
    sem_destroy(&semMa);
	sem_destroy(&semRa);
	sem_destroy(&semDo);
}


int main ()
{
    printf("ingrese la cantidad de cantos que desea: ");
    scanf("%i", &cantidad);

    Sem();
    hilos();
    
    pthread_exit(NULL);
 
	destruirSem();

    return 0;
    
}