#include <lua.h>
#include <lauxlib.h>
#include <runic.h>
#include <string.h>
#include <stdlib.h>
/// @brief  safely attempts to allocate a string from the lua stack
/// @return  the string, or NULL
char *runic_safe_alloc(lua_State *lua, const char *field_name) {
    char *result = NULL;
    lua_getfield(lua,-1,field_name);
    if (!lua_isnil(lua,-1)) {
        result = strdup(lua_tostring(lua,-1));
    }
    lua_pop(lua,1);
    return result;
}
/// @brief safely gets an integer
/// @param lua the lua state
/// @param field_name the name of the field you wanna grab out of
/// @param default_val the fallback value if the int doesnt exist
/// @return the desired value, or the default
int runic_safe_alloc_int(lua_State *lua, const char *field_name, int default_val) {
    lua_getfield(lua, -1, field_name);
    int result = lua_isnil(lua, -1) ? default_val : (int)lua_tointeger(lua, -1);
    lua_pop(lua, 1);
    return result;
}
/// @brief Safely allocates room for a function and gives it a reference to use for the duration of the lua state's existence.
/// @param lua  The lua state.
/// @param field_name  the name of the field to grab (could be resolve, or effect for static abilities)
/// @return The reference number of the function, or -1 if it failed anywhere.
int runic_safe_alloc_fn(lua_State *lua, const char *field_name) {
    int ret = -1;
    lua_getfield(lua, -1, field_name);
    if (!lua_isnil(lua,-1)) {
        const char *src = lua_tostring(lua,-1);
        if (luaL_loadstring(lua,src) == LUA_OK) {
            
            ret = luaL_ref(lua,LUA_REGISTRYINDEX);
            lua_pop(lua,1);
        } else {
            lua_pop(lua,2);
        }
    } else {
        lua_pop(lua, 1);
    }
    return ret;
}
/// @brief  given lua, and the file name, parses a file into my handy dandy little struct
/// @param lua the lua state
/// @return  the card struct
Card runic_parse(lua_State *lua, char *file_name) {
    // empty stack to prevent undefined behavior
    lua_settop(lua,0);
    Card ret;
    if (luaL_dofile(lua,file_name) != LUA_OK) {
        fprintf(stderr, "failed to load %s: %s\n", file_name, lua_tostring(lua, -1));
        ret.name = strdup("FAIL"); 
        return ret;
    }
    ret.name = runic_safe_alloc(lua,"name");
    ret.type = runic_safe_alloc(lua,"type");
    ret.mana_cost = runic_safe_alloc(lua,"mana_cost");
    lua_getfield(lua,-1,"abilities");
    if (!lua_isnil(lua,-1)) {
        int n = lua_rawlen(lua,-1);
        Ability *abilities = malloc(sizeof(Ability) * n);
        for (int i = 1; i <= n; i++) {
            lua_rawgeti(lua,-1,i);
            abilities[i-1].kind = runic_safe_alloc(lua,"kind");
            abilities[i-1].cost = runic_safe_alloc(lua,"cost");
            if (strcmp(abilities[i-1].kind, "activated") == 0 || strcmp(abilities[i-1].kind, "triggered") == 0) {
                abilities[i-1].resolve_ref = NULL; // TODO: change to runic_safe_alloc_fn when written
            }
            lua_getfield(lua,-1,"produces");
            if (!lua_isnil(lua,-1)) {
                abilities[i-1].produces_color = runic_safe_alloc(lua,"color"); 
                abilities[i-1].produces_amount = runic_safe_alloc_int(lua,"amount",0);
            } 
            else {
                abilities[i-1].produces_color = NULL;
                abilities[i-1].produces_amount = 0;
            }
        
            lua_pop(lua,2);
        
        }
        ret.abilities = abilities;
        ret.ability_count = n;
        lua_pop(lua,2);
    } else {
        ret.abilities = NULL;
        ret.ability_count = 0;
        lua_pop(lua,1);
    }
    return ret;
}
