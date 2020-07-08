#ifndef NUMBER_H
#define NUMBER_H

#include "gennumber.h"
#include "table.h"

#include <QInputDialog>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>
#include <QLineEdit>
#include <QVariant>
#include <QObject>
#include <QFile>
#include <QDir>


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

    void setValue(int32_t input);

    void setValue(QString input);

    int32_t cntCows(int32_t ourNumber, int32_t trueNumber);

    int32_t cntBulls(int32_t ourNumber, int32_t trueNumber);

    void refresh();

    void newNum();

    void showTable();
};

#endif // NUMBER_H

