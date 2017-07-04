#ifndef PEDIDOWIDGET_H
#define PEDIDOWIDGET_H

#include <QWidget>

#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <pedidowindow.h>

namespace BancoDados {
    class PedidoWidget;
}

class PedidoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PedidoWidget(QWidget *parent = Q_NULLPTR);
    explicit PedidoWidget(const QString &title, QWidget *parent = Q_NULLPTR);
    explicit PedidoWidget(int cod_pedido, const QString &data, const QString &subTotal,
                              const QString &status,const QString &data_Url, const QString &subTotal_Url,
                              const QString &status_Url, const QString &mesa, QWidget *parent = Q_NULLPTR);
    ~PedidoWidget();

    QPushButton* getStatusButton()const{return pushButton_Status_Pixmap; }
    QGroupBox* getGroupBox()const { return groupBox_this; }
signals:

public slots:
    void pedidoDetalhes();

private:
    QGroupBox *groupBox_this;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_Subtotal;
    QLabel *label_Subtotal_Pixmap;
    QLabel *label_Subtotal_Header;
    QHBoxLayout *horizontalLayout_Status;
    QPushButton *pushButton_Status_Pixmap;
    QLabel *label_Status_Header;
    QHBoxLayout *horizontalLayout_Data;
    QLabel *label_Data_Pixmap;
    QLabel *label_Data_Header;
    QLabel *label_Data;
    QLabel *label_Status;
    QLabel *label_Subtotal;
    QFrame *line_Divisoria;

    int cod_Pedido;

};

#endif // PEDIDOWIDGET_H
