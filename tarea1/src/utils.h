#pragma once
#ifndef UTILS_H
#define UTILS_H

/// Configura la seed. Si el parametro es negativo, se usa la hora actual.
void rand_seed(int seed);
/// Entrega un número random contenido en el rango entre ambos parametros, considerando ambos parametros inclusivos.
int rand_int(int lower_limit, int upper_limit);

#endif /* UTILS_H */
