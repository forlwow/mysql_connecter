#ifndef WD_CELL_SQL_H
#define WD_CELL_SQL_H

#include <QComboBox>
#include <QStringListModel>
#include "wd_cell.h"
#include "mysql_handler.h"

class wd_cell_sql: public wd_cell{
    Q_OBJECT
public:
    explicit wd_cell_sql(QWidget *parent = nullptr);

    ~wd_cell_sql() override = default;

    // 设置sql连接
    void set_sql_tool(const sql_handler::sql_handler<sql_handler::MySQL_Handler>& tmp_sql_tools);

    void reset_tool();

    // 查询
    int query(const QString &data);

    void set_model_msg(QStandardItemModel *model_sql, const QString &data);

    void set_combobox_model(QStringListModel *model);

    inline QComboBox *get_combobox_select() {return select_sql;}

    void update_combobox(const QStringList &data);

protected slots:
    void on_btn_start_clicked();

    // sql选项改变时
    void on_combobox_changed(int index);

signals:
    // textEdit信号
    void set_text_signal(const QString &data);
    void get_text_signal(QString &data);

    // ComboBox信号
    void combobox_changed(const QString &data);

protected:
    sql_handler::sql_handler<sql_handler::MySQL_Handler> sql_tools;

    QComboBox *select_sql;
};

#endif