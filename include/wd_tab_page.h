#ifndef WD_TAB_PAGE_H
#define WD_TAB_PAGE_H

#include <QScrollArea>
#include "wd_cell_sql.h"

typedef QMap<QString, sql_handler::sql_handler<sql_handler::MySQL_Handler>> map_name_sql;

class wd_tab_page: public QScrollArea {
    Q_OBJECT
public:
    explicit wd_tab_page(QWidget *parent = nullptr, QStringListModel *model=nullptr, map_name_sql *connections=nullptr);
    ~wd_tab_page() noexcept override;

    void set_sql_model(QStringListModel *model);
protected:
    void setup_ui();

    wd_cell_sql *create_cell() const;

protected:
    QWidget *ui;

    QStringListModel *combobox_model;

    map_name_sql *cur_connections; // 所有保存的连接

protected slots:
    void on_act_cell_height_changed(int changed_height); //当单元格高度变化时的导入的槽

    void on_act_tableView_double_clicked(const QModelIndex &index);

    void on_cell_combobox_changed(const QString &data);
};


#endif //WD_TAB_PAGE_H
