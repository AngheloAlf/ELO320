#pragma once
#ifndef SUBSET_H
#define SUBSET_H


/// Representa subsets para busqueda usando union-find
typedef struct{
    int *parent; /// Arreglo de parents.
    int *rank; /// Arreglo de ranks.
} Subset;


/// Crea un objeto `Subset`, e inicializa los subarreglos correspondientes.
Subset *Subset_new(int size);
/// Destruye el objeto `Subset`.
void Subset_free(Subset *subsets);

/// Algoritmo de busqueda de union-find. 
int Subset_find(Subset *subsets, int i);

/// Algoritmo de union de subsets.
void Subset_union(Subset *subsets, int x, int y);


#endif /* SUBSET_H */
