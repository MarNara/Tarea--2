#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/treemap.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h> 

//estructura de las canciones
// id, artists, album_name, track_name, tempo y track_genre
typedef struct {
  char id[100];
  char artists[100];
  char track_name[100];
  char track_genre[100];
  char album_name[300];
  float tempo;
} Song;

int lower_than_str(void* a, void* b) 
{
  return strcmp((char*)a, (char*)b) < 0;
}
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Base de Datos de Canciones");
  puts("========================================");

  puts("1) Cargar Canciones");
  puts("2) Buscar por Género");
  puts("3) Buscar por Artista");
  puts("4) Buscar por Tempo");
  puts("5) Crear Lista de Reproducción");
  puts("6) Agregar Canción a Lista");
  puts("7) Mostrar Canciones de una Lista");
  puts("8) Salir");
}


void cargarArchivo(const char *ruta, TreeMap* cancionesID,TreeMap* cancionesGenero) 
{
    List *lista_id = list_create();

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) 
    {
        perror("Error al abrir el archivo");
        presioneTeclaParaContinuar();
        return;
    }

    // Leer y descartar la primera línea (cabeceras)
    char **cabeceras = leer_linea_csv(archivo, ',');
    if (cabeceras == NULL) {
        printf("Archivo vacío o con formato incorrecto\n");
        presioneTeclaParaContinuar();
        fclose(archivo);
        return;
    }

    // campos queda como un arreglo en el cual es guardado la cada dato
    char **campos;
    while ((campos = leer_linea_csv(archivo, ',')) != NULL)
    {
      Song *cancion = (Song *)malloc(sizeof(Song));
      if (cancion == NULL) {
        perror("Error al asignar memoria para canción");
        presioneTeclaParaContinuar();
        continue;
      }

      // Asignaciones seguras con strncpy
      strncpy(cancion->id, campos[0], sizeof(cancion->id) - 1);
      strncpy(cancion->track_name, campos[4], sizeof(cancion->track_name) - 1);
      strncpy(cancion->artists, campos[2], sizeof(cancion->artists) - 1);
      strncpy(cancion->album_name, campos[3], sizeof(cancion->album_name) - 1);
      strncpy(cancion->track_genre, campos[20], sizeof(cancion->track_genre) - 1);
      cancion->tempo = atof(campos[18]);

      insertTreeMap(cancionesID, cancion->id, cancion);

      if (searchTreeMap(cancionesGenero, cancion->track_genre) == NULL)
      {
        list_pushCurrent(lista_id, cancion->id);
        insertTreeMap(cancionesGenero,cancion->track_genre,lista_id);
      }
      else
      {
        list_pushCurrent(lista_id, cancion->id);
        insertTreeMap(cancionesGenero,cancion->track_genre,lista_id);
      }

  printf("Archivo cargado perfectamente\n");

  presioneTeclaParaContinuar();
  fclose(archivo);
  }
}

/*
    List *generos = cancion->track_genre;
    char *genero;
    while ((genero = list_next(generos)) != NULL)
    {
      Pair *par = searchTreeMap(por_genero,genero);
      List *lista_genero;

      if(par == NULL)
      {
        lista_genero = list_create();
        insertTreeMap(por_genero, strdup(genero), lista_genero);
      }
      else
      {
        lista_genero = (List *)par->value;//lista con todas las canciones
      }

      list_pushBack(lista_genero, cancion);
    }
    
  // Normalizar el nombre del artista a minúsculas
  char artista_normalizado[100];
  strcpy(artista_normalizado, cancion->artists);  // Copia el nombre original
  for (int i = 0; artista_normalizado[i]; i++) {
    artista_normalizado[i] = tolower(artista_normalizado[i]);
  }                  // Convierte a minúsculas

  // Buscar o insertar en el mapa con la clave normalizada
  Pair *par_artista = searchTreeMap(por_artista, artista_normalizado);
  List *lista_artista;

  if (par_artista == NULL) {
      lista_artista = list_create();
      insertTreeMap(por_artista, strdup(artista_normalizado), lista_artista);  // Usa la versión normalizada
  } else {
      lista_artista = (List *)par_artista->value;
  }
  list_pushBack(lista_artista, cancion);
  

    char *categoria;
    if (cancion->tempo < 80) categoria = "Lentas";
    else if (cancion->tempo <= 120) categoria = "Moderadas";
    else categoria = "Rapidas";

    Pair *par_tempo = searchTreeMap(por_tempo, categoria);
    List *lista_tempo;

    if (par_tempo == NULL)
    {
      lista_tempo = list_create();
      insertTreeMap(por_tempo, strdup(categoria), lista_tempo);
    }
    else
    {
      lista_tempo = (List *) par_tempo->value;
    }
    list_pushBack(lista_tempo, cancion);
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas

}
*/

/**
 * Busca y muestra la información de una película por su ID en un mapa.
 */


 //Arreglar
void buscar_por_genero(TreeMap* cancions_bygeneros) {
  char genero[100];

  // Solicita al usuario el ID de la canción
  printf("Ingrese el género de la canción: ");
  scanf(" %[^\n]", genero); // Lee el ID del teclado

  Pair *pair = searchTreeMap(cancions_bygeneros, genero);
  
  if (pair != NULL) {
    List* canciones = pair->value;
    Song *cancion = list_first(canciones);
    int contador = 0;
    printf("canciones del genero: %s", genero);
    while (cancion != NULL) {  
      printf("ID: %s \n Artista: %s \n Album: %s \n Canción: %s \n Tempo: %d \n", 
        cancion->id, cancion->artists, cancion->album_name, cancion->track_name, cancion->tempo);
      contador++;
      cancion = list_next(canciones);  
        
        //presioneTeclaParaContinuar();
    }
  }
  else{
    printf("No se han encontardo canciones del género %s", genero);
  }
  presioneTeclaParaContinuar();
}


