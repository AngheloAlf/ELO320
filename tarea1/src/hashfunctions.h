#pragma once
#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H

#include "hashtable.h"

size_t linearProbing(node_t k, unsigned long i, unsigned long m);
size_t quadraticProbing(node_t k, unsigned long i, unsigned long m);
size_t doubleHashing(node_t k, unsigned long i, unsigned long m);

#endif /* HASHFUNCTIONS_H */
