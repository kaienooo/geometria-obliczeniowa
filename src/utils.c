#include "../include/utils.h"

#include <stdio.h>
//----------------------------------------------------- DATA FUNCTION -----------------------------------------------------------------

float getDataTwoDimXFromElements(ProgData* data, size_t element, size_t vertex)
{
    return data->twoDim[data->elements[element].vertices[vertex]].x;
}

float getDataTwoDimYFromElements(ProgData* data, size_t element, size_t vertex)
{
    return data->twoDim[data->elements[element].vertices[vertex]].y;
}

//----------------------------------------------------- Vector 2 FUNCTION -------------------------------------------------------------

Vector2 Vector2Add(Vector2 u, Vector2 v)
{
    return (Vector2){u.x + v.x, u.y + v.y};
}

Vector2 Vector2Sub(Vector2 u, Vector2 v)
{
    return (Vector2){u.x - v.x, u.y - v.y};
}

Vector2 Vector2Mult(Vector2 u, float t)
{
    return (Vector2){u.x * t, u.y * t};
}

void Vector2ToStr(char* s, size_t n, Vector2 u)
{
    snprintf(s,n,"x: %0.6f\ty: %0.6f\n",u.x,u.y);
}

float Vector2DotProduct(Vector2 u, Vector2 v)
{
    return u.x * v.x + u.y * v.y;
}

//----------------------------------------------------- Vector 3 FUNCTION -------------------------------------------------------------

Vector3 Vector3Add(Vector3 u, Vector3 v)
{
    return (Vector3){u.x + v.x, u.y + v.y, u.z + v.z};
}

Vector3 Vector3Sub(Vector3 u, Vector3 v)
{
    return (Vector3){u.x - v.x, u.y - v.y, u.z - v.z};
}

Vector3 Vector3Mult(Vector3 u, float t)
{
    return (Vector3){u.x * t, u.y * t,u.z * t};
}

void Vector3ToStr(char* s, size_t n, Vector3 u)
{
    snprintf(s,n,"x: %0.6f\ty: %0.6f\tz: %0.6f\n",u.x,u.y,u.z);
}

float Vector3DotProduct(Vector3 u, Vector3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

//  i   j   k
//  u.x u.y u.z
//  v.x v.y v.z

Vector3 Vector3CrossProduct(Vector3 u, Vector3 v)
{
    return (Vector3){u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
}

//----------------------------------------------------- LINES FUNCTION -------------------------------------------------------------

Vector2 getLineIntersection(Vector2 p1, Vector2 p2)
{
    return (Vector2){(p2.y - p1.y)/(p2.x - p1.x), p1.y - (p2.y - p1.y)/(p2.x - p1.x) * p1.x};
}