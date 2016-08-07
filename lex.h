#ifndef __LEX_H_
#defien __LEX_H_

enum token {
    TK_BEGIN,
#define TOKEN(k, s) k,
#include "token.h"
#undef TOKEN
};

union value {
    int i[2];
    float f;
    double d;
    void *p;
};

#define HIGH_4BIT(v)    ((v) >> (8 * sizeof(int) - 4) & 0x0f)
#define HIGH_3BIT(v)    ((v) >> (8 * sizeof(int) - 3) & 0x07)
#define HIGH_1BIT(v)    ((v) >> (8 * sizeof(int) - 1) & 0x01)

void SetupLexer();
void BeginPeekToken();
void EndPeekToken();
int GetNextToken();

extern union value token_value;
extern struct Coord token_coord;
extern struct Coord prev_coord;
extern char *token_strings[];

#endif
