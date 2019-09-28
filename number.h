#ifndef NUMBER_H
#define NUMBER_H

#include <QObject>
#include <QPushButton>
#include <QMainWindow>
#include <QFile>
#include <QLineEdit>

class Number : public QObject
{
    Q_OBJECT
private:
    int m_data;
    int correct;
    QPushButton* giveup;
    QMainWindow* w;
    QPushButton* check;

public:
    explicit Number(QObject *parent = 0);
    Number(int data_, int correct_, QMainWindow* w_, QPushButton* giveup_, QPushButton*  check_)
    {
        m_data = data_;
        correct = correct_;
        w = w_;
        giveup = giveup_;
        check = check_;
    }

signals:
    void valueChanged(int);
    void valueChanged(QString);
    void valueNew(int);
    void printMes(QString);   

public slots:
    void setValue(int);
    void setValue(QString);
    void refresh();
    bool incorrect(int);
    int cnt_cows(int, int);
    int cnt_bulls(int, int);
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


class Key :  public QObject
{
    Q_OBJECT
private:

    QPushButton * answer;
    QLabel * feedback;
    QLabel * guess;
    QLineEdit * cows;
    QLineEdit * bulls;
    int cur;
    int cur_bulls;
    int cur_cows;
    std :: set <int> correct;

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
        sort(t.begin(), t.end());
        for (int i = 0; i < 3; ++i)
            if (t[i] == t[i + 1])
                return true;
        return false;
    }

public:
    explicit Key(QObject *parent = 0);
    Key(QLabel* fb, QLabel * sg, QLineEdit * sc, QLineEdit * sb, QPushButton * ans)
    {
        feedback = fb;
        guess = sg;
        bulls = sb;
        cows = sc;
        cur_bulls = 0;
        cur_cows = 0;
        answer = ans;
        for (int i = 1000; i < 10000; ++i)
        {
            if (!incorrect(i))
                correct.insert(i);
        }
        cur = *correct.begin();
        correct.erase(correct.begin());
        guess->setText(QString::number(cur));
    }

signals:
    void valueChanged(int);
    void valueChanged(QString);
    void valueNew(int);
    void printMes(QString);

public slots:

    int correct_data(QString);
    void check();

    int cnt_cows(int, int);
    int cnt_bulls(int, int);

    void newGame();

    void setNew();
    //void setBulls(int);
    //void setBulls(QString);

    /*void refresh();
    bool incorrect(int);

    int cnt_bulls(int, int);*/
    //void newNum();
};

#endif // KEY_H



