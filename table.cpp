#include "table.h"


Table::Table(const std::string &name) {
    filename = name;
    load();
}


bool Table::load(int32_t cnt) {
    std::ifstream fin(filename);
    table.clear();
    if (fin.fail()) {
        return true;
    }
    std::string s;
    while (getline(fin, s)) {
        int32_t rating = 0;
        int32_t pos = 0;
        while (s[pos] != '|') {
            rating = rating * 10 + (s[pos] - '0');
            pos++;
        }
        std::string name = s.substr(pos + 1, s.size());
        table.emplace_back(rating, name);
    }
    fin.close();
    return table.size() < 5 || cnt < table.back().first;
}


void Table::save() {
    std::ofstream fout(filename);
    for (const auto &x : table) {
        fout << x.first << "|" << x.second << '\n';
    }
    fout.close();
}


void Table::add(int32_t pts, const QString &qs) {
    std::string name = qs.toUtf8().constData();
    if (table.size() < 5 || table.back().first > pts) {
        if (table.size() == 5) {
            table.pop_back();
        }
        table.emplace_back(pts, name);
        sort(table.begin(), table.end());
    }
    save();
}


std::vector<std::pair<QString, int32_t>> Table::get_results() {
    load();
    std::vector<std::pair<QString, int32_t>> res;
    for (const auto &x : table) {
        res.push_back(std::make_pair(QString::fromUtf8(x.second.c_str()), x.first));
    }
    return res;
}
