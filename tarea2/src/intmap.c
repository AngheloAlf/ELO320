#include "intmap.h"

#include <stdlib.h>
#include <stdio.h>


IntMap *IntMap_new(int size){
    IntMap *arr = malloc(sizeof(IntMap));
    if(arr == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    arr->size = size;
    arr->nodes_ids = malloc(size*sizeof(int));
    if(arr->nodes_ids == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    for(int i = 0; i < size; ++i){
        /// No hay ningún nodo que tenga una id asignada al principio.
        arr->nodes_ids[i] = -1;
    }

    arr->len = 0;
    arr->used_ids = malloc(size*sizeof(int));
    if(arr->used_ids == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    return arr;
}

void IntMap_free(IntMap *arr){
    free(arr->used_ids);
    free(arr->nodes_ids);
    free(arr);
}


bool IntMap_id_exists(IntMap *arr, int id){
    for(int i = 0; i < arr->len; ++i){
        if(arr->used_ids[i] == id){
            return true;
        }
    }
    return false;
}


bool IntMap_put(IntMap *arr, int pos, int id){
    if(pos >= arr->size){
        fprintf(stderr, "intmap put pos error\n");
        exit(-1);
    }

    /// Queremos que la id sea única.
    if(IntMap_id_exists(arr, id)){
        return false;
    }

    /// El nodo ya tiene una id asignada;
    if(arr->nodes_ids[pos] != -1){
        return false;
    }

    /// Almacenamos esta id en nuestro arreglo de ids usadas.
    arr->used_ids[arr->len] = id;
    ++arr->len;

    arr->nodes_ids[pos] = id;
    return true;
}

int IntMap_get(IntMap *arr, int pos){
    if(pos >= arr->size){
        fprintf(stderr, "intmap get pos error\n");
        exit(-1);
    }

    return arr->nodes_ids[pos];
}


