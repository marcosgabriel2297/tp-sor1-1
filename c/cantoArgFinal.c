#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t semOle, semOla, semCadaDia, semOhArg, semSent, aux;

int cantidad;

void *imprimirOle()
{
    for (int i = 0; i < cantidad * 2; i++)
    {
        sem_wait(&semOle);
        printf("ole ole ole  ♪ ♪\n");
        sem_post(&aux);
    }
    pthread_exit(NULL);
}
void *imprimirOla()
{
    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semOla);
        sem_wait(&aux);
        printf("ole ole ole olá  ♪ ♪\n");
        sleep(1);
        sem_post(&semCadaDia);
        sem_post(&semOle);
    }
    pthread_exit(NULL);
}
void *imprimirCadaDia()
{
    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semCadaDia);
        sem_wait(&aux);
        printf("cada dia te quiero más  ♪ ♪ \n");
        sleep(1);
        sem_post(&semOhArg);
    }
    pthread_exit(NULL);
}

void *imprimirOhArg()
{
    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semOhArg);
        printf("oooh Argentinaaaaa  ♪ ♪ \n");
        sem_post(&semSent);
    }
    pthread_exit(NULL);
}

void *imprimirSent()
{
    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semSent);
        printf("es un sentimiento, no puedo parar.... ♪ ♪ \n");
        printf("\n");
        sleep(2);
        sem_post(&semOla);
        sem_post(&semOle);
    }
    pthread_exit(NULL);
}

void *sem()
{
    sem_init(&semOla, 0, 1);
    sem_init(&semOle, 0, 1);
    sem_init(&semCadaDia, 0, 0);
    sem_init(&semOhArg, 0, 0);
    sem_init(&semSent, 0, 0);
}

void *hilos()
{
    pthread_t hiloOle, hiloOla, hiloCadaDia, hiloOhArg, hiloSent;

    pthread_create(&hiloOle, NULL, imprimirOle, NULL);
    pthread_create(&hiloOla, NULL, imprimirOla, NULL);
    pthread_create(&hiloCadaDia, NULL, imprimirCadaDia, NULL);
    pthread_create(&hiloOhArg, NULL, imprimirOhArg, NULL);
    pthread_create(&hiloSent, NULL, imprimirSent, NULL);

    pthread_join(hiloOle, NULL);
    pthread_join(hiloOla, NULL);
    pthread_join(hiloCadaDia, NULL);
    pthread_join(hiloOhArg, NULL);
    pthread_join(hiloSent, NULL);
}

void *destruirSem()
{
    sem_destroy(&semOla);
    sem_destroy(&semOle);
    sem_destroy(&semCadaDia);
    sem_destroy(&semOhArg);
    sem_destroy(&semSent);
}

int main()
{
    printf("ingrese la cantidad de cantos que desea: ");
    scanf("%i", &cantidad);
    printf("\n");
    printf("\n");

    sem();

    hilos();

    destruirSem();
    return 0;
}