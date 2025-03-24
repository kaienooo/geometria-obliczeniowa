#ifdef TEST
#include "../include/test.h"
#endif
    
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/parser.h"
#include "../include/prepare_data.h"

#include "../lua/include/lua.h"
#include "../lua/include/lualib.h"
#include "../lua/include/lauxlib.h"


int main(int argc, char** argv)
{
    char filenamePlotData[] = "data/plot_data.txt";
    char filenameLabelsData[] = "data/labels_data.txt";
    char bufor[BUFFER_SIZE] = {0};
    // RUN TESTS
    // TODO: make function runAllTests() or modular testing framework
    #ifdef TEST
    printf("Running tests!\n");
    memcpy(bufor,"3d vector calcualtions",BUFFER_SIZE);
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

    a = (Vector3){0.5f,0.5f,0.5f};
    b = (Vector3){0.5f,0.5f,0.5f};
    c = (Vector3){.0f,.0f,.0f};

    testVector3Sub(bufor,testn++,a,b,c);

    a = (Vector3){2.0f,2.0f,2.0f};
    float t = 2.0f;
    c = (Vector3){4.0f,4.0f,4.0f};

    testVector3Mult(bufor,testn++,a,t,c);

    a = (Vector3){2.0f,2.0f,2.0f};
    b = (Vector3){2.0f,2.0f,2.0f};

    t = 12.0f;

    testVector3DotProduct(bufor,testn++,a,b,t);

    a = (Vector3){1.0f,0.0f,0.0f};
    b = (Vector3){0.0f,1.0f,0.0f};
    c = (Vector3){0.0f,0.0f,1.0f};

    testVector3CrossProduct(bufor,testn++,a,b,c);

    a = (Vector3){1.0f,2.0f,3.0f};
    b = (Vector3){3.0f,2.0f,-1.0f};
    c = (Vector3){-8.0f,10.0f,-4.0f};

    testVector3CrossProduct(bufor,testn++,a,b,c);

    printf("\n\n");

    memcpy(bufor,"2d vector calcualtions",BUFFER_SIZE);

    testn = 1;

    Vector2 i = {-15.0f,-15.0};
    Vector2 j = {15.0f,15.0f};
    Vector2 k = {.0f,.0f};

    testVector2Add(bufor,testn++,i,j,k);

    i = (Vector2){3.33f,3.33f};
    j = (Vector2){2.0f,2.0f};
    k = (Vector2){1.33f,1.33f};

    testVector2Sub(bufor,testn++,i,j,k);

    i = (Vector2){3.33f,3.33f};
    t = 2.0f;
    k = (Vector2){6.66f, 6.66f};

    testVector2Mult(bufor,testn++,i,t,k);

    i = (Vector2){3.33f,3.33f};
    j = (Vector2){2.0f,2.0f};
    t = 13.32f;

    testVector2DotProduct(bufor,testn++,i,j,t);
    #endif
    // END RUN TESTS

    ProgData data;
    loadData(argv[1],&data);
    
    float x1;
    float x2;
    float y1;
    float y2;

    // -------------------------------------------------- INLINE DATA progData ---------------------------------------------------------------------
    // here introduce INLINE DATA that is stored in memory and then written using prepareData() and prepareLabels()
    // automatically checked for out of bounds
    
    Vector2 point1 = (Vector2){-10.0f,-10.0f};
    Vector2 point2 = (Vector2){10.0f,10.0f};
    Vector3 circle = (Vector3){2.0f,2.0f,2.0f};
    Vector2 line = getLineFromPoints(point1,point2);

    splitCircle(circle,line,6,&data);

    #ifdef TEST

    printf("twoDimCount: %llu\nelementsCount: %llu\n",data.twoDimCount,data.elementsCount);
    
    for (size_t i = 0; i < data.twoDimCount; i++)
    {
        printf("2D: %llu %f %f\n",i + 1,data.twoDim[i].x,data.twoDim[i].y);
    }
    
    printf("\n");
    
    for (size_t i = 0; i < data.elementsCount; i++)
    {
        printf("Element %llu:\n",i);
        for (size_t j = 0; j < data.elements[i].verticesCount; j++)
        {
            size_t vertex = data.elements[i].vertices[j];
            printf("id: %llu x: %f y: %f\n",vertex,data.twoDim[vertex-1].x,data.twoDim[vertex-1].y);
            // pamiec 0 - id 1
            // pamiec 1 - id 2
            // pamiec 2 - id 3
        }
        printf("\n");
    }

    #endif //TEST

    // -------------------------------------------------- INLINE DATA progData ---------------------------------------------------------------------
    
    prepareData(filenamePlotData,&data,&x1,&x2,&y1,&y2);
    prepareLabels(filenameLabelsData,&data);

    // -------------------------------------------------- INLINE DATA raw ---------------------------------------------------------------------
    // here introduce INLINE DATA that is written directly to text file specified in filename... variable
    // When finished introducing INLINE DATA
    // check if INLINE DATA is out of plotting area

    writeNewVector(filenamePlotData,point1,point2);

    // -------------------------------------------------- INLINE DATA raw ---------------------------------------------------------------------

    if (x1 > point1.x)
    {
        x1 = point1.x;
    }

    if (x2 < point2.x)
    {
        x2 = point2.x;
    }

    if (y1 > point1.y)
    {
        y1 = point1.y;
    }

    if (y2 < point2.y)
    {
        y2 = point2.y;
    }

    // ----------------------------------------------- CHECK INLINE DATA ----------------------------------------------------------------------

    lua_State *L = luaL_newstate(); // Create a new Lua state
    luaL_openlibs(L); // Load Lua libraries
    

    if (luaL_dofile(L, "lua_s/script.lua")) {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        return 1;
    }

    lua_getglobal(L, "drawData"); // Get the function prepareData from Lua

    lua_pushinteger(L, (int)x1);
    lua_pushinteger(L, (int)x2);
    lua_pushinteger(L, (int)y1);
    lua_pushinteger(L, (int)y2);
    lua_pushstring(L, filenamePlotData);
    lua_pushstring(L, filenameLabelsData);
    if (lua_pcall(L, 6, 0, 0) != LUA_OK) 
    {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L); // Close the Lua state


    //deallocation
    free(data.twoDim);

    for (size_t i = 0; i < data.elementsCount; i++)
    {
        free(data.elements[i].vertices);
    }
    free(data.elements);

    return 0;
}