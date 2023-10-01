#include "mysql_handler.h"
#include "transfer.hpp"
#include "global.h"


using sql_handler::MySQL_Handler;

// 初始化静态测试连接对象
MYSQL *MySQL_Handler::tester = mysql_init(nullptr);

MySQL_Handler::MySQL_Handler():
    sql_handler_inner(),
    mysql_connection(nullptr),
    result(nullptr)
{

}

MySQL_Handler::~MySQL_Handler(){
    qDebug() << transfer::chars2qs("Delete MySQL_Handler");
}

int MySQL_Handler::connect(const QList<QString> &data){
    if (is_connected()) return 2; // 防止重复连接
    mysql_connection.reset(mysql_init(nullptr)); // 新建连接信息
    MYSQL *tmp = mysql_real_connect(
        mysql_connection.get(),
        transfer::qs2qb(data[CON_IP]),
        transfer::qs2qb(data[CON_USER]),
        transfer::qs2qb(data[CON_PASSWD]),
        transfer::qs2qb(data[CON_DB_NAME]),
        transfer::qs2uint(data[CON_PORT]),
        nullptr,
        0
    );
    if (tmp){
        // 如果连接成功，则重设连接
        mysql_connection.reset(tmp);//
        return 0;
    }
    else{
        return 1;
    }
}

int MySQL_Handler::test_connect(const QList<QString> &data){
    mysql_init(tester);
    MYSQL *tmp_test = mysql_real_connect(
        tester, 
        transfer::qs2qb(data[CON_IP]),
        transfer::qs2qb(data[CON_USER]),
        transfer::qs2qb(data[CON_PASSWD]),
        transfer::qs2qb(data[CON_DB_NAME]),
        transfer::qs2uint(data[CON_PORT]),
        nullptr,
        0
    );
    int res = 0;
    if (tmp_test){
        res = 0;
    }
    else{
        res =  1;
    }
    mysql_close(tmp_test);
    return res;
}

void MySQL_Handler::query(QStandardItemModel* model, const QString &data){
    model->clear();
    model->setColumnCount(1); model->setRowCount(1);
    int query_stat = mysql_query(mysql_connection.get(), transfer::qs2qb(data).data());
    if (query_stat){
        auto msg = mysql_error(mysql_connection.get());
        QString qmsg = transfer::chars2qs(msg);
        if (qmsg.isEmpty()) qmsg = transfer::chars2qs("OK");
        model->setData(model->index(0, 0), qmsg);
        return;
    }
    // 取结果
    auto mr = mysql_store_result(mysql_connection.get());
    result.reset(mr);
    if (!mr){
        auto msg = mysql_error(mysql_connection.get());
        QString qmsg = transfer::chars2qs(msg);
        if (qmsg.isEmpty()) qmsg = transfer::chars2qs("OK");
        model->setData(model->index(0, 0), qmsg);
        return ;
    }

    // 结果的行列
    auto row = mysql_num_rows(result.get());
    auto col = mysql_num_fields(result.get());
    int row_int = static_cast<int>(row), col_int = static_cast<int>(col);
    if (row > static_cast<uint64_t>(INTMAX_MAX)) return ;
    model->setRowCount(row_int);
    model->setColumnCount(col_int);

    // 标题栏
    MYSQL_FIELD *header_raw = mysql_fetch_field(result.get());
    QStringList header;
    for (int i = 0; i < col_int; i++){
        header.emplace_back(header_raw[i].name);
    }
    model->setHorizontalHeaderLabels(header);

    MYSQL_ROW cur_row;
    for (int i = 0; i < row_int; ++i){
        cur_row = mysql_fetch_row(result.get());
        for (int j = 0; j < col_int; ++j){
            model->setData(model->index(i, j), cur_row[j], Qt::DisplayRole);
        }
    }
    return ;
}

bool MySQL_Handler::is_connected(){
    if (mysql_connection.isNull()) return false;
    auto stat = mysql_stat(mysql_connection.get());
    QString st = transfer::chars2qs(stat);
    if (st.first(4) != transfer::chars2qs("Lost")) return true;
    else return false;
}

void sql_handler::MySQL_Handler::disconnect() {
    mysql_connection.reset(nullptr);
    result.reset(nullptr);
}
