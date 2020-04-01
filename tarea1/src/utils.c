#include "utils.h"

#include <stdlib.h>
#include <time.h>


void rand_seed(int seed){
    if(seed < 0){
        srand(time(NULL));
    }
    else{
        srand(seed);
    }
}

int rand_int(int lower_limit, int upper_limit){
    return rand() % (1 + upper_limit - lower_limit) + lower_limit;
}
