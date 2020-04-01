#include "hashtable.h"

/**
 * Funcion auxiliar.
 * Genera un arreglo de punteros de `node_t`, y lo inicializa con `NULL`s.
 * - `size`: Cantidad de casillas disponibles en el arreglo (tamaño).
**/
node_t **nodes_new(size_t size){
    node_t **nodes_arr = malloc(size * sizeof(node_t *));
    if(nodes_arr == NULL){
        fprintf(stderr, __PRETTY_FUNCTION__);
        fprintf(stderr, ": malloc error.\n");
        exit(-1);
    }
    for(size_t i = 0; i < size; ++i){
        nodes_arr[i] = NULL;
    }
    return nodes_arr;
}

hashtable_t *hashtable_new(size_t size, hashfunc_t hasher){
    hashtable_t *table = malloc(sizeof(hashtable_t));
    if(table == NULL){
        fprintf(stderr, __PRETTY_FUNCTION__);
        fprintf(stderr, ": malloc error.\n");
        exit(-1);
    }
    table->hasher = hasher;
    table->size = size;
    table->len = 0;
    table->data = nodes_new(table->size);
    return table;
}

/**
 * Funcion auxiliar.
 * Destruye el arreglo de punteros de `node_t`.
 * - `nodes_arr`: El arreglo mismo.
 * - `size`: Tamaño del arreglo.
**/
void nodes_destroy(node_t **nodes_arr, size_t size){
    for(size_t i = 0; i < size; ++i){
        // Si `free` recibe un `NULL`, hace nada, por lo que no hay que preocuparse por eso. 
        free(nodes_arr[i]);
    }
    free(nodes_arr);
}

void hashtable_destroy(hashtable_t *table){
    nodes_destroy(table->data, table->size);
    free(table);
}


/**
 * Funcion auxiliar.
 * Agrega `element` al arreglo `node_arr` usando la función `hasher`.
 * - `nodes_arr`: El arreglo mismo.
 * - `size`: Tamaño del arreglo.
 * - `element`: Elemento a ser agregado.
 * - `hasher`: Función para calcular el hash de `element`.
 * 
 * Retorna: `true` si `element` fue agregado. `false` si despues de `arr_size` no se encontró una 
 * posición para almacenar a `element`.
**/
bool node_add(node_t **node_arr, size_t arr_size, node_t element, hashfunc_t hasher){
    for(size_t i = 0; i < arr_size; ++i){
        int j = hasher(element, i, arr_size);
        if(node_arr[j] == NULL){
            node_arr[j] = malloc(sizeof(node_t));
            *(node_arr[j]) = element;
            return true;
        }
    }

    return false;

    /// Si nos queremos ir de hocico al no encontrar un espacio.
    //fprintf(stderr, __PRETTY_FUNCTION__);
    //fprintf(stderr, ": node array overflow.\n");
    //exit(-1);
}

bool hashtable_add(hashtable_t *table, node_t element){
    /// Si no queda espacio en la tabla, doblamos su tamaño.
    if(table->len == table->size){
        size_t new_nodes_size = 2*table->size;
        node_t **new_nodes_arr = nodes_new(new_nodes_size);

        /// Re-hasheamos los elementos en el nuevo arreglo.
        for(size_t i = 0; i < table->size; ++i){
            if(table->data[i] != NULL){
                node_add(new_nodes_arr, new_nodes_size, *table->data[i], table->hasher);
            }
        }

        nodes_destroy(table->data, table->size);
        table->data = new_nodes_arr;
        table->size = new_nodes_size;
    }

    /*
    /// No queda espacio disponible.
    if(table->len == table->size){
        return false;
    }
    */

    ++table->len;
    return node_add(table->data, table->size, element, table->hasher);
}


void hashtable_writeToFile(hashtable_t *table, FILE *file, int columns){
    size_t i = 0;
    while(i < table->size){
        if(table->data[i] == NULL){
            /// No hay elemento.
            fprintf(file, " ");
        }
        else{
            /// Hay elemento.
            fprintf(file, "X");
        }
        ++i;
        if(i % columns == 0){
            /// Alcanzamos el máximo de columnas, pasemos a una fila nueva.
            fprintf(file, "\n");
        }
    }
}

