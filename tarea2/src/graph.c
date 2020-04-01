#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

#include "subset.h"


Graph *Graph_new(int nodes_amount, int edges_amount){
    Graph *graph = malloc(sizeof(Graph));
    if(graph == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }

    graph->nodes = IntMap_new(nodes_amount);
    graph->edges = EdgeArr_new(edges_amount);

    return graph;
}

void Graph_free(Graph *graph){
    IntMap_free(graph->nodes);
    EdgeArr_free(graph->edges);
    free(graph);
}


bool Graph_set_id(Graph *graph, int pos, int id){
    return IntMap_put(graph->nodes, pos, id);
}

int Graph_get_id(Graph *graph, int pos){
    return IntMap_get(graph->nodes, pos);
}


void Graph_fill(Graph *graph, const char *filename){
    FILE *config = fopen(filename, "r");

    if(config == NULL){
        fprintf(stderr, "no se pudo abrir el archivo <%s>\n", filename);
        exit(-1);
    }

    /// Leemos todos los posibles arcos de los (nodos*nodos) posibles del archivo.
    for(int i = 0; i < graph->nodes->size; ++i){
        for(int j = 0; j < graph->nodes->size; ++j){
            int gbps;
            if(fscanf(config, "%i", &gbps) != 1){
                fprintf(stderr, "no se pudo leer el archivo\n");
                exit(-1);
            }

            if(gbps != 0){
                /// Como el grafo es no-dirigido, no nos interesa agregar un arco que ya tenemos pero en la dirección contraria.
                if(EdgeArr_search(graph->edges, i, j) == NULL){
                    EdgeArr_append(graph->edges, i, j, gbps);
                }
            }
        }
    }

    fclose(config);
}



EdgeArr *Graph_kruskal(Graph *graph){
    IntMap *nodes = graph->nodes;
    EdgeArr *edges = graph->edges;

    EdgeArr *result = EdgeArr_new(edges->len);
    Subset *subsets = Subset_new(nodes->len);

    EdgeArr_sort(edges);

    for(int i=0, j=0; j < nodes->len - 1 && i < edges->len; ++i){
        Edge *next_edge = edges->arr[i];

        int x = Subset_find(subsets, next_edge->src);
        int y = Subset_find(subsets, next_edge->dest);

        if(x != y){
            EdgeArr_append(result, next_edge->src, next_edge->dest, next_edge->speed);
            Subset_union(subsets, x, y);
        }
    }

    Subset_free(subsets);

    return result;
}


