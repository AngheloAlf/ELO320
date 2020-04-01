#include "hashfunctions.h"

size_t h0(node_t k){
    return (size_t)k;
}
size_t h1(node_t k, unsigned long m){
    return (size_t)(k % m);
}
size_t h2(node_t k, unsigned long m){
    return (size_t)(1 + (k % (m-1)));
}

const long c1 = 3;
const long c2 = 5;


size_t linearProbing(node_t k, unsigned long i, unsigned long m){
    return (h0(k) + i) % m;
}

size_t quadraticProbing(node_t k, unsigned long i, unsigned long m){
    return (h0(k) + c1*i + c2*i*i) % m;
}

size_t doubleHashing(node_t k, unsigned long i, unsigned long m){
    return (h1(k, m) + i*h2(k, m)) % m;
}
