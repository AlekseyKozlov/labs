#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    c1 = new QSerialPort("COM1");
    c2 = new QSerialPort("COM2");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButtonCom1_clicked()
{
    if(ui->textEditCom1->toPlainText().length() > 0)
    {
        ui->textFieldCom1->setText(ui->textFieldCom1->toPlainText() + "You: " + ui->textEditCom1->toPlainText()+"\n");
        writeCom1(ui->textEditCom1->toPlainText()+"\n");
        ui->textEditCom1->clear();
    }
}

void MainWindow::on_sendButtonCom2_clicked()
{
    if(ui->textEditCom2->toPlainText().length() > 0)
    {
        ui->textFieldCom2->setText(ui->textFieldCom2->toPlainText() + "You: " + ui->textEditCom2->toPlainText()+"\n");
        writeCom2(ui->textEditCom2->toPlainText()+"\n");
        ui->textEditCom2->clear();
    }
}

void MainWindow::readCom1()
{
    QByteArray data = c1->readAll();
    data = deleteBitStuffing(data);
    ui->textFieldCom1->setText(ui->textFieldCom1->toPlainText()+"Com2: "+ data);
}

void MainWindow::readCom2()
{
    QByteArray data = c2->readAll();
    data = deleteBitStuffing(data);
    ui->textFieldCom2->setText(ui->textFieldCom2->toPlainText()+"Com1: "+ data);
}

void MainWindow::writeCom1(QString data)
{
    QByteArray byteArray = insertBitStuffing(data.toUtf8().data());
    c1->write(byteArray);
}

void MainWindow::writeCom2(QString data)
{
    QByteArray byteArray = insertBitStuffing(data.toUtf8().data());
    c2->write(byteArray);
}

void MainWindow::setStyle()
{
    ui->setupUi(this);

    QStringList list = (QStringList() << "1200" << "2400" << "4800" << "9600" << "19200");
    ui->speedComboBoxCom1->addItems(list);
    ui->speedComboBoxCom2->addItems(list);
}

void MainWindow::setSettings()
{
    c1->open(QIODevice::ReadWrite);
    c2->open(QIODevice::ReadWrite);

    c1->setBaudRate(QSerialPort::Baud1200);
    c1->setFlowControl(QSerialPort::NoFlowControl);
    c1->setParity(QSerialPort::NoParity);
    c1->setDataBits(QSerialPort::Data8);
    c1->setStopBits(QSerialPort::OneStop);

    c2->setBaudRate(QSerialPort::Baud1200);
    c2->setFlowControl(QSerialPort::NoFlowControl);
    c2->setParity(QSerialPort::NoParity);
    c2->setDataBits(QSerialPort::Data8);
    c2->setStopBits(QSerialPort::OneStop);

    connect(c1, &QSerialPort::readyRead, this, &MainWindow::readCom1);
    connect(c2, &QSerialPort::readyRead, this, &MainWindow::readCom2);
}

QBitArray MainWindow::byte_to_bit(QByteArray byteArray)
{
    QBitArray bitArray;
    bitArray.resize(byteArray.size()*8);
 //qDebug() << byteArray.size()<<"B";
    for(int i = 0; i < byteArray.count(); i++) {
        for(int j = 0; j < 8; j++) {
            bitArray.setBit(i * 8 + j, byteArray.at(i) & (1 << (7-j)));
        }
    }
   //  qDebug() << bitArray<<"B";
    return bitArray;
}

QByteArray MainWindow::bit_to_byte(QList<bool> bitArray)
{
    QByteArray bytes;
    bytes.resize(0);
    for(int b = 0; b < bitArray.size(); b++) {
        if(b % 8 == 0) {
            bytes.resize(bytes.size()+1);
            bytes[bytes.size()-1] = NULL;
        }
        bytes[b/8] = (bytes.at(b/8) | ((bitArray[b] ? 1 : 0) << (7-b % 8)));
        //qDebug() << bytes<<"Byte1 ";
    }
  // qDebug() << bytes<<"Byte ";
    qDebug() << "После: " << byte_to_bit(bytes) << endl;
    return bytes;
}

QByteArray MainWindow::insertBitStuffing(QByteArray byteArray)
{
    QBitArray bitArray = byte_to_bit(byteArray);
    int count = 0;
      qDebug()<<"До: "<< bitArray << endl;
  //  qDebug() << bitArray<<"K";
    char startByte = '~';
    QList<bool> list;

    for(int i = 0; i < 8; i++) {
        list.append(startByte & (1 << (7-i)));
       // qDebug() <<list<<"list";
    }

    for(int i = 0; i < bitArray.count(); i++) {
        if(bitArray[i]) {
            count++;
        } else {
            count = 0;
        }
        list.append(bitArray[i]);
        if(count == 5) {
            list.append(false);
            count = 0;
        }
    }
    qDebug() << "View insert: " << list << endl;
     // qDebug() <<list<<"list2";
    return bit_to_byte(list);
}

QByteArray MainWindow::deleteBitStuffing(QByteArray byteArray)
{
    if(byteArray[0] == '~') {
        byteArray.remove(0, 1);
        QBitArray bitArray = byte_to_bit(byteArray);
        QList<bool> list;
        int count = 0;

        for(int i = 0; i < bitArray.size(); i++) {
            if(bitArray[i]) {
                count++;
            } else {
                count = 0;
            }

            list.append(bitArray[i]);
            if(count == 5) {
                i++;
            }
        }
         qDebug() << "View removed: " << list << endl;
        return bit_to_byte(list);
    } else {
        return NULL;
    }
}


void MainWindow::on_speedComboBoxCom1_currentIndexChanged(const QString &newSpeed)
{
    c1->setBaudRate(newSpeed.toInt());
}

void MainWindow::on_speedComboBoxCom2_currentIndexChanged(const QString &newSpeed)
{
    c2->setBaudRate(newSpeed.toInt());
}

void MainWindow::on_checkBoxCom1_clicked()
{
    if(ui->checkBoxCom1->isChecked())
        c1->setParity(QSerialPort::OddParity);
    else c1->setParity(QSerialPort::NoParity);
}

void MainWindow::on_checkBoxCom2_clicked()
{
    if(ui->checkBoxCom2->isChecked())
        c2->setParity(QSerialPort::OddParity);
    else c2->setParity(QSerialPort::NoParity);
}
