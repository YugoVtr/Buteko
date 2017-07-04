#include "pedidowindow.h"
#include "ui_pedidowindow.h"

pedidowindow::pedidowindow(QWidget *parent,int codigo) :
    QDialog(parent),
    ui(new Ui::pedidowindow),
    codigo(codigo)
{
    ui->setupUi(this);
    if(this->codigo == -1){
        QSqlDatabase db = QSqlDatabase::database();
        QString query = " SELECT MAX(cod_pedido) FROM pedido;";
        if(!db.open()) throw QString(db.lastError().text());
        QSqlQuery queryExec;
        if(!queryExec.exec(query)) throw QString(queryExec.lastError().text());
        queryExec.first();
        this->codigo = queryExec.value(0).toInt() + 1;
        ui->lineEdit_Pedido_Cod->setText(QString::number(this->codigo));
    }

}

pedidowindow::~pedidowindow()
{
    delete ui;
}

void pedidowindow::populaWindow()
{
    try
    {
        ui->comboBox_ItensCadapio->hide();
        ui->pushButton_addItemCardapio->hide();

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
                )          AS valor_pedido, \
                cards.nome AS descricao, \
                cards.valor AS preco \
                FROM Pedido  AS pedido \
                LEFT JOIN ItemPedido itens \
                ON itens.cod_pedido = pedido.cod_pedido \
                LEFT JOIN ItemCardapio cards \
                ON itens.cod_item_cardapio = cards.cod_item_cardapio\
                INNER JOIN mesapedido mesaped \
                ON mesaped.cod_pedido = pedido.cod_pedido \
                INNER JOIN mesa mesa \
                ON mesaped.cod_mesa = mesa.cod_mesa\
                WHERE pedido.cod_pedido = :cod_Pedido \
                ORDER BY pedido.data DESC, pedido.cod_pedido;");

        QSqlDatabase db = QSqlDatabase::database();

        if(!db.open()) throw QString(db.lastError().text());

        QSqlQuery queryExec;
        queryExec.prepare(query);
        queryExec.bindValue(":cod_Pedido",this->codigo);
        if(!queryExec.exec()) throw QString(queryExec.lastError().text());

        QSqlRecord rec = queryExec.record();

        queryExec.next();
        ui->lineEdit_Pedido_Cod->setText(queryExec.value(rec.indexOf("cod_pedido")).toString());
        ui->label_Pedido_Status->setText(queryExec.value(rec.indexOf("status")).toString().toUpper());
        ui->lineEdit_Mesa_Cod->setText("Mesa " + queryExec.value(rec.indexOf("cod_mesa")).toString());
        ui->lineEdit_Pedido_Atendente->setText(queryExec.value(rec.indexOf("atendente")).toString());
        QStringList data = queryExec.value(rec.indexOf("data_pedido")).toString().split('/');
        ui->calendarWidget_Pedido_Data->setSelectedDate(QDate(data[2].toInt(),data[1].toInt(),data[0].toInt()));
        QString subTotal =  "R$ " + queryExec.value(rec.indexOf("valor_pedido")).toString();
        if(!subTotal.contains('.')) subTotal += ".00";
        subTotal.replace('.',",");
        ui->lineEdit_Total->setText(subTotal);

        QStandardItemModel *model = new QStandardItemModel(this);
        QString descricao = queryExec.value(rec.indexOf("descricao")).toString();
        if(!descricao.isEmpty()){
            model->insertColumns(0,2);
            model->setHeaderData(0,Qt::Horizontal,"Descrição");
            model->setHeaderData(1,Qt::Horizontal,"Preço");

            int i = 0;
            do {
                model->insertRow(i);
                descricao = queryExec.value(rec.indexOf("descricao")).toString();
                model->setData(model->index(i,0),descricao);
                QString valor = "R$ " + queryExec.value(rec.indexOf("preco")).toString();
                if(!valor.contains('.')) valor += ".00";
                valor.replace('.',",");
                model->setData(model->index(i,1),valor);
                i++;
            } while (queryExec.next());
        }
        ui->tableView_ItensDoPedido->setModel(model);
        ui->tableView_ItensDoPedido->columnAt(1);
        ui->tableView_ItensDoPedido->setColumnWidth(0,330);
        db.close();
    } catch (QString &erro) {QMessageBox::information(this,"ERRO",erro);}
}

