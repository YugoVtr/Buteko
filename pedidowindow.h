#ifndef PEDIDOWINDOW_H
#define PEDIDOWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QStandardItemModel>

namespace Ui {
class pedidowindow;
}

class pedidowindow : public QDialog
{
    Q_OBJECT

public:
     pedidowindow(QWidget *parent = 0,int codigo = -1);
    ~pedidowindow();
     void populaWindow();

private:
    Ui::pedidowindow *ui;
    int codigo;
};

#endif // PEDIDOWINDOW_H
