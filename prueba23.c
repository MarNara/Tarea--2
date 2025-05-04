#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/treemap.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int lower_than_int(void* a, void* b) {
    return (*(int*)a < *(int*)b);
}

int lower_than_str(void* a, void* b) {
    return strcmp((char*)a, (char*)b) < 0;
}

int lower_than_float(void* a, void* b) {
    return (*(float*)a < *(float*)b);
}

  typedef struct {
    char id[100];
    char artists[100];
    char track_name[100];
    List *track_gener;
    char album_name[300];
    int tempo;
  } Song;

  int is_equal_int(void *key1, void *key2) {
    return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
  }


void cargar_canciones(const char * ruta_archivo, TreeMap *canciones, TreeMap *por_genero, TreeMap *por_artista, TreeMap *por_tempo) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
      perror(
          "Error al abrir el archivo");
      return;
    }
  
    char **campos;
    
    campos = leer_linea_csv(archivo, ','); 
  
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) 
    {
      Song *cancion = (Song *)malloc(sizeof(Song));
      strcpy(cancion->id, campos[0]);        // Asigna ID
      strcpy(cancion->track_name, campos[4]);     // Asigna título
      strcpy(cancion->artists, campos[2]); // Asigna artists
      strcpy(cancion->album_name, campos[3]);
      cancion->tempo = atof(campos[18]); // Asigna año, convirtiendo de cadena a entero
      cancion->track_gener = split_string(campos[20], ",");       // Inicializa la lista de géneros
      
  
      insertTreeMap(canciones, cancion->id, cancion);
      
      List *generos = cancion->track_gener;
      if (list_size(generos) > 0) {
        char *genero = list_first(generos);
        while (genero != NULL)
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
            genero = list_next(generos);
        }
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


  int main() {
    char ruta[1000];
    TreeMap *canciones_id = createTreeMap(lower_than_str);
    TreeMap *canciones_byGenero = createTreeMap(lower_than_str);
    TreeMap *canciones_byTempo = createTreeMap(lower_than_int);
    TreeMap *canciones_byArtista = createTreeMap(lower_than_str);
    
    printf("Directorio actual: ");
    system("pwd"); // Muestra dónde busca el archivo
    
    printf("\nIngrese ruta del archivo (sin comillas): ");
    scanf("%999[^\n]", ruta);
    getchar();

    // Eliminar comillas si las hay
    if (ruta[0] == '"' && ruta[strlen(ruta)-1] == '"') {
        memmove(ruta, ruta+1, strlen(ruta));
        ruta[strlen(ruta)-1] = '\0';
    }

    printf("Intentando abrir: %s\n", ruta);
    
    cargar_canciones(ruta, canciones_id, canciones_byGenero, canciones_byArtista, canciones_byTempo);

    // Verificar si se cargaron canciones
    Pair *pair = firstTreeMap(canciones_id);
    if (pair == NULL) {
        printf("\nNo se cargaron canciones. Verifica:\n");
        printf("1. Que el archivo existe en la ruta especificada\n");
        printf("2. Que tienes permisos de lectura\n");
        printf("3. Que el formato del archivo es correcto\n");
        return 1;
    }

    // También podemos verificar algunos artistas cargados
    printf("\nAlgunos artistas cargados:\n");
    printf("=========================\n");
    pair = firstTreeMap(canciones_byArtista);
    int contador = 0;
    
    while (pair != NULL && contador < 5) {
        printf("Artista: %s (%d canciones)\n", 
               (char *)pair->key, 
               list_size((List *)pair->value));
        pair = nextTreeMap(canciones_byArtista);
        contador++;
    }

    return 0;
}


//gcc tdas/*.c prueba23.c -Wno-unused-result -o test.exe

/*compilar para ver otros errores:
        gcc -Wall -Wextra tdas/extra.c tdas/list.c tdas/treemap.c tdas/map.c prueba23.c -o test.exe
*/

//./test.exe