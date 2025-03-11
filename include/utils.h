#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#define BUFFER_SIZE 64

//----------------------------------------------------- Vector 2 STRUCT ---------------------------------------------------------------

typedef struct
{
    float x;
    float y;
} Vector2;

//----------------------------------------------------- Vector 3 STRUCT ---------------------------------------------------------------
// prosta jako Vector3
// Ax + By + C = 0, gdzie Vector3.x = A itd.

typedef struct 
{
    float x;
    float y;
    float z;
} Vector3;

//----------------------------------------------------- Line STRUCT -------------------------------------------------------------------

typedef struct
{
    Vector2 startPos;
    Vector2 endPos;
} Line2D;

typedef struct
{
    Vector3 startPos;
    Vector3 endPos;
} Line3D;

//----------------------------------------------------- Face STRUCT -------------------------------------------------------------------

typedef struct
{
    size_t verticesCount;
    size_t* vertices;
    //size_t normal;
} Face;

//----------------------------------------------------- Vector 2 FUNCTION -------------------------------------------------------------

Vector2 Vector2Add(Vector2 u, Vector2 v);
Vector2 Vector2Sub(Vector2 u, Vector2 v);
Vector2 Vector2Mult(Vector2 u, float t);
Vector2 Vector2DotProduct(Vector2 u, Vector2 v);
Vector2 Vector2CrossProduct(Vector2 u, Vector2 v);

void Vector2ToStr(char* s, size_t n, Vector2 u);

//----------------------------------------------------- Vector 3 FUNCTION -------------------------------------------------------------

Vector3 Vector3Add(Vector3 u, Vector3 v);
Vector3 Vector3Sub(Vector3 u, Vector3 v);
Vector3 Vector3Mult(Vector3 u, float t);
Vector3 Vector3DotProduct(Vector3 u, Vector3 v);
Vector3 Vector3CrossProduct(Vector3 u, Vector3 v);

void Vector3ToStr(char* s, size_t n, Vector3 u);

#endif
