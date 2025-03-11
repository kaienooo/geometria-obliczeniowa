#include "../include/utils.h"

#include <stdio.h>

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