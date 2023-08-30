#ifndef NEW_SQL_CONNECT_H
#define NEW_SQL_CONNECT_H

#include <QWidget>

namespace Ui {
class new_sql_connect;
}

class new_sql_connect : public QWidget
{
    Q_OBJECT

public:
    explicit new_sql_connect(QWidget *parent = nullptr);
    ~new_sql_connect();

private:
    Ui::new_sql_connect *ui;
};

#endif // NEW_SQL_CONNECT_H
