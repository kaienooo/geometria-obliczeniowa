#include "../include/test.h"

#include <stdio.h>
#include <string.h>
//----------------------------------------------------- Vector GENERAL ----------------------------------------------------------------

void testVector(char* test, char* testResult, char* expected, char* passed, int testn)
{
    if (!strcmp(expected,testResult))
    {
        memcpy(passed,"Passed",8);
    }
    else
    {
        memcpy(passed,"Failed",8);
    }

    printf("Test %s No. %d:\t%s\nExpected\t%s\ngot\t\t%s\n",test,testn,passed,expected,testResult);
}

//----------------------------------------------------- Vector 2 FUNCTION -------------------------------------------------------------

void testVector2Add(char* test, int testn,Vector2 u, Vector2 v,Vector2 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];
    char passed[8];

    u = Vector2Add(u,v);

    Vector2ToStr(testResult,BUFFER_SIZE,u);
    Vector2ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,passed,testn);
}

void testVector2Sub(char* test, int testn,Vector2 u, Vector2 v,Vector2 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];
    char passed[8];

    u = Vector2Sub(u,v);

    Vector2ToStr(testResult,BUFFER_SIZE,u);
    Vector2ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,passed,testn);
}

void testVector2Mult(char* test, int testn,Vector2 u, float t,Vector2 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];
    char passed[8];

    u = Vector2Mult(u,t);

    Vector2ToStr(testResult,BUFFER_SIZE,u);
    Vector2ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,passed,testn);
}

//----------------------------------------------------- Vector 3 FUNCTION -------------------------------------------------------------

void testVector3Add(char* test, int testn,Vector3 u, Vector3 v,Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];
    char passed[8];

    u = Vector3Add(u,v);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,passed,testn);
}

void testVector3Sub(char* test, int testn,Vector3 u, Vector3 v,Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];
    char passed[8];

    u = Vector3Sub(u,v);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,passed,testn);
}

void testVector3Mult(char* test, int testn,Vector3 u, float t,Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];
    char passed[8];

    u = Vector3Mult(u,t);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,passed,testn);
}