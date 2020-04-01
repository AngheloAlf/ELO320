#pragma once
#ifndef INTMAP_H
#define INTMAP_H

#include <stdbool.h>


/// Almacena el id asociado a un nodo en particular.
/// Cada nodo tiene una posición (desde 0 hasta 999 si hay 1000 nodos),
/// y cada uno de estos nodos tiene un id asociado.
/// Se busca que cada id sea único.
typedef struct{
    int size; /// Tamaño alocado en memoria para cada arreglo.
    
    /// Arreglo de ids. El indice es la posicion de un nodo, el elemento es el id de dicho nodo.
    /// Un valor negativo indica que este nodo no se le ha entregado un id.
    int *nodes_ids; 
    int len; /// Cantidad de ids que se han agregado.
    int *used_ids; /// Arreglo no-ordenado con los ids que se han ingresado.
} IntMap;


/// Genera la estructura
IntMap *IntMap_new(int size);
/// Destruye la estructura
void IntMap_free(IntMap *arr);

/// Retorna `true` si el id entregado ya ha sido asignado.
bool IntMap_id_exists(IntMap *arr, int id);

/// Intenta asignar `id` al nodo `pos`.
/// Si el `id` ya fue asignado a alguien o si el nodo ya tiene una id asignada retorna `false`.
/// Si se asigna correctamente el id al nodo, retorna `true`.
bool IntMap_put(IntMap *arr, int pos, int id);

/// Entrega el id asignado al nodo `pos`.
/// Si el nodo no tiene una id asignada, entrega -1.
int IntMap_get(IntMap *arr, int pos);


#endif /* INTMAP_H */
