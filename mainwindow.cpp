#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    linha(0),
    coluna(0)
{
    ui->setupUi(this);
    ui->scrollArea_Pedidos->setHorizontalScrollBarPolicy ( Qt :: ScrollBarAlwaysOff );

    QString query("SELECT pedido.cod_pedido, \
            pedido.status, \
            mesa.cod_mesa, \
            DATE_FORMAT(pedido.data, '%d/%m/%Y') AS data_pedido, \
            CASE \
              WHEN pedido.cod_gerente IS NOT NULL \
              THEN \
                (SELECT gerente.nome \
                FROM Gerente gerente \
                WHERE gerente.cod_gerente = pedido.cod_gerente \
                )\
              WHEN pedido.cod_garcom IS NOT NULL \
              THEN \
                (SELECT garcom.nome \
                FROM Garcom garcom \
                WHERE garcom.cod_garcom = pedido.cod_garcom \
                ) \
              WHEN pedido.cod_cliente IS NOT NULL \
              THEN \
                (SELECT cliente.nome \
                FROM Cliente cliente \
                WHERE cliente.cod_cliente = pedido.cod_cliente \
                ) \
            END         AS atendente, \
            pedido.data AS data_pedido, \
            (SELECT SUM(card.valor) \
            FROM ItemPedido item \
            INNER JOIN ItemCardapio card \
            ON item.cod_item_cardapio = card.cod_item_cardapio \
            WHERE item.cod_pedido     = pedido.cod_pedido \
            )          AS valor_pedido \
          FROM Pedido  AS pedido \
          INNER JOIN mesapedido mesaped \
          ON mesaped.cod_pedido = pedido.cod_pedido \
          INNER JOIN mesa mesa \
          ON mesaped.cod_mesa = mesa.cod_mesa\
          ORDER BY pedido.data DESC, pedido.cod_pedido;");
    this->query(query);
    this->setFixedWidth(this->width());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPedido(int cod_pedido, const QString &data,const QString &subTotal,const QString &status,const QString &mesa)
{
    if(coluna>2) {
        coluna = 0;
        linha++;
    }
    QString data_Url = "../Buteko/Arquivos/data.png";
    QString subTotal_Url = "../Buteko/Arquivos/subtotal.png";
    QString status_Url = "../Buteko/Arquivos/status.png";

    PedidoWidget *groupBox = new PedidoWidget(cod_pedido,data,subTotal,status,data_Url,
                                                      subTotal_Url,status_Url,mesa,ui->scrollAreaWidgetContents);
    connect(groupBox->getStatusButton(),SIGNAL(clicked(bool)),groupBox,SLOT(pedidoDetalhes()));

    ui->gridLayout_2->addWidget(groupBox->getGroupBox(), linha, coluna, 1, 1);

    coluna++;

    if(linha>2){
        int width = ui->scrollArea_Pedidos->width();
        int height = ui->scrollArea_Pedidos->height();
        ui->scrollArea_Pedidos->setWidgetResizable(true);
        ui->scrollArea_Pedidos->resize(width-100,height+groupBox->getGroupBox()->height());
        ui->scrollArea_Pedidos->setWidgetResizable(false);
        ui->scrollArea_Pedidos->resize(width,height);
    }
}

void MainWindow::query(const QString &query)
{
    try
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("buteko");
        db.setUserName("root");
        db.setPassword("");

        if(!db.open()) throw QString(db.lastError().text());

        QSqlQuery queryExec;
        if(!queryExec.exec(query)) throw QString(queryExec.lastError().text());

        QSqlRecord rec = queryExec.record();
        while (queryExec.next())
        {
            int cod_pedido = queryExec.value(rec.indexOf("cod_pedido")).toInt();
            QString status = queryExec.value(rec.indexOf("status")).toString();
            QString mesa = "Mesa " + queryExec.value(rec.indexOf("cod_mesa")).toString();
            mesa += " - " + queryExec.value(rec.indexOf("atendente")).toString();
            QString data = queryExec.value(rec.indexOf("data_pedido")).toString();

            QString subTotal =  "R$ " + queryExec.value(rec.indexOf("valor_pedido")).toString();
            if(!subTotal.contains('.')) subTotal += ".00";
            subTotal.replace('.',',');
            this->addPedido(cod_pedido,data,subTotal,status,mesa);
        }
        db.close();
    } catch (QString &erro) {QMessageBox::information(this,"ERRO",erro);}

}
void MainWindow::on_pushButton_addPedido_clicked()
{
    pedidowindow detalhes(this);
    detalhes.setWindowTitle("Novo Pedido");
    detalhes.setModal(true);
    detalhes.exec();
}
