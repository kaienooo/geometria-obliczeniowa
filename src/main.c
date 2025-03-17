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
    const char filename[] = "data/plot_data.txt";
    char bufor[BUFFER_SIZE] = {0};
    // RUN TESTS
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
        }
        printf("\n");
    }

    float x1;
    float x2;
    float y1;
    float y2;

    prepareData(filename,&data,&x1,&x2,&y1,&y2);

    // TODO: do funkcji
    
    // gnuplot script
    FILE* gnuplot_script = fopen("plot_script.plt","w");
    fprintf(gnuplot_script,"set xrange [%d:%d]\n",(int)(x1-2),(int)(x2+2));
    fprintf(gnuplot_script,"set yrange [%d:%d]\n",(int)(y1-2),(int)(y2+2));
    fprintf(gnuplot_script,"plot '%s' using 1:2:3:4 with vectors nohead",filename);
    
    fclose(gnuplot_script);
    
    lua_State *L = luaL_newstate(); // Create a new Lua state
    luaL_openlibs(L); // Load Lua libraries
    

    if (luaL_dofile(L, "lua_s/script.lua")) {
        fprintf(stderr, "Błąd: %s\n", lua_tostring(L, -1));
        return 1;
    }

    lua_getglobal(L, "drawData"); // Get the function prepareData from Lua

    if (lua_pcall(L, 0, 0, 0) != LUA_OK) 
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