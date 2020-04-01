#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "utils.h"

#include "graph.h"

/// Genera un archivo de matriz con gbps randomizados. Requiere un archivo de matriz que indique los arcos.
/// - `in_file`: Archivo de matriz de ceros y unos que indica los arcos de los nodos.
/// - `out_file`: El nombre que se desea que tenga el archivo generado.
/// - `nodes_amount`: Cantidad de nodos.
int generateNetworkConfig(const char *in_file, const char *out_file, int nodes_amount){
    int arcos = 0;

    /// Matriz de gbps
    /// Se usa más que nada para asegurar que los valores de los arcos sean iguales en ambos sentidos.
    int **gbps_matrix = malloc(nodes_amount*sizeof(int *));
    if(gbps_matrix == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    for(int i = 0; i < nodes_amount; ++i){
        gbps_matrix[i] = calloc(nodes_amount, sizeof(int));
        if(gbps_matrix[i] == NULL){
            fprintf(stderr, "malloc error\n");
            exit(-1);
        }
    }


    FILE *conn_matrix = fopen(in_file, "r");
    FILE *config = fopen(out_file, "w");

    if(conn_matrix == NULL || config == NULL){
        fprintf(stderr, "no se pudo abrir el archivo\n");
        exit(-1);
    }

    for(int i = 0; i < nodes_amount; ++i){
        for(int j = 0; j < nodes_amount; ++j){
            int has_connection;

            if(fscanf(conn_matrix, "%i", &has_connection) != 1){
                fprintf(stderr, "no se pudo leer el archivo\n");
                exit(-1);
            }

            if(has_connection){
                int gbps;
                /// Revisamos si a este arco ya le asignamos gbps.
                if(gbps_matrix[j][i] != 0){
                    gbps = gbps_matrix[j][i];
                }
                else{
                    /// Si no le hemos asignado un gbps, le asignamos.
                    gbps = rand_int(GBPS_MIN, GBPS_MAX);
                    gbps_matrix[j][i] = gbps;
                    ++arcos;
                }
                gbps_matrix[i][j] = gbps;
                fprintf(config, "%i ", gbps);
            }
            else{
                fprintf(config, "%i ", 0);
            }
        }
        fprintf(config, "\n");
    }

    fclose(config);
    fclose(conn_matrix);


    for(int i = nodes_amount-1; i >= 0; --i){
        free(gbps_matrix[i]);
    }
    free(gbps_matrix);

    return arcos;
}

void write_ids(const char *out_file, IntMap *nodes){
    FILE *f = fopen(out_file, "w");
    for(int i = 0; i < nodes->size; ++i){
        int id = IntMap_get(nodes, i);
        if(id != -1){
            fprintf(f, "%04i: %04i\n", i, id);
        }
    }
    fclose(f);
}


int main(int argc, char **argv){
    rand_seed(1);

    if(argc < 4){
        printf("Uso: %s <cantidad nodos> <archivo matrix> <archivo network config>\n", argv[0]);
        exit(-1);
    }

    int nodos;
    char *conn_matrix = argv[2];
    char *network_config = argv[3];
    sscanf(argv[1], "%i", &nodos);

    int arcos = generateNetworkConfig(conn_matrix, network_config, nodos);

    Graph *graph = Graph_new(nodos, arcos);
    /// Se generan los ids para cada nodo.
    for(int i = 0; i < nodos; ++i){
        int id;
        bool insertado = false;
        while(!insertado){
            id = rand_int(ID_MIN, ID_MAX);
            insertado = Graph_set_id(graph, i, id);
        }
    }
    /// Escribimos las ids asignadas a cada nodo en un archivo.
    write_ids("nodes_ids.txt", graph->nodes);

    /// Leemos los arcos del archivo de configuracion.
    Graph_fill(graph, network_config);

    /// Generamos un arbol recubridor minimo.
    EdgeArr *result = Graph_kruskal(graph);

    /// Ordenamos los arcos según su costo.
    EdgeArr_sort(result);
    /// Mostramos por pantalla los arcos.
    for(int i = 0; i < result->len; ++i){
        Edge *edge = result->arr[i];

        int src_id = Graph_get_id(graph, edge->src);
        int dest_id = Graph_get_id(graph, edge->dest);
        int speed = edge->speed;

        printf("%04i <-> %04i:  %03i [Gbps]\n", src_id, dest_id, speed);
    }

    EdgeArr_free(result);
    Graph_free(graph);

    return 0;
}

