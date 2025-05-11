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
  char opcion;
  

  do
  {
    limpiarPantalla();
    printf("=== (Pagina %d/%d) ===\n",pagina_actual + 1, total_paginas);
    printf("╔═══════╦═══════════╦══════════════════════╦══════════════════════╦════════════════════════════════╦════════════════╗\n");
    printf("║ %-4s  ║ %-6s║ %-22s ║ %-22s ║ %-30s ║ %-10s ║\n", "ID", "Tempo", "Canción", "Álbum", "Artista", "Género");
    printf("╠═══════╬═══════════╬══════════════════════╬══════════════════════╬════════════════════════════════╬════════════════╣\n");

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
    printf("║ %-4s ║ %-6.2f ║ %-22.22s ║ %-22.22s ║ %-30.30s ║ %-10.10s ║\n",cancion->id, cancion->tempo,cancion->track_name, cancion->album_name, cancion->artists, cancion->track_gener);
      cancion = list_next(lista);
    }
    printf("╚═══════╩════════╩═════════════════════════╩══════════════════════╩════════════════════════════════╩════════════════╝\n");

    printf("\nOpciones:\n");
    printf("1) Página anterior --- 2) Volver al menú --- 3) Página siguiente\n");
    printf("Seleccione: ");
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    opcion = buffer[0];
    


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
        Pair *por_genero = searchTreeMap(cancion_genero, cancion->track_gener);
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


//Arreglar
void buscar_por_genero(TreeMap* cancions_bygeneros) {
  char genero[100];
  //fgets(buffer, sizeof(buffer), stdin);
  //opcion = buffer[0];

  // Solicita al usuario el ID de la canción
  printf("Ingrese el género de la canción: ");
  //scanf(" %[^\n]", genero); // Lee el genero del teclado
  fgets(genero, sizeof(genero), stdin);
  
  //agregar un \n
  size_t len = strlen(genero);
  if (len > 0 && genero[len - 1] == '\n') 
  {
    genero[len - 1] = '\0';
  }

  Pair *pair = searchTreeMap(cancions_bygeneros, genero);
  //printf("canciones del genero: %s", genero);
  if (pair != NULL) {
    List* canciones = (List*)pair->value;
    //Song* cancion = list_first(canciones);
    limpiarPantalla();
    mostrar_cancion_paginas(canciones);
  }
  if (pair == NULL)
  {
    printf("No se han encontardo canciones del género %s\n", genero);
  }
  presioneTeclaParaContinuar();
}

//buscar por artista
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


//buscar tempo, necesito un switch, ARREGLAR
void buscar_por_tempo(List* lista_lentas, List* lista_moderadas, List* lista_rapidas){
  //char opcion;
  char opcion[10];  //pedir al usuario que ingrese un tempo
  printf("Ingrese la “velocidad” deseada de las canciones: \n");
  printf("1) Lentas: menor 80 BPM \n");
  printf("2) Moderadas: mayor o igual a 80, menor o igual a 120 \n");
  printf("3) Rapidas: mayor a 120\n");
  printf("\nIngrese la velocidad : " );
  //VEERaux EL SACNFauxTIPO DE DATO
  fgets(opcion, sizeof(opcion), stdin); // Lee la opción de las velocidades
  //opcion = aux[0]; 
  
  //reemplazar "\n" por cero.
  opcion[strcspn (opcion,"\n")] = 0;

  if ( strcmp(opcion, "1") == 0) {
    mostrar_cancion_paginas(lista_lentas);
  }
  else if(strcmp(opcion, "2") == 0){
    mostrar_cancion_paginas(lista_moderadas);
  }
  else if(strcmp(opcion, "3") == 0){
    mostrar_cancion_paginas(lista_rapidas);
  }
  else{
    printf("Tempo inválido...");
  }
  presioneTeclaParaContinuar();
}

/*crear lista de reproduccion: para eso debo ir haciendo diversas preguntas como por ejemplo, ingresar nombre, 
e ingresar el nombre de la cancion*/
void crear_lista_reproduccion(TreeMap* mapa_listas_reproduccion){
  //preguntar al usuario que nombre desea colocar a la lista
  printf("Ingrese el nombre para la nueva lista:\n");
  char nombre_lista[100];
  scanf("%99[^\n]", nombre_lista);
  getchar();
  
  //verificar si la lista ya existe
  if (searchTreeMap(mapa_listas_reproduccion, nombre_lista) != NULL){
    printf("ya existe una lista con el nombre %s",nombre_lista);
  }

  
  List* lista_new = list_create();//crear la nueva lista de reproduccion
  if(lista_new == NULL){
    printf("Error al crear la nueva lista\n");
    return;
  }
  
  //ver si el duplicado mesta bien creado o si hay algun fallo
  char* nombre_lista_duplicado = strdup(nombre_lista);
  if(nombre_lista_duplicado == NULL){
    printf("Error al USAR nombre_lista_duplicado\n");
    return;
  }
  insertTreeMap(mapa_listas_reproduccion, nombre_lista_duplicado, lista_new); //insertTreeMap(TreeMap * tree, void* key, void * value);
  printf("Su lista %s a sido creada con exito\n", nombre_lista);  
  /*si libero el mapa de la funcion, cuando lo quiera utilizar de nuevo el programa podria fallar, asi que tendre
  que eliminarlo*/
  presioneTeclaParaContinuar();
}


