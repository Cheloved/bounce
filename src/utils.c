#include "libs/utils.h"

int randint(int low, int high)
{
    assert((low < high) && " [ERROR] in randint(): low should be < than high");
    
    int diff = high - low;
    return (rand() % diff) + low;
}

float randfloat(float low, float high)
{
    assert((low < high) && " [ERROR] in randfloat(): low should be < than high");
    
    float random = ((float)rand()) / (float)(RAND_MAX);
    float diff = high - low;
    return (random * diff) + low;
}
