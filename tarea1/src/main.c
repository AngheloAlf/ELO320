#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "hashtable.h"
#include "hashfunctions.h"
#include "utils.h"

#define LOCAL_ARRAY_LEN(x) sizeof((x))/sizeof(*(x))

/**
 * Agrega `amount` números aleatorios (en el rango matemático [`lower_limit`, `upper_limit`]) a `table`.
 * - `table`: Tabla hash.
 * - `amount`: Cantidad de elementos a agregar.
 * - `lower_limit`: Limite inferior para los números aleatorios.
 * - `upper_limit`: Limite superior para los números aleatorios.
**/
void fillHashTable(hashtable_t *table, unsigned int amount, int lower_limit, int upper_limit){
    for(size_t i = 0; i < amount; ++i){
        long element = rand_int(lower_limit, upper_limit);
        bool added = hashtable_add(table, element);
        if(!added){
            fprintf(stderr, "\tNo se pudo agregar el elemento <%li>.\n", element);
        }
    }
}

int main(){
    /// Para resultados deterministas, cambiar este número a uno positivo.
    rand_seed(-1);

    /// Tamaño de la tabla.
    const size_t size_hashtable = 1500;

    const int lower_random = 0;
    const int upper_random = 1000000;

    /// Arreglo con las cantidades de elementos pedidas en la pregunta 4.
    const int sizes_arr[4] = {100, 500, 1000, 1500};
    //const char *sizes_arr_str[4] = {"0100", "0500", "1000", "1500"};
    /// En caso de que se quiera especificar distintas cantidades de columnas según la cantidad de elementos.
    const int columns_arr[4] = {100, 100, 100, 100};
    /// Arreglo de funciones de hash.
    const hashfunc_t hash_types_arr[3] = {linearProbing, quadraticProbing, doubleHashing};
    /// Nombres de cada uno de los métodos de hashing.
    const char * hash_types_arr_str[3] = {"linear", "quadratic", "double"};

    for(size_t i = 0; i < LOCAL_ARRAY_LEN(hash_types_arr); ++i){
        for(size_t j = 0; j < LOCAL_ARRAY_LEN(sizes_arr); ++j){
            /// Generamos el nombre el archivo.
            char filename[25];
            sprintf(filename, "hash_%s_%04i.txt", hash_types_arr_str[i], sizes_arr[j]);
            printf("Generando: <%s>\n", filename);

            /// Creamos una tabla y la llenamos con la cantidad de elementos correspondientes.
            hashtable_t *table = hashtable_new(size_hashtable, hash_types_arr[i]);
            fillHashTable(table, sizes_arr[j], lower_random, upper_random);

            /// Escribimos la representación de la tabla hash en el archivo.
            FILE *file = fopen(filename, "w");
            if(file == NULL){
                fprintf(stderr, __PRETTY_FUNCTION__);
                fprintf(stderr, ": fopen error.\n");
                exit(-1);
            }
            hashtable_writeToFile(table, file, columns_arr[j]);
            fclose(file);

            hashtable_destroy(table);
        }
        printf("\n");
    }

    return 0;
}

