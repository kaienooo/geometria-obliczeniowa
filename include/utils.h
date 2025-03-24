#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#define BUFFER_SIZE 64
#define GNU_PLOT_STEP 0.1f
#define EPSILON 0.0001f
#define PI 3.14159265359f

//----------------------------------------------------- Vector 2 STRUCT ---------------------------------------------------------------
// prosta jako Vector2
// y = Vector2.x * x + Vector2.y

//float x;
//float y;
typedef struct
{
    float x;
    float y;
} Vector2;

//----------------------------------------------------- Vector 3 STRUCT ---------------------------------------------------------------

// okrag jako Vector3
// a = Vector3.x
// b = Vector3.y
// r = Vector3.z


//float x;
//float y;
//float z;
typedef struct 
{
    float x;
    float y;
    float z;
} Vector3;

//----------------------------------------------------- Segment STRUCT ---------------------------------------------------------------

//Vector2 p1;
//Vector2 p2;
typedef struct
{
    Vector2 p1;
    Vector2 p2;
} Segment;

//----------------------------------------------------- Element STRUCT ----------------------------------------------------------------

//size_t verticesCount;
//size_t* vertices;
typedef struct
{
    size_t verticesCount;
    size_t* vertices;
} Element;

//----------------------------------------------------- ProgData STRUCT ---------------------------------------------------------------

//Vector2* twoDim;
//Vector3* threeDim;
//size_t twoDimCount;
//size_t threeDimCount;
//Element* elements;
//size_t elementsCount;
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

Vector2 getLineFromPoints(Vector2 p1, Vector2 p2);

// czy punkt lezy na prostej?
// jezeli isPointOnLine < -epsilon to punkt po lewej stronie prostej
// jezeli isPointOnLine > epsilon to punkt po prawej stronie prostej
// jezeli isPointOnLine < epsilon i isPointOnLine > -epsilon to punkt lezy na prostej
float isPointOnLine(Vector2 p1, Vector2 line);

void reflectPoint(Vector2* point, Vector2 line);

//----------------------------------------------------- SEGMENTS FUNCTION -------------------------------------------------------------

float isPointOnSegment(float x1, float x2, Vector2 p1, Vector2 line);

//det(p,q,r) > 0 r po lewej pq
//det(p,q,r) == 0 p na pq
//det(p,q,r) < 0 p po prawej pr 
int pointVsVector(Vector2 p, Vector2 q, Vector2 r);

void translateSegment(Segment* segment, Vector2 translation);

//----------------------------------------------------- CIRCLE FUNCTION -------------------------------------------------------------

//no memory allocated for Element and points
void generateCircle(Vector3 circle, int n, ProgData* data);

//memory allocated for Element but not for points
void generateCircleAllocated(Vector3 circle, size_t e, int n, ProgData* data);

void generateSplittedElementsFromCircle(Vector3 circle, int n, Vector2 p1, Vector2 p2, ProgData* data);

void splitCircle(Vector3 circle, Vector2 line,int n, ProgData* data);

#endif