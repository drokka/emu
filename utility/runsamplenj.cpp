//
// Created by peter on 1/04/2022.
//
#include "runsamplenj.h"

extern int runsamplewrapimp(int nparam, char** param, unsigned char **pngBuf, int *len) ;


    int runsamplewrap(int nparam, char **param, unsigned char **pngBuf, int *len) {

        int resy = runsamplewrapimp(nparam, param,  pngBuf, len);

    return resy;
}
