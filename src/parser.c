#include <lua.h>
#include <lauxlib.h>
#include <runic.h>
#include <string.h>

/// @brief  
/// @return 
char*runic_safe_alloc(lua_State *lua, const char *field_name) {
    char *result = NULL;
    lua_getfield(lua,-1,field_name);
    if (!lua_isnil(lua,-1)) {
        result = strdup(lua_tostring(lua,-1));
    }
    lua_pop(lua,1);
    return result;
}

/// @brief  given lua, and the file name, parses a file into my handy dandy little struct
/// @param lua the lua state
/// @return  the card struct
Card runic_parse(lua_State *lua, char *file_name) {
    // empty stack to prevent undefined behavior
    lua_settop(lua,0);
    Card ret;
    luaL_dofile(lua,file_name);
    ret.name = runic_safe_alloc(lua,"name");
    ret.type = runic_safe_alloc(lua,"type");
    ret.mana_cost = runic_safe_alloc(lua,"mana_cost");
    
    

   
    
    

    lua_getfield(lua,-1,"abilities");
    int n = lua_rawlen(lua,-1);
    Ability *abilities = malloc(sizeof(Ability) * n);
    for (int i = 1; i <= n; i++) {
        lua_rawgeti(lua,-1,i);
        
    
        abilities[i-1].kind = runic_safe_alloc(lua,"kind");
        

        
        abilities[i-1].cost = runic_safe_alloc(lua,"cost");
        
        // no need to safety check here because if its nil then itll be caught later anyways
        lua_getfield(lua,-1,"produces");

        
        abilities[i-1].produces_color = runic_safe_alloc(lua,"color"); 
        abilities[i-1].produces_amount = runic_safe_alloc(lua,"amount"); // FIXME: this is supposed to be a number

        lua_pop(lua,2);
        
    }
    


    


}
