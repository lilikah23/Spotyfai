#ifndef estructura_h
#define estructura_h

#include "tdas/list.h"

// Estructura para representar una canción.
typedef struct {
    char id[100];
    char title[100];
    char artist[200];
    List *genres;
    float tempo;
  } cancion;

// Estructura para un nodo de la lista enlazada (para usar en los mapas)
typedef struct NodoLista {
    cancion* cancion;
    struct NodoLista* siguiente;
} NodoLista;

// Estructura para el Mapa
typedef struct {
    NodoLista** tabla;
    int capacidad;
    int tamano;
} Mapa;

#endif