#include <runic.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    Card test_card = runic_parse(L,"solring.runic");

    printf("Name: %s\n", test_card.name);
    printf("First Ability: %s\n",test_card.abilities[0].kind);
    runic_free_card(&test_card);
    lua_close(L);



}