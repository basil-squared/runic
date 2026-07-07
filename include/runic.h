#ifndef RUNIC_H
#define RUNIC_H
#include <lua.h>
typedef struct {
    char *kind;
    char *cost;
    char *produces_color;
    int produces_amount;
} Ability;

typedef struct {
    char *name;
    char *type;
    char *mana_cost;
    char *power;
    char *toughness;
    Ability *abilities;
    int ability_count;
} Card;

Card runic_parse(lua_State *lua, char *file_name);
char *runic_safe_alloc(lua_State *lua, const char *field_name);
int runic_safe_alloc_int(lua_State *lua, const char *field_name, int default_val);
void runic_free_card(Card *c);
#endif