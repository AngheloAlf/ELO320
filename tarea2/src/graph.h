#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#include "intmap.h"
#include "edge.h"


/// Estructura que representa el grafo bidireccional
typedef struct{
    IntMap *nodes;
    EdgeArr *edges;
} Graph;


/// Construye un grafo vacio.
/// Los parametros son la cantidad de nodos y la cantidad de arcos.
Graph *Graph_new(int nodes_amount, int edges_amount);
/// Destruye el grafo y sus contenidos.
void Graph_free(Graph *graph);

/// Asigna la id `id` al nodo `pos`.
/// Retorna `true` si se asignó satisfactoriamente.
/// Retorna `false` si el id ya ha sido utilizado o si el nodo `pos` ya tiene una id asignada.
bool Graph_set_id(Graph *graph, int pos, int id);

/// Entrega el id del nodo `pos`, o -1 si dicho nodo no tiene una id asignada.
int Graph_get_id(Graph *graph, int pos);

/// Llena el grafo con arcos.
/// Los arcos son leidos de un archivo con formato matriz, donde un cero indica que no hay arco 
/// y un número distinto de cero indica el Gbps de ese arco.
void Graph_fill(Graph *graph, const char *filename);

/// Algoritmo de kruskal para general un arbol recubridor minimo.
EdgeArr *Graph_kruskal(Graph *graph);


#endif /* GRAPH_H */
