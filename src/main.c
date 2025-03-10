#define BUFFER_SIZE 64
#include <stdio.h>
#include <string.h>

typedef struct 
{
    float x;
    float y;
    float z;
} Vector3;

Vector3 Vector3Add(Vector3 u, Vector3 v)
{
    return (Vector3){u.x + v.x, u.y + v.y, u.z + v.z};
}

void Vector3ToStr(char* s, size_t n, Vector3 u)
{
    snprintf(s,n,"x: %0.6f\ty: %0.6f\tz: %0.6f\n",u.x,u.y,u.z);
}


void testVector3Add(char* test, int testn,Vector3 u, Vector3 v,Vector3 eV)
{
    char testResult[BUFFER_SIZE];
    char expected[BUFFER_SIZE];
    char passed[8];

    u = Vector3Add(u,v);

    Vector3ToStr(testResult,BUFFER_SIZE,u);
    Vector3ToStr(expected,BUFFER_SIZE,eV);

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

int main()
{
    char bufor[BUFFER_SIZE];

    memcpy(bufor,"Dodawanie wektorow 3D",BUFFER_SIZE);
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
}