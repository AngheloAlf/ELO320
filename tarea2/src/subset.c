#include "subset.h"

#include <stdlib.h>
#include <stdio.h>


Subset *Subset_new(int size){
    Subset *subsets = malloc(sizeof(Subset));
    if(subsets == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    subsets->parent = malloc(size*sizeof(int));
    if(subsets->parent == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    subsets->rank = calloc(size, sizeof(int));
    if(subsets->rank == NULL){
        fprintf(stderr, "malloc error\n");
        exit(-1);
    }
    for(int i = 0; i < size; ++i){
        subsets->parent[i] = i;
    }

    return subsets;
}

void Subset_free(Subset *subsets){
    free(subsets->rank);
    free(subsets->parent);
    free(subsets);
}


int Subset_find(Subset *subsets, int i){
    if(subsets->parent[i] != i){
        subsets->parent[i] = Subset_find(subsets, subsets->parent[i]);
    }
    return subsets->parent[i];
}

void Subset_union(Subset *subsets, int x, int y){
    int x_root = Subset_find(subsets, x);
    int y_root = Subset_find(subsets, y);

    if(subsets->rank[x_root] < subsets->rank[y_root]){
        subsets->parent[x_root] = y_root;
    }
    else if(subsets->rank[x_root] > subsets->rank[y_root]){
        subsets->parent[y_root] = x_root;
    }
    else{
        subsets->parent[y_root] = x_root;
        subsets->rank[x_root] += 1;
    }
}

