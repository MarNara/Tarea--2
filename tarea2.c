#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/treemap.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lower_than_int(void* a, void* b) {
  return (*(int*)a < *(int*)b);
}

int lower_than_str(void* a, void* b) {
  return strcmp((char*)a, (char*)b) < 0;
}

int lower_than_float(void* a, void* b) {
   return (*(float*)a < *(float*)b);
}

//estructura de las canciones
// id, artists, album_name, track_name, tempo y track_genero
typedef struct {
  char id[100];
  char artists[100];
  char track_name[100];
  List *track_genero;
  char album_name[300];
  int tempo;
} Song;


// Menú principal
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

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */
void cargar_canciones(const char * ruta_archivo, TreeMap *canciones, TreeMap *por_genero, TreeMap *por_artista, TreeMap *por_tempo) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen(ruta_archivo, "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) 
  {
    // Crea una nueva estructura Film y almacena los datos de cada película
    Song *cancion = (Song *)malloc(sizeof(Song));
    strcpy(cancion->id, campos[0]);        // Asigna ID
    strcpy(cancion->track_name, campos[5]);     // Asigna título
    strcpy(cancion->artists, campos[3]); // Asigna artists
    cancion->track_genero = split_string(campos[20], ",");       // Inicializa la lista de géneros
    cancion->tempo = atoi(campos[18]); // Asigna año, convirtiendo de cadena a entero
    strcpy(cancion->album_name, campos[2]);

    insertTreeMap(canciones, cancion->id, cancion);
    
    List *generos = cancion->track_genero;
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
    Pair *par_artista = searchTreeMap(por_artista, cancion->artists);
    List *lista_artista;

    if(par_artista == NULL)
    {
      lista_artista = list_create();
      insertTreeMap(por_artista, strdup(cancion->artists), lista_artista);
    }
    else
    {
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
      
    while (cancion != NULL) { 
      char* genero2 = list_first(cancion->track_genero);
        
      while(genero2 != NULL){
        printf("ID: %s \n Artista: %s \n Album: %s \n Canción: %s, Género: %s \n Tempo: %d \n", 
          cancion->id, cancion->artists, cancion->album_name, cancion->track_name, genero, cancion->tempo);
        cancion = list_next(canciones);
      }
        
        
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
  printf("Ingrese la “velocidad” deseada de las canciones: \n ");
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
      printf("ID: %s \n Artista: %s \n Album: %s \n Canción: %s, Género: %s \n Tempo: %d \n", 
        cancion->id, cancion->artists, cancion->album_name, cancion->track_name, cancion->track_genero, cancion->tempo); 
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
  fgets(artista, sizeof(artista), stdin);
  
  // Elimina el salto de línea final si existe
  artista[strcspn(artista, "\n")] = '\0';

  Pair *par = searchTreeMap(cancionesPorArtistas, artista);
  if (par == NULL) {
      puts("Artista no encontrado");
      return;
  }
  
  List *canciones = (List *)par->value;
  Song *cancion = list_first(canciones);
  while (cancion != NULL) {
      // Mostrar géneros correctamente
      printf("🎵 %s - %s (Album: %s, Tempo: %d)\n", 
             cancion->track_name, 
             cancion->artists, 
             cancion->album_name, 
             cancion->tempo);
      
      printf("Géneros: ");
      char *genero = list_first(cancion->track_genero);
      while (genero != NULL) {
          printf("%s, ", genero);
          genero = list_next(cancion->track_genero);
      }
      printf("\n\n");
      
      cancion = list_next(canciones);
  }
  presioneTeclaParaContinuar();
}

int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario
               // (sin uso en este fragmento)
  char ruta[1000];


  //crear mapa de canciones
  //falta implementar treeMap

  TreeMap *canciones_id = createTreeMap(lower_than_str);
  TreeMap *canciones_byGenero = createTreeMap(lower_than_str);
  TreeMap *canciones_byTempo = createTreeMap(lower_than_int);
  TreeMap *canciones_byArtista = createTreeMap(lower_than_str);
  List* nombre_lista;

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);
    getchar();

    switch (opcion) {
    case '1':
      puts("Ingrese ruta de cancion:");
      scanf(" %c",ruta);  
      cargar_canciones(ruta,canciones_id,canciones_byGenero,canciones_byArtista,canciones_byTempo);
      break;
    case '2':
      buscar_por_genero(canciones_byGenero);
      break;
    case '3':
      buscar_por_artista(canciones_byArtista);
      break;
    case '4':
      buscar_por_tempo(canciones_byTempo);
      break;
    case '5':
      //crear_list_reproduccion(canciones_id, nombre_lista);
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