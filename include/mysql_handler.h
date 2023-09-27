#ifndef MYSQL_HANDLER_H_
#define MYSQL_HANDLER_H_

#include "sql_handler.h"
#include "mysql.h"
#include <QScopedPointer>

namespace sql_handler{

struct mysql_connection_deleter{      //自定义的cleanup handler
     static inline void cleanup(MYSQL *pointer){   //需要包含一个cleanup(T *)p)的函数
         if (pointer) {
             mysql_close(pointer);
         }
     }
 };

 struct mysql_result_deleter{
    static inline void cleanup(MYSQL_RES *pointer){
        mysql_free_result(pointer);
    }
 };

class MySQL_Handler: public sql_handler_inner{
public:
    MySQL_Handler();

    ~MySQL_Handler() override;

    int connect(const QList<QString> &data) override;

    static int test_connect(const QList<QString> &data);

    void query(QStandardItemModel *model, const QString &data) override;

    bool is_connected() override;

protected:
    static MYSQL *tester;

    QScopedPointer<MYSQL, mysql_connection_deleter> mysql_connection; // 实际的连接

    QScopedPointer<MYSQL_RES, mysql_result_deleter> result;
};

}
#endif