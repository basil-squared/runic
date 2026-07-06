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