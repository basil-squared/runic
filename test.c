#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

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



}