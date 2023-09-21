#include "wd_cell_sql.h"
#include "ui_wd_cell.h"

wd_cell_sql::wd_cell_sql(QWidget *parent) :
    wd_cell(parent)
{
    connect(ui->btn_start, &QPushButton::clicked, this, &wd_cell_sql::on_btn_start_clicked);
}

wd_cell_sql::~wd_cell_sql(){

}

void wd_cell_sql::set_sql_tool(sql_handler::sql_handler<sql_handler::MySQL_Handler> tmp_sql_tools){
    sql_tools = tmp_sql_tools;
}

int wd_cell_sql::query(const QString &data){
    if (sql_tools.isNull()) return 3;
    if (!sql_tools.is_connected()){
        return 1;
    }
    model_sql = sql_tools.query(data);
    if (model_sql) return 0;
    else return 2;
}

void wd_cell_sql::on_btn_start_clicked(){
    QString text = ui->text_input->toPlainText();
    int res = query(text);
    if (!res){
        ui->tableView->setModel(model_sql);
    }
}
