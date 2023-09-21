#ifndef WD_CELL_H
#define WD_CELL_H

#include <QWidget>
#include "global.h"

class QStandardItemModel;

namespace Ui {
class wd_cell;
}

class wd_cell : public QWidget
{
    Q_OBJECT

public:
    explicit wd_cell(QWidget *parent = nullptr);
    virtual ~wd_cell();

signals:
    void editor_changed(int changed_height);

protected:
    int font_size;  // 字体大小
    QFont edit_font;    // 字体族

    int line_count; // 行数

    int min_height; // 输入框的最小高度

public:

protected slots:
    void text_content_adjust();

    void line_num_content_adjust();

    



protected:
    Ui::wd_cell *ui;
};

#endif // WD_CELL_H
