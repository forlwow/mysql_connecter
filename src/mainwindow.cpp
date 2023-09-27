#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "other.hpp"
#include "global.h"
#include "transfer.hpp"
#include "wd_create_sql_con.h"
#include "connections_handler.h"
#include "wd_cell_sql.h"
#include <QDebug>
#include <QSet>
#include <QScrollArea>
#include <QSizePolicy>
#include <QVBoxLayout>
#include "wd_tab_page.h"

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

    ui->tabWidget->clear();
    new_tab();
    qDebug() << "MainWindow init complete";
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
            qDebug() << "contain item:" << item->text(0);
            cur_con.remove(item->text(0));
        }
        else{
            qDebug() << "delete item:" << item->text(0);
            delete ui->interface_connections->topLevelItem(index);
        }  
    }
    // 添加新内容
    for (const QString &name : cur_con){
        QTreeWidgetItem *tmp = new QTreeWidgetItem(ui->interface_connections);
        tmp->setText(0, name.toLocal8Bit()); // 如果不转会乱码
        tmp->setData(RealData, 0, name);
    }
}

// 初始化左侧树形图
void MainWindow::init_tree_widget(){
    ui->interface_connections->clear();
    ui->interface_connections->setColumnCount(1);
    ui->interface_connections->header()->setHidden(true);
}

// 新建一个tab
void MainWindow::new_tab(){
    auto page = new wd_tab_page;
    ui->tabWidget->addTab(page, "p2");
}

void MainWindow::on_act_test_triggered()
{
    auto cell = ui->tabWidget->currentWidget()->findChild<wd_cell_sql*>("cell");
    if (cell){
        cell->set_sql_tool(current_connections["tests"]);
    }
}

int MainWindow::new_sql_server(const QString &name) {
    if (current_connections.count(name)) return 1;
    auto tmp = transfer::get_mysql_connection(name);
    if (!tmp.isNull() && tmp.is_connected()){
        current_connections[name] = tmp;
        return 0;
    }
    else {
        return 2;
    }
}

void MainWindow::del_sql_server(const QString &name) {
    if (current_connections.contains(name))
        current_connections.remove(name);
}

void MainWindow::on_interface_connections_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int index = ui->interface_connections->indexOfTopLevelItem(item);
    QString i = ui->interface_connections->topLevelItem(index)->data(RealData, 0).toString();
    qDebug() << i;
    int res = new_sql_server(i);
    switch (res) {
        case 0:
            qDebug() << "new_sql_server";
            break;
        case 1:
            qDebug() << "already new_sql_server";
            break;
        case 2:
            qDebug() << "error new_sql_server";
            break;
        default:
            break;
    }
}

