#ifndef PARSER_H
#define PARSER_H

#include "utils.h"

void loadData(char* filename, ProgData* data);

void parseElement(char* buffer, Element* element);

#endif // PARSER_H