#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
int main(void) {
    char buf[256];
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    
    
    
    lua_close(L);



}