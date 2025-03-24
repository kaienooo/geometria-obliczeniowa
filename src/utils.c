#include "../include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

Vector2 getLineFromPoints(Vector2 p1, Vector2 p2)
{
    return (Vector2){(p2.y - p1.y)/(p2.x - p1.x), p1.y - (p2.y - p1.y)/(p2.x - p1.x) * p1.x};
}

float isPointOnLine(Vector2 p, Vector2 line)
{
    return p.y - line.x * p.x - line.y;
}

void reflectPoint(Vector2* p, Vector2 line)
{
    Vector2 translation = Vector2Sub(
        (Vector2){
        (line.x * p->y + p->x - line.x * line.y)/(line.x * line.x + 1),
        (line.x * line.x * p->y + line.x * p->x + line.y)/(line.x * line.x + 1)},
        *p);

    *p = Vector2Add(*p,Vector2Mult(translation,2.0f));
}

//----------------------------------------------------- SEGMENT FUNCTION -------------------------------------------------------------

float isPointOnLineSegment(float x1, float x2, Vector2 p1, Vector2 line)
{
    if (p1.x < x1 || p1.x > x2)
    {
        return 1;
    }
    
    return isPointOnLine(p1,line);
}

//det(p,q,r) > 0 r po lewej pq
//det(p,q,r) == 0 p na pq
//det(p,q,r) < 0 p po prawej pr 
int pointVsVector(Vector2 p, Vector2 q, Vector2 r)
{
    float det = (p.x * q.y) + (p.y * r.x) + (q.x * r.y) - (q.y * r.x) - (p.y * q.x) - (p.x * r.y);

    if (fabsf(det) - EPSILON < 0)
    {
        return 0;
    }

    if(det < 0)
    {
        return 1;
    }

    return -1;
}

void translateSegment(Segment* segment, Vector2 translation)
{
    segment->p1 = Vector2Add(segment->p1,translation);
    segment->p2 = Vector2Add(segment->p2,translation);
}

// ----------------------------------------------------- CIRCLE FUNCTION --------------------------------------------------------------

void generateCircle(Vector3 circle, int n, ProgData* data)
{
    if (n < 3)
    {
        printf("Error: Circle must have at least 3 vertices\n");
        return;
    }


    data->elementsCount++;
    data->elements = realloc(data->elements,data->elementsCount * sizeof(Element));

    data->elements[data->elementsCount - 1].verticesCount = n;
    data->elements[data->elementsCount - 1].vertices = malloc(sizeof(size_t) * n);

    size_t circleVerticesIndex = data->twoDimCount;
    data->twoDimCount += n;
    data->twoDim = realloc(data->twoDim,data->twoDimCount * sizeof(Vector2));


    float angle = 0.0f;
    float angleStep = 2.0f * (float)PI / (float)n;

    // lets say that there are 10 vertices already in memory
    // data.twoDimCount = 10
    // id = index + 1
    // so whenever i try to write an new vertex to memory i write it as normal
    // but when assigning it to an element i have to add 1 to the value

    // data->twoDimCount = 5
    //              =    0     1     2     3     4
    // data->twoDim = {(0,0),(1,0),(2,0),(3,0),(4,0)}
    // realloc(data->twoDim,10)
    //              =   0~1   1~2   2~3   3~4   4~5   5~6   6~7   7~8   8~9   9~10
    // data->twoDim = {(0,0),(1,0),(2,0),(3,0),(4,0),(-,-),(-,-),(-,-),(-,-),(-,-)}
    // data->elements[index] = {5,6,7,8,9}
    // circleVerticesIndex = 5
    // data->elements[circleVerticesIndex] = circleVerticesIndex + i + 1



    for (size_t i = 0; i < n; i++)
    {
        data->twoDim[circleVerticesIndex + i] = (Vector2){circle.x + circle.z * cosf(angle),circle.y + circle.z * sinf(angle)};
        data->elements[data->elementsCount - 1].vertices[i] = circleVerticesIndex + i + 1;
        angle += angleStep;
    }
}

void generateCircleAllocated(Vector3 circle, size_t e, int n, ProgData* data)
{
    if (n < 3)
    {
        printf("Error: Circle must have at least 3 vertices\n");
        return;
    }

    data->elements[e].verticesCount = n;
    data->elements[e].vertices = malloc(sizeof(size_t) * n);

    size_t circleVerticesIndex = data->twoDimCount;
    data->twoDimCount += n;
    data->twoDim = realloc(data->twoDim,data->twoDimCount * sizeof(Vector2));

    float angle = 0.0f;
    float angleStep = 2.0f * (float)PI / (float)n;

    for (size_t i = 0; i < n; i++)
    {
        data->twoDim[circleVerticesIndex + i] = (Vector2){circle.x + circle.z * cosf(angle),circle.y + circle.z * sinf(angle)};
        data->elements[e].vertices[i] = circleVerticesIndex + i + 1;
        angle += angleStep;
    }
}

