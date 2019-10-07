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
//Funcion utilizada para que el jugador juegue una carta de su mano y esta se mueva al directorio Juego
int tirar_carta(int carta_a_jugar, char* origen){
  char carta[30];
  char carta_actual[30];
  //printf("ESTOUYYYYSDSADAS AQUIII");
  encontrar_carta("Juego",0,carta_actual);
  carta_a_jugar--;
  encontrar_carta(origen, carta_a_jugar,carta);
  // Si es del mismo color o del mismo numero.
  if(cumple_condiciones(carta,carta_actual) == 0){
    char destino[50] = "Juego/";
    char elimina[50] = "Juego";
    eliminar_carta(elimina,1);
    strcat(origen,"/");
    strcat(origen,carta);
    strcat(destino,carta);
    mover_archivo(origen,destino);
    return 0;
  }
  // Si es cambia color o +4, si o si debo eliminar la carta que ya estaba en juego.
  else if(carta[0] == 'c' || carta[1] == '4'){
    char destino[50] = "Juego/";
    char elimina[50] = "Juego";
    eliminar_carta(elimina,1);
    strcat(origen,"/");
    strcat(origen,carta);
    strcat(destino,carta);
    mover_archivo(origen,destino);
    return 0;
  }
  // Sino no puedo tirar esa carta.
  else{
    printf("No se puede tirar dicha carta\n");
    return 1;
  }
}

// Funcion que retorna el tamanio del directorio.
int tamanio_directorio(char* directorio){
  DIR *d;
  int cont = 0;
  struct dirent *dir;
  d = opendir(directorio);
  if (d){
      while ((dir = readdir(d)) != NULL){
        if (dir->d_type == DT_REG){
          cont++;
        }
      }
      closedir(d);
  }
  return cont;
}

//Funcion que elimina la carta dado su nombre y el directorio en que se encuentra

void robar_carta_paso(char* directorio, int cantidad, int tamanio, char* carta){
  escoger_carta_random(tamanio_directorio("Mazo"),carta);
  char destino[30];
  strcpy(destino,directorio);
  char origen[50] = "Mazo/";
  strcat(destino,"/");
  strcat(origen,carta);
  strcat(destino,carta);
  mover_archivo(origen,destino);
  printf("Robaste la carta: %s\n", carta);
}

void robar_carta(char* directorio, int cantidad, int tamanio){
  int i = 0;
  int tamanio_actual = tamanio;
  while(i < cantidad){
    char carta[30];
    escoger_carta_random(tamanio_actual, carta);
    char destino[30];
    strcpy(destino,directorio);
    char origen[50] = "Mazo/";
    strcat(destino,"/");
    strcat(origen,carta);
    strcat(destino,carta);
    mover_archivo(origen,destino);
    printf("Robaste la carta: %s\n",carta);
    i++;
    tamanio_actual--;
    //Si el mazo se queda sin cartas se acaba el juego
    if(tamanio_actual == 0){
      break;
    }
  }
}

//Funcion que verifica la carta que ya estaba en el juego.
int verificar_carta_jugada(char* carta_actual){
  int caso;
  if(carta_actual[0] == '+'){
    if(carta_actual[1] == '2'){
      return 0;
    }
    else if(carta_actual[1] == '4'){
      return 1;
    }
  }
  else if(carta_actual[0] == 's'){
    return 2; //Indica que el jugador ya fue saltado para no ser saltado nuevamente
  }
  else{
    return 3;
  }
}

// Funcion que verifica la carta que acabo de lanzar.
int verificar_carta_lanzada(char* carta_actual){
  int caso;
  if(carta_actual[0] == 'c' || carta_actual[1] == '4'){
    printf("Tienes derecho a cambiar el color\n");
    return 1;
  }
  else if(carta_actual[0] == 'r'){
    //printf("Se cambia el sentido\n");
    return 2;
  }
  else{
    //printf("Otro caso\n");
    return 3;
  }
}

