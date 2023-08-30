#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "winsock.h"
#include "mysql.h"
#include "other.h"
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //连接MySql数据库
    try{
        MYSQL *sql_con = new MYSQL();
        mysql_init(sql_con);
        // localhost:服务器 root为账号密码 test为数据库名 3306为端口
        if(!mysql_real_connect(sql_con, "localhost","root","123456","test",3306,NULL,0)){
            qDebug() << "q OK";
        }
        else{
            qDebug() << "q error";
        }
        mysql_close(sql_con);
    }
    catch (...){
        print("Error");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}



