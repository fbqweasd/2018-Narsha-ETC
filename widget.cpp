#include "widget.h"
#include "ui_widget.h"
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    port = new QSerialPort();
    port->setPortName("COM6");
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if(!port->open(QIODevice::ReadWrite)){
        qDebug() << "\n Serial port open Error \n";
        ui->label->setText("Serial port Error");
    }

    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(text_Reading()));
}

Widget::~Widget()
{
    port->close();
    delete ui;
}

void Widget::text_Sending(){
    QByteArray send_Data;
    send_Data = ui->textEdit->toPlainText().toUtf8().left(1);
    port->write(send_Data.data());

}

void Widget::text_Reading(){
    QByteArray read_Data;
    read_Data = port->readAll();

    ui->label->setText(read_Data);
    ui->label->show();

    qDebug() << read_Data.length();
}

void Widget::on_pushButton_clicked()
{
    QString input_data;
    input_data = ui->textEdit->toPlainText();
    ui->label->setText(input_data);
}
