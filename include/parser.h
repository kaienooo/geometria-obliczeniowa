#ifndef PARSER_H
#define PARSER_H

#include "utils.h"

void loadData(char* filename, ProgData* data);

void parseElement(char* buffer, Element* element);

void parseCircle(char* buffer, size_t e, ProgData* data);

#endif // PARSER_H