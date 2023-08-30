#include "new_sql_connect.h"
#include "ui_new_sql_connect.h"

new_sql_connect::new_sql_connect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_sql_connect)
{
    ui->setupUi(this);
}

new_sql_connect::~new_sql_connect()
{
    delete ui;
}
