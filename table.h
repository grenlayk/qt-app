#ifndef TABLE_H
#define TABLE_H

#include "gennumber.h"
#include <QString>

class Table
{
 public:
    std::string filename;
    std::vector <std::pair<int32_t, std::string>> table;

    Table(const std::string &name);

    bool load(int32_t cnt = INF);

    void save();

    void add(int32_t pts, const QString &qs);

    std::vector <std::pair<QString, int32_t >> get_results();
};


#endif // TABLE_H
