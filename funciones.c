#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#include "estructura.h"
#include "tdas/extra.h"
#include "tdas/map.h"

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("=========== SPOTYFAI ===========");
    puts("1) Cargar Canciones");
    puts("2) Buscar por Genero");
    puts("3) Buscar por Artista");
    puts("4) Buscar por Tempo");
    puts("5) Salir");
    puts("=================================");
}  

//funcion para comparar cadenas
int is_equal_str(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2) == 0;
}

void mostrarCancion(cancion *s) {
    printf("ID: %s\n", s->id);
    printf("Titulo: %s\n", s->title);
    printf("Artista: %s\n", s->artist);
    printf("Tempo: %.1f BPM\n", s->tempo);
    printf("Generos: ");
    for (char *g = list_first(s->genres); g != NULL; g = list_next(s->genres)) {
        printf("%s ", g);
    }
    printf("\n-----------------------------\n");
}

//convertir a minusculas
char *to_lowercase(const char *str) {
    char *result = strdup(str);
    for (int i = 0; result[i]; i++) {
        result[i] = tolower((unsigned char)result[i]);
    }
    return result;
}

//elimina espacios en blanco al inicio y al final de una cadena, asi no hay errores al buscar
char *trim(char *str) {
    while (isspace((unsigned char)*str)) str++;  // avanzar desde el inicio
    if (*str == 0) return str;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

//cargar canciones desde el archivo csv y guardarlas en los mapas
void cargar_canciones(Map *by_id, Map *by_artist, Map *by_genre) {
    FILE *archivo = fopen("canciones.csv", "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos = leer_linea_csv(archivo, ','); // Leer encabezado, y asi crear los campos, que contienen los nombres de las columnas
    if (!campos) {
        fclose(archivo);
        return;
    }

    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        if (!campos[0] || !campos[2] || !campos[4] || !campos[18] || !campos[20]) {
            for (int i = 0; campos[i] != NULL; i++) free(campos[i]);
            free(campos);
            continue;
        }

        // Se crea la canción
        cancion *s = malloc(sizeof(cancion));
        strcpy(s->id, campos[0]);
        strcpy(s->title, campos[4]);
        strcpy(s->artist, campos[2]);
        s->tempo = atof(campos[18]);
        s->genres = split_string(campos[20], ";");

        map_insert(by_id, strdup(s->id), s);

        // Insertar por cada artista separado por ';'
        List *artistas = split_string(campos[2], ";");
        for (char *a = list_first(artistas); a != NULL; a = list_next(artistas)) {
            char *clave_artist = to_lowercase(trim(a));
            MapPair *artist_pair = map_search(by_artist, clave_artist);
            List *lista_artist = artist_pair ? artist_pair->value : NULL;

            if (!lista_artist) {
                lista_artist = list_create();
                map_insert(by_artist, clave_artist, lista_artist);
            } else {
                free(clave_artist);  // se libera la clave si ya existe
            }
            list_pushBack(lista_artist, s);
        }

        // Insertar por género
        for (char *g = list_first(s->genres); g != NULL; g = list_next(s->genres)) {
            char *clave_gen = to_lowercase(trim(g));
            MapPair *genre_pair = map_search(by_genre, clave_gen);
            List *lista_gen = genre_pair ? genre_pair->value : NULL;

            if (!lista_gen) {
                lista_gen = list_create();
                map_insert(by_genre, clave_gen, lista_gen);
            } else {
                free(clave_gen);
            }
            list_pushBack(lista_gen, s);
        }

        // Liberar memoria de la lista de artistas, para que no haya fugas
        for (int i = 0; campos[i] != NULL; i++) free(campos[i]);
        free(campos);
    }

    printf("Se han cargado las canciones :)\n");
    presioneTeclaParaContinuar();
    fclose(archivo);
}

// Buscar canciones por artista
void buscar_por_artista(Map *by_artist) {
    char nombre[200];
    printf("Ingrese el nombre del artista: ");
    scanf(" %[^\n]", nombre);
    printf("\n");

    char *clave = to_lowercase(trim(nombre));
    MapPair *pair = map_search(by_artist, clave);
    free(clave);

    if (!pair) {
        printf("No se encontraron canciones del artista.\n");
        presioneTeclaParaContinuar();
        limpiarPantalla();
        return;
    }

    // Mostrar todas las canciones del artista
    List *lista = pair->value;
    for (cancion *s = list_first(lista); s != NULL; s = list_next(lista)) {
        mostrarCancion(s);
    }
    presioneTeclaParaContinuar();
    limpiarPantalla();
}


// Buscar canciones por género
void buscar_por_genero(Map *by_genre) {
    char genero[100];
    printf("Ingrese el genero a buscar: ");
    scanf(" %[^\n]", genero);
    printf("\n");

    char *clave = to_lowercase(trim(genero));
    MapPair *pair = map_search(by_genre, clave);
    free(clave);

    if (!pair) {
        printf("No se encontraron canciones de ese genero.\n");
        presioneTeclaParaContinuar();
        limpiarPantalla();
        return;
    }

    // Mostrar todas las canciones del género
    List *lista = pair->value;
    for (cancion *s = list_first(lista); s != NULL; s = list_next(lista)) {
        mostrarCancion(s);
    }
    presioneTeclaParaContinuar();
    limpiarPantalla();
}

// Buscar canciones por tempo
void buscar_por_tempo(Map *by_id) {
    char tipo[20];
    printf("Ingrese tipo de tempo (lentas, moderadas, rapidas): ");
    scanf(" %s", tipo);
    printf("\n");

    float min = 0, max = 1000;
    if (strcmp(tipo, "lentas") == 0) max = 80;
    else if (strcmp(tipo, "moderadas") == 0) { min = 80; max = 120; }
    else if (strcmp(tipo, "rapidas") == 0) min = 120;
    else {
        printf("Tipo no reconocido.\n");
        presioneTeclaParaContinuar();
        limpiarPantalla();
        return;
    }

    MapPair *pair = map_first(by_id);
    int total = 0;

    // Contar cuántas canciones cumplen el rango, para luego mostrar las canciones de a 10 en 10
    while (pair) {
        cancion *s = pair->value;
        if (s->tempo >= min && s->tempo < max)
            total++;
        pair = map_next(by_id);
    }

    if (total == 0) {
        printf("No se encontraron canciones con ese tempo.\n");
        return;
    }

    // Mostrar canciones con ese tempo. Con esto primero debemos volver al incicio del mapa

    pair = map_first(by_id);
    int mostradas = 0;
    limpiarPantalla();

    while (pair) {
        cancion *s = pair->value;
        if (s->tempo >= min && s->tempo < max) {
            mostrarCancion(s);
            mostradas++;

            // se pausa cada 10 resultados
            if (mostradas % 10 == 0 && mostradas < total) {
                printf("\nMostradas %d de %d canciones. Presione ENTER para continuar o 's' para salir: ", mostradas, total);
                char opcion = getchar();
                if (opcion == '\n') opcion = getchar();  // limpiar buffer
                if (opcion == 's' || opcion == 'S') {
                    printf("\nSaliendo de la busqueda por tempo.\n");
                    break;
                }
                limpiarPantalla();
            }
        }
        pair = map_next(by_id);
    }

    if (mostradas == total)
        printf("\nFin de los resultados. Se mostraron %d canciones.\n", mostradas);
}
