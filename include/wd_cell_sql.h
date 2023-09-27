#ifndef WD_CELL_SQL_H
#define WD_CELL_SQL_H

#include "wd_cell.h"
#include "mysql_handler.h"

class wd_cell_sql: public wd_cell{
    Q_OBJECT
public:
    explicit wd_cell_sql(QWidget *parent = nullptr);

    ~wd_cell_sql() override = default;

    void set_sql_tool(sql_handler::sql_handler<sql_handler::MySQL_Handler> tmp_sql_tools);

    int query(const QString &data);

    void set_model_msg(QStandardItemModel *model_sql, const QString &data);

protected slots:
    void on_btn_start_clicked();

signals:
    // textEdit信号
    void set_text_signal(const QString &data);
    void get_text_signal(QString &data);

protected:
    sql_handler::sql_handler<sql_handler::MySQL_Handler> sql_tools;

};

#endif