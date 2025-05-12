#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "estructura.h"
#include "tdas/map.h"
#include "tdas/list.h"


// Funciones de utilidad
void mostrarMenuPrincipal();
int is_equal_str(void *key1, void *key2);
void mostrarCancion(cancion *c);

// Funciones de carga
void cargar_canciones(Map *canciones_byid, Map *canciones_bygenre, Map *canciones_byartist);

// Funciones de búsqueda
void buscar_por_genero(Map *canciones_bygenre);
void buscar_por_artista(Map *canciones_byartist);
void buscar_por_tempo(Map *canciones_byid);

#endif