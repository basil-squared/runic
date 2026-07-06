#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
int main(void) {
    char buf[256];
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    int status = luaL_dofile(L,"solring.runic");
    if (status != LUA_OK) {
        printf("error: %s\n", lua_tostring(L, -1));
        return 1;
    }
    // Lua's stack goes -1,-2,-3 for searching from the top and 1,2,3 from the bottom. important things to remember!!! 
    lua_getfield(L,-1,"abilities");
    lua_getfield(L,-1,"kind");
    const char* kind = lua_tostring(L,-1);
    char *kind_copy = strdup(kind);
    free(kind_copy); 
    lua_close(L);



}