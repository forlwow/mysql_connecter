#include "wd_cell_sql.h"
#include "ui_wd_cell.h"
#include "transfer.hpp"
#include <QListView>

wd_cell_sql::wd_cell_sql(QWidget *parent) :
    wd_cell(parent), sql_tools()
{
    // 避免崩溃，需要使用信号来调用
    connect(this, &wd_cell_sql::set_text_signal, this, &wd_cell_sql::set_text);
    connect(this, &wd_cell_sql::get_text_signal, this, &wd_cell_sql::get_text);

    connect(ui->btn_start, &QPushButton::clicked, this, &wd_cell_sql::on_btn_start_clicked);

    // 添加ComboBox
    select_sql = new QComboBox;
    select_sql->setObjectName("ComboBbox_select_sql");
    select_sql->setMinimumWidth(font_size * 6);
    ui->layout_bottom->insertWidget(0, select_sql);
    connect(select_sql, &QComboBox::currentIndexChanged, this, &wd_cell_sql::on_combobox_changed);
    select_sql->setView(new QListView);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableView->setModel(new QStandardItemModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    emit set_text_signal(transfer::chars2qs("USE atguigudb;"));

    qDebug() << "create cell";
}

void wd_cell_sql::set_sql_tool(const sql_handler::sql_handler& tmp_sql_tools) {
    sql_tools = tmp_sql_tools;
}

int wd_cell_sql::query(const QString &data){
    auto model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    if (sql_tools.isNull()) {
        set_model_msg(model, transfer::chars2qs("MYSQL init error"));
        return 3;
    }
    if (!sql_tools->is_connected()){
        set_model_msg(model, transfer::chars2qs("MYSQL connect error"));
        return 1;
    }
    sql_tools->query(model, data);
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

void wd_cell_sql::set_combobox_model(QStringListModel *model) {
    select_sql->setModel(model);
}

void wd_cell_sql::on_combobox_changed(int index) {
    auto comboBox = get_combobox_select();
    QString text = comboBox->model()->data(comboBox->model()->index(index, 0)).toString();
    emit combobox_changed(text);
}

void wd_cell_sql::update_combobox(const QStringList &data) {
//    auto combobox = get_combobox_select();

    // TODO
}

void wd_cell_sql::reset_tool() {
    sql_tools = {};
}
