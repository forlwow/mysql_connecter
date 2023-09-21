#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class wd_create_sql_con;
class wd_cell;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    wd_create_sql_con *sql_con; // 新建连接的窗口
    QSet<QString> all_connections; // 所有保存的连接

public:
    void set_all_connections(); // 从json文件读入所有保存连接

    void update_connections_interface(); // 更新左侧连接界面

    void init_tree_widget();  // 初始化左侧树形结构

    void new_tab(); // 新建一个tab

    wd_cell *create_cell(); // 新建一个单元格

private slots:
    void on_act_new_connect_triggered(); // 点击新建连接按钮

    void on_act_test_triggered();   // 测试按钮

    void on_act_cell_height_changed(int changed_height); //当单元格高度变化时的导入的槽

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
