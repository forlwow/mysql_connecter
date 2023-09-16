#ifndef __MYSQL_HANDLER_H_
#define __MYSQL_HANDLER_H_

#include "sql_handler.h"
#include "mysql.h"
#include "QScopedPointer"

namespace sql_handler{

struct mysql_connection_deleter{      //自定义的cleanup handler
     static inline void cleanup(MYSQL *pointer){   //需要包含一个cleanup(T *)p)的函数
         mysql_close(pointer);
     }
 };

 struct mysql_result_deleter{
    static inline void cleanup(MYSQL_RES *pointer){
        mysql_free_result(pointer);
    }
 };

class MySQL_Handler: public sql_handler{
public:
    MySQL_Handler();

    ~MySQL_Handler() override;

    int connect(const QList<QString> &data) override;

    int test_connect(const QList<QString> &data) override;

    QStandardItemModel* query(const QString &data) override;

protected:
    static MYSQL *tester;

    QScopedPointer<MYSQL, mysql_connection_deleter> mysql_connection;
    
    QScopedPointer<MYSQL_RES, mysql_result_deleter> result;
};

}
#endif