#include "wd_tab_page.h"
#include "wd_show_table.h"
#include <QScrollArea>
#include <QTableView>

wd_tab_page::wd_tab_page(QWidget *parent, QStringListModel *model, map_name_sql *connections):
    QScrollArea(parent), combobox_model(model), cur_connections(connections)
{
    setup_ui();
    this->setAttribute(Qt::WA_QuitOnClose, false);
}

wd_tab_page::~wd_tab_page() noexcept {
    qDebug() << "tab:" << this->objectName() << " deleted";
}

void wd_tab_page::setup_ui() {
    // ScrollAreaContent
    this->setObjectName("QScrollArea");
    auto space = new QWidget(); // 占位
    ui_layout = new QVBoxLayout();

    wd_cell_sql *sql_res = create_cell();

    ui = new QWidget();
    ui->setObjectName("QScrollAreaContent");
    ui->resize(1000, 1000);
    this->setWidget(ui);

    space->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    space->setObjectName("space");

    ui_layout->setObjectName("QVBoxLayout");
    ui_layout->addWidget(sql_res);
    ui_layout->setStretchFactor(sql_res, 1);
    ui_layout->addWidget(space);
    ui_layout->setStretchFactor(space, INT16_MAX);

    ui->setLayout(ui_layout);
    this->setWidget(ui);
}

wd_cell_sql *wd_tab_page::create_cell() const {
    auto res = new wd_cell_sql();
    res->setObjectName("cell");
    res->set_combobox_model(combobox_model);
    connect(res, &wd_cell_sql::editor_changed, this, &wd_tab_page::on_act_cell_height_changed);
    connect(res, &wd_cell_sql::tableview_doubleClicked, this, &wd_tab_page::on_act_tableView_double_clicked);
    connect(res, &wd_cell_sql::combobox_changed, this, &wd_tab_page::on_cell_combobox_changed);
    connect(res, &wd_cell_sql::btn_add_clicked, this, &wd_tab_page::insert_cell);
    connect(res, &wd_cell_sql::btn_remove_clicked, this, &wd_tab_page::remove_cell);
    return res;
}

void wd_tab_page::on_act_cell_height_changed(int changed_height) {
    if (!changed_height) return;
    // 获取来源查询单元
    auto *obj = sender();
    if (!obj) {
        qDebug() << obj;
        return;
    }
    // 获取其widget画布
    obj = obj->parent();
    if (!obj) {
        qDebug() << "No Parent";
        return;
    }

    QWidget *scrol_contenter = qobject_cast<QWidget*>(obj);
    if (!scrol_contenter) {
        qDebug() << "convert to widget failed" << scrol_contenter;
        return;
    }
    scrol_contenter->setFixedHeight(scrol_contenter->size().height() + changed_height);
}

void wd_tab_page::on_act_tableView_double_clicked(const QModelIndex &index) {
    qDebug() << "on_act_tableView_double_clicked";
    auto come = sender();
    auto cell = qobject_cast<wd_cell*>(come);
    if (!cell)
        return;
    auto tableview = cell->get_table_view();
    if (!tableview)
        return;
    auto show_model_wd = new wd_show_table();
    show_model_wd->set_model(tableview->model());
    show_model_wd->show();
}

void wd_tab_page::set_sql_model(QStringListModel *model) {
    if(combobox_model)
        combobox_model = model;
}

void wd_tab_page::on_cell_combobox_changed(const QString &data) {
    auto cell = qobject_cast<wd_cell_sql*>(sender());
    if (!cell) return;
    if (cur_connections->contains(data))
        cell->set_sql_tool(cur_connections->value(data));
    else {
        cell->get_combobox_select()->setCurrentIndex(0);
        cell->reset_tool();
    }
}

void wd_tab_page::insert_cell() {
    auto cell = qobject_cast<wd_cell_sql*>(sender());
    if (!cell) return;
    auto index = ui_layout->indexOf(cell);
    if (index != -1){
        auto new_cell = create_cell();
        ui_layout->insertWidget(index + 1, new_cell);
        ui_layout->setStretchFactor(new_cell, 1);
    }
}

void wd_tab_page::remove_cell() {
    auto cell = qobject_cast<wd_cell_sql*>(sender());
    if (!cell) return;
    if (ui_layout->count() <= 2) return;
    ui_layout->removeWidget(cell);
    cell->deleteLater();
}
