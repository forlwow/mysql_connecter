#ifndef SQL_HANDLER_H_
#define SQL_HANDLER_H_

#include <QString>
#include <QStandardItemModel>
#include <QList>
#include <QSharedPointer>

namespace sql_handler{

class sql_handler_inner{
public:
    sql_handler_inner() = default;
    virtual ~sql_handler_inner() = default;

    virtual void query(QStandardItemModel *model, const QString &data) = 0;

    virtual bool is_connected() = 0;

    virtual int connect(const QList<QString> &data) = 0;

    virtual void disconnect() = 0;
};

typedef QSharedPointer<sql_handler_inner> sql_handler;

//template<typename T>
//class sql_handler{
//protected:
//    QSharedPointer<sql_handler_inner> ptr_sql_handler;
//
//public:
//    sql_handler() :ptr_sql_handler() {}
//
//    ~sql_handler() {qDebug() << "delete sql_handler";};
////    ~sql_handler() = default;
//
//    void create_new_sql(){
//        ptr_sql_handler.reset(new T);
//    }
//
//    bool isNull(){
//        return ptr_sql_handler.isNull();
//    }
//
//    sql_handler_inner *get(){
//        return ptr_sql_handler.get();
//    }
//
//    void query(QStandardItemModel *model, const QString &data){
//        return ptr_sql_handler->query(model, data);
//    }
//
//    int connect(const QList<QString> &data){
//        return ptr_sql_handler->connect(data);
//    }
//
//    bool is_connected(){
//        return ptr_sql_handler->is_connected();
//    }
//
//    void disconnect(){
//        return ptr_sql_handler->disconnect();
//    }
//
//};

}
#endif