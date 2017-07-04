#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QDebug>
#include "PedidoWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addPedido(int cod_pedido,const QString &data, const QString &subTotal, const QString &status, const QString &mesa);
    void query(const QString &query);

private slots:

    void on_pushButton_addPedido_clicked();

private:
    Ui::MainWindow *ui;
    int linha;
    int coluna;
};

#endif // MAINWINDOW_H
