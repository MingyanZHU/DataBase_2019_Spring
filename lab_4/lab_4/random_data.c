//
// Created by zmy on 19-4-22.
//

#include "random_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

R *randomGenerateRelationR() {
    R *r = (R *) malloc(NUMBER_OF_R * sizeof(R));
    int i;
    srand(time(NULL));
    for (i = 0; i < NUMBER_OF_R; i++) {
        int a = rand() % (A_MAX + 1 - A_MIN) + A_MIN;
        int b = rand() % (B_MAX + 1 - B_MIN) + B_MIN;

        r[i].a = a;
        r[i].b = b;
    }
    return r;
}


S *randomGenerateRelationS() {
    S *s = (S *) malloc(NUMBER_OF_S * sizeof(S));
    int i;
    srand(time(NULL));
    for (i = 0; i < NUMBER_OF_S; i++) {
        int c = rand() % (C_MAX + 1 - C_MIN) + C_MIN;
        int d = rand() % (D_MAX + 1 - D_MIN) + D_MIN;

        s[i].c = c;
        s[i].d = d;
    }
    return s;
}