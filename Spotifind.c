#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//odio github

//estructura de las canciones
// id, artists, album_name, track_name, tempo y track_genero
typedef struct {
  char id[100];
  char artists[100];
  char track_name;
  List *track_genero;
  char album_name[300];
  int tempo;
} Song;

/*typedef struct {
  char id[100];
  char title[100];
  List *generos;
  char artists[300];
  float rating;
  int tempo;
} Film;
*/

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
void cargar_canciones(Map *cancions_byid, Map *cancions_bygeneros) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/Top1500.csv", "r");
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
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Film y almacena los datos de cada película
    Song *cancion = (Song *)malloc(sizeof(Song));
    strcpy(cancion->id, campos[1]);        // Asigna ID
    strcpy(cancion->track_name, campos[14]);     // Asigna título
    strcpy(cancion->artists, campos[14]); // Asigna artists
    cancion->track_genero = split_string(campos[11], ",");       // Inicializa la lista de géneros
    cancion->tempo =
        atoi(campos[10]); // Asigna año, convirtiendo de cadena a entero

    
    // Inserta la película en el mapa usando el ID como clave
    map_insert(cancions_byid, cancion->id, cancion);

    // Código generado con ayuda de chatgpt3.5
    // conversación: https://chat.openai.com/share/5f0643ad-e8f5-4fb7-a0fa-2d2f92408429
    
    // Obtiene el primer género de la lista de géneros de la película
    char *genero = list_first(cancion->track_genero);
    // Itera sobre cada género de la película
    while (genero != NULL) {
        // Busca el género en el mapa cancions_bygeneros
        MapPair *genero_pair = map_search(cancions_bygeneros, genero);

        // Si el género no existe en el mapa, crea una nueva lista y agrégala al mapa
        if (genero_pair == NULL) {
            List *new_list = list_create();
            list_pushBack(new_list, cancion);
            map_insert(cancions_bygeneros, genero, new_list);
        } else {
            // Si el género ya existe en el mapa, obtén la lista y agrega la película
            List *genero_list = (List *)genero_pair->value;
            list_pushBack(genero_list, cancion);
        }

        // Avanza al siguiente género en la lista
        genero = list_next(cancion->track_genero);
    }
    
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas


  // Itera sobre el mapa para mostrar las películas cargadas
  MapPair *pair = map_first(cancions_byid);
  while (pair != NULL) {
    Song *cancion = pair->value;
    printf("ID: %s, Canción: %s, Artista: %s, Tempo: %d\n", cancion->id, cancion->track_name,
           cancion->artists, cancion->tempo);

    printf("Géneros: ");
    for(char *genero = list_first(cancion->track_genero); genero != NULL; genero = list_next(cancion->track_genero))
      printf("%s, ", genero);
    printf("\n");
    
    pair = map_next(cancions_byid); // Avanza al siguiente par en el mapa
  }
}

/**
 * Busca y muestra la información de una película por su ID en un mapa.
 */
//CAMBIE POR BUSCAR POR GENERO
void buscar_por_id(Map *cancions_byid) {
  char id[10]; // Buffer para almacenar el ID de la película

  // Solicita al usuario el ID de la película
  printf("Ingrese el id de la canción: ");
  scanf("%s", id); // Lee el ID del teclado

  // Busca el par clave-valor en el mapa usando el ID proporcionado
  MapPair *pair = map_search(cancions_byid, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la
  // película
  if (pair != NULL) {
    Song *cancion =
        pair->value; // Obtiene el puntero a la estructura de la película
    // Muestra el título y el año de la película
    printf("Cancion: %s, tempo: %d\n", cancion->track_name, cancion->tempo);
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La canción con id %s no existe\n", id);
  }
}

void buscar_por_genero(Map *cancions_bygeneros) {
  char genero[100];

  // Solicita al usuario el ID de la película
  printf("Ingrese el género de la película: ");
  scanf("%s", genero); // Lee el ID del teclado

  MapPair *pair = map_search(cancions_bygeneros, genero);
  
  if (pair != NULL) {
      List* cancions = pair->value;
      Song *cancion = list_first(cancions);
      
      while (cancion != NULL) {
        printf("ID: %s, Canción: %s, artists: %s, Tempo: %d\n", cancion->id, cancion->track_name,
           cancion->artists, cancion->tempo);
        cancion = list_next(cancions);
      }
  }
}

int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario
               // (sin uso en este fragmento)

  // Crea un mapa para almacenar películas, utilizando una función de
  // comparación que trabaja con claves de tipo string.
  Map *cancions_byid = map_create(is_equal_str);
  Map *cancions_bygeneros = map_create(is_equal_str);

  // Recuerda usar un mapa por criterio de búsqueda

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_canciones(cancions_byid, cancions_bygeneros);
      break;
    case '2':
      buscar_por_id(cancions_byid);//para seguir mirando la funcion.
      buscar_por_genero(cancions_byid);
      break;
    case '3':
      buscar_por_artista(cancions_bygeneros);
      break;
    case '4':
      buscar_por_tempo(cancions_byid);
      break;
    case '5':
      crear_list_reproduccion(cancions_byid, cancions_bygeneros);
      break;
    case '6':
      agregar_cancion_aLista(cancions_byid);
      break;
    case '7':
      mostrar_list_canciones(cancions_byid);
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}
