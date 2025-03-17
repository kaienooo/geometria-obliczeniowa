#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#define BUFFER_SIZE 64
#define GNU_PLOT_STEP 0.1f

//----------------------------------------------------- Vector 2 STRUCT ---------------------------------------------------------------
// prosta jako Vector2
// y = Vector2.x * x + Vector2.y
typedef struct
{
    float x;
    float y;
} Vector2;

//----------------------------------------------------- Vector 3 STRUCT ---------------------------------------------------------------

typedef struct 
{
    float x;
    float y;
    float z;
} Vector3;

//----------------------------------------------------- Element STRUCT ----------------------------------------------------------------

typedef struct
{
    size_t verticesCount;
    size_t* vertices;
} Element;

//----------------------------------------------------- ProgData STRUCT ---------------------------------------------------------------

typedef struct
{
    Vector2* twoDim;
    Vector3* threeDim;

    size_t twoDimCount;
    size_t threeDimCount;

    Element* elements;
    size_t elementsCount;
} ProgData;

//----------------------------------------------------- DATA FUNCTION ---------------------------------------------------------------

float getDataTwoDimXFromElements(ProgData* data, size_t element, size_t vertex);
float getDataTwoDimYFromElements(ProgData* data, size_t element, size_t vertex);

//----------------------------------------------------- Vector 2 FUNCTION -------------------------------------------------------------

Vector2 Vector2Add(Vector2 u, Vector2 v);
Vector2 Vector2Sub(Vector2 u, Vector2 v);
Vector2 Vector2Mult(Vector2 u, float t);
float Vector2DotProduct(Vector2 u, Vector2 v);


void Vector2ToStr(char* s, size_t n, Vector2 u);

//----------------------------------------------------- Vector 3 FUNCTION -------------------------------------------------------------

Vector3 Vector3Add(Vector3 u, Vector3 v);
Vector3 Vector3Sub(Vector3 u, Vector3 v);
Vector3 Vector3Mult(Vector3 u, float t);
float Vector3DotProduct(Vector3 u, Vector3 v);
Vector3 Vector3CrossProduct(Vector3 u, Vector3 v);

void Vector3ToStr(char* s, size_t n, Vector3 u);

//----------------------------------------------------- LINES FUNCTION -------------------------------------------------------------

Vector2 getLineIntersection(Vector2 p1, Vector2 p2);

#endif