//mostrar listas de reproduccion para tener claridad si tenemos las funciones bien creadas
//listo
void mostrar_listas_reproduccion(TreeMap* mapa_listas_reproduccion){
  if(mapa_listas_reproduccion == NULL){
    printf("No tiene listas de reproducción creadas");
  }
  else{
    Pair* pair = firstTreeMap(mapa_listas_reproduccion);/*no puedo usar el search ya que solo muestro y no le pido al 
    usuario el nombre de la lista*/
    printf("================ Mis Listas De Reproducción ================\n");
    while(pair != NULL){
      char* nombre_lista = pair->key;//recordar los punteros
      printf(">  %s\n", nombre_lista);
      pair = nextTreeMap(mapa_listas_reproduccion);
    }
  }
  printf("\n");
}

/*en agregar cancion debo verificar si la cancion esta en la lista o no, tambien debo usar la funcion insert para insertar 
una cancion a una lista de reproduccion, primero debo mostrar las listas que tengo, luego debo preguntar al usuario el nombre
de  la cancion que desea agregar a la lista*/
void agregar_cancion_Alista(TreeMap* mapa_listas_reproduccion, TreeMap* mapa_id){
  mostrar_listas_reproduccion(mapa_listas_reproduccion);
  printf("================ Para Agregar Canciones ================\n");
  printf("-Ingrese el nombre de la lista a la\nque desea agregar una canción: ");
  char nombre_lista[100];
  scanf("%99[^\n]", nombre_lista);
  getchar();
  //buscar el nombre de la lista
  Pair* pair_listas = searchTreeMap(mapa_listas_reproduccion, nombre_lista);
  if(pair_listas == NULL){
    printf("La lista que busca no existe\n");
  }
  
  printf("\n\n-Ingrese el ID de la canción que \ndesea agregar: ");
  char id_cancion[100];
  scanf("%99[^\n]", id_cancion);
  getchar();

  
  //buscar el id
  Pair* pair_id = searchTreeMap(mapa_id, id_cancion);
  if(pair_id == NULL){
    printf("El ID que a ingresado no existe\n");
  }

  //ya existe la cancion en la lista
  

  //obtener la lista y la cancion que el usuario quiere agregar pero con el id porque el nombre de la cancion es muy larga
  List* canciones = pair_listas->value;//recordar que es una lista y no un mapa :(
  Song* cancion = pair_id->value;//aqui esta el id especifico

  Song* actual_id = (Song*)list_first(canciones);
  int cancion_existe;
  while(actual_id != NULL){
    if(strcmp(actual_id->id, id_cancion) == 0){
      cancion_existe = 1;
      break;
    }
    actual_id = (Song*)list_next(canciones);
  }

    if(cancion_existe){
      printf("El ID que a ingresado ya existe en la lista\n");
    }
    else{
      list_pushBack(canciones, cancion);//list_pushFront(List *L, void *dato);
      printf("La cancion '%s' se a agregado con exito a '%s'.\n", cancion->track_name, nombre_lista);//->track_name
    }  

  
  presioneTeclaParaContinuar();
  
}

//mostrar
void mostra_canciones_DeLista(TreeMap* mapa_listas_reproduccion){
  mostrar_listas_reproduccion(mapa_listas_reproduccion);
  printf("================ Para Mostrar Canciones ================\n");
  char nombre_lista[100];
  printf("Ingrese el nombre de la lista de canciones que desea ver:");
  scanf("%99[^\n]", nombre_lista);
  getchar();

  Pair* pair = searchTreeMap(mapa_listas_reproduccion, nombre_lista);
  while(pair != NULL){
    List* canciones = pair->value;
    mostrar_cancion_paginas(canciones);
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
  TreeMap* listas_reproduccion = createTreeMap(lower_than_str);//recordar que es un mapa, solo el nombre es para la ocasion :(

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
        buscar_por_genero(canciones_byGenero);
        break;
      
      case '3':
        limpiarPantalla();
        buscar_por_artista(cancion_artista);
        break;

      case '4':
        limpiarPantalla();
        
        buscar_por_tempo(Lista_de_tempo.lentas, Lista_de_tempo.moderadas, Lista_de_tempo.rapidas);
        break;

      case '5':
        limpiarPantalla();
        crear_lista_reproduccion(listas_reproduccion);
        break;

      case '6':
        limpiarPantalla();
        agregar_cancion_Alista(listas_reproduccion, canciones_id);
        break;

      case '7':
        limpiarPantalla();
        mostra_canciones_DeLista(listas_reproduccion);
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