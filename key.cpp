#include "key.h"

bool isEnd = false;


int32_t Key::correctData(QString input) {
    int32_t intValue;
    bool isInt;

    while (input.size() != 0 && input.back() == ' ') {
        input.resize((int32_t)input.size() - 1);
    }
    if (input.size() == 0)
        return 0;
    intValue = input.toInt(&isInt);
    bool isCorrect = (isInt && intValue < 5 && intValue >= 0);
    if (isCorrect)
        return intValue;
    else
        return -1;
}


int32_t Key::cntBulls(int32_t ourNumber, int32_t trueNumber) {
    int32_t bulls = 0;
    for (int32_t i = 0; i < SZ; ++i) {
        if (trueNumber % 10 == ourNumber % 10) {
            ++bulls;
        }
        ourNumber /= 10;
        trueNumber /= 10;
    }
    return bulls;
}


int32_t Key::cntCows(int32_t ourNumber, int32_t trueNumber) {
    std::vector<int32_t> digitsCnt(10);
    for (int32_t i = 0; i < SZ; ++i) {
        if (trueNumber % 10 != ourNumber % 10) {
            digitsCnt[ourNumber % 10]++;
            digitsCnt[trueNumber % 10]++;
        }
        ourNumber /= 10;
        trueNumber /= 10;
    }
    int32_t cows = 0;
    for (int32_t i = 0; i < 10; ++i) {
        if (digitsCnt[i] >= 2)
            ++cows;
    }
    return cows;
}


void Key::newGame() {
    answer->setText("Restart game");
    isEnd = true;
}


void Key::setNew() {
    answer->setText("Reply");
    feedback->setText("Enter the quantity bulls and cows");
    correct.clear();
    for (int32_t i = BORD; i < MOD; ++i) {
        if (!isIncorrect(i))
            correct.insert(i);
    }
    cur = *correct.begin();
    correct.erase(correct.begin());
    guess->setText(QString::number(cur));
}


void Key::check() {
    if (isEnd) {
        setNew();
        isEnd = false;
        return;
    }
    curCows = correctData(cows->text());
    curBulls = correctData(bulls->text());
    if (curCows == -1 || curBulls == -1) {
        feedback->setText("Incorrect input");
        return;
    } else if (curCows + curBulls > 4) {
        feedback->setText("Incorrect input");
        return;
    } else {
        feedback->setText("Enter the quantity bulls and cows");
        if (curBulls == 4) {
            feedback->setText("Your number: " + QString::number(cur));
            newGame();
            return;
        }

        std::set<int32_t> correctNew;
        for (auto x : correct) {
            if (cntBulls(x, cur) == curBulls && cntCows(x, cur) == curCows) {
                correctNew.insert(x);
            }
        }
        if (correctNew.empty()) { // restart
            feedback->setText("You lied!");
            newGame();
        } else {
            correct = correctNew;
            cur = *correct.begin();
            correct.erase(correct.begin());
            guess->setText(QString::number(cur));
        }
    }
}

