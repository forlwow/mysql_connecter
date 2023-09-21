#ifndef WD_CELL_SQL_H
#define WD_CELL_SQL_H

#include "wd_cell.h"
#include "mysql_handler.h"

namespace Ui{
    class wd_cell_sql;
}

class wd_cell_sql: public wd_cell{
    Q_OBJECT
public:
    wd_cell_sql(QWidget *parent = nullptr);

    ~wd_cell_sql() override;

    void set_sql_tool(sql_handler::sql_handler<sql_handler::MySQL_Handler> tmp_sql_tools);

    int query(const QString &data);

protected slots:
    void on_btn_start_clicked();

protected:
    QStandardItemModel *model_sql;
    
    sql_handler::sql_handler<sql_handler::MySQL_Handler> sql_tools;

};

#endif