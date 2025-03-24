#ifndef PREPARE_DATA_H
#define PREPARE_DATA_H

#include "utils.h"
#include <stdio.h>

void prepareData(char* filename, ProgData* data, float* x1, float* x2, float* y1, float* y2);
void prepareLabels(char* filename, ProgData* data);

void writeVector(FILE* file, Vector2 start, Vector2 end);


#endif // PREPARE_DATA_H