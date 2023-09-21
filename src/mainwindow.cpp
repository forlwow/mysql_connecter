#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "other.hpp"
#include "transfer.hpp"
#include "wd_create_sql_con.h"
#include "connections_handler.h"
#include "wd_cell_sql.h"
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
    // TODO 测试transfer::get_mysql_connection
    //      测试mysql_handler.query

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
    }
}

// 初始化右侧树形图
void MainWindow::init_tree_widget(){
    ui->interface_connections->clear();
    ui->interface_connections->setColumnCount(1);
    ui->interface_connections->header()->setHidden(true);
}

// 新建一个tab
void MainWindow::new_tab(){
    // QScrollArea => QWidget => QVBoxLayout => wd_sql_result
    wd_cell *sql_res = create_cell();
    sql_res->setObjectName("1");
    wd_cell *sql_res2 = create_cell();
    sql_res2->setObjectName("2");

    QScrollArea *scol = new QScrollArea();
    scol->setObjectName("QScrollArea");
    QWidget *scol_content = new QWidget();
    scol_content->setObjectName("QScrollAreaContent");
    scol_content->resize(500, 1000);
    scol->setWidget(scol_content);

    QWidget *space = new QWidget();
    space->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    space->setObjectName("space");

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->setObjectName("QVBoxLayout");
    vlayout->addWidget(sql_res);
    vlayout->setStretchFactor(sql_res, 1);
    vlayout->addWidget(sql_res2);
    vlayout->setStretchFactor(sql_res2, 1);
    vlayout->addWidget(space);
    vlayout->setStretchFactor(space, INT16_MAX);

    scol_content->setLayout(vlayout);
    ui->tabWidget->addTab(scol, "new tab");
}

void MainWindow::on_act_test_triggered()
{
    int index = ui->tabWidget->currentIndex();
    QWidget *page = ui->tabWidget->widget(index);
    auto scroll = qobject_cast<QScrollArea*>(page);
    qDebug() << scroll->widget()->size();
}

void MainWindow::on_act_cell_height_changed(int changed_height){
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

wd_cell *MainWindow::create_cell(){
    wd_cell *res = new wd_cell_sql();
    connect(res, &wd_cell::editor_changed, this, on_act_cell_height_changed);
    return res;
}
