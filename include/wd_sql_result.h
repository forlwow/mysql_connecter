#ifndef WD_SQL_RESULT_H
#define WD_SQL_RESULT_H

#include <QWidget>
#include "global.h"

namespace Ui {
class wd_sql_result;
}

class wd_sql_result : public QWidget
{
    Q_OBJECT

public:
    explicit wd_sql_result(QWidget *parent = nullptr);
    ~wd_sql_result();

signals:
    void editor_changed();

public:
    int font_size;
    QFont edit_font;

    int line_count;

    int min_height;

private slots:
    void text_content_adjust();

    void line_num_content_adjust();

private:
    Ui::wd_sql_result *ui;
};

#endif // WD_SQL_RESULT_H
