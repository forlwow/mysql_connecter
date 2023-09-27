#ifndef WD_TAB_PAGE_H
#define WD_TAB_PAGE_H

#include <QScrollArea>
#include "wd_cell_sql.h"


class wd_tab_page: public QScrollArea {
    Q_OBJECT
public:
    explicit wd_tab_page(QWidget *parent = nullptr);
    ~wd_tab_page() noexcept override;

protected:
    void setup_ui();

    wd_cell_sql *create_cell() const;

protected:
    QWidget *ui;

protected slots:
    void on_act_cell_height_changed(int changed_height); //当单元格高度变化时的导入的槽

    void on_act_tableView_double_clicked(const QModelIndex &index);
};


#endif //WD_TAB_PAGE_H
