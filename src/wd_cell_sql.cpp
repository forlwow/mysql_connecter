#include "wd_cell_sql.h"
#include "ui_wd_cell.h"
#include "transfer.hpp"

wd_cell_sql::wd_cell_sql(QWidget *parent) :
    wd_cell(parent)
{
    connect(ui->btn_start, &QPushButton::clicked, this, &wd_cell_sql::on_btn_start_clicked);
    // 避免崩溃，需要使用信号来调用
    connect(this, &wd_cell_sql::set_text_signal, this, &wd_cell_sql::set_text);
    connect(this, &wd_cell_sql::get_text_signal, this, &wd_cell_sql::get_text);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableView->setModel(new QStandardItemModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    emit set_text_signal(transfer::chars2qs("USE atguigudb;"));
}

void wd_cell_sql::set_sql_tool(sql_handler::sql_handler<sql_handler::MySQL_Handler> tmp_sql_tools){
    sql_tools = tmp_sql_tools;
}

int wd_cell_sql::query(const QString &data){
    auto model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    if (sql_tools.isNull()) {
        set_model_msg(model, transfer::chars2qs("MYSQL init error"));
        return 3;
    }
    if (!sql_tools.is_connected()){
        set_model_msg(model, transfer::chars2qs("MYSQL connect error"));
        return 1;
    }
    sql_tools.query(model, data);
    return 0;
}

void wd_cell_sql::on_btn_start_clicked(){
    QString text = {};
    emit get_text_signal(text);
    query(text);
}

void wd_cell_sql::set_model_msg(QStandardItemModel *model_sql, const QString &data) {
    model_sql->clear();
    model_sql->setColumnCount(1);
    model_sql->setRowCount(1);
    model_sql->setData(model_sql->index(0, 0), data);
}
