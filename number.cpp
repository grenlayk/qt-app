#include "number.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <QVariant>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <string>
#include <fstream>

using namespace std;

const int D = 1e3;
const int MOD = 1e4;
const int INF = 1e9;
bool cor = false;
int last = -1;
int cnt = 0;
bool nowWin = false;
bool cor2 = false;
bool nowWin2 = false;

struct Table {

    string filename;
    vector< pair<int, string> > table;

    bool load(int cnt = INF) {
        ifstream fin(filename);
        table.clear();
        if (fin.fail()) {
            return true;
        }
        string s;
        while (getline(fin, s)) {
            int rating = 0;
            int pos = 0;
            while (s[pos] != '|') {
                rating = rating * 10 + (s[pos] - '0');
                pos++;
            }
            string name = s.substr(pos + 1, s.size());
            table.emplace_back(rating, name);
        }
        fin.close();
        return table.size() < 5 || cnt < table.back().first;
    }

    Table(const string & name){
        filename = name;
        load();
    }

    void save() {
        ofstream fout(filename);
        for (const auto & x : table) {
            fout << x.first << "|" << x.second << '\n';
        }
        fout.close();
    }


    void add(int pts, const QString & qs) {
        string name = qs.toUtf8().constData();
        if (table.size() < 5 || table.back().first > pts) {
            if (table.size() == 5) {
                table.pop_back();
            }
            table.emplace_back(pts, name);
            sort(table.begin(), table.end());
        }
        save();
    }


    vector< pair<QString, int> > get_results() {
        load();
        vector< pair<QString, int> > res;
        for (const auto & x : table) {
            res.push_back(make_pair(QString::fromUtf8(x.second.c_str()), x.first));
        }
        return res;
    }
}

res_table("table.txt");

void Number :: setValue(int val)
{
    m_data = val;
    std::cout << m_data << std::endl;
    QString S;
    S.setNum(m_data);
    emit valueChanged(m_data);
    emit valueChanged(S);
}

void Number::setValue(QString val)
{
    int val_int;
    bool ok;
    while(val.size() != 0 && val.back() == ' ')
        val.resize((int)val.size() - 1);
    val_int = val.toInt(&ok);
    cor = (ok && val_int / D != 0 && val_int / MOD == 0) && !incorrect(val_int) && val_int > 0 && ((int)val.size() == 4 || (int)val.size() == 5 && val[0] == '+');
    if (cor)
    {
         setValue(val_int);
    }
}

bool Number::incorrect(int num)
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

int Number::cnt_cows(int a, int b)
{
    std::vector<int> cnt(10);
    for (int i = 0; i < 4; ++i)
    {
        if (b % 10 != a % 10)
        {
            int nu = a % 10;
            cnt[nu]++;
            nu = b % 10;
            cnt[nu]++;
        }
        a /= 10;
        b /= 10;
    }
    int ans = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (cnt[i] > 1)
            ans++;
    }
    return ans;
}

int Number::cnt_bulls(int a, int b)
{
    int ans = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (b % 10 == a % 10)
        {
            ans++;
        }
        a /= 10;
        b /= 10;
    }
    return ans;
}

void Number::refresh()
{
    QString mes;
    if (correct == m_data)
    {
        ++cnt;
        mes = "Right answer!\nNumber of moves: " + QString::number(cnt);
        giveup->setText("Restart game");
        check->setEnabled(false);
        nowWin = true;
        bool ok;
        if (res_table.load(cnt))
        {
            QString text = QInputDialog::getText(w, tr("Right answer!\n"), tr("Enter your name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
            {
                res_table.add(cnt, text);
            }
        }
    }
    else if (cor)
    {
        if (last != m_data)
            ++cnt;
        int bulls = cnt_bulls(m_data, correct);
        int cows = cnt_cows(m_data, correct);
        QString b = QString::number(bulls);
        QString c = QString::number(cows);
        last = m_data;
        mes = "Bulls: " + b + "\n" + "Cows: " + c + "\n";
    }
    else
    {
        mes = "Incorrect number";
    }
    emit printMes(mes);
}

void Number::newNum()
{
    QString mes = "";
    if (nowWin)
    {
        giveup->setText("Give Up");
        check->setEnabled(true);
        nowWin = false;
    }
    else
    {
        mes = "Right number: " + QString::number(correct);
    }
    emit printMes(mes);
    int newcorrect = 0;
    last = -1;
    cnt = 0;
    while (incorrect(newcorrect))
    {
        newcorrect = (unsigned)rand() % MOD;
    }
    correct = newcorrect;
    std::cerr << correct << '\n';
}

void Number :: showTable()
{
    QMessageBox msgBox;
    QString mes;
    vector< pair<QString, int> > arr = res_table.get_results();
    int i = 1;
    mes += "Place. Name - Points\n";
    for (pair<QString, int>  x : arr)
    {
        string name = x.first.toUtf8().constData();
        mes += QString::number(i) + ". " + x.first + " - " + QString::number(x.second) + "\n";
        ++i;
    }
    msgBox.setText(mes);
    msgBox.exec();
}

int Key :: correct_data(QString val)
{
    int val_int;
    bool ok;

    while(val.size() != 0 && val.back() == ' ')
        val.resize((int)val.size() - 1);
    if (val.size() == 0)
        return 0;
    val_int = val.toInt(&ok);
    cor2 = (ok && val_int < 5 && val_int >= 0);
    if (cor2)
         return val_int;
    else
        return -1;
}

int Key::cnt_bulls(int a, int b)
{
    int ans = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (b % 10 == a % 10)
        {
            ans++;
        }
        a /= 10;
        b /= 10;
    }
    return ans;
}

int Key::cnt_cows(int a, int b)
{
    std::vector<int> cnt(10);
    for (int i = 0; i < 4; ++i)
    {
        if (b % 10 != a % 10)
        {
            int nu = a % 10;
            cnt[nu]++;
            nu = b % 10;
            cnt[nu]++;
        }
        a /= 10;
        b /= 10;
    }
    int ans = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (cnt[i] > 1)
            ans++;
    }
    return ans;
}

void Key :: newGame()
{
    answer->setText("Restart game");
    nowWin = false;

}

void Key :: setNew()
{
    answer->setText("Reply");
    feedback->setText("Enter the quantity bulls and cows");
    correct.clear();
    for (int i = 1000; i < 10000; ++i)
    {
        if (!incorrect(i))
            correct.insert(i);
    }
    cur = *correct.begin();
    correct.erase(correct.begin());
    guess->setText(QString::number(cur));
}

void Key :: check()
{
    if (nowWin2)
    {
        setNew();
        nowWin2 = false;
        return;
    }
    QString s1 = cows->text();
    QString s2 = bulls->text();
    cur_cows = correct_data(s1);
    cur_bulls = correct_data(s2);
    if (cur_cows == -1 || cur_bulls == -1)
    {
        feedback->setText("Incorrect input");
        return;
    }
    else if (cur_cows + cur_bulls > 4)
    {
        feedback->setText("Incorrect input");
        return;
    }
    else
    {
        feedback->setText("Enter the quantity bulls and cows");
        if (cur_bulls == 4)
        {
            feedback->setText("Your number: " + QString::number(cur));
            nowWin2 = true;
            newGame();
            return;
        }

        std :: set <int> new_correct;
        for (auto x : correct)
        {
            if (cnt_bulls(x, cur) == cur_bulls && cnt_cows(x, cur) == cur_cows)
            {
                new_correct.insert(x);
            }
        }
        if (new_correct.empty())
        {
            feedback->setText("You lied!");
            nowWin2 = true;
            newGame();
            //restart
        }
        else
        {
            correct = new_correct;
            cur = *correct.begin();
            correct.erase(correct.begin());
            guess->setText(QString::number(cur));
        }
    }
}



