#include "../include/prepare_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void prepareData(char* filename, ProgData* data,float* x1, float* x2, float* y1, float* y2)
{
    FILE* file = fopen(filename,"w");

    if (file == NULL)   
    {
    printf("Error opening file!\n");
        fprintf(stderr,"Error opening file!\n");
        exit(1);
    }

    *x1 = data->twoDim[0].x;
    *x2 = data->twoDim[0].x;

    *y1 = data->twoDim[0].y;
    *y2 = data->twoDim[0].y;


    // find min and max values
    // for plotting
    for (size_t i = 1; i <data->twoDimCount; i++)
    {
        if (data->twoDim[i].x < *x1)
        {
            *x1 = data->twoDim[i].x;
        }

        if (data->twoDim[i].x > *x2)
        {
            *x2 = data->twoDim[i].x;
        }

        if (data->twoDim[i].y < *y1)
        {
            *y1 = data->twoDim[i].y;
        }

        if (data->twoDim[i].y > *y2)
        {
            *y2 = data->twoDim[i].y;
        }
    }

    size_t linesCount = 0;

    // obliczanie ile prostych jest do narysowania
    // gdy punktow jest 2 to rysuje sie 1 linie
    // gdy punktow jest n>2 to rysuje sie n linii
    for (size_t i = 0; i < data->elementsCount; i++)
    {
        if (data->elements[i].verticesCount == 2)
        {
            linesCount++;
        }
        else
        {
            linesCount += data->elements[i].verticesCount;
        }
    }

    size_t j = 0;
    for (size_t i = 0; i < data->elementsCount; i++)
    {
        Element element = data->elements[i];
        if (element.verticesCount == 2)
        {
            writeVector(file,data->twoDim[element.vertices[0]-1],data->twoDim[element.vertices[1]-1]);
            j++;
        }
        else if (element.verticesCount > 2)
        {
            for (size_t k = 0; k < element.verticesCount; k++)
            {
                writeVector(file,data->twoDim[element.vertices[k]-1],data->twoDim[element.vertices[(k+1)%element.verticesCount]-1]);
                // 0 1
                // 1 2
                // 2 3%3 = 0
            }
        }
        else
        {
            printf("TODO: implement more complex shapes!\n");
        }
    }

    /*
    for (int i = 0; i < linesCount; i++)
    {
        printf("y = %fx + %f\n",lines[i].x,lines[i].y);
    }
    
    for (float x = *x1; x < *x2; x += GNU_PLOT_STEP)
    {
        fprintf(file,"%f ",x);
        for (size_t i = 0; i < linesCount; i++)
        {
            fprintf(file,"%f ", lines[i].x * x + lines[i].y);    // y = ax + b
        }
        fprintf(file,"\n");
    }
    */
   fclose(file);
}

void prepareLabels(char* filename, ProgData* data)
{
    FILE* file = fopen(filename,"w");

    if (file == NULL)   
    {
        printf("Error opening file!\n");
        fprintf(stderr,"Error opening file!\n");
        exit(1);
    }

    for (size_t i = 0; i < data->twoDimCount; i++)
    {
        fprintf(file,"%lld %f %f\n",i + 1,data->twoDim[i].x,data->twoDim[i].y);
    }

    fclose(file);
}

void writeVector(FILE* file, Vector2 start, Vector2 end)
{
    fprintf(file,"%f %f %f %f\n",start.x,start.y,end.x - start.x, end.y - start.y);
}

void writeNewVector(char* filename, Vector2 start, Vector2 end)
{
    FILE* file = fopen(filename,"a");
    fprintf(file,"%f %f %f %f\n",start.x,start.y,end.x - start.x, end.y - start.y);
    fclose(file);
}