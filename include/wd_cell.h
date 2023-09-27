#ifndef WD_CELL_H
#define WD_CELL_H

#include <QWidget>
#include "global.h"

class QModelIndex;
class QTableView;;

namespace Ui {
class wd_cell;
}

class wd_cell : public QWidget
{
    Q_OBJECT

protected:
    Ui::wd_cell *ui;

public:
    explicit wd_cell(QWidget *parent = nullptr);

    ~wd_cell() override;

    QTableView *get_table_view();

signals:
    void editor_changed(int changed_height);

    void tableview_doubleClicked(const QModelIndex &index);

protected:
    int font_size;  // 字体大小

    QFont edit_font;    // 字体族

    int line_count; // 行数

    int edit_min_height; // 输入框的最小高度
    int num_min_width;
public:

protected slots:
    // textEdit接口
    void set_text(const QString &data);
    void get_text(QString &data);

    void text_content_adjust();

    void line_num_content_adjust();

    void pass_tableview_doubleClicked(const QModelIndex &index);
};

#endif // WD_CELL_H
