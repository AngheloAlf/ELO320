#include "edge.h"

#include <stdlib.h>
#include <stdio.h>


Edge *Edge_new(int src, int dest, int speed){
    Edge *edge = malloc(sizeof(Edge));
    if(edge == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    edge->src = src;
    edge->dest = dest;
    edge->speed = speed;

    return edge;
}

void Edge_free(Edge *edge){
    free(edge);
}

int Edge_cmp(const void* a, const void* b){
    Edge *edge = *(Edge **)a;
    Edge *other = *(Edge **)b;

    /// ordenar de mayor a menor Gbps
    if(edge->speed < other->speed){
        return 1;
    }
    if(edge->speed > other->speed){
        return -1;
    }
    return 0;
}



EdgeArr *EdgeArr_new(int size){
    EdgeArr *arr = malloc(sizeof(EdgeArr));
    if(arr == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }

    arr->size = size;
    arr->len = 0;
    arr->arr = malloc(size*sizeof(Edge *));
    if(arr->arr == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }

    return arr;
}

void EdgeArr_free(EdgeArr *arr){
    for (int i = arr->len - 1; i >= 0 ; --i){
        Edge_free(arr->arr[i]);
    }
    
    free(arr->arr);
    free(arr);
}


void EdgeArr_append(EdgeArr *arr, int src, int dest, int speed){
    if(arr->len == arr->size){
        fprintf(stderr, "edgearr append error: full\n");
        exit(-1);
    }

    arr->arr[arr->len] = Edge_new(src, dest, speed);
    ++arr->len;
}

const Edge *EdgeArr_search(EdgeArr *arr, int src, int dest){
    for (int i = 0; i < arr->len; ++i){
        Edge *edge = arr->arr[i];
        if(edge->src == src && edge->dest == dest){
            return edge;
        }
        if(edge->src == dest && edge->dest == src){
            return edge;
        }
    }

    return NULL;
}


void EdgeArr_sort(EdgeArr *arr){
    qsort(arr->arr, arr->len, sizeof(Edge *), Edge_cmp);
}