//buscar tempo, necesito un switch, ARREGLAR
void buscar_por_tempo(TreeMap* canciones_tempo){
  int opcion;
  //pedir al usuario que ingrese un tempo
  printf("Ingrese la “velocidad” deseada de las canciones: \n");
  printf("1) Lentas: menor 80 BPM \n");
  printf("2) Moderadas: mayor o igual a 80, menor o igual a 120 \n");
  printf("3) Rapidas: mayor a 120\n");
  //VEERIFICAR EL SACNF Y EL TIPO DE DATO
  scanf("%d", &opcion); // Lee el ID del teclado
  char* clave;
  switch(opcion){
    case 1 : 
      clave = "Lentas";
      break;
    case 2 :
      clave = "Moderadas";
      break;
    case 3 :
      clave = "Rapidas";
      break;
    default :
      printf("Opción Invalida");
      return;
  }
  Pair* pair = searchTreeMap(canciones_tempo, clave);
  
  //Song *cancion = (Song *)malloc(sizeof(Song));
  if (pair != NULL) {
    List* canciones = pair->value;
    Song *cancion = list_first(canciones);
    while (pair != NULL)
    {
      printf("ID: %s \n Artista: %s \n Album: %s \n Canción: %s, Género: %s \n Tempo: %d \n\n", 
        cancion->id, cancion->artists, cancion->album_name, cancion->track_name, cancion->track_genre, cancion->tempo); 
      cancion = list_next(canciones);
      //presioneTeclaParaContinuar();   
    }
    //pair = nextTreeMap(canciones_tempo);
  }
  else{
    printf("Tempo inválido...");
  }
  presioneTeclaParaContinuar();
}

void buscar_por_artista(TreeMap *cancionesPorArtistas) {
  char artista[100];
  printf("Ingrese nombre del artista: ");
  scanf("%99[^\n]", artista);
  getchar();  // Limpiar el buffer

  // Normalizar entrada a minúsculas
  for (int i = 0; artista[i]; i++) {
      artista[i] = tolower(artista[i]);
  }

  Pair *par = searchTreeMap(cancionesPorArtistas, artista);
  if (par != NULL) {
      List *canciones = (List *)par->value;
      Song *cancion = list_first(canciones);
      while (cancion != NULL) {
          printf("🎵 %s - %s (Álbum: %s, Tempo: %d)\n", 
                 cancion->track_name, 
                 cancion->artists, 
                 cancion->album_name, 
                 cancion->tempo);
          cancion = list_next(canciones);
      }
  } else {
      printf("Artista '%s' no encontrado.\n", artista);
  }
  presioneTeclaParaContinuar();
}

void crear_lista_reproduccion(TreeMap* canciones_id){
  //verificar si existe
  char nombre_lista[100];
  bool nombre_lista_valida = false;
  /*
  while(!nombre_lista_valida){
    if (searchTreeMap(crear_lista_reproduccion, nombre_lista) != NULL){
      printf("ya existe una lista con el nombre %s", );

    }
  }
  */
  //preguntar al ususario porqué nombre quiere para implementar la lista
  printf("Ingrese el nombre para la nueva lista:");
  scanf("%99[^\n]", &nombre_lista);
  getchar();

  //debo verificar si ya existe el nombre de la lista

}


int main() 
{
  SetConsoleOutputCP(65001); //esta funcion sirve para poner el formato UTF-8 sirve para mostrar los caractares españoles

  TreeMap *canciones_id = createTreeMap(lower_than_str);
  TreeMap *canciones_byGenero = createTreeMap(lower_than_str);
  TreeMap *canciones_byTempo = createTreeMap(lower_than_str);//debiese ser tipo float??
  TreeMap *canciones_byArtista = createTreeMap(lower_than_str);
  List* nombre_lista;

  char ruta[1000]; //variable ruta para mas tarde;
  char opcion; // variable opcion

  do // bucle de menú
  {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf("%c", &opcion); //obtengo la opcion
    getchar(); // Limpiar el buffer después de scanf
    
    switch(opcion) 
    {
      case '1': 
        limpiarPantalla();
        printf("Ingrese la ubicación del archivo CSV: ");
        fgets(ruta, sizeof(ruta), stdin); // se obtiene la ruta
        ruta[strcspn(ruta, "\n")] = '\0'; // se le quita el \n de al final
        cargar_canciones(ruta, canciones_id, canciones_byGenero);
        break;

        case '2':
        limpiarPantalla();
        buscar_por_genero(canciones_byGenero);
        break;
      case '3':
        limpiarPantalla();
        buscar_por_artista(canciones_byArtista);
        break;
      case '4':
        limpiarPantalla();
        buscar_por_tempo(canciones_byTempo);
        break;
      case '5':
        //crear_list_reproduccion(canciones_id);
        break;
      case '6':
        //agregar_cancion_aLista(canciones);
        break;
      case '7':
        //mostrar_list_canciones(canciones);
        break;
      }
      presioneTeclaParaContinuar();
  
    } while (opcion != '8');
  
    return 0;
  }