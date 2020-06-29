#ifndef NUMBER_H
#define NUMBER_H

#include "gennumber.h"
#include "table.h"

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QFile>
#include <QLineEdit>


class Number : public QObject {
    Q_OBJECT
private:
    int32_t m_data;
    int32_t correct;
    QPushButton *giveup;
    QMainWindow *w;
    QPushButton *check;

public:
    explicit Number(QObject *parent = 0);

    Number(int32_t data_, int32_t correct_, QMainWindow *w_, QPushButton *giveup_, QPushButton *check_) {
        m_data = data_;
        correct = correct_;
        w = w_;
        giveup = giveup_;
        check = check_;
    }

    signals:

    void valueChanged(int32_t);

    void valueChanged(QString);

    void valueNew(int32_t);

    void printMes(QString);

public
    slots:

    void setValue(int32_t);

    void setValue(QString);

    void refresh();

    int32_t cnt_cows(int32_t, int32_t);

    int32_t cnt_bulls(int32_t, int32_t);

    void newNum();

    void showTable();
};

#endif // NUMBER_H

#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QFile>
#include <set>
#include <QLabel>


class Key : public QObject {
    Q_OBJECT
private:

    QPushButton *answer;
    QLabel *feedback;
    QLabel *guess;
    QLineEdit *cows;
    QLineEdit *bulls;
    int32_t cur;
    int32_t cur_bulls;
    int32_t cur_cows;
    std::set<int32_t> correct;

public:
    explicit Key(QObject *parent = 0);

    Key(QLabel *fb, QLabel *sg, QLineEdit *sc, QLineEdit *sb, QPushButton *ans) {
        feedback = fb;
        guess = sg;
        bulls = sb;
        cows = sc;
        cur_bulls = 0;
        cur_cows = 0;
        answer = ans;
        for (int32_t i = 1000; i < 10000; ++i) {
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

    int32_t correct_data(QString);

    void check();

    int32_t cnt_cows(int32_t, int32_t);

    int32_t cnt_bulls(int32_t, int32_t);

    void newGame();

    void setNew();
};

#endif // KEY_H
