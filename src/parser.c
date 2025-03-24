#include "../include/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

typedef enum
{
    DEFAULT,
    NODES,
    ELEMENTS,
    CIRCLES
} Mode;

// CIRCLE in format:
// CIRCLE is an element and insert element id which is an increment of previous element
// id_e         -- integer
// n            -- integer (how many vertices)
// a            -- a as in (x -a)^2 + (y - b)^2 = r^2
// b            -- b as in ...
// r            -- r as in ...


void loadData(char* filename, ProgData* data)
{
    data->twoDimCount = 0;
    data->threeDimCount = 0;
    data->elementsCount = 0;

    FILE* file = fopen(filename,"r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char buffer[BUFFER_SIZE] = {0};
    Mode mode = DEFAULT;

    while (fgets(buffer,BUFFER_SIZE,file))
    {
        if (buffer[0] == '#')
        {
            continue;
        }

        if (buffer[0] == '*' && !memcmp(buffer,"*NODES",6))
        {
            mode = NODES;
            continue;
        }

        if(buffer[0] == '*' && !memcmp(buffer,"*ELEMENTS",9))
        {
            mode = ELEMENTS;
            continue;
        }

        if(buffer[0] == '*' && !memcmp(buffer,"*CIRCLES",8))
        {
            mode = CIRCLES;
            continue;
        }

    // TODO: Implement reading data when working in 3D

        switch (mode)
        {
        case NODES:
            data->twoDimCount++;
            break;
        case ELEMENTS:
            data->elementsCount++;
            break;
        case CIRCLES:
            data->elementsCount++;
            break;
        case DEFAULT:
            break;
        }
    }

    // TODO: Implement memory allocation for 3D data

    data->twoDim = (Vector2*)malloc(sizeof(Vector2) * data->twoDimCount);
    data->elements = (Element*)malloc(sizeof(Element) * data->elementsCount);

    size_t v2d = 0, e = 0;

    size_t id = 0;

    rewind(file);

    while (fgets(buffer,BUFFER_SIZE,file))
    {
        if (buffer[0] == '#')
        {
            continue;
        }

        if (buffer[0] == '*' && !memcmp(buffer,"*NODES",6))
        {
            mode = NODES;
            continue;
        }

        if(buffer[0] == '*' && !memcmp(buffer,"*ELEMENTS",9))
        {
            mode = ELEMENTS;
            continue;
        }

        if(buffer[0] == '*' && !memcmp(buffer,"*CIRCLES",8))
        {
            mode = CIRCLES;
            continue;
        }

        switch (mode)
        {
        case NODES:
            sscanf(buffer,"%llu %f %f",&id,&(data->twoDim[v2d].x),&(data->twoDim[v2d].y));
            v2d++;
            break;
        case ELEMENTS:
            parseElement(buffer,&(data->elements[e]));
            e++;
            break;
        case CIRCLES:
            parseCircle(buffer,e,data);
            e++;
            break;
        case DEFAULT:
            break;
        }
    }

    fclose(file);
}

//TODO: update parseElement to work with more than 1 digit arguments
void parseElement(char* buffer, Element* element)
{
    element->verticesCount = (strlen(buffer) - 1)/2;
    element->vertices = (size_t*)malloc(sizeof(size_t) * element->verticesCount);

    buffer += 2;    // skip id and space
    for (size_t i = 0; i < element->verticesCount; i++)
    {
        element->vertices[i] = atoi(buffer);
        buffer += 2;
    }
}

//used when parsing from file
void parseCircle(char* buffer, size_t e, ProgData* data)
{
    printf("\n\nParsing Circle    %s",buffer);
    int id = 0;
    int n = 0;
    Vector3 circle = (Vector3){0.0f,0.0f,0.0f};
    sscanf(buffer,"%d %d %f %f %f",&id,&n,&circle.x,&circle.y,&circle.z);

    printf("id = %d, n = %d, a = %f, b = %f, c = %f\n",id,n,circle.x,circle.y,circle.z);

    generateCircleAllocated(circle,e,n,data);
}