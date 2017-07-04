#include "PedidoWidget.h"

PedidoWidget::PedidoWidget(QWidget *parent) : QWidget(parent),
    groupBox_this(new QGroupBox(parent)),
    gridLayout(0),
    horizontalLayout_Subtotal(0),
    label_Subtotal_Pixmap(0),
    label_Subtotal_Header(0),
    horizontalLayout_Status(0),
    pushButton_Status_Pixmap(0),
    label_Status_Header(0),
    horizontalLayout_Data(0),
    label_Data_Pixmap(0),
    label_Data_Header(0),
    label_Data(0),
    label_Status(0),
    label_Subtotal(0),
    line_Divisoria(0),
    cod_Pedido(-1)
{

}

PedidoWidget::PedidoWidget(const QString &title, QWidget *parent): QWidget(parent),
    groupBox_this(new QGroupBox(title,parent)),
    gridLayout(0),
    horizontalLayout_Subtotal(0),
    label_Subtotal_Pixmap(0),
    label_Subtotal_Header(0),
    horizontalLayout_Status(0),
    pushButton_Status_Pixmap(0),
    label_Status_Header(0),
    horizontalLayout_Data(0),
    label_Data_Pixmap(0),
    label_Data_Header(0),
    label_Data(0),
    label_Status(0),
    label_Subtotal(0),
    line_Divisoria(0),
    cod_Pedido(-1)
{

}

PedidoWidget::PedidoWidget(int cod_pedido,const QString &data, const QString &subTotal,
                                   const QString &status, const QString &data_Url,
                                   const QString &subTotal_Url, const QString &status_Url,
                                   const QString &mesa, QWidget *parent): QWidget(parent),
    groupBox_this(new QGroupBox(mesa,parent)),
    gridLayout(0),
    horizontalLayout_Subtotal(0),
    label_Subtotal_Pixmap(0),
    label_Subtotal_Header(0),
    horizontalLayout_Status(0),
    pushButton_Status_Pixmap(0),
    label_Status_Header(0),
    horizontalLayout_Data(0),
    label_Data_Pixmap(0),
    label_Data_Header(0),
    label_Data(0),
    label_Status(0),
    label_Subtotal(0),
    line_Divisoria(0),
    cod_Pedido(cod_pedido)
{
    groupBox_this->setFixedSize(258,117);
    groupBox_this->setObjectName(QStringLiteral("groupBox_this"));

    gridLayout = new QGridLayout(groupBox_this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    horizontalLayout_Subtotal = new QHBoxLayout();
    horizontalLayout_Subtotal->setSpacing(6);
    horizontalLayout_Subtotal->setObjectName(QStringLiteral("horizontalLayout_Subtotal"));

    label_Subtotal_Pixmap = new QLabel(groupBox_this);
    label_Subtotal_Pixmap->setObjectName(QStringLiteral("label_Subtotal_Pixmap"));
    label_Subtotal_Pixmap->setMinimumSize(QSize(30, 30));
    label_Subtotal_Pixmap->setMaximumSize(QSize(30, 30));
    label_Subtotal_Pixmap->setPixmap(QPixmap(subTotal_Url));
    label_Subtotal_Pixmap->setScaledContents(true);

    horizontalLayout_Subtotal->addWidget(label_Subtotal_Pixmap);

    label_Subtotal_Header = new QLabel(groupBox_this);
    label_Subtotal_Header->setObjectName(QStringLiteral("label_Subtotal_Header"));
    label_Subtotal_Header->setMinimumSize(QSize(30, 30));
    label_Subtotal_Header->setMaximumSize(QSize(50, 50));
    label_Subtotal_Header->setText("SubTotal");

    horizontalLayout_Subtotal->addWidget(label_Subtotal_Header);

    gridLayout->addLayout(horizontalLayout_Subtotal, 0, 1, 1, 1);

    horizontalLayout_Status = new QHBoxLayout();
    horizontalLayout_Status->setSpacing(6);
    horizontalLayout_Status->setObjectName(QStringLiteral("horizontalLayout_Status"));

    pushButton_Status_Pixmap = new QPushButton(groupBox_this);
    pushButton_Status_Pixmap->setObjectName(QStringLiteral("pushButton_Status_Pixmap"));
    pushButton_Status_Pixmap->setMinimumSize(QSize(30, 30));
    pushButton_Status_Pixmap->setMaximumSize(QSize(30, 30));
    pushButton_Status_Pixmap->setIcon(QIcon(status_Url));
    pushButton_Status_Pixmap->setIconSize(QSize(30,30));
    pushButton_Status_Pixmap->setFlat(true);
    pushButton_Status_Pixmap->setToolTip("Detalhes");
    pushButton_Status_Pixmap->setToolTipDuration(5000);

    horizontalLayout_Status->addWidget(pushButton_Status_Pixmap);

    label_Status_Header = new QLabel(groupBox_this);
    label_Status_Header->setObjectName(QStringLiteral("label_Status_Header"));
    label_Status_Header->setMinimumSize(QSize(30, 30));
    label_Status_Header->setMaximumSize(QSize(30, 30));
    label_Status_Header->setText("Status");

    horizontalLayout_Status->addWidget(label_Status_Header);

    gridLayout->addLayout(horizontalLayout_Status, 0, 2, 1, 1);

    horizontalLayout_Data = new QHBoxLayout();
    horizontalLayout_Data->setSpacing(6);
    horizontalLayout_Data->setObjectName(QStringLiteral("horizontalLayout_Data"));

    label_Data_Pixmap = new QLabel(groupBox_this);
    label_Data_Pixmap->setObjectName(QStringLiteral("label_Data_Pixmap"));
    label_Data_Pixmap->setMinimumSize(QSize(30, 30));
    label_Data_Pixmap->setMaximumSize(QSize(30, 30));
    label_Data_Pixmap->setPixmap(QPixmap(data_Url));
    label_Data_Pixmap->setScaledContents(true);

    horizontalLayout_Data->addWidget(label_Data_Pixmap);

    label_Data_Header = new QLabel(groupBox_this);
    label_Data_Header->setObjectName(QStringLiteral("label_Data_Header"));
    label_Data_Header->setMinimumSize(QSize(30, 30));
    label_Data_Header->setMaximumSize(QSize(30, 30));
    label_Data_Header->setText("Data");

    horizontalLayout_Data->addWidget(label_Data_Header);

    gridLayout->addLayout(horizontalLayout_Data, 0, 0, 1, 1);

    label_Data = new QLabel(groupBox_this);
    label_Data->setObjectName(QStringLiteral("label_Data"));
    label_Data->setAlignment(Qt::AlignCenter);
    label_Data->setText(data);

    gridLayout->addWidget(label_Data, 2, 0, 1, 1);

    label_Status = new QLabel(groupBox_this);
    label_Status->setObjectName(QStringLiteral("label_Status"));
    label_Status->setFrameShadow(QFrame::Plain);
    label_Status->setTextFormat(Qt::AutoText);
    label_Status->setAlignment(Qt::AlignCenter);
    label_Status->setWordWrap(false);
    label_Status->setText(status);

    gridLayout->addWidget(label_Status, 2, 2, 1, 1);

    label_Subtotal = new QLabel(groupBox_this);
    label_Subtotal->setObjectName(QStringLiteral("label_Subtotal"));
    label_Subtotal->setAlignment(Qt::AlignCenter);
    label_Subtotal->setText(subTotal);

    gridLayout->addWidget(label_Subtotal, 2, 1, 1, 1);

    line_Divisoria = new QFrame(groupBox_this);
    line_Divisoria->setObjectName(QStringLiteral("line_Divisoria"));
    line_Divisoria->setFrameShape(QFrame::HLine);
    line_Divisoria->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line_Divisoria, 1, 0, 1, 3);

    label_Data_Pixmap->raise();
    label_Data_Header->raise();
    label_Data->raise();
    label_Subtotal->raise();
    label_Status->raise();
    line_Divisoria->raise();
}

PedidoWidget::~PedidoWidget()
{
    delete groupBox_this;
}

void PedidoWidget::pedidoDetalhes()
{
    pedidowindow detalhes(this,cod_Pedido);
    detalhes.setWindowTitle("Pedido " + QString::number(cod_Pedido));
    detalhes.populaWindow();
    detalhes.setModal(true);
    detalhes.exec();
}
