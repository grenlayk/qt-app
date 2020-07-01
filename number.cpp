#include "number.h"

int32_t last = -1;
int32_t cnt = 0;
bool isCorrect = false;
bool nowWin = false;
bool cor2 = false;
bool nowWin2 = false;


Table res_table("table.txt");


void Number::setValue(int32_t input) {
    m_data = input;
    std::cout << m_data << std::endl;
    QString S;
    S.setNum(m_data);
    emit valueChanged(m_data);
    emit valueChanged(S);
}


void Number::setValue(QString input) {
    int32_t intValue;
    bool isInt;
    while (input.size() != 0 && input.back() == ' ')
        input.resize((int32_t)input.size() - 1);
    intValue = input.toInt(&isInt);
    isCorrect = (isInt && intValue > BORD && intValue < MOD) && !isIncorrect(intValue) &&
          ((int32_t)input.size() == 4 || (int32_t)input.size() == 5 && input[0] == '+');
    if (isCorrect) {
        setValue(intValue);
    }
}


int32_t Number::cntCows(int32_t a, int32_t b) {
    std::vector<int32_t> cnt(10);
    for (int32_t i = 0; i < 4; ++i) {
        if (b % 10 != a % 10) {
            int32_t nu = a % 10;
            cnt[nu]++;
            nu = b % 10;
            cnt[nu]++;
        }
        a /= 10;
        b /= 10;
    }
    int32_t ans = 0;
    for (int32_t i = 0; i < 10; ++i) {
        if (cnt[i] > 1)
            ans++;
    }
    return ans;
}


int32_t Number::cntBulls(int32_t a, int32_t b) {
    int32_t ans = 0;
    for (int32_t i = 0; i < 4; ++i) {
        if (b % 10 == a % 10) {
            ans++;
        }
        a /= 10;
        b /= 10;
    }
    return ans;
}


void Number::refresh() {
    QString mes;
    if (correct == m_data) {
        ++cnt;
        mes = "Right answer!\nNumber of moves: " + QString::number(cnt);
        giveup->setText("Restart game");
        check->setEnabled(false);
        nowWin = true;
        bool ok;
        if (res_table.load(cnt)) {
            QString text = QInputDialog::getText(w, tr("Right answer!\n"), tr("Enter your name:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty()) {
                res_table.add(cnt, text);
            }
        }
    } else if (isCorrect) {
        if (last != m_data)
            ++cnt;
        int32_t bulls = cntBulls(m_data, correct);
        int32_t cows = cntCows(m_data, correct);
        QString b = QString::number(bulls);
        QString c = QString::number(cows);
        last = m_data;
        mes = "Bulls: " + b + "\n" + "Cows: " + c + "\n";
    } else {
        mes = "Incorrect number";
    }
    emit printMes(mes);
}


void Number::newNum() {
    QString mes = "";
    if (nowWin) {
        giveup->setText("Give Up");
        check->setEnabled(true);
        nowWin = false;
    } else {
        mes = "Right number: " + QString::number(correct);
    }
    emit printMes(mes);
    last = -1;
    cnt = 0;
    correct = genNumber();
    std::cerr << correct << '\n';
}


void Number::showTable() {
    QMessageBox msgBox;
    QString mes;
    std::vector <std::pair<QString, int32_t>> arr = res_table.get_results();
    int32_t i = 1;
    mes += "Place. Name - Points\n";
    for (std::pair<QString, int32_t> x : arr) {
        std::string name = x.first.toUtf8().constData();
        mes += QString::number(i) + ". " + x.first + " - " + QString::number(x.second) + "\n";
        ++i;
    }
    msgBox.setText(mes);
    msgBox.exec();
}


int32_t Key::correct_data(QString val) {
    int32_t val_int;
    bool ok;

    while (val.size() != 0 && val.back() == ' ')
        val.resize((int) val.size() - 1);
    if (val.size() == 0)
        return 0;
    val_int = val.toInt(&ok);
    cor2 = (ok && val_int < 5 && val_int >= 0);
    if (cor2)
        return val_int;
    else
        return -1;
}


int32_t Key::cntBulls(int32_t a, int32_t b) {
    int32_t ans = 0;
    for (int32_t i = 0; i < 4; ++i) {
        if (b % 10 == a % 10) {
            ans++;
        }
        a /= 10;
        b /= 10;
    }
    return ans;
}


int32_t Key::cntCows(int32_t a, int32_t b) {
    std::vector<int32_t> cnt(10);
    for (int32_t i = 0; i < 4; ++i) {
        if (b % 10 != a % 10) {
            int32_t nu = a % 10;
            cnt[nu]++;
            nu = b % 10;
            cnt[nu]++;
        }
        a /= 10;
        b /= 10;
    }
    int32_t ans = 0;
    for (int32_t i = 0; i < 10; ++i) {
        if (cnt[i] > 1)
            ans++;
    }
    return ans;
}


void Key::newGame() {
    answer->setText("Restart game");
    nowWin = false;
}


void Key::setNew() {
    answer->setText("Reply");
    feedback->setText("Enter the quantity bulls and cows");
    correct.clear();
    for (int32_t i = 1000; i < 10000; ++i) {
        if (!isIncorrect(i))
            correct.insert(i);
    }
    cur = *correct.begin();
    correct.erase(correct.begin());
    guess->setText(QString::number(cur));
}


void Key::check() {
    if (nowWin2) {
        setNew();
        nowWin2 = false;
        return;
    }
    QString s1 = cows->text();
    QString s2 = bulls->text();
    curCows = correct_data(s1);
    curBulls = correct_data(s2);
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
            nowWin2 = true;
            newGame();
            return;
        }

        std::set<int32_t> new_correct;
        for (auto x : correct) {
            if (cntBulls(x, cur) == curBulls && cntCows(x, cur) == curCows) {
                new_correct.insert(x);
            }
        }
        if (new_correct.empty()) {
            feedback->setText("You lied!");
            nowWin2 = true;
            newGame();
            //restart
        } else {
            correct = new_correct;
            cur = *correct.begin();
            correct.erase(correct.begin());
            guess->setText(QString::number(cur));
        }
    }
}
