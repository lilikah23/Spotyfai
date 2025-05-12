# Spotyfai - Explorador de Canciones

Spotyfai es una aplicación de consola, en la que permite cargar canciones desde un archivo CSV y buscar por artista, género o tempo. Además, permite visualizar los resultados paginados, ordenados y estructurados, facilitando la exploración de una librería musical por tempo.

---------------------------------------------------------------------------------

## Estructura del Proyecto

├──tdas **Definiciones de tdas a utilizar(como map, list y extras)**
├──canciones.csv    **Archivo de canciones (formato CSV)**
├── estructura.h    **Definición de estructuras como 'canción' y nodos**
├── funciones.c/h  **Funciones para cargar y buscar canciones**
├── main.c     **Menú principal del programa**  
└── README.md  **Este archivo**

---------------------------------------------------------------------------------
**Recomendacion**
como el archivo csv, tiene varias canciones y titulos, con diferentes idiomas y caracteres, suele haber pequeños errores
como de escritura, por lo que podria solucionar algunos casos, ejecutar el siguiente comando dentro el terminal antes de hacer funcionar el programa, para forzar a la consola como UTF-8: 

*chcp 65001*

## ¿Cómo compilar y ejecutar?
* Requisitos: Tener gcc instalado en tu sistema (puedes usar MinGW en Windows o gcc en Linux/macOS).*

Se compila el programa ejecutando el siguiente comando en la terminal (cmd o bash):

gcc main.c funciones.c tdas/list.c tdas/map.c tdas/extra.c -o spotyfai

**Esto creara un ejecutable**
*Luego ejecuta el programa así:*

./spotyfai

---------------------------------------------------------------------------------

# Funciones implementadas : 

1) Cargar canciones desde un archivo CSV (título, artista, géneros, tempo, etc.)

2) Buscar por artista: muestra canciones de un artista ingresado, sin importar si se ingresa en mayuscula o minusculas, .

3) Buscar por género: muestra canciones de un género, también sin importar si se ingresa en mayuscula o minusculas.

4) Buscar por tempo: canciones lentas, moderadas o rápidas (según BPM), con opción a navegar por páginas (hasta 10 por pagina y con la opcion de apretar "S" para salir del buscador y volver al menu principal).

5) Normalización de entrada: las búsquedas no son sensibles a mayusculas/minusculas.

6) Presionar Enter para continuar y limpiar pantalla tras cada página.

7) Manejo básico de caracteres especiales en campos de texto. (con el UTF-8, aunque aveces suele fallar, en mejoras lo explico mejor)

---------------------------------------------------------------------------------

## Funcionalidades con detalles o mejoras pendientes

-⚠️ Validación de entradas: todavía pueden fallar si el CSV tiene caracteres no válidos o corruptos.

-⚠️ Nombres con caracteres especiales: algunos artistas y titulos pueden aparecer con símbolos raros si el CSV no está codificado en UTF-8 o tiene caracteres extraños(algo que por lomenos no me han explicado como resolver).

-⚠️En el buscar por artista y por genero, muestra todo lo que se desea buscar, por lo que puede ser un poco anti estetico, pero enrealidad pude haber aplicado, lo mismo que hice en el buscar por tempo, que le puse la opcion de paginas, solo que me quede sin tiempo, asi que lo dejare como futura mejora.

-⚠️ No hay guardado en archivo de resultados ni historial.

-⚠️ Interfaz de consola básica, sin colores ni navegación mejorada. (aun no se hacerlo de otra manera :c, lo mismo que en el de tickets).

-⚠️ Solo funciona con un archivo CSV llamado canciones.csv en el mismo directorio.(aunque si se cargara otro csv y en la funcion cargarCancion, pongo la nueva ruta de csv, deberia funcionar de igual manera, aunque no lo he intentado).

---------------------------------------------------------------------------------

# 💡 Ejemplo de uso(no es estrictamente así, pero contiene las mismas funcionalidades):

========= SPOTYFAI ==========
1. Cargar canciones
2. Buscar por artista
3. Buscar por género
4. Buscar por tempo
5. Salir
==============================

Seleccione una opción: 1
> Se han cargado las canciones :)

----------------------------
Seleccione una opción: 2
Ingrese el nombre del artista: Eminem

Mostrando canciones del artista "Eminem":
1. Lose Yourself
2. Without Me
...
Presione ENTER para continuar...

----------------------------

Seleccione una opción: 4
Ingrese tipo de tempo (lentas, moderadas, rapidas): lentas

Mostrando canciones lentas (BPM < 80):
1. River Flows In You - Yiruma
2. Piano Concerto No. 2 - Rachmaninoff
...

Mostradas 10 de 50 canciones. Presione ENTER para continuar o 's' para salir:

---------------------------------------------------------------------------------