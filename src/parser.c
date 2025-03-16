#include <../include/parser.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    DEFAULT,
    NODES,
    ELEMENTS
} Mode;

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

    char buffer[BUFFER_SIZE];
    Mode mode = DEFAULT;

    while (fgets(buffer,BUFFER_SIZE,file))
    {
        if (buffer[0] == '#')
        {
            continue;
        }

        if (buffer[0] == '*' && strcmp(buffer,"*NODES\n"))
        {
            mode = NODES;
            continue;
        }

        if(buffer[0] == '*' && strcmp(buffer,"*ELEMENTS\n"))
        {
            mode = ELEMENTS;
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
        DEFAULT:
            break;
        }
    }

    // TODO: Implement memory allocation for 3D data

    data->twoDim = (Vector2*)malloc(sizeof(Vector2) * data->twoDimCount);
    data->elements = (Element*)malloc(sizeof(Element) * data->elementsCount);

    size_t v2d = 0, e = 0;

    size_t id;

    rewind(file);

    while (fgets(buffer,BUFFER_SIZE,file))
    {
        if (buffer[0] == '#')
        {
            continue;
        }

        if (buffer[0] == '*' && strcmp(buffer,"*NODES\n"))
        {
            mode = NODES;
            continue;
        }

        if(buffer[0] == '*' && strcmp(buffer,"*ELEMENTS\n"))
        {
            mode = ELEMENTS;
            continue;
        }

        switch (mode)
        {
        case NODES:
            sscanf(buffer,"%d %f %f",id,&(data->twoDim[v2d].x),&(data->twoDim[v2d].y));
            v2d++;
            break;
        case ELEMENTS:
            parseElement(buffer,&(data->elements[e]));
            e++;
            break;
        case DEFAULT:
            break;
        }
    }

    fclose(file);
}

void parseElement(char* buffer, Element* element)
{
    element->verticesCount = strlen(buffer)/2;
    element->vertices = (size_t*)malloc(sizeof(size_t) * element->verticesCount);

    buffer += 2;    // skip id and space
    for (int i = 0; i < element->verticesCount; i++)
    {
        element->vertices[i] = atoi(buffer);
        buffer += 2;
    }
}