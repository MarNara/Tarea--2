#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/treemap.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 

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

typedef struct {
  char id[100];
  char artists[100];
  char track_name[100];
  char track_gener[100];
  char album_name[300];
  float tempo;
} Song;

void cargarArchivo(const char *ruta, TreeMap* cancionesID) 
{
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
        strncpy(cancion->track_gener, campos[20], sizeof(cancion->track_gener) - 1);
        cancion->tempo = atof(campos[18]);

        insertTreeMap(cancionesID, cancion->id, cancion);

        
    }




    printf("Archivo cargado perfectamente\n");

    presioneTeclaParaContinuar();
    fclose(archivo);
}

// Función para imprimir los datos de una canción individual
void imprimir_cancion(Song *cancion) {
  if (cancion == NULL) {
      printf("Canción no encontrada.\n");
      return;
  }
  
  printf("\n=== Detalles de la Canción ===\n");
  printf("ID: %s\n", cancion->id);
  printf("Título: %s\n", cancion->track_name);
  printf("Artista(s): %s\n", cancion->artists);
  printf("Álbum: %s\n", cancion->album_name);
  printf("Género(s): %s\n", cancion->track_gener);
  printf("Tempo: %d BPM\n", cancion->tempo);
  printf("=============================\n");
  presioneTeclaParaContinuar();
}

void buscar_imprimir_por_id(TreeMap *canciones) {
  if (canciones == NULL) {
      printf("No hay canciones cargadas.\n");
      return;
  }
  
  char id_buscar[100];
  printf("\nIngrese el ID de la canción a buscar: ");
  scanf("%99s", id_buscar);
  getchar(); // Limpiar el buffer de entrada
  
  Pair *resultado = searchTreeMap(canciones, id_buscar);
  if (resultado != NULL) {
      imprimir_cancion((Song*)resultado->value);
  } else {
      printf("No se encontró una canción con el ID: %s\n", id_buscar);
  }
}


int main() 
{
  SetConsoleOutputCP(65001); //esta funcion sirve para poner el formato UTF-8 sirve para mostrar los caractares españoles

  TreeMap *canciones_id = createTreeMap(lower_than_str); //se crea el mapa ordenado de canciones

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
        cargarArchivo(ruta, canciones_id); // se mete a la funcion
        break;

      case '2':
        limpiarPantalla();
        //buscar_por_genero(canciones_byGenero);
        break;
      
      case '3':
        limpiarPantalla();
        //buscar_por_artista(canciones_byArtista);
        break;

      case '8':
        printf("Saliendo del programa...\n");
        break;
      default:
        printf("Opción no válida. Intente nuevamente.\n");
        presioneTeclaParaContinuar();
      }
  } while (opcion != '8');
  
  return 0;
}

//gcc tdas/*.c prueba.c -Wno-unused-result -o test.exe

//./test.exe