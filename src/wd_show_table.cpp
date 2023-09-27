#include "wd_show_table.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QAbstractItemModel>

wd_show_table::wd_show_table(QWidget *parent):
    QDialog(parent), layout(new QVBoxLayout),
    view(new QTableView)
{
    setup_ui();
    this->setAttribute(Qt::WA_DeleteOnClose);
}

wd_show_table::~wd_show_table() {
    qDebug() << "delete show table";
}

void wd_show_table::setup_ui() {
    this->resize(500, 500);
    layout->addWidget(view);
    this->setLayout(layout);
}

void wd_show_table::set_model(QAbstractItemModel *tmodel) {
    view->setModel(tmodel);
}
