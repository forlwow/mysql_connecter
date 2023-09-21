#include "wd_create_sql_con.h"
#include "ui_wd_create_sql_con.h"
#include <QDebug>
#include <QMessageBox>
#include "global.h"
#include "connections_handler.h"
#include "transfer.hpp"
#include "mysql_handler.h"

wd_create_sql_con::wd_create_sql_con(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wd_create_sql_con)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, reject);

}

wd_create_sql_con::~wd_create_sql_con()
{
    delete ui;
}

bool wd_create_sql_con::on_btn_connect_clicked()
{
    int con_res = sql_handler::MySQL_Handler::test_connect(get_data());
    bool res = false;

    if (con_res == 0){
        qDebug() << QString::fromLocal8Bit("连接成功");
        res = true;
    }
    else{
        qDebug() << QString::fromLocal8Bit("连接失败");
    }
    return res;
}

QStringList wd_create_sql_con::get_data(){
    QStringList con_data;
    con_data.push_back(ui->edit_con_name->text());
    con_data.push_back(ui->edit_con_db->text());
    con_data.push_back(ui->edit_con_ip->text());
    con_data.push_back(ui->edit_con_port->text());
    con_data.push_back(ui->edit_con_usr->text());
    con_data.push_back(ui->edit_con_passwd->text());
    return con_data;
}



void wd_create_sql_con::on_buttonBox_accepted()
{
    int res = save_con_data(get_data());
    switch (res)
    {
    case con_handler::CON_FILE_OK:
        this->accept();
        qDebug() << "save ok";
        break;
    case con_handler::CON_FILE_ERROR_NAME_SAME:
        QMessageBox::about(this, tr("名称重复"), tr("名称重复"));
        qDebug() << "save same name error";
        break;
    case con_handler::CON_FILE_ERROR_NAME_EMPTY:
        QMessageBox::about(this, tr("名称不能为空"), tr("名称不能为空"));
        qDebug() << "save empty name error";
        break;
    default:
        qDebug() << "save error:" << res;
        break;
    }
}

int wd_create_sql_con::save_con_data(QStringList data){
    qDebug() << "save_con_data" << "\n" << data;
    // 通过connections_handler保存文件
    return con_handler::save_con_data(transfer::qslist2stdsvector(data));
}

