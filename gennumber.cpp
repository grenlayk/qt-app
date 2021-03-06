#include "gennumber.h"

std::mt19937 mt_rand(time(0));

bool isIncorrect(int32_t number) {
    if (number < BORD)
        return true;

    std::vector<int32_t> digits(SZ);
    for (int32_t i = 0; i < SZ; ++i) {
        digits[i] = number % 10;
        number /= 10;
    }

    sort(digits.begin(), digits.end());
    digits.resize(unique(digits.begin(), digits.end()) - digits.begin());

    return digits.size() < SZ;
}


int genNumber() {
    int32_t currentNumber = 0;
    while (isIncorrect(currentNumber)) {
        currentNumber = (unsigned)mt_rand() % MOD;
    }
    return currentNumber;
}
