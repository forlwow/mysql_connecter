#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "other.hpp"
#include "transfer.hpp"
#include "wd_create_sql_con.h"
#include "connections_handler.h"
#include "wd_sql_result.h"
#include <QDebug>
#include <QSet>
#include <QMessageBox>
#include <QSplitter>
#include <QScrollArea>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 新建查询窗口
    sql_con = new wd_create_sql_con(this);

    // 获取本地连接数据
    // 初始化树形连接
    init_tree_widget();
    update_connections_interface();
    qDebug() << "MainWindow init complete";

    ui->tabWidget->clear();
    new_tab();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_act_new_connect_triggered()
{
    if (sql_con->exec() == QDialog::Accepted){
        qDebug() << "on_act_new_connect_triggered:" << "accept";
        update_connections_interface();
    }
    else{
        qDebug() << "on_act_new_connect_triggered:" << "reject";
    }

}

void MainWindow::set_all_connections(){
    all_connections.clear();

    all_connections = transfer::stdset2qset(con_handler::get_all_connections());
}

void MainWindow::update_connections_interface(){
    set_all_connections();

    QSet<QString> cur_con(all_connections);
    qDebug() << "all item:" << cur_con;
    // 遍历顶层
    for (int index = ui->interface_connections->topLevelItemCount() - 1; index >= 0 ; --index){
        QTreeWidgetItem *item =  ui->interface_connections->topLevelItem(index);
        if (cur_con.contains(item->text(0))){
            cur_con.remove(item->text(0));
            qDebug() << "contain item:" << item->text(0);
        }
        else{
            delete ui->interface_connections->topLevelItem(index);
            qDebug() << "delete item:" << item->text(0);
        }  
    }
    // 添加新内容
    for (const QString &name : cur_con){
        QTreeWidgetItem *tmp = new QTreeWidgetItem(ui->interface_connections);
        tmp->setText(0, name.toLocal8Bit());
        qDebug() << "add item:" << name;
    }
}

// 初始化右侧树形图
void MainWindow::init_tree_widget(){
    ui->interface_connections->clear();
    ui->interface_connections->setColumnCount(1);
    ui->interface_connections->header()->setHidden(true);
}

void MainWindow::new_tab(){
    wd_sql_result *sql_res = new wd_sql_result();
    wd_sql_result *sql_res2 = new wd_sql_result();

    QScrollArea *scol = new QScrollArea();
    QWidget *scol_content = new QWidget();
    scol_content->resize(500, 1000);
    scol->setWidget(scol_content);

    QSpacerItem *space = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding); 

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(sql_res);
    vlayout->setStretchFactor(sql_res, 1);
    vlayout->addItem(space);
    vlayout->setStretch(1, 100);

    scol_content->setLayout(vlayout);
    ui->tabWidget->addTab(scol, "test");

}
