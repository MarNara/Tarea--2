## Aplicación de música

Descripción: En este programa se crea Spotifind, una herramienta de consola que permite cargar una base de datos de canciones y, carga canciones desde un archivo csv, busca canciones por género, busca canciones por artista y busca canciones según su velocidad o tempo. También puede crear listas de reproduccion, puede agregar canciones a las listas ya creadas y por ultimo puede mostrar las canciones de una lista en especifico. Además, la aplicación permitirá organizar tus canciones favoritas en listas de reproducción personalizadas.

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
 Ingrese su opci├│n: 1 Registrar nuevo ticket Ingrese el ID: 45 Ingrese la descripci├│n: El Pc se apago y ya no enciende El ticket se a registrado con exito. Presione una tecla para continuar...

----------------------- **EJEMPLO (2) Buscar por Género** --------------------------- Ingrese su opci├│n: 2 Ingrese el ID al cual quiere asignar una nueva prioridad: 45 Asigne la prioridad: Alta es 1 Media es 2 Baja es 3. 1 su prioridad a sido asignada como Alta Presione una tecla para continuar...

----------------------- **EJEMPLO (3) Buscar por Artista** --------------------------- Ingrese su opci├│n: 3 Mostrar ticket por prioridad y orden de llegada:

ID: 45. Descripci├│n: El Pc se apago y ya no enciende. Prioridad: Alta. Hora de Registro: 14:15:05

ID: 67. Descripci├│n: El celular no carga muy bien aunque aveces si lo hace bien. Prioridad: Media. Hora de Registro: 14:16:34

ID: 80. Descripci├│n: Se reinicia la laptop cuando abro algunos programas. Prioridad: Media. Hora de Registro: 14:17:53

ID: 23. Descripci├│n: instalar un antivirus. Prioridad: Baja. Hora de Registro: 14:14:41

ID: 73. Descripci├│n: actualizar aplicaciones. Prioridad: Baja. Hora de Registro: 14:17:10

Presione una tecla para continuar...

----------------------- **EJEMPLO (4) Buscar por Tempo** --------------------------- Ingrese su opci├│n: 4 Ticket de prioridad Alta siendo atendido ID: 45. Descripci├│n: El Pc se apago y ya no enciende. Prioridad: Alta. Hora de Registro: 14:15:05

Presione una tecla para continuar...

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