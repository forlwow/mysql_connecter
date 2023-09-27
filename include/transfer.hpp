#ifndef __TRANSFER_H_
#define __TRANSFER_H_

#include <QSet>
#include <QStringList>
#include <QByteArray>
#include <vector>
#include <string>
#include <unordered_set>

#include "connections_handler.h"
#include "mysql_handler.h"
#include "boost/locale.hpp"

namespace transfer
{

using std::vector;
using std::string;
using std::unordered_set;

// UTF-8 String => Unicode String
inline string utf2locale(const string &data){
    auto locale_string = QString::fromUtf8(data).toLocal8Bit();
    return locale_string.toStdString();
}

// QStringList => vector<string>
inline vector<string> qslist2stdsvector(const QStringList &data){
    vector<string> res;
    for (auto &i : data){
        res.emplace_back(i.toLocal8Bit());
    }
    return res;
}

// vector<string> => QStringList
inline QStringList stdsvector2qslist(const vector<string> &data){
    QStringList res;
    for (auto &i : data){
        res.push_back(QString::fromLocal8Bit(i.data()));
    }
    return res;
}

// QSet<QString> => unordered_set<string>
inline unordered_set<string> qset2stdset(const QSet<QString> &data){
    unordered_set<string> res;
    for (const QString &i : data){
        res.insert(string(i.toLocal8Bit()));
    }
    return res;
}

// unordered_set<string> => QSet<QString>
inline QSet<QString> stdset2qset(const unordered_set<string> &data){
    QSet<QString> res;
    for (const string &i : data){
        res.insert(QString::fromLocal8Bit(i.data()));
    }
    return res;
}

template<typename T>
inline unordered_set<T> qset2stdset(const QSet<T> data){
    unordered_set<T> res;
    for (const T &i : data){
        res.insert(i);
    }
    return res;
}

template<typename T>
inline QSet<T> stdset2qset(const unordered_set<T> data){
    QSet<T> res;
    for (const T &i : data){
        res.insert(i);
    }
    return res;
}

// QString => QBtyeArray
inline QByteArray qs2qb(const QString &data){
    return data.toLocal8Bit();
}

inline QString chars2qs(const char* data){
    return QString::fromLocal8Bit(data);
}

inline unsigned int qs2uint(const QString &data){
    return data.toLocal8Bit().toUInt();
}

inline sql_handler::sql_handler<sql_handler::MySQL_Handler> get_mysql_connection(const QString &name){
    sql_handler::sql_handler<sql_handler::MySQL_Handler> res;
    res.create_new_sql();
    if (res.isNull()) return {};
    // 使用qs2qb防止乱码
    QStringList con_data = stdsvector2qslist(con_handler::get_con_data(qs2qb(name).data()));
    if (con_data.size() != con_handler::CON_DATA_SIZE) return {};
    res.connect(con_data);
    if (res.is_connected())
    {
        return res;
    }
    else{
        return {};
    }
}

} // namespace transfer






#endif