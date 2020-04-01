#pragma once
#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>


/// Estructura que representa un arco entre 2 nodos.
typedef struct{
    int src; /// Nodo 1
    int dest; /// Nodo 2
    int speed; /// Gbps
} Edge;

/// Representa un arreglo de arcos.
typedef struct{
    int size; /// Tamaño alocado en memoria
    int len; /// Cantidad de elementos en el arreglo
    Edge **arr; // Arreglo de punteros
} EdgeArr;


/// Crea un nuevo arco.
Edge *Edge_new(int src, int dest, int speed);
/// Destruye el arco.
void Edge_free(Edge *edge);

/// Funcion para usar en qsort.
/// Ordena los arcos segun Gbps, de mayor a menor.
int Edge_cmp(const void* a, const void* b);


/// Crea un arreglo de arcos.
EdgeArr *EdgeArr_new(int size);
/// Destruye el arreglo y los arcos que contiene.
void EdgeArr_free(EdgeArr *arr);

/// Agrega un arco al final del arreglo.
/// Si el arreglo ya está lleno, el programa se cierra.
void EdgeArr_append(EdgeArr *arr, int src, int dest, int speed);

/// Busca el arco que conecte ambos nodos dentro del arreglo.
/// Como el grafo es bidireccional, esta función prueba ambas direcciones del arco.
/// Si el arco no está en el arreglo, retorna NULL.
const Edge *EdgeArr_search(EdgeArr *arr, int src, int dest);

/// Ordenar de mayor Gbps a menor Gbps (es menor el costo cuando se tiene mayor Gbps).
void EdgeArr_sort(EdgeArr *arr);


#endif /* EDGE_H */
