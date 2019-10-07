#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

//Funcion que crea las cartas del 1-9
void crear_numeros1_9(){
  char colores[8][25] = {" rojo.txt"," azul.txt"," amarillo.txt"," verde.txt", " rojo (2).txt"," azul (2).txt"," amarillo (2).txt"," verde (2).txt"};
  int i;
  for(i = 0; i < 8; i++){
    int numero = 1; //Primero se crean todas las cartas 1's de distintos colores, despues las 2's y asi sucesivamente
    while(numero < 10){
      char directorio[50] = "Mazo/"; //Directorio en donde se guardan las cartas
      char n[2];
      sprintf(n,"%d", numero); //El entero numero se transforma a string
      strcat(directorio,n); //Se concatena el string directorio con el numero de la carta y se guarda en el string directorio
      strcat(directorio,colores[i]); //Se concatena nuevamente el string directorio (este ya fue concatenado con el numero) con el color, quedando de la forma Mazo/numero color.txt
      FILE *fp = fopen(directorio,"a"); //Se  crea el archivo de la carta
      fclose(fp);
      numero++;
    }
  }
}

//Funcion que crea las cartas 0's
void crear_0(){
  char colores[4][25] = {" rojo.txt"," azul.txt"," amarillo.txt"," verde.txt"};
  int i;
  for(i = 0; i < 4; i++){
    char directorio[30] = "Mazo/0";
    strcat(directorio,colores[i]);
    FILE *fp = fopen(directorio,"a");
    fclose(fp);
  }
}


//Funcion para crear todos los directorios a utillizar
void crear_directorios(){
  mkdir("Mazo",0700);
  mkdir("Jugador1",0700);
  mkdir("Jugador2",0700);
  mkdir("Jugador3",0700);
  mkdir("Jugador4",0700);
  mkdir("Juego",0700);
}

//Funcion que crea todas cartas que no son numeros
void crear_especiales(){
  char colores[8][25] = {" rojo.txt"," azul.txt"," amarillo.txt"," verde.txt", " rojo (2).txt"," azul (2).txt"," amarillo (2).txt"," verde (2).txt"};
  int i;
  for(i = 0; i < 8; i++){
    char directorio[30] = "Mazo/+2";
    char directorio2[30] = "Mazo/reversa";
    char directorio3[30] = "Mazo/salto";
    strcat(directorio,colores[i]);
    strcat(directorio2,colores[i]);
    strcat(directorio3,colores[i]);
    FILE *fp = fopen(directorio,"a");
    FILE *fp2 = fopen(directorio2,"a");
    FILE *fp3 = fopen(directorio3,"a");
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
  }
  for(i = 0; i < 4; i++){
    char directorio[30] = "Mazo/+4.txt";
    char directorio2[30] = "Mazo/+4 (2).txt";
    char directorio3[30] = "Mazo/+4 (3).txt";
    char directorio4[30] = "Mazo/+4 (4).txt";
    char directorio5[30] = "Mazo/cambio color.txt";
    char directorio6[30] = "Mazo/cambio color (2).txt";
    char directorio7[30] = "Mazo/cambio color (3).txt";
    char directorio8[30] = "Mazo/cambio color (4).txt";
    FILE *fp = fopen(directorio,"a");
    FILE *fp2 = fopen(directorio2,"a");
    FILE *fp3 = fopen(directorio3,"a");
    FILE *fp4 = fopen(directorio4,"a");
    FILE *fp5 = fopen(directorio5,"a");
    FILE *fp6 = fopen(directorio6,"a");
    FILE *fp7 = fopen(directorio7,"a");
    FILE *fp8 = fopen(directorio8,"a");
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
    fclose(fp7);
    fclose(fp8);
  }
}

//Funcion que mueve un archivo de un directorio origen (directorio_origen) a uno de destino (directorio_destino)
void mover_archivo(char directorio_origen[30], char directorio_destino[30]){
  rename(directorio_origen,directorio_destino);
}

//Funcion que lista en pantalla todos los archivos del directorio entregado
void ver_archivos(char directorio[30]){
  DIR *d;
  int i = 1;
  struct dirent *dir;
  d = opendir(directorio);
  if (d){
      while ((dir = readdir(d)) != NULL){
        if (dir->d_type == DT_REG){
          printf("%d) %s\n", i,dir->d_name);
          i++;
        }
      }
      closedir(d);
    }
}