void generateSplittedElementsFromCircle(Vector3 circle, int n, Vector2 p1, Vector2 p2, ProgData* data)
{
    data->elementsCount+=2;
    data->elements = realloc(data->elements,data->elementsCount * sizeof(Element));
    // allocate data for both elements

    size_t circleVerticesIndex = data->twoDimCount;
    data->twoDimCount += n + 2;
    data->twoDim = realloc(data->twoDim,data->twoDimCount * sizeof(Vector2));
    data->twoDim[circleVerticesIndex] = p1;
    data->twoDim[circleVerticesIndex+1] = p2;

    circleVerticesIndex += 2;

    Element tempCircle;
    tempCircle.verticesCount = n;
    tempCircle.vertices = malloc(sizeof(size_t) * n);

    //generate circle

    float angle = 0.0f;
    float angleStep = 2.0f * (float)PI / (float)n;

    for (size_t i = 0; i < n; i++)
    {
        // points allocated on heap
        data->twoDim[circleVerticesIndex + i] = (Vector2){circle.x + circle.z * cosf(angle),circle.y + circle.z * sinf(angle)};
        // circle on stack
        tempCircle.vertices[i] = circleVerticesIndex + i + 1;
        angle += angleStep;
    }

    // loop through each point of the circle
    // count how many on left side, how many on right side

    size_t left = 2;
    size_t right = 2;
    int* left_right = malloc(sizeof(int) * n);


    // TODO: what if pointVsVector == 0
    for (size_t i = 0; i < n; i++)
    {
        if (pointVsVector(p1,p2,data->twoDim[tempCircle.vertices[i] - 1]) == -1)
        {
            left_right[i] = -1;
            left++;
        }
        else
        {
            left_right[i] = 1;
            right++;
        }
    }

    Element* leftElement = &data->elements[data->elementsCount - 2];
    Element* rightElement = &data->elements[data->elementsCount - 1];

    leftElement->verticesCount = left;
    rightElement->verticesCount = right;

    leftElement->vertices = malloc(sizeof(size_t) * left);
    rightElement->vertices = malloc(sizeof(size_t) * right);

    leftElement->vertices[0] = circleVerticesIndex - 1;
    leftElement->vertices[1] = circleVerticesIndex;

    rightElement->vertices[0] = circleVerticesIndex;
    rightElement->vertices[1] = circleVerticesIndex - 1;

    size_t l = 2;
    size_t r = 2;

    for (size_t i = 0; i < n; i++)
    {
        if (left_right[i] == -1)
        {
            leftElement->vertices[l] = tempCircle.vertices[i];
            l++;
        }
        else if (left_right[i] == 1)
        {
            rightElement->vertices[r] = tempCircle.vertices[i];
            r++;
        }
    }

    free(left_right);
}

void splitCircle(Vector3 circle,Vector2 line,int n, ProgData* data)
{
    if ( n < 3)
    {
        printf("przyblizenie okregu musiec miec przynajmniej 3  punkty!");
        return;
    }

    float delta = 4 * (
        powf(line.x * line.y - circle.y * line.x - circle.x,2) -
        (line.x * line.x - 1) * (line.y * line.y + circle.y * circle.y + circle.x * circle.x - circle.z - 2 * circle.y * line.y));

    printf("%f",delta);

    if (delta + EPSILON < 0)
    {
        printf("Brak punktow przeciecia pomiedzy okregiem a linia\n");
        return;
    }

    if(fabsf(delta) - EPSILON < 0)
    {
        printf("Punkt przeciecia na okregu, prosta jest styczna do okregu\n");
        return;
    }

    float x1 = (-2 * (line.x * line.y - circle.y * line.x - circle.x) - (line.x * line.y - circle.y * line.x - circle.x < 0 ? -1.0f : 1.0f) * sqrtf(delta))/ (2 * (line.x * line.x - 1));
    float x2 = (line.y * line.y + circle.y * circle.y + circle.x * circle.x - circle.z - 2.0f * circle.y * line.y)/( (line.x * line.x - 1) * x1);

    Vector2 p1 = (Vector2){x1,line.x * x1 + line.y};
    Vector2 p2 = (Vector2){x2,line.x * x2 + line.y};

    generateSplittedElementsFromCircle(circle,n,p1,p2,data);
}