#ifdef TEST
#include "../include/test.h"
#endif
    
#include <stdio.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/parser.h"

int main(int argc, char** argv)
{
    char bufor[BUFFER_SIZE];
    // RUN TESTS
    #ifdef TEST
    printf("Running tests!\n");
    memcpy(bufor,"Operacje na wektorach 3D",BUFFER_SIZE);
    int testn = 1;

    Vector3 a = {.0f,.0f,.0f};
    Vector3 b = {1.0f,1.0f,1.0f};
    Vector3 c = {1.0f,1.0f,1.0f};

    testVector3Add(bufor,testn++,a,b,c);

    a = (Vector3){-15.0f,-15.0f,-15.0f};
    b = (Vector3){15.0f,15.0f,15.0f};
    c = (Vector3){.0f,.0f,.0f};

    testVector3Add(bufor,testn++,a,b,c);

    a = (Vector3){-0.5f,-0.5f,-0.5f};
    b = (Vector3){0.5f,0.5f,0.5f};
    c = (Vector3){.0f,.0f,.0f};

    testVector3Add(bufor,testn++,a,b,c);

    a = (Vector3){0.5f,0.5f,0.5f};
    b = (Vector3){0.5f,0.5f,0.5f};
    c = (Vector3){.0f,.0f,.0f};

    testVector3Sub(bufor,testn++,a,b,c);

    a = (Vector3){2.0f,2.0f,2.0f};
    float t = 2.0f;
    c = (Vector3){4.0f,4.0f,4.0f};

    testVector3Mult(bufor,testn++,a,t,c);

    a = (Vector3){2.0f,2.0f,2.0f};
    b = (Vector3){2.0f,2.0f,2.0f};

    t = 12.0f;

    testVector3DotProduct(bufor,testn++,a,b,t);

    a = (Vector3){1.0f,0.0f,0.0f};
    b = (Vector3){0.0f,1.0f,0.0f};
    c = (Vector3){0.0f,0.0f,1.0f};

    testVector3CrossProduct(bufor,testn++,a,b,c);

    a = (Vector3){1.0f,2.0f,3.0f};
    b = (Vector3){3.0f,2.0f,-1.0f};
    c = (Vector3){-8.0f,10.0f,-4.0f};

    testVector3CrossProduct(bufor,testn++,a,b,c);

    printf("\n\n");

    memcpy(bufor,"Operacje na wektorach 2D",BUFFER_SIZE);

    testn = 1;

    Vector2 i = {-15.0f,-15.0};
    Vector2 j = {15.0f,15.0f};
    Vector2 k = {.0f,.0f};

    testVector2Add(bufor,testn++,i,j,k);

    i = (Vector2){3.33f,3.33f};
    j = (Vector2){2.0f,2.0f};
    k = (Vector2){1.33f,1.33f};

    testVector2Sub(bufor,testn++,i,j,k);

    i = (Vector2){3.33f,3.33f};
    t = 2.0f;
    k = (Vector2){6.66f, 6.66f};

    testVector2Mult(bufor,testn++,i,t,k);

    i = (Vector2){3.33f,3.33f};
    j = (Vector2){2.0f,2.0f};
    t = 13.32f;

    testVector2DotProduct(bufor,testn++,i,j,t);
    #endif
    // END RUN TESTS

    ProgData data;
    loadData(argv[1],&data);

    for (size_t i = 0; i < data.twoDimCount; i++)
    {
        printf("2D: %f %f\n",data.twoDim[i].x,data.twoDim[i].y);
    }

    printf("\n");

    for (size_t i = 0; i < data.elementsCount; i++)
    {
        printf("Element %d: ",i);
        for (size_t j = 0; j < data.elements[i].verticesCount; j++)
        {
            printf("%f %f\n",getDataTwoDimXFromElements(&data,i,j),getDataTwoDimYFromElements(&data,i,j));
        }
        printf("\n");
    }
    

    return 0;
}