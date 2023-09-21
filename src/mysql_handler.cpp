#include "mysql_handler.h"
#include "transfer.hpp"
#include "global.h"

using sql_handler::MySQL_Handler;

MYSQL *MySQL_Handler::tester = mysql_init(nullptr);

MySQL_Handler::MySQL_Handler(): sql_handler_inner() {
    mysql_connection.reset(mysql_init(nullptr));
}

MySQL_Handler::~MySQL_Handler(){

}

int MySQL_Handler::connect(const QList<QString> &data){
    MYSQL *tmp = mysql_real_connect(
        mysql_connection.get(), 
        transfer::qs2qb(data[CON_IP]),
        transfer::qs2qb(data[CON_USER]),
        transfer::qs2qb(data[CON_PASSWD]),
        transfer::qs2qb(data[CON_DB_NAME]),
        transfer::qs2uint(data[CON_PORT]),
        NULL,
        0
    );
    if (tmp){
        mysql_connection.reset(tmp);
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
        NULL,
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

QStandardItemModel* MySQL_Handler::query(const QString &data){
    QStandardItemModel *model = new QStandardItemModel();
    if (!mysql_query(mysql_connection.get(), transfer::qs2qb(data).data())){
        auto msg = mysql_error(mysql_connection.get());
        model->setData(model->index(0, 0), msg);
        return nullptr;
    }
    result.reset(mysql_store_result(mysql_connection.get()));

    // 结果的行列
    auto row = mysql_num_rows(result.get());
    auto col = mysql_num_fields(result.get());
    int row_int = static_cast<int>(row), col_int = static_cast<int>(col);
    if (row > static_cast<uint64_t>(INTMAX_MAX)) return nullptr;
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
    for (int i = 0; i < col_int; ++i){
        for (int j = 0; j < row_int; ++j){
            cur_row = mysql_fetch_row(result.get());
            model->setData(model->index(i, j), cur_row[i][j], Qt::DisplayRole);
        }
    }
    return model;
}

bool MySQL_Handler::is_connected(){
    if (mysql_connection.get()) return true;
    else return false;
}
