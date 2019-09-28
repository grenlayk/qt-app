#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include "number.h"
//#include "key.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>
#include <QInputDialog>
#include <QtGui>

const int MOD = 1e4;
const int D = 1e3;

using namespace std;

#include <unistd.h>
#include <QStringList>
#include <QVariant>
#include <QInputDialog>
#include <QDir>
//#include "number.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <QVariant>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <string>
#include <fstream>


bool incorrect(int num)
{
    int cur = num;
    int correct = cur;
    std::vector<int> t(4);
    for (int i = 0; i < 4; ++i)
    {
        t[i] = cur % 10;
        cur /= 10;
    }
    if ((correct / 1000) == 0)
        return true;
    sort(t.begin(), t.end());
    for (int i = 0; i < 3; ++i)
        if (t[i] == t[i + 1])
            return true;
    return false;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);

    QStringList items;
    items << QInputDialog::tr("Угадывать") << QInputDialog::tr("Загадывать");

    bool ok;
    QWidget *widget = new QWidget();
    widget->setGeometry(100, 0, 1200, 700);
    QString item = QInputDialog::getItem(widget, QInputDialog::tr(""),
                                         QInputDialog::tr("Режим игры:"), items, 0, false, &ok);
    if (ok && !item.isEmpty() && item == QString::fromUtf8("Угадывать"))
    {
        QMainWindow w;
        w.resize(550, 150);
        w.setMinimumHeight(100);
        w.setMinimumWidth(550);

        QPushButton *check = new QPushButton("Угадать", &w);
        check->setGeometry(120, 10, 100, 30);

        QPushButton *show = new QPushButton("Таблица результатов", &w);
        show->setGeometry(320, 10, 200, 30);

        QPushButton *giveup = new QPushButton("Сдаться", &w);
        giveup->setGeometry(220, 10, 100, 30);

        QLineEdit * enter = new QLineEdit(&w);
        enter->setGeometry(10, 10, 90, 30);

        QLabel * out = new QLabel("", &w);
        out->setGeometry(10, 50, 200, 50);

        int correct = 0;
        while (incorrect(correct))
        {
            correct = (unsigned)rand() % MOD;
        }
        cerr << correct << '\n';

        Number * num = new Number(0, correct, &w, giveup, check);
        QObject::connect(check, SIGNAL(clicked()), num, SLOT(refresh()));
        QObject::connect(enter, SIGNAL(textChanged(QString)), num, SLOT(setValue(QString)));
        QObject::connect(num, SIGNAL(printMes(QString)), out, SLOT(setText(QString)));
        QObject::connect(giveup, SIGNAL(clicked()), num, SLOT(newNum()));
        QObject::connect(show, SIGNAL(clicked()), num, SLOT(showTable()));

        w.show();
        return a.exec();
    }
    else if (ok && !item.isEmpty() && item == QString::fromUtf8("Загадывать"))
    {
        QMainWindow w;
        w.resize(550, 150);

        QLabel * quess = new QLabel("Предположение: ", &w);
        quess->setGeometry(10, 0, 400, 50);

        QLabel * showGuess = new QLabel("____", &w);
        showGuess->setGeometry(130, 0, 400, 50);

        QLabel * bulls = new QLabel("Быков: ", &w);
        bulls->setGeometry(10, 35, 200, 30);

        QLineEdit * showBulls = new QLineEdit(&w);
        showBulls->setGeometry(70, 40, 80, 20);

        QLabel * cows = new QLabel("Коров: ", &w);
        cows->setGeometry(10, 65, 200, 30);

        QLineEdit * showCows = new QLineEdit(&w);
        showCows->setGeometry(70, 70, 80, 20);

        QPushButton * answer = new QPushButton("Ответить", &w);
        answer->setGeometry(220, 50, 140, 30);

        QLabel * feedback = new QLabel("Введите число быков и коров", &w);
        feedback->setGeometry(10, 100, 200, 30);

        Key * key = new Key(feedback, showGuess, showCows, showBulls, answer);

        QObject::connect(answer, SIGNAL(clicked()), key, SLOT(check()));

        //QObject::connect(showCows, SIGNAL(textChanged(QString)), key, SLOT(setCows(QString)));

        /*

        QObject::connect(check, SIGNAL(clicked()), num, SLOT(refresh()));
        QObject::connect(enter, SIGNAL(textChanged(QString)), num, SLOT(setValue(QString)));
        QObject::connect(num, SIGNAL(printMes(QString)), out, SLOT(setText(QString)));
        QObject::connect(giveup, SIGNAL(clicked()), num, SLOT(newNum()));
        QObject::connect(show, SIGNAL(clicked()), num, SLOT(showTable()));*/


        w.show();
        return a.exec();
    }

}

