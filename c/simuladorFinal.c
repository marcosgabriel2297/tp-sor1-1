#include <stdlib.h>    
#include <unistd.h>         // para castear de puntero a entero
#include <string.h>
#include <time.h>
#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
///////////////////////////////////////////////////////////////////////////
// Info de grupos
///////////////////////////////////////////////////////////////////////////
#define CANTIDAD_GRUPOS 8
char* grupos_labels[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
sem_t semGrupos,semOctavos,semCuartos,semSemi,semFinal;

struct MyStructure{

char *nombre_equipo_1;
char *nombre_equipo_2; 
int index_partido;
char**data_winners;
};

char* grupo_A[] = {"Rusia", "Arabia Saudita", "Egipto", "Uruguay"};
int grupo_A_favoritos[] = {1, 0, 0, 1};
int grupo_A_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


char* grupo_B[] = {"Portugal", "España", "Marruecos", "Irán"};
int grupo_B_favoritos[] = {1, 1, 0, 0};
int grupo_B_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


char* grupo_C[] = {"Francia", "Australia", "Peru", "Dinamarca"};
int grupo_C_favoritos[] = {1, 0, 0, 0};
int grupo_C_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


char* grupo_D[] = {"Argentina", "Islandia", "Croacia", "Nigeria"};
int grupo_D_favoritos[] = {1, 0, 0, 0};
int grupo_D_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


char* grupo_E[] = {"Brasil","Suiza", "Costa Rica", "Serbia"};
int grupo_E_favoritos[] = {1, 0, 0, 0};
int grupo_E_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


char* grupo_F[] = {"Alemania", "Mexico", "Suecia", "Korea del Sur"};
int grupo_F_favoritos[] = {1, 1, 0, 0};
int grupo_F_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


char* grupo_G[] = {"Belgica", "Panama", "Tunez", "Inglaterra"};
int grupo_G_favoritos[] = {0, 0, 0, 1};
int grupo_G_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


char* grupo_H[] = {"Polonia", "Senegal", "Colombia", "Japón"};
int grupo_H_favoritos[] = {0, 0, 1, 0};
int grupo_H_puntos[4][8] = { { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} ,
                             { 0,0,0,0,0,0,0,0} };


void print_tabla_grupo(char* grupo_data[], int tabla[][8]){
  int i, j;
  for (i = 0; i < 4; i++){
        printf ("%s ,",grupo_data[i]);
   
        for (j = 0; j < 8; j++){
          printf ("%d ,",tabla[i][j]);
        }
        printf("\n");
  }
}




///////////////////////////////////////////////////////////////////////////
// End Info de grupos
///////////////////////////////////////////////////////////////////////////


void llenar_tabla(int tabla[][8], int equipo_1, int equipo_2, int goles_equipo_1, int goles_equipo_2)
{

  tabla[equipo_1][1] = tabla[equipo_1][1]+1;
  tabla[equipo_2][1] = tabla[equipo_2][1]+1;


  if(goles_equipo_1 > goles_equipo_2)
  {

        tabla[equipo_1][0] = tabla[equipo_1][0]+3;          

        tabla[equipo_1][2] = tabla[equipo_1][2]+1;

        tabla[equipo_2][4] = tabla[equipo_2][4]+1;

 }
 else if (goles_equipo_1 == goles_equipo_2){
        //empataron
        tabla[equipo_1][0] = tabla[equipo_1][0]+1;          
        tabla[equipo_2][0] = tabla[equipo_2][0]+1;
        //columna 4 = PE(Partidos Empatados)
        tabla[equipo_1][3] = tabla[equipo_1][3]+1;
        tabla[equipo_2][3] = tabla[equipo_2][3]+1;          
  }else{
        //gano el equipo 2
        tabla[equipo_2][0] = tabla[equipo_2][0]+3;          
        tabla[equipo_2][2] = tabla[equipo_2][2]+1;
        //columna 5 = PP(Partidos Perdidos)
        tabla[equipo_1][4] = tabla[equipo_1][4]+1;
  }


  //columna 6 = GF(Goles a Favor)
  tabla[equipo_1][5] = tabla[equipo_1][5]+goles_equipo_1;
  tabla[equipo_2][5] = tabla[equipo_2][5]+goles_equipo_2;


  //columna 7 = GC(Goles en contra)
  tabla[equipo_1][6] = tabla[equipo_1][6]+goles_equipo_2;
  tabla[equipo_2][6] = tabla[equipo_2][6]+goles_equipo_1;


  //columna 8 = Dif(Diferencia de Gol)
  tabla[equipo_1][7] = 0; //TODO:revisar
  tabla[equipo_2][7] = 0; //TODO:revisar
}


void jugar_partido (int equipo_1, int equipo_2, int instancia, char* grupo_data[] , int grupo_puntos[][8], int grupo_favoritos[] ){
  char * nombre_equipo_1;
  char * nombre_equipo_2;
  int goles_equipo_1;
  int goles_equipo_2;

  nombre_equipo_1=grupo_data[equipo_1];
  nombre_equipo_2=grupo_data[equipo_2];
 
  /* random int entre 0 y 10 */
  int rango_gol_equipo1 = 1;
  int rango_gol_equipo2 = 1;
  int base=0;
  if(grupo_favoritos[equipo_1]){
    rango_gol_equipo1 = 7;
    base=3;
  }

  if(grupo_favoritos[equipo_2]){
    rango_gol_equipo2 = 7;
    base=3;
  }

  goles_equipo_1 = (rand() % rango_gol_equipo1)+base;
  goles_equipo_2 = (rand() % rango_gol_equipo2)+base;

  printf("Resultado %s %d -- %s %d \n", nombre_equipo_1, goles_equipo_1, nombre_equipo_2, goles_equipo_2);

  switch(instancia) {
  case 0 :
    //es instancia de grupos
    llenar_tabla(grupo_puntos, equipo_1, equipo_2, goles_equipo_1, goles_equipo_2);
    break;
  default :
    printf("Invalid instancia\n" );
  }

}

void *jugar_grupo (int *grupo)
{
  printf("***************************************** \n");
  printf("Jugando grupo %c \n", *grupos_labels[*grupo]);
  switch(*grupo) {
  case 0 : 
    jugar_partido(0,1, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(0,2, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(2,1, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(2,3, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(3,1, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(3,0, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);

    break;
  case 1 :
    jugar_partido(0,1, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(0,2, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(2,1, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(2,3, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(3,1, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(3,0, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);

    break;
  case 2 :
    jugar_partido(0,1, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(0,2, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(2,1, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(2,3, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(3,1, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(3,0, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);

    break;
  case 3 :
    jugar_partido(0,1, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(0,2, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(2,1, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(2,3, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(3,1, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(3,0, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    print_tabla_grupo(grupo_D, grupo_D_puntos);

    break;
  case 4 :
    jugar_partido(0,1, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(0,2, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(2,1, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(2,3, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(3,1, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(3,0, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);

    break;
  case 5 :
    jugar_partido(0,1, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(0,2, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(2,1, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(2,3, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(3,1, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(3,0, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);

    break;
  case 6 :
    jugar_partido(0,1, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(0,2, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(2,1, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(2,3, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(3,1, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(3,0, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);

    break;
  case 7 :
    jugar_partido(0,1, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(0,2, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(2,1, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(2,3, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(3,1, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(3,0, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    break;
  default :
        printf("Invalid grupo\n" );
  }
}


void jugar_grupos ()
{
  sem_wait(&semGrupos);
  for(int i=0; i < CANTIDAD_GRUPOS; i++ )
  {   
      jugar_grupo(&i);  
  }
  sem_post(&semOctavos);
  pthread_exit(NULL);
}

char* winer_octavos[] = {"Wp49", "Wp50", "Wp51", "Wp52", "Wp53", "Wp54", "Wp55", "Wp56"};

void *jugar_partido_winners(void*p)
{
  struct MyStructure *datos=(struct MyStructure*) p;
  printf("Jugando partido entre %s y %s \n", datos->nombre_equipo_1, datos->nombre_equipo_2);
  int goles_equipo_1;
  int goles_equipo_2;
  /* random int entre 0 y 10 */
  goles_equipo_1 = rand() % 10;
  goles_equipo_2 = rand() % 10;
  if(goles_equipo_1 > goles_equipo_2)
  {
    datos->data_winners[datos->index_partido]=datos->nombre_equipo_1;
  }
  else
  {
    datos->data_winners[datos->index_partido]=datos->nombre_equipo_2;
  }

pthread_exit(NULL);
}

int obtener_primero(int grupo_puntos[][8])
{
  int i;
  int puntaje_maximo=-1;
  int index_maximo=-1;
  for (i = 0; i < 4; i++)
  {
    if(grupo_puntos[i][0]>=puntaje_maximo)
    {
      index_maximo=i;
      puntaje_maximo=grupo_puntos[i][0];
    }
  }
  return index_maximo;
}

int obtener_segundo(int grupo_puntos[][8]){
  int i;
  int puntaje_maximo=-1;
  int index_segundo=-1;


  int index_primero=obtener_primero(grupo_puntos);
  for (i = 0; i < 4; i++){
        if(grupo_puntos[i][0]>=puntaje_maximo && i!=index_primero){
          index_segundo=i;
          puntaje_maximo=grupo_puntos[i][0];
        }
  }
  return index_segundo;
}


void* jugar_octavos ()
{
  sem_wait(&semOctavos);
  srand(time(NULL));

  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;

  printf("***************************************** \n");
  printf("Jugando octavos \n");
  pthread_t hiloAB,hiloCD,hiloBA,hiloDC,hiloEF,hiloGH,hiloFE,hiloHG;

  //partido 49: A1 vs B2
  index_1=obtener_primero(grupo_A_puntos);
  nombre_equipo_1=grupo_A[index_1];
  index_2=obtener_segundo(grupo_B_puntos);
  nombre_equipo_2=grupo_B[index_2];
  struct MyStructure datos={nombre_equipo_1,nombre_equipo_2,0,winer_octavos};
  pthread_create(&hiloAB,NULL ,jugar_partido_winners, &datos);

  //partido 50: C1 vs D2
  index_1=obtener_primero(grupo_C_puntos);
  nombre_equipo_1=grupo_C[index_1];
  index_2=obtener_segundo(grupo_D_puntos);
  nombre_equipo_2=grupo_D[index_2];
  struct MyStructure datos2={nombre_equipo_1,nombre_equipo_2,1,winer_octavos};
  pthread_create(&hiloCD,NULL,(void *)jugar_partido_winners,(void*)&datos2);

  //partido 51: B1 vs A2
  index_1=obtener_primero(grupo_B_puntos);
  nombre_equipo_1=grupo_B[index_1];
  index_2=obtener_segundo(grupo_A_puntos);
  nombre_equipo_2=grupo_A[index_2];
  struct MyStructure datos3={nombre_equipo_1,nombre_equipo_2,2,winer_octavos};
  pthread_create(&hiloBA,NULL,(void *)jugar_partido_winners,(void*)&datos3);

  //partido 52: D1 vs C2
  index_1=obtener_primero(grupo_D_puntos);
  nombre_equipo_1=grupo_D[index_1];
  index_2=obtener_segundo(grupo_C_puntos);
  nombre_equipo_2=grupo_C[index_2];
  struct MyStructure datos4={nombre_equipo_1,nombre_equipo_2,3,winer_octavos};
  pthread_create(&hiloDC,NULL,(void *)jugar_partido_winners,(void*)&datos4);

  //partido 53: E1 vs F2
  index_1=obtener_primero(grupo_E_puntos);
  nombre_equipo_1=grupo_E[index_1];
  index_2=obtener_segundo(grupo_F_puntos);
  nombre_equipo_2=grupo_F[index_2];
  struct MyStructure datos5={nombre_equipo_1,nombre_equipo_2,4,winer_octavos};
  pthread_create(&hiloEF,NULL,(void *)jugar_partido_winners,(void*)&datos5);

  //partido 54: G1 vs H2
  index_1=obtener_primero(grupo_G_puntos);
  nombre_equipo_1=grupo_G[index_1];
  index_2=obtener_segundo(grupo_H_puntos);
  nombre_equipo_2=grupo_H[index_2];
  struct MyStructure datos6={nombre_equipo_1,nombre_equipo_2,5,winer_octavos};
  pthread_create(&hiloGH,NULL,(void *)jugar_partido_winners,(void*)&datos6);
  
  //partido 55: F1 vs E2
  index_1=obtener_primero(grupo_F_puntos);
  nombre_equipo_1=grupo_F[index_1];
  index_2=obtener_segundo(grupo_E_puntos);
  nombre_equipo_2=grupo_E[index_2];
  struct MyStructure datos7={nombre_equipo_1,nombre_equipo_2,6,winer_octavos};
  pthread_create(&hiloFE,NULL,(void *)jugar_partido_winners,(void*)&datos7);

  //partido 56: H1 vs G2
  index_1=obtener_primero(grupo_H_puntos);
  nombre_equipo_1=grupo_H[index_1];
  index_2=obtener_segundo(grupo_G_puntos);
  nombre_equipo_2=grupo_G[index_2];
  struct MyStructure datos8={nombre_equipo_1,nombre_equipo_2,7,winer_octavos};
  pthread_create(&hiloHG,NULL,(void *)jugar_partido_winners,(void*)&datos8);
  
  pthread_join(hiloAB,NULL);
  pthread_join(hiloCD,NULL);
  pthread_join(hiloBA,NULL);
  pthread_join(hiloDC,NULL);
  pthread_join(hiloGH,NULL);
  pthread_join(hiloGH,NULL);
  pthread_join(hiloFE,NULL);
  pthread_join(hiloHG,NULL);

  sem_post(&semCuartos);
  pthread_exit(NULL);

}

char* winer_cuartos[] = {"Wp57", "Wp58", "Wp59", "Wp60"};

void* jugar_cuartos ()
{
  sem_wait(&semCuartos);
  printf("***************************************** \n");
  printf("Jugando cuartos \n");
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;

  //partido 57: Wp49 vs Wp50
  pthread_t hilo1,hilo2,hilo3,hilo4;
  struct MyStructure datos1={winer_octavos[0],winer_octavos[1],0,winer_cuartos};
  pthread_create(&hilo1,NULL,(void *)jugar_partido_winners,(void*)&datos1);
      
    //partido 58: Wp53 vs Wp54
  struct MyStructure datos2={winer_octavos[4],winer_octavos[5],1,winer_cuartos};
  pthread_create(&hilo2,NULL,(void *)jugar_partido_winners,(void*)&datos2);

    //partido 59: Wp51 vs Wp52
  struct MyStructure datos3={winer_octavos[2],winer_octavos[3],2,winer_cuartos};
  pthread_create(&hilo3,NULL,(void *)jugar_partido_winners,(void*)&datos3);

    //partido 60: Wp55 vs Wp5:
  struct MyStructure datos4={winer_octavos[6],winer_octavos[7],3,winer_cuartos};
  pthread_create(&hilo4,NULL,(void *)jugar_partido_winners,(void*)&datos4);

  pthread_join(hilo1,NULL);
  pthread_join(hilo2,NULL);
  pthread_join(hilo3,NULL);
  pthread_join(hilo4,NULL);

  sem_post(&semSemi);
  pthread_exit(NULL);
}

char* winer_semis[] = {"Wp61", "Wp62"};
char* champion[] = {"Wfinal"};


void *jugar_semis ()
{
  sem_wait(&semSemi);   
  printf("***************************************** \n");
  printf("Jugando semis \n");

  //partido 61: Wp57 vs Wp58
  pthread_t hilo1,hilo2;
  struct MyStructure datos1={winer_cuartos[0],winer_cuartos[1],0,winer_semis};
  pthread_create(&hilo1,NULL,(void *)jugar_partido_winners,(void*)&datos1);

  //partido 62: Wp59 vs Wp60
  struct MyStructure datos2={winer_cuartos[2],winer_cuartos[3],1,winer_semis};
  pthread_create(&hilo2,NULL,(void *)jugar_partido_winners,(void*)&datos2);

  pthread_join(hilo1,NULL);
  pthread_join(hilo2,NULL);

  sem_post(&semFinal);
  pthread_exit(NULL);
}


void* jugar_final ()
{
  sem_wait(&semFinal);
  srand(time(NULL));
    
  printf("***************************************** \n");
  printf("Jugando final \n");
  
  //final: Wp91 vs Wp62
  pthread_t hilo;
  struct MyStructure datos1={winer_semis[0],winer_semis[1],0,champion};
  pthread_create(&hilo,NULL,(void *)jugar_partido_winners,(void*)&datos1);
  pthread_join(hilo,NULL);

  printf("***************************************** \n");
  printf("El nuevo campeon del mundo es %s \n", champion[0]);
  printf("***************************************** \n");

  pthread_exit(NULL);
}

void semaforos()
{
  sem_init(&semGrupos,0,1);
  sem_init(&semOctavos,0,0);
  sem_init(&semCuartos,0,0);
  sem_init(&semSemi,0,0);
  sem_init(&semFinal,0,0);
}

void hilos()
{
  pthread_t hiloGrupos,hiloOctavos, hiloCuartos, hiloSemi, hiloFinal;
  pthread_create(&hiloGrupos,NULL,(void *)jugar_grupos,NULL);
  pthread_create(&hiloOctavos,NULL,(void *)jugar_octavos,NULL);
  pthread_create(&hiloCuartos,NULL,(void *)jugar_cuartos,NULL);
  pthread_create(&hiloSemi,NULL,(void *)jugar_semis,NULL);
  pthread_create(&hiloFinal,NULL,(void *)jugar_final,NULL);

  pthread_join(hiloGrupos,NULL);
  pthread_join(hiloOctavos,NULL);
  pthread_join(hiloCuartos,NULL);
  pthread_join(hiloSemi,NULL);
  pthread_join(hiloFinal,NULL);
}


int main ()
{
  //////////////////////////////////////////////////////////////////////
  // start mundial
  //////////////////////////////////////////////////////////////////////
  semaforos();

  hilos();
  pthread_exit(NULL);
  /////////////////////////////////////////////////////////////////////
  // end mundial
  //////////////////////////////////////////////////////////////////////
}
