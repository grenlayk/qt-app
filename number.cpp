#include "number.h"

int32_t lastInput = -1;
int32_t moves = 0;
bool isCorrect = false;
bool isVictory = false;


Table res_table("table.txt");


void Number::setValue(int32_t input) {
    m_data = input;
    std::cerr << m_data << std::endl;
    QString newValue;
    newValue.setNum(m_data);
    emit valueChanged(m_data);
    emit valueChanged(newValue);
}


void Number::setValue(QString input) {
    int32_t intValue;
    bool isInt;
    while (input.size() != 0 && input.back() == ' ') {
        input.resize((int32_t)input.size() - 1);
    }
    intValue = input.toInt(&isInt);
    isCorrect = (isInt && intValue > BORD && intValue < MOD) && !isIncorrect(intValue) &&
          ((int32_t)input.size() == SZ || ((int32_t)input.size() == SZ + 1 && input[0] == '+'));
    if (isCorrect) {
        setValue(intValue);
    }
}


int32_t Number::cntCows(int32_t ourNumber, int32_t trueNumber) {
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


int32_t Number::cntBulls(int32_t ourNumber, int32_t trueNumber) {
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


void Number::refresh() {
    QString message;
    if (correct == m_data) {
        ++moves;
        message = "Right answer!\nNumber of moves: " + QString::number(moves);
        giveup->setText("Restart game");
        check->setEnabled(false);
        isVictory = true;
        bool okClicked;
        if (res_table.load(moves)) {
            QString text = QInputDialog::getText(w, tr("Right answer!\n"), tr("Enter your name:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &okClicked);
            if (okClicked && !text.isEmpty()) {
                res_table.add(moves, text);
            }
        }
    } else if (isCorrect) {
        if (lastInput != m_data) {
            ++moves;
        }
        int32_t bulls = cntBulls(m_data, correct);
        int32_t cows = cntCows(m_data, correct);
        lastInput = m_data;
        message = "Bulls: " + QString::number(bulls) + "\n" + "Cows: " + QString::number(cows) + "\n";
    } else {
        message = "Incorrect number";
    }
    emit printMes(message);
}


void Number::newNum() {
    QString message = "";
    if (isVictory) {
        giveup->setText("Give Up");
        check->setEnabled(true);
        isVictory = false;
    } else {
        message = "Right number: " + QString::number(correct);
    }
    emit printMes(message);
    lastInput = -1;
    moves = 0;
    correct = genNumber();
    std::cerr << correct << '\n';
}


void Number::showTable() {
    QMessageBox msgBox;
    QString message;
    std::vector <std::pair<QString, int32_t>> scoreTable = res_table.get_results();
    int32_t place = 1;
    message += "Place. Name - Points\n";
    for (std::pair<QString, int32_t> user : scoreTable) {
        std::string name = user.first.toUtf8().constData();
        message += QString::number(place) + ". " + user.first + " - " + QString::number(user.second) + "\n";
        ++place;
    }
    msgBox.setText(message);
    msgBox.exec();
}