//Funcion que recibe un directorio y un entero n, y entrega el archivo n-esimo de ese directorio
void encontrar_carta(char directorio[30],int n, char* carta){
  DIR *d;
  int i = 0;
  struct dirent *dir;
  d = opendir(directorio);
  if (d){
      while ((dir = readdir(d)) != NULL){
        if (dir->d_type == DT_REG){
          if(i == n){
          strcpy(carta,dir->d_name);
          break;
        }
          i++;
      }
    }
      closedir(d);
    }
  }

//Funcion que retorna una carta al azar desde el mazo con "tamanio" cantidad de cartas
void escoger_carta_random(int tamanio, char* carta){
  srand(time(NULL));
  int n = rand() % tamanio;
  encontrar_carta("Mazo", n, carta);
}

//Funcion que reparte 7 cartas al azar a cada jugador. Mueve las cartas desde el directorio Mazo ak directorio del jugador
void repartir_cartas(){
    int cont_tamanio = 0;
    int cont_cartas = 0;
    while (cont_cartas < 7){
      char carta[30];
      escoger_carta_random(107-cont_tamanio,carta);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador1/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
    cont_cartas = 0;
    while (cont_cartas < 7){
      char carta[30];
      escoger_carta_random(107-cont_tamanio, carta);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador2/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
    cont_cartas = 0;
    while (cont_cartas < 7){
      char carta[30];
      escoger_carta_random(107-cont_tamanio, carta);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador3/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
    cont_cartas = 0;
    while (cont_cartas < 7){
      char carta[30];
      escoger_carta_random(107-cont_tamanio,carta);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador4/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
    char carta[30];
    escoger_carta_random(107-cont_tamanio,carta);
    char origen[50] = "Mazo/";
    char destino[50] = "Juego/";
    strcat(origen,carta);
    strcat(destino,carta);
    mover_archivo(origen,destino);
}

char* obtener_color(char* carta){
  char *color;
  //Color para la carta salto
  if(carta[0] == 's'){
    if(carta[7] == 'o'){
      color = "rojo";
    }
    else if(carta[7] == 'z'){
      color = "azul";
    }
    else if(carta[7] == 'm'){
      color = "amarillo";
    }
    else if(carta[7] == 'e'){
      color = "verde";
    }
  }
  //Color para la carta reversa
  else if(carta[0] == 'r'){
    if(carta[9] == 'o'){
      color = "rojo";
    }
    else if(carta[9] == 'z'){
      color = "azul";
    }
    else if(carta[9] == 'm'){
      color = "amarillo";
    }
    else if(carta[9] == 'e'){
      color = "verde";
    }
  }
  //Color para el +2
  else if(carta[0] == '+'){
    if(carta[4] == 'o'){
      color = "rojo";
    }
    else if(carta[4] == 'z'){
      color = "azul";
    }
    else if(carta[4] == 'm'){
      color = "amarillo";
    }
    else if(carta[4] == 'e'){
      color = "verde";
    }
  }
  // Color para los numeros
  else{
    if(carta[3] == 'o'){
      color = "rojo";
    }
    else if(carta[3] == 'z'){
      color = "azul";
    }
    else if(carta[3] == 'm'){
      color = "amarillo";
    }
    else if(carta[3] == 'e'){
      color = "verde";
    }
  }
  char * col = color;
  return col;
}

int cumple_condiciones(char* carta, char* carta_actual){
  //Se ve si el nuemro o la primera letra de la carta son iguales, en caso de serlo, la carta fue correctamente tirada
  //printf("Hasta aca va bien\n");
  char *color1 = obtener_color(carta);
  char *color2 = obtener_color(carta_actual);
  if(carta[0] == carta_actual[0]){
    return 0;
  }
  else if(strcmp(color1,color2) == 0){
    return 0;
  }
  return 1;
}

void eliminar_carta(char* origen, int carta_a_jugar){
  char carta [30];
  carta_a_jugar--;
  encontrar_carta(origen, carta_a_jugar, carta);
  strcat(origen,"/");
  strcat(origen,carta);
  remove(origen);
}