## Aplicación de música

Descripción: En este programa se crea Spotifind, una herramienta de consola que permite cargar una base de datos de canciones y, carga canciones desde un archivo csv, busca canciones por género, busca canciones por artista y busca canciones según su velocidad o tempo. También puede crear listas de reproduccion, puede agregar canciones a las listas ya creadas y por ultimo puede mostrar las canciones de una lista en especifico. 
-------------------------------------------------------------------------------------------------------------------------------

## Cómo compilar y ejecutar la tarea:
-Ingresar al visual studio code. 
-Clonar en repositorio GitHub el link enviado al aula virtual:

-----------Para compilar y ejecutar el codigo--------------

Abre el archivo principal (por ejemplo, tarea2.c).

Abre la terminal con ctrl + ñ.

En la terminal bash, compila el programa con el siguiente comando : 
### gcc tdas/*.c tarea2.c -Wno-unused-result -o tarea2

Luego debe escribir lo siguiente para ejecutar la tarea: 
### ./tarea2

Archivo para cargar canciones:
### song_dataset_.csv

-------------------------------------------------------------------------------------------------------------------------------

las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas;
Las opiones que funcionan son las siguientes: 
(1) Cargar Canciones. (2) Buscar por Género. (3) Buscar por Artista. (4) Buscar por Tempo. (5) Crear Lista de Reproducción. (6) Agregar Canción a Lista. (7) Mostrar Canciones de una Lista . (8) Salir.

------OBSERVACIÓN----- 
Al pasar a otra opcion debo presionar cualquier tecla. También cuando queremos salir con la opción 2 en la ultima

-------------------------------------------------------------------------------------------------------------------------------

## Ejemplos mostrando como interactuar con la aplicación.

----------------------- **EJEMPLO (1) Cargar Canciones** ---------------------------
 Ingrese su opción: 1 
 Ingrese la ubicación del archivo CSV: song_dataset_.csv
Archivo cargado perfectamente
Presione una tecla para continuar...

----------------------- **EJEMPLO (2) Buscar por Género** --------------------------- 
Ingrese su opción: 2
Ingrese el género de la canción: pop
=== (Pagina 1/200) ===
╔═══════╦═══════════╦══════════════════════╦══════════════════════╦════════════════════════════════╦════════════════╗
║ ID    ║ Tempo ║ Canción               ║ Álbum                 ║ Artista                        ║ Género    ║
╠═══════╬═══════════╬══════════════════════╬══════════════════════╬════════════════════════════════╬════════════════╣
║ 81000 ║ 171.01 ║ Blinding Lights        ║ After Hours            ║ The Weeknd                     ║ pop        ║
║ 81001 ║ 191.83 ║ Mann Mera              ║ Table No. 21 (Original ║ Gajendra Verma                 ║ pop        ║
║ 81002 ║ 114.98 ║ Summer High            ║ Summer High            ║ AP Dhillon                     ║ pop        ║
║ 81003 ║ 116.99 ║ Under The Influence    ║ Indigo (Extended)      ║ Chris Brown                    ║ pop        ║
║ 81004 ║ 186.00 ║ Starboy                ║ Starboy                ║ The Weeknd;Daft Punk           ║ pop        ║
║ 81005 ║ 98.97  ║ Insane                 ║ Insane                 ║ AP Dhillon;Shinda Kahlon;Gurin ║ pop        ║
║ 81006 ║ 100.02 ║ Akhiyaan               ║ Akhiyaan               ║ Mitraz                         ║ pop        ║
║ 81007 ║ 98.06  ║ Daku                   ║ Daku                   ║ Chani Nattan;Inderpal Moga     ║ pop        ║
║ 81008 ║ 79.97  ║ Jhoom - R&B Mix        ║ Jhoom                  ║ Ali Zafar                      ║ pop        ║
║ 81009 ║ 90.07  ║ Na Ja                  ║ Na Ja                  ║ Pav Dharia                     ║ pop        ║
╚═══════╩════════╩═════════════════════════╩══════════════════════╩════════════════════════════════╩════════════════╝

Opciones:
1) Página anterior --- 2) Volver al menú --- 3) Página siguiente
Seleccione: 2
Presione una tecla para continuar...

----------------------- **EJEMPLO (3) Buscar por Artista** --------------------------- 

----------------------- **EJEMPLO (4) Buscar por Tempo** --------------------------- 

----------------------- **Ejemplo (5) Crear Lista de Reproducción** ---------------------------

Cuando hay un ID
Ingrese su opci├│n: 5 Ingrese el ID que desea buscar: 67 ID: 67. Descripci├│n: El celular no carga muy bien aunque aveces si lo hace bien. Prioridad: Media. Hora de Registro: 14:16:34

Presione una tecla para continuar...

Cuando NO hay ID:
Ingrese su opci├│n: 5 Ingrese el ID que desea buscar: 56 El ID que a ingresado no existe Presione una tecla para continuar...

----------------------- **Ejemplo (6) Agregar Canción a Lista** ---------------------------

----------------------- **Ejemplo (7) Mostrar Canciones de una Lista** ---------------------------

----------------------- Ejemplo (5) Crear Lista de Reproducción ---------------------------


## Contribuciones 

### Juan Gatica:

- Desarrolló las siguientes funciones:
    - mostrar_cancion_paginas, cargarArchivo, Mostrar_cancion, imprimir_cancion, buscar_imprimir_por_id, buscar_por_artista.
- Diseño inicial de la interfaz de usuario.
- Orden del código.
- **Auto-evaluación**: 3 (Aporte excelente).

### Martina Ahumada:

- Desarrolló las siguientes funciones:
    - buscar_por_genero, buscar_por_tempo, crear_lista_reproduccion, mostrar_listas_reproduccion, agregar_cancion_Alista, mostra_canciones_DeLista.
- Documentación y comentarios en el código.
- Diseño y redacción del README.
- **Auto-evaluación**: 3 (Aporte excelente).

Si bien cada uno se encargaba de una función en especifico de igual forma se recibia ayuda mutuamente.