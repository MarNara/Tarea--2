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
void mostrarMenuPrincipal() 
{
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

typedef struct 
{
  List* lentas;
  List* moderadas;
  List* rapidas;

}ListaTempoStruck;


void mostrar_cancion_paginas(List* lista)
{
  if (lista == NULL)
  {
    printf("No hay canciones para mostrar.\n");
    presioneTeclaParaContinuar();
    return;
  }

  int pagina_actual = 0;
  int canciones_por_pagina = 10;
  int total_paginas = (list_size(lista) + canciones_por_pagina - 1) / canciones_por_pagina;
  char opcion ;

  do
  {
    limpiarPantalla();
    printf("=== (Pagina %d/%d) ===\n",pagina_actual + 1, total_paginas);
    printf("------------------------------------------------------------\n");
    printf("ID\tTempo\tCanción\t\tÁlbum\n");
    printf("------------------------------------------------------------\n");

    int inicio = pagina_actual * canciones_por_pagina;
    int fin = (pagina_actual + 1) * canciones_por_pagina;
    if (fin > list_size(lista)) fin = list_size(lista);

    Song* cancion = list_first(lista);
    for (int i = 0; i < inicio && cancion != NULL; i++)
     {
        cancion = list_next(lista);
    }

    for (int i = inicio; i < fin && cancion != NULL; i++) 
    {
        printf("%.6s\t%f\t%.20s\t%.20s\n", cancion->id, cancion->tempo, cancion->track_name, cancion->album_name);
        cancion = list_next(lista);
    }

    printf("\nOpciones:\n");
    printf("1) Página anterior --- 2) Volver al menú --- 3) Página siguiente\n");
    printf("Seleccione: ");
    scanf("%c", &opcion);
    getchar();

    switch (opcion) {
        case '1':
            if (pagina_actual > 0) pagina_actual--;
            break;

        case '2':  
            return ;

        case '3':
            if ((pagina_actual + 1) * canciones_por_pagina < list_size(lista)) pagina_actual++;
            break;
        default:
            printf("Opción no válida.\n");
            presioneTeclaParaContinuar();
    }

    
  }while(opcion != '2');
  return;
}


void cargarArchivo(const char *ruta, TreeMap* cancionesID, TreeMap* cancion_artista, TreeMap* cancion_genero, ListaTempoStruck* Lista_de_tempo) 
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

        //Genero----------------------------------------------------------------------------------------------
        Pair *por_genero = searchTreeMap(cancion_genero, cancion->artists);
        List *lista_genero;

        if (por_genero == NULL)
        {
          lista_genero = list_create();
          insertTreeMap(cancion_genero, strdup(cancion->track_gener), lista_genero);
        }
        else
        {
          lista_genero = (List*)por_genero->value;
        }
        list_pushBack(lista_genero, cancion);


        //artista---------------------------------------------------------------------------------------------
        Pair *por_artista = searchTreeMap( cancion_artista , cancion->artists);
        List *lista_artista;

        if (por_artista == NULL)
        {
          lista_artista = list_create();
          insertTreeMap(cancion_artista , strdup(cancion->artists), lista_artista);
        }
        else
        {
          lista_artista = (List*)por_artista->value;
        }

        list_pushBack(lista_artista, cancion);

        //Tempo-----------------------------------------------------------------------------------------------
        if (cancion->tempo < 80)
        {
          list_pushBack(Lista_de_tempo->lentas, cancion);
        }
        else if (cancion->tempo <= 120)
        {
          list_pushBack(Lista_de_tempo->moderadas, cancion);
        }
        else
        {
          list_pushBack(Lista_de_tempo->rapidas, cancion);
        }
        
        
    }




    printf("Archivo cargado perfectamente\n");

    presioneTeclaParaContinuar();
    fclose(archivo);
}

// Función para imprimir los datos de una canción individual

void Mostrar_cancion(Song *cancion) {
  if (cancion == NULL) {
      printf("Canción no encontrada.\n");
      return;
  }
  
    printf("🎵 %s - %s (Álbum: %s, Tempo: %f)\n", 
      cancion->track_name, 
      cancion->artists, 
      cancion->album_name, 
      cancion->tempo);
}


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


void buscar_por_artista(TreeMap * cancion_artista)
{
    char artista[100];
    printf("Ingrese nombre del artista: ");
    scanf("%99[^\n]", artista);
    getchar();

    Pair *par = searchTreeMap(cancion_artista, artista);
    
    if (par != NULL) 
    {
      List *canciones = (List *)par->value;
      limpiarPantalla();
      mostrar_cancion_paginas(canciones);
  } 
  else 
  {
      printf("Artista no encontrado.\n");
  }
  presioneTeclaParaContinuar();
}

int main() 
{
  SetConsoleOutputCP(65001); //esta funcion sirve para poner el formato UTF-8 sirve para mostrar los caractares españoles

  TreeMap *canciones_id = createTreeMap(lower_than_str); //se crea el mapa ordenado de canciones
  TreeMap *cancion_artista = createTreeMap(lower_than_str);
  TreeMap *canciones_byGenero = createTreeMap(lower_than_str);
  ListaTempoStruck Lista_de_tempo;
  Lista_de_tempo.lentas = list_create();
  Lista_de_tempo.moderadas = list_create();
  Lista_de_tempo.rapidas = list_create();

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
        cargarArchivo(ruta, canciones_id, cancion_artista, canciones_byGenero, &Lista_de_tempo); // se mete a la funcion
        break;

      case '2':
        limpiarPantalla();
        //buscar_por_genero(canciones_byGenero);
        break;
      
      case '3':
        limpiarPantalla();
        buscar_por_artista(cancion_artista);
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