#ifndef MYSQL_CONNECTER_WD_SHOW_TABLE_H
#define MYSQL_CONNECTER_WD_SHOW_TABLE_H

#include <QDialog>

class QAbstractItemModel;
class QVBoxLayout;
class QTableView;

class wd_show_table: public QDialog{
public:
    explicit wd_show_table(QWidget *parent = nullptr);
    ~wd_show_table() override;

    void setup_ui();

    void set_model(QAbstractItemModel *model);

public:
    QVBoxLayout *layout;
    QTableView *view;
};


#endif //MYSQL_CONNECTER_WD_SHOW_TABLE_H
