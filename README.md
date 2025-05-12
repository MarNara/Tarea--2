## Aplicación de música:

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

**------OBSERVACIÓN------** 

- Al pasar a otra opcion debo presionar cualquier tecla. 
- Sería bueno implementar una función para controlar casos donde el nombre del artista o el nombre de los géneros 
tenga letras minusculas o mayusculas pero sean la misma palabra, como por ejemplo: pop = Pop.
- Tambien estaria bien agregar un buscar por pagina que me mueva directamente a la pagina.

**------Nota------**

- La biblioteca windows.h si bien no sale en las bibliotecas standar que el profesor dijo que se podian ocupar, la unica funcion que ocupamos fue "SetConsoleOutputCP(65001);" que lo que hace es cambiar al encoding a utf-8, de esta manera lograbamos hacer que los acentos se mostraran correctamente en la terminal. 

-------------------------------------------------------------------------------------------------------------------------------

## Ejemplos mostrando como interactuar con la aplicación.

**----------------------- EJEMPLO (1) Cargar Canciones ---------------------------**
 
 Ingrese su opción: 1 
 Ingrese la ubicación del archivo CSV: song_dataset_.csv
Archivo cargado perfectamente
Presione una tecla para continuar...

**----------------------- EJEMPLO (2) Buscar por Género ---------------------------** 

Ingrese su opción: 2
Ingrese el género de la canción: pop
=== (Pagina 1/100) ===
╔═══════╦═══════════╦══════════════════════╦══════════════════════╦════════════════════════════════╦════════════════╗
║ ID   ║ Tempo ║ Canción               ║ Álbum                 ║ Artista                        ║ Género    ║
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

**----------------------- EJEMPLO (3) Buscar por Artista ---------------------------** 
Ingrese su opción: 3
Ingrese nombre del artista: Gen Hoshino
=== (Pagina 1/1) ===
╔═══════╦═══════════╦══════════════════════╦══════════════════════╦════════════════════════════════╦════════════════╗
║ ID   ║ Tempo ║ Canción               ║ Álbum                 ║ Artista                        ║ Género    ║
╠═══════╬═══════════╬══════════════════════╬══════════════════════╬════════════════════════════════╬════════════════╣
║ 0    ║ 87.92  ║ Comedy                 ║ Comedy                 ║ Gen Hoshino                    ║ acoustic   ║
║ 406  ║ 158.12 ║ Koi                    ║ POP VIRUS              ║ Gen Hoshino                    ║ acoustic   ║
║ 663  ║ 129.99 ║ I Wanna Be Your Ghost  ║ I Wanna Be Your Ghost  ║ Gen Hoshino                    ║ acoustic   ║
║ 751  ║ 89.02  ║ FUSHIGI                ║ FUSHIGI                ║ Gen Hoshino                    ║ acoustic   ║
║ 756  ║ 159.99 ║ Doraemon               ║ Doraemon               ║ Gen Hoshino                    ║ acoustic   ║
║ 800  ║ 108.17 ║ SUN                    ║ YELLOW DANCER          ║ Gen Hoshino                    ║ acoustic   ║
║ 850  ║ 78.18  ║ Pop Virus              ║ POP VIRUS              ║ Gen Hoshino                    ║ acoustic   ║
║ 62102 ║ 87.92  ║ Comedy                 ║ Comedy                 ║ Gen Hoshino                    ║ j-pop      ║
║ 99152 ║ 87.92  ║ Comedy                 ║ Comedy                 ║ Gen Hoshino                    ║ singer-son ║
║ 102151 ║ 87.92  ║ Comedy                 ║ Comedy                 ║ Gen Hoshino                    ║ songwriter ║
╚═══════╩════════╩═════════════════════════╩══════════════════════╩════════════════════════════════╩════════════════╝

Opciones:
1) Página anterior --- 2) Volver al menú --- 3) Página siguiente
Seleccione: 2
Presione una tecla para continuar...

----------------------- **EJEMPLO (4) Buscar por Tempo** --------------------------- 
Ingrese su opción: 4
Ingrese la “velocidad” deseada de las canciones: 
1) Lentas: menor 80 BPM 
2) Moderadas: mayor o igual a 80, menor o igual a 120 
3) Rapidas: mayor a 120

Ingrese la velocidad : 3

