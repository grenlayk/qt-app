#ifndef KEY_H
#define KEY_H

#include "gennumber.h"
#include "table.h"

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <set>



class Key : public QObject {
    Q_OBJECT
private:

    QPushButton *answer;
    QLabel *feedback;
    QLabel *guess;
    QLineEdit *cows;
    QLineEdit *bulls;
    int32_t cur;
    int32_t curBulls;
    int32_t curCows;
    std::set<int32_t> correct;

public:
    explicit Key(QObject *parent = 0);

    Key(QLabel *fb, QLabel *sg, QLineEdit *sc, QLineEdit *sb, QPushButton *ans) {
        feedback = fb;
        guess = sg;
        bulls = sb;
        cows = sc;
        curBulls = 0;
        curCows = 0;
        answer = ans;
        for (int32_t i = BORD; i < MOD; ++i) {
            if (!isIncorrect(i))
                correct.insert(i);
        }
        cur = *correct.begin();
        correct.erase(correct.begin());
        guess->setText(QString::number(cur));
    }

    signals:

    void valueChanged(int32_t);

    void valueChanged(QString);

    void valueNew(int32_t);

    void printMes(QString);

public
    slots:

    int32_t correctData(QString input);

    int32_t cntCows(int32_t ourNumber, int32_t trueNumber);

    int32_t cntBulls(int32_t ourNumber, int32_t trueNumber);

    void check();

    void newGame();

    void setNew();
};

#endif // KEY_H

