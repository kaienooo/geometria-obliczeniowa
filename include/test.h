#ifndef TEST_H
#define TEST_H

#include "utils.h"

//Vector general

void testVector(char* test, char* testResult, char* expected, char* passed, int testn);

// Vector 2

void testVector2Add(char* test, int testn,Vector2 u, Vector2 v,Vector2 eV);
void testVector2Sub(char* test, int testn,Vector2 u, Vector2 v,Vector2 eV);
void testVector2Mult(char* test, int testn,Vector2 u, float t,Vector2 eV);

// Vector 3

void testVector3Add(char* test, int testn,Vector3 u, Vector3 v,Vector3 eV);
void testVector3Sub(char* test, int testn,Vector3 u, Vector3 v,Vector3 eV);
void testVector3Mult(char* test, int testn,Vector3 u, float t,Vector3 eV);


#endif