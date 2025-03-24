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

//----------------------------------------------------- ELEMENT FUNCTION -------------------------------------------------------------

void translateElement(Element* element, Vector2 translation, ProgData* data)
{
    for (size_t i = 0; i < element->verticesCount; i++)
    {
        data->twoDim[element->vertices[i]-1] = Vector2Add(data->twoDim[element->vertices[i]-1],translation);
    }
}

// ----------------------------------------------------- CIRCLE FUNCTION --------------------------------------------------------------

void circleLineIntersection(Vector3 c, Vector2 l, Vector2* p1, Vector2* p2)
{
    printf("c.x = %f c.y = %f c.z = %f l.x = %f l.y = %f\n",c.x,c.y,c.z,l.x,l.y);

    float Ly_Cy = l.y - c.y;
    float delta = (4.0f * powf(l.x * Ly_Cy - c.x,2.0f)) - (4.0f * (l.x * l.x + 1.0f) * (Ly_Cy * Ly_Cy + c.x * c.x - c.z * c.z));


    printf("A   = %f\n", l.x * l.x + 1.0f);
    printf("B   = %f\n", 2.0f * (l.x * Ly_Cy - c.x));
    printf("C   = %f\n", Ly_Cy * Ly_Cy + c.x * c.x - c.z * c.z);
    printf("B^2 = %f\n", 4.0f * powf(l.x * Ly_Cy - c.x,2.0f));
    printf("4AC = %f\n", (4.0f * (l.x * l.x + 1.0f) * (Ly_Cy * Ly_Cy + c.x * c.x - c.z * c.z)));

    printf("delta = %f\n",delta);


    if (fabsf(delta) - EPSILON < 0)
    {
        printf("Prosta jest styczna do okregu\n");
        *p1 = *p2;      // dzieki temu program wie ze wystepuje blad
        return;
    }

    if(delta < 0)
    {
        printf("Prosta nie ma punktow przeciecia z okregiem\n");
        *p1 = *p2;      // dzieki temu program wie ze wystepuje blad
        return;
    }

  
    p1->x = ((-2.0f * (l.x * Ly_Cy - c.x)) - sqrtf(delta))/(2.0f * (l.x * l.x + 1.0f));
    p2->x = (Ly_Cy * Ly_Cy + c.x * c.x - c.z * c.z) / (p1->x * (l.x * l.x + 1.0f));

    printf("x1 = %f x2 = %f\n",p1->x, p2->x);

    if (p2->x < p1->x)
    {
        float temp = p1->x;
        p1->x = p2->x;
        p2->x = temp;
    }

    p1->y = l.x * p1->x + l.y;
    p2->y = l.x * p2->x + l.y;
}

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

void generateSplittedElementsFromCircle(Vector3 circle,Vector2 line ,int n, Vector2 p1, Vector2 p2, ProgData* data)
{
    data->elementsCount+=2;
    data->elements = realloc(data->elements,data->elementsCount * sizeof(Element));
    // allocate data for both elements

    size_t circleVerticesIndex = data->twoDimCount;
    data->twoDimCount += n + 4;
    data->twoDim = realloc(data->twoDim,data->twoDimCount * sizeof(Vector2));
    data->twoDim[circleVerticesIndex] = p1;         //p1 left
    data->twoDim[circleVerticesIndex+1] = p2;       //p2 left
    data->twoDim[circleVerticesIndex+2] = p1;       //p1 right
    data->twoDim[circleVerticesIndex+3] = p2;       //p2 right

    circleVerticesIndex += 4;

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

    /*
    leftElement->vertices[0] = circleVerticesIndex - 1;
    leftElement->vertices[1] = circleVerticesIndex;
    
    rightElement->vertices[0] = circleVerticesIndex;
    rightElement->vertices[1] = circleVerticesIndex - 1;
    */

    size_t l = 0;
    size_t r = 0;
    
    typedef enum
    {
        LEFT,
        RIGHT,
        DEFAULT
    } Side;

    Side side = DEFAULT;

    if (left_right[0] == -1)
        side = LEFT;
    else
        side = RIGHT;

    // writing to memory information about points
    for (size_t i = 0; i < n; i++)
    {
        switch (side)
        {
            case LEFT:
                if(left_right[i] == -1)
                {
                    leftElement->vertices[l++] = tempCircle.vertices[i];
                }
                else
                {
                    leftElement->vertices[l++] = circleVerticesIndex - 3;
                    leftElement->vertices[l++] = circleVerticesIndex - 2;
                    rightElement->vertices[r++] = tempCircle.vertices[i];
                    side = RIGHT;
                }
                break;
            case RIGHT:
                if(left_right[i] == 1)  // do tej pory po prawej i nowy tez po prawej
                {
                    rightElement->vertices[r++] = tempCircle.vertices[i];
                }
                else                    // do tej pory po prawej i nowy po lewej
                {
                    rightElement->vertices[r++] = circleVerticesIndex;
                    rightElement->vertices[r++] = circleVerticesIndex - 1;
                    leftElement->vertices[l++] = tempCircle.vertices[i];
                    side = LEFT;
                }
                break;
            case DEFAULT:
                break;
        }
    }

    // translating right element
    // line.x = 0 exluded
    float a2 = (-1.0f/line.x);

    Vector2 translation = (Vector2){(circle.z/2.0f) / sqrtf(a2*a2 + 1), (a2*(circle.z/2.0f))/(sqrtf(a2*a2 + 1))};

    printf("translation: x = %f, y =%f\n",translation.x, translation.y);
    
    translateElement(rightElement,translation,data);

    printf("finished translation\n");
    

    free(left_right);
}

void splitCircle(Vector3 circle,Vector2 line,int n, ProgData* data)
{
    if ( n < 3)
    {
        printf("przyblizenie okregu musiec miec przynajmniej 3  punkty!\n");
        return;
    }

    Vector2 p1;
    Vector2 p2;

    circleLineIntersection(circle,line,&p1,&p2);

    printf("p1 %f %f\np2 %f %f\n",p1.x,line.x * p1.x + line.y,p2.x,line.x * p2.x + line.y);

    if (p1.x == p2.x && p2.x == p2.y)
    {
        return;
    }

    generateSplittedElementsFromCircle(circle,line,n,p1,p2,data);
}