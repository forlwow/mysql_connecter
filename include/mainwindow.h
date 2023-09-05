#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class wd_create_sql_con;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    wd_create_sql_con *sql_con;
    QSet<QString> all_connections;

public:
    void set_all_connections();

    void update_connections_interface();

    void init_tree_widget();

private slots:
    void on_act_new_connect_triggered();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
