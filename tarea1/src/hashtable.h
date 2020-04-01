#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/// Por ponerle un nombre bonito.
typedef unsigned long node_t;

/**
 * Firma de las funciones de hash.
 * -`k` es el elemento al cual le vamos a calcular el hash.
 * -`i` es el número de la iteración (siempre menor que m).
 * -`m` es el tamaño de la tabla hash.
**/
typedef size_t (*hashfunc_t)(node_t k, unsigned long i, unsigned long m);

/// La estructura principal de la tabla hash.
typedef struct{
    /// Puntero a una función de hash.
    hashfunc_t hasher;
    /// Cantidad total de casillas en la tabla hash.
    size_t size;

    /// Cantidad de elementos en la tabla hash.
    size_t len;
    /// Arreglo de punteros. Cada puntero apunta a un elemento. Si el puntero es NULL, el espacio está vacio.
    node_t **data;
} hashtable_t;


/**
 * Crea un objeto `hashtable_t`.
 * - `size`: Cantidad de casillas para la tabla hash.
 * - `hasher`: Función de hash que usara la tabla hash para saber donde almacenar el elemento.
 * 
 * Retorna: Puntero al objeto `hashtable_t`.
**/
hashtable_t *hashtable_new(size_t size, hashfunc_t hasher);

/**
 * Destruye un objeto `hashtable_t`, liberando toda su memoria.
 * - `table`: Puntero a una tabla hash.
**/
void hashtable_destroy(hashtable_t *table);

/**
 * Agrega un elemento a la tabla hash.
 * - `table`: Puntero a una tabla hash.
 * - `element`: Elemento a ser agregado.
 * 
 * Retorna: `true` si `element` pudo ser agregado a la tabla, `false` si no pudo, ya sea por falta de
 * espacio (tabla llena) o porque nunca se pudo encontrar un espacio usando la funcion de hash.
**/
bool hashtable_add(hashtable_t *table, node_t element);

/**
 * Escribe una representación de la tabla hash a un archivo.
 * Un 'X' significa que hay un elemento en esa posición, ' ' significa lo contrario.
 * - `table`: Puntero a una tabla hash.
 * - `file`: Puntero a un archivo, previamente abierto, en modo de escritura.
 * - `columns`: Cantidad de columnas que tendrá el archivo.
**/
void hashtable_writeToFile(hashtable_t *table, FILE *file, int columns);

#endif /* HASHTABLE_H */
