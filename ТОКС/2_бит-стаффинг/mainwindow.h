#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QTextEdit>
#include <QtSerialPort/QtSerialPort>
#include<QBitArray>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     void setStyle();
     void setSettings();
     QBitArray byte_to_bit(QByteArray byteArray);
     QByteArray bit_to_byte(QList<bool> bitArray);
     QByteArray insertBitStuffing(QByteArray byteArray);
     QByteArray deleteBitStuffing(QByteArray byteArray);

private slots:
    void on_sendButtonCom1_clicked();
    void on_sendButtonCom2_clicked();
    void readCom1();
    void readCom2();
    void writeCom1(QString data);
    void writeCom2(QString data);

    void on_speedComboBoxCom1_currentIndexChanged(const QString &arg1);
    void on_speedComboBoxCom2_currentIndexChanged(const QString &arg1);
    void on_checkBoxCom1_clicked();
    void on_checkBoxCom2_clicked();


private:
    Ui::MainWindow *ui;
    QSerialPort *c1;
    QSerialPort *c2;
};

#endif // MAINWINDOW_H
