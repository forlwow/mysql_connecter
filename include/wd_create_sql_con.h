#ifndef WD_CREATE_SQL_CON_H
#define WD_CREATE_SQL_CON_H

#include <QDialog>

class MYSQL;

namespace Ui {
class wd_create_sql_con;
}

class wd_create_sql_con : public QDialog
{
    Q_OBJECT

public:
    explicit wd_create_sql_con(QWidget *parent = nullptr);
    ~wd_create_sql_con();

public:
    int save_con_data(QStringList data);


public:
    QStringList get_data();

private:
    Ui::wd_create_sql_con *ui;

signals:
    void send_data(QStringList data);

private slots:
    bool on_btn_connect_clicked();

    void on_buttonBox_accepted();

};

#endif // WD_CREATE_SQL_CON_H