=== (Pagina 1/6067) ===
╔═══════╦═══════════╦══════════════════════╦══════════════════════╦════════════════════════════════╦════════════════╗
║ ID   ║ Tempo ║ Canción               ║ Álbum                 ║ Artista                        ║ Género    ║
╠═══════╬═══════════╬══════════════════════╬══════════════════════╬════════════════════════════════╬════════════════╣
║ 3    ║ 181.74 ║ Can't Help Falling In  ║ Crazy Rich Asians (Ori ║ Kina Grannis                   ║ acoustic   ║
║ 6    ║ 141.28 ║ Say Something          ║ Is There Anybody Out T ║ A Great Big World;Christina Ag ║ acoustic   ║
║ 7    ║ 150.96 ║ I'm Yours              ║ We Sing. We Dance. We  ║ Jason Mraz                     ║ acoustic   ║
║ 8    ║ 130.09 ║ Lucky                  ║ We Sing. We Dance. We  ║ Jason Mraz;Colbie Caillat      ║ acoustic   ║
║ 11   ║ 133.41 ║ I Won't Give Up        ║ Love Is a Four Letter  ║ Jason Mraz                     ║ acoustic   ║
║ 12   ║ 124.23 ║ Solo                   ║ Solo                   ║ Dan Berk                       ║ acoustic   ║
║ 14   ║ 120.00 ║ Hold On - Remix        ║ Hold On (Remix)        ║ Chord Overstreet;Deepend       ║ acoustic   ║
║ 18   ║ 130.09 ║ Lucky                  ║ We Sing. We Dance. We  ║ Jason Mraz;Colbie Caillat      ║ acoustic   ║
║ 20   ║ 150.96 ║ I'm Yours              ║ We Sing. We Dance. We  ║ Jason Mraz                     ║ acoustic   ║
║ 22   ║ 141.28 ║ Say Something          ║ Is There Anybody Out T ║ A Great Big World;Christina Ag ║ acoustic   ║
╚═══════╩════════╩═════════════════════════╩══════════════════════╩════════════════════════════════╩════════════════╝

Opciones:
1) Página anterior --- 2) Volver al menú --- 3) Página siguiente
Seleccione: 2
Presione una tecla para continuar...

----------------------- **Ejemplo (5) Crear Lista de Reproducción** ---------------------------
Ingrese su opción: 5
Ingrese el nombre para la nueva lista:
mix_variados
Su lista mix_variados a sido creada con exito
Presione una tecla para continuar...

----------------------- **Ejemplo (6) Agregar Canción a Lista** ---------------------------
Ingrese su opción: 6
================ Mis Listas De Reproducción ================
>  mix_variados

================ Para Agregar Canciones ================
-Ingrese el nombre de la lista a la
que desea agregar una canción: mix_variados


-Ingrese el ID de la canción que 
desea agregar: 101518
La cancion 'Rain: Showers' se a agregado con exito a 'mix_variados'.
Presione una tecla para continuar...

**Cuando se ingresa el nombre de la lista en la primera opción que aparece, en el caso de que el nombre de la lista sea inválido o no existe la lista, el programa se devuelve al menú principal y no muestra la parte de los ID**

----------------------- **Ejemplo (7) Mostrar Canciones de una Lista** ---------------------------
Ingrese su opción: 7
================ Mis Listas De Reproducción ================
>  mix_variados

================ Para Mostrar Canciones ================
Ingrese el nombre de la lista de canciones que desea ver: mix_variados

=== (Pagina 1/1) ===
╔═══════╦═══════════╦══════════════════════╦══════════════════════╦════════════════════════════════╦════════════════╗
║ ID   ║ Tempo ║ Canción               ║ Álbum                 ║ Artista                        ║ Género    ║
╠═══════╬═══════════╬══════════════════════╬══════════════════════╬════════════════════════════════╬════════════════╣
║ 101518 ║ 140.88 ║ Rain: Showers          ║ Rain And Waves         ║ Rain Sounds Factory STHLM      ║ sleep      ║
╚═══════╩════════╩═════════════════════════╩══════════════════════╩════════════════════════════════╩════════════════╝

Opciones:
1) Página anterior --- 2) Volver al menú --- 3) Página siguiente
Seleccione: 2
Presione una tecla para continuar...

**Cuando se llega a la parte de  "Para Mostrar Canciones" e ingreso la lista que deseo buscar se debe presionar enter para pasar a ver las canciones de esa lista**

----------------------- **Ejemplo (8) Salir** ---------------------------
Ingrese su opción: 8
Saliendo del programa...
## Contribuciones 

### Juan Gatica:

- Encargado de la descarga de archivos para empezar el trabajo.
- Desarrolló las siguientes funciones:
    - mostrar_cancion_paginas, cargarArchivo, buscar_por_artista.
- Diseño inicial de la interfaz de usuario.
- Orden del código.
- Documentación y comentarios en el código.
- **Auto-evaluación**: 3 (Aporte excelente).

### Martina Ahumada:
- Encargada de crear el repositorio.
- Desarrolló las siguientes funciones:
    - buscar_por_genero, buscar_por_tempo, crear_lista_reproduccion, mostrar_listas_reproduccion, agregar_cancion_Alista, mostra_canciones_DeLista.
- Documentación y comentarios en el código.
- Diseño y redacción del README.
- **Auto-evaluación**: 3 (Aporte excelente).

Si bien cada uno se encargaba de una función en específico de igual forma se recibía ayuda mutuamente corrigiendo errores o si alguno no lograba terminar la función, por lo tanto el "Desarrolló las siguientes funciones" no muestra realmente si alguien realizó muchas o pocas cosas en el código, ya que se realizaron muchos otros códigos y funciones de prueba que por motivos de presentación para la entrega hemos tenido que eliminarlas.