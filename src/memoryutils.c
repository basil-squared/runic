#include <stdlib.h>
#include <runic.h>
// i do this becuase free() on a null value is a noop, but freeing an already freed piece of memory is undefined behavior
#define FREE_AND_NULL(p) do { free(p); (p) = NULL; } while(0)

void runic_free_card(Card *c) {
    FREE_AND_NULL(c->name);
    FREE_AND_NULL(c->mana_cost);
    FREE_AND_NULL(c->power);
    FREE_AND_NULL(c->toughness);
    FREE_AND_NULL(c->type);
    for (int i=0; i < c->ability_count; i++) {
        FREE_AND_NULL(c->abilities[i].cost);
        FREE_AND_NULL(c->abilities[i].kind);
        FREE_AND_NULL(c->abilities[i].produces_color);
    }
    FREE_AND_NULL(c->abilities);
    
    
}