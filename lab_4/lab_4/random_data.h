#ifndef RANDOM_DATA_H
#define RANDOM_DATA_H

#define A_MAX 40
#define A_MIN 1
#define B_MAX 1000
#define B_MIN 1
#define C_MAX 60
#define C_MIN 20
#define D_MAX 1000
#define D_MIN 1

#define NUMBER_OF_R 112
#define NUMBER_OF_S 224

#define RANDOM_SEED 3

typedef struct relationR {
    int a, b;
} R;

typedef struct relationS {
    int c, d;
} S;

R *randomGenerateRelationR();

S *randomGenerateRelationS();

#endif