#ifndef GENNUMBER_H
#define GENNUMBER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <random>
#include <fstream>
#include <string>

const int32_t SZ = 4;
const int32_t MOD = 1e4;
const int32_t INF = 1e9;

bool isIncorrect(int32_t number);

int genNumber();

#endif // GENNUMBER_H
