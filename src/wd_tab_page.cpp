#include "wd_tab_page.h"
#include "wd_show_table.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTableView>

wd_tab_page::wd_tab_page(QWidget *parent):
    QScrollArea(parent)
{
    setup_ui();
    this->setAttribute(Qt::WA_QuitOnClose, false);
}

wd_tab_page::~wd_tab_page() noexcept {
    qDebug() << "tab:" << this->objectName() << " deleted";
}

void wd_tab_page::setup_ui() {
    wd_cell_sql *sql_res = create_cell();
    wd_cell_sql *sql_res2 = create_cell();

    this->setObjectName("QScrollArea");
    auto scol_content = new QWidget();
    scol_content->setObjectName("QScrollAreaContent");
    scol_content->resize(1000, 1000);
    this->setWidget(scol_content);

    auto space = new QWidget();
    space->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    space->setObjectName("space");

    auto vlayout = new QVBoxLayout();
    vlayout->setObjectName("QVBoxLayout");
    vlayout->addWidget(sql_res);
    vlayout->setStretchFactor(sql_res, 1);
    vlayout->addWidget(sql_res2);
    vlayout->setStretchFactor(sql_res2, 1);
    vlayout->addWidget(space);
    vlayout->setStretchFactor(space, INT16_MAX);

    scol_content->setLayout(vlayout);
    this->setWidget(scol_content);
}

wd_cell_sql *wd_tab_page::create_cell() const {
    auto res = new wd_cell_sql();
    res->setObjectName("cell");
    connect(res, &wd_cell_sql::editor_changed, this, &wd_tab_page::on_act_cell_height_changed);
    connect(res, &wd_cell_sql::tableview_doubleClicked, this, &wd_tab_page::on_act_tableView_double_clicked);
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
