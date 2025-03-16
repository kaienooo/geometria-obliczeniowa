#include "../include/test.h"

#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//----------------------------------------------------- Vector GENERAL ----------------------------------------------------------------

void testVector(char* test, char* testResult, char* expected, int testn)
{
    if (!strcmp(expected,testResult))
    {
        printf("Test %s No. %d:\t" ANSI_COLOR_GREEN "Passed" ANSI_COLOR_RESET "\nExpected\t%s\ngot\t\t%s\n",test,testn,expected,testResult);
    }
    else
    {
        printf("Test %s No. %d:\t" ANSI_COLOR_RED "Failed" ANSI_COLOR_RESET "\nExpected\t%s\ngot\t\t%s\n",test,testn,expected,testResult);
    }
}

//----------------------------------------------------- Vector 2 FUNCTION -------------------------------------------------------------

void testVector2Add(char* test, int testn,Vector2 u, Vector2 v,Vector2 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];


    u = Vector2Add(u,v);

    Vector2ToStr(testResult,BUFFER_SIZE,u);
    Vector2ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,testn);
}

void testVector2Sub(char* test, int testn,Vector2 u, Vector2 v,Vector2 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    u = Vector2Sub(u,v);

    Vector2ToStr(testResult,BUFFER_SIZE,u);
    Vector2ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,testn);
}

void testVector2Mult(char* test, int testn,Vector2 u, float t,Vector2 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    u = Vector2Mult(u,t);

    Vector2ToStr(testResult,BUFFER_SIZE,u);
    Vector2ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,testn);
}

void testVector2DotProduct(char* test, int testn, Vector2 u, Vector2 v, float eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    float dot = Vector2DotProduct(u,v);

    snprintf(testResult,BUFFER_SIZE,"%f",dot);
    snprintf(expected,BUFFER_SIZE,"%f",eV);

    testVector(test,testResult,expected,testn);
}

//----------------------------------------------------- Vector 3 FUNCTION -------------------------------------------------------------

void testVector3Add(char* test, int testn,Vector3 u, Vector3 v,Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    u = Vector3Add(u,v);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,testn);
}

void testVector3Sub(char* test, int testn,Vector3 u, Vector3 v,Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    u = Vector3Sub(u,v);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,testn);
}

void testVector3Mult(char* test, int testn,Vector3 u, float t,Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    u = Vector3Mult(u,t);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,testn);
}

void testVector3DotProduct(char* test, int testn, Vector3 u, Vector3 v, float eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    float dot = Vector3DotProduct(u,v);

    snprintf(testResult,BUFFER_SIZE,"%f",dot);
    snprintf(expected,BUFFER_SIZE,"%f",eV);

    testVector(test,testResult,expected,testn);
}

void testVector3CrossProduct(char* test, int testn, Vector3 u, Vector3 v, Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];

    u = Vector3CrossProduct(u,v);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

    testVector(test,testResult,expected,testn);
}