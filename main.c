#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include "estructura.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
    limpiarPantalla();
    Map *canciones_byid = map_create(is_equal_str);
    Map *canciones_bygenre = map_create(is_equal_str);
    Map *canciones_byartist = map_create(is_equal_str);
    setlocale(LC_ALL, ""); // Configurar la localización para caracteres especiales

    char opcion;

    do {
        mostrarMenuPrincipal();
        printf("Ingrese una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case '1':
                cargar_canciones(canciones_byid,canciones_byartist ,canciones_bygenre );
                break;
            case '2':
                buscar_por_genero(canciones_bygenre);
                break;
            case '3':
                buscar_por_artista(canciones_byartist);
                break;
            case '4':
                buscar_por_tempo(canciones_byid);
                break;
            case '5':
                puts("Saliendo del programa...");
                presioneTeclaParaContinuar();
                break;
            default:
                puts("Opcion no valida. Intente de nuevo.");
                presioneTeclaParaContinuar();
        }

        printf("\n");
    } while (opcion != '5');
    limpiarPantalla();
    return 0;
}