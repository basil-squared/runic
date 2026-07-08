#include <lua.h>
#include <stdio.h>



/// @brief Given a reference to the registry index and lua, grabs the ref and puts it on top of the stackso i may use it later
/// @param lua lua!
/// @param ref The integer pointing towards where the ref is
void runic_push_ref(lua_State *lua, int ref) {
    lua_rawgeti(lua,LUA_REGISTRYINDEX,ref);
}
/// @brief Attempts to resolve a stacked function to return the results of the card's effect post-resolution
/// @param lua  the lua state
/// @param ref  the number reference towards registryindex
/// @param param_count the number of parameters the card receives
/// @return an integer error code/success code, the actual table will be left on top of the stack for manipulation later
int runic_call_resolve(lua_State *lua, int ref,int param_count) {
    runic_push_ref(lua,ref);
    int ret = lua_pcall(lua,param_count,1,0);
    if (ret != LUA_OK) {
        fprintf(stderr, "runic: resolve call failed: %s\n", lua_tostring(lua, -1));
        lua_pop(lua, 1); // pop error message so the stack doesnt go out of wack
        // heehee. stack out of wack. you can laugh now
        return 1; 
    }

    return 0;
}