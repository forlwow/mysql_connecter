#ifndef __SQL_HANDLER_H_
#define __SQL_HANDLER_H_

#include <QString>
#include <QStandardItemModel>
#include <QList>

namespace sql_handler{

class sql_handler{
public:
    sql_handler() = default;
    virtual ~sql_handler() = default;

    virtual QStandardItemModel* query(const QString &data) = 0;

    virtual int connect(const QList<QString> &data) = 0 ;

    virtual int test_connect(const QList<QString> &data) = 0;
};

}
#endif