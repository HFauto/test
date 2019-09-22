#ifndef SERIALWINDOW_H
#define SERIALWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTextBrowser>
#include <QStringList>

class SerialWindow : public QWidget
{
    Q_OBJECT

public:
    QString objctDeviceinfor;
    QSerialPort receiver;
private:
    QStringList serialPortNames;    
    QSerialPortInfo  *receiverInfor = nullptr;
    QPushButton *scanBt;
    QPushButton *connectBt;
    QLabel *serialNameLabel;
    QComboBox   *serialNamebox;
    QTextBrowser *serialInfo;

public:
    explicit SerialWindow(QWidget *parent = 0);

    void send(QByteArray data);
signals:
     void updateSerialPortNames();
     void openOrClose(bool isOk);

public slots:

private slots:
    void  connectSerial();
    void  scanSerial();

};
#endif // SERIALWINDOW_H
