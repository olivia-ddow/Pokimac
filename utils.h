
#ifndef UTILS_H
#define UTILS_H

//initialise des structures
struct Case{
    int type;
    int index;
};

struct Position{
    int x;
    int y;
};

typedef struct {
    Position anc_pos;
    Position nouv_pos;
} Evol_pos;

void sleep(unsigned int ms);
void ligne_vague();

#endif