int main(){
  ///Creacion de directorios y de las cartas///////////
  crear_directorios();
  crear_numeros1_9();
  crear_0();
  crear_especiales();
  //Se reparten 7 cartas a cada jugador
  repartir_cartas();
  int cont = 0;
  int c;
  char jugador[30]; //Almacena Jugador actual
  char directorio[30];
  char color[30];
  char carta_jugada[30];
  char carta_lanzar[30];
  char carta_color[30];
  char cambio_color[15] = "verde";
  int cambiaron_color = 0;
  int fin = 0;
  int pasa_turno = 0;
  int usado = 0;
  while(fin == 0){
    strcpy(jugador,"Jugador1");
    printf("TUUUURNO DEEEEE %s\n", jugador);
    printf("JUEGO ACTUAL\n");
    ver_archivos("Juego");
    encontrar_carta("Juego",0,carta_jugada);
    c = verificar_carta_jugada(carta_jugada);
    //printf("caso: %d\n", c);
    switch (c)
    {
    case 0:
      //printf("Caso del +2\n");
      if(usado == 0){
        printf("Te han tirado un +2, debes robar 2 cartas y terminar tu turno\n");
        robar_carta(jugador,2,tamanio_directorio("Mazo"));
        pasa_turno = 1;
        usado = 1;
      }
      break;
    case 1:
      //printf("Caso del +4\n");
      if(usado == 0){
        printf("Te han tirado un +4, debes robar 4 cartas y terminar tu turno\n");
        robar_carta(jugador,4,tamanio_directorio("Mazo"));
        pasa_turno = 1;
        usado = 1;
      }
      break;
    case 2:
      //printf("Caso del skip\n");
      if(usado == 0){
        printf("Te han tirado una carta de salto, debes terminar tu turno\n");
        pasa_turno = 1;
        usado = 1;
      }
      break;
    case 3:
      //printf("Otro caso\n");
      usado = 1;
      break;
    }
    if(pasa_turno == 0 && usado == 1){
      printf("ESTA ES TU MANO: \n");
      ver_archivos(jugador);
      if(tamanio_directorio(jugador) == 1){
        printf("UNO!!!!\n");
      }
      if(cambiaron_color == 1){
          printf("CAMBIARON COLOR A: %s\n", cambio_color);
      }
      printf("Ingrese carta a jugar: (Si no tiene, robe con 0) \n");
      scanf("%d", &c);
      if(c != 0){
        if(cambiaron_color == 1){
          strcpy(directorio,"Jugador1");
          encontrar_carta(jugador,c-1,carta_color);
          strcpy(color,obtener_color(carta_color));
          if(color[2] == cambio_color[2]){
            tirar_carta(c,directorio);
            c = 3;
            cambiaron_color = 0;
          }
          else if(carta_color[0] == 'c' || carta_color[1] == '4'){
            tirar_carta(c ,directorio);
            c = 1;
          }
          else{
            c = 0;
          }
        }
        else{
          strcpy(directorio,"Jugador1");
          c = tirar_carta(c,directorio);
          if(c == 0){
              encontrar_carta("Juego",0,carta_lanzar);
              c = verificar_carta_lanzada(carta_lanzar);
          }
          else{
            c = 4;
          }
        }
      }
      char carta_paso[30];
      int opcion;
      switch (c)
      {
        case 0:
          strcpy(directorio,"Jugador1");
          robar_carta(directorio,1,tamanio_directorio("Mazo"));
          /*robar_carta_paso(jugador,1,tamanio_directorio("Mazo"),carta_paso);
          printf("Quieres tirar la carta?\n");
          printf("0) No\n");
          printf("1) Si\n");
          scanf("%d", &opcion);
          if(opcion == 1){
            c = verificar_carta_lanzada("")
            if(c == 0){
              encontrar_carta("Juego",0,carta_lanzar);
              c = verificar_carta_lanzada(carta_lanzar);
              break;
            }
            else{
              robar_carta(directorio,1,tamanio_directorio("Mazo"));
              break;
            }
          }
          else{
            break;
          }*/
        case 1:
          printf("Escoge el color a cambiar: \n");
          printf("1) Rojo\n");
          printf("2) Azul\n");
          printf("3) Amarillo\n");
          printf("4) Verde\n");
          int opc_color;
          scanf("%d",&opc_color);
          if(opc_color == 1){
            strcpy(cambio_color,"rojo");
          }
          else if(opc_color == 2){
            strcpy(cambio_color,"azul");
          }
          else if(opc_color == 3){
            strcpy(cambio_color,"amarillo");
          }
          else if(opc_color == 4){
            strcpy(cambio_color,"verde");
          }
          cambiaron_color = 1;
          break;
        case 2:
          printf("Cambiaste el sentido\n");
          break;
        case 3:
          break;
        case 4:
          robar_carta(jugador,1,tamanio_directorio("Mazo"));
          break;
      }
      usado = 0;
      if(tamanio_directorio(jugador) == 0){
        printf("Un jugador se ha quedado sin cartas y gana el juego\n");
        fin = 1;
      }
      if(tamanio_directorio("Mazo") == 0){
        printf("Se han agotado las cartas del mazo\n");
        fin = 1;
      }
    }
    else{
      pasa_turno = 0;
    }
  }
  printf("\n###########EL JUEGO HA FINALIZADO###########\n");
  /*printf("CARTAS DE JUGADOR1\n");*/
  /*ver_archivos("Jugador1");
  printf("Ingrese carta a eliminar: \n");
  scanf("%d", &c);
  strcpy(directorio,"Jugador1");
  eliminar_carta(directorio,c);*/
  /*tirar_carta(c,directorio);*/
  //strcpy(directorio,"Jugador1");
  //robar_carta(directorio,2,50);
  /*while(cont < 5){
    ver_archivos("Jugador1");
    printf("Ingrese carta a eliminar: \n");
    scanf("%d", &c);
    strcpy(directorio,"Jugador1");
    tirar_carta(c,directorio);
    //eliminar_carta(directorio,c);
    cont++;
  */

  return 0;
}
