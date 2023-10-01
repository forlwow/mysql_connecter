#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QMap>
#include <QStringListModel>
#include <mysql_handler.h>
#include "wd_show_table.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class wd_create_sql_con;
class wd_cell;
class QTreeWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public:
    enum DataColnumn{RealData = Qt::UserRole + 1};

    wd_create_sql_con *sql_con; // 新建连接的窗口
    QSet<QString> all_connections; // 所有保存的连接
    QStringListModel *combobox_model; // 用于在combobox中显示的模型
    QMap<QString, sql_handler::sql_handler<sql_handler::MySQL_Handler>> current_connections; // 已经连接的连接

public:
    int new_sql_server(const QString &name);

    void del_sql_server(const QString &name);

    void set_all_connections(); // 从json文件读入所有保存连接

    void update_connections_interface(); // 更新左侧连接界面

    void init_tree_widget();  // 初始化左侧树形结构

    void new_tab(); // 新建一个tab

private slots:
    void on_act_new_connect_triggered(); // 点击新建连接按钮

    void on_act_test_triggered();   // 测试按钮

    void on_interface_connections_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_act_test2_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
