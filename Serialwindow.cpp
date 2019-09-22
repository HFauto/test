#include "Serialwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
SerialWindow::SerialWindow(QWidget *parent) : QWidget(parent)
{

   this->scanBt = new QPushButton(tr("扫描"));
   connect(this->scanBt,SIGNAL(clicked(bool)),
           this,SLOT(scanSerial()) );
   this->connectBt = new QPushButton(tr("连接"));
   connect( this->connectBt,SIGNAL(clicked(bool)),
            this,SLOT(connectSerial())
          );

   this->serialNameLabel = new QLabel(tr("设备号:"));
   this->serialInfo = new QTextBrowser;
   this->serialNamebox   = new QComboBox;
   QHBoxLayout *hLayout = new QHBoxLayout;
   hLayout->addWidget(this->serialNameLabel);
   hLayout->addWidget(this->serialNamebox);
   hLayout->addWidget(this->connectBt);
   hLayout->addWidget(this->scanBt);

   QVBoxLayout *vLayout = new QVBoxLayout(this);
   vLayout->addLayout(hLayout);
   vLayout->addWidget(this->serialInfo);

   this->objctDeviceinfor = "Silicon Labs CP210x USB to UART Bridge";//目标串口
}


void SerialWindow::connectSerial(){

    if(this->serialNamebox->count() > 0 &&
       tr("连接") == this->connectBt->text()){

       if(this->receiverInfor){
       this->receiverInfor  = new QSerialPortInfo(this->serialNamebox->currentText());
      }
      else{

        delete this->receiverInfor;
        this->receiverInfor  = new QSerialPortInfo(this->serialNamebox->currentText());
      }

     this->receiver.setPortName(this->serialNamebox->currentText());
     this->receiver.setBaudRate(76800);
     this->receiver.setStopBits(QSerialPort::OneStop);
     this->receiver.setParity(QSerialPort::NoParity);
     this->receiver.setDataBits(QSerialPort::Data8);
     this->receiver.setFlowControl(QSerialPort::NoFlowControl);
     bool isok = this->receiver.open(QIODevice::ReadOnly|QIODevice::WriteOnly);

     if(isok){

       this->connectBt->setText(tr("关闭"));
       QString information = this->receiverInfor->description();

       if(information == this->objctDeviceinfor){

         this->serialInfo->setText(information+"\n"+tr("这是需要的设备"));
       }
       else{

         this->serialInfo->setText(information+"\n"+tr("这不是需要的设备请重新连接"));
       }

     }
     emit openOrClose(true);

    }
    else{

      if(tr("关闭") == this->connectBt->text()){
        this->receiver.close();
        this->connectBt->setText(tr("连接"));
        this->serialInfo->clear();
        delete this->receiverInfor;
        emit openOrClose(false);
      }

    }
}

void SerialWindow::scanSerial(){

  QStringList newSerialPortNames;

  for(auto &newSerial: QSerialPortInfo::availablePorts()){

    newSerialPortNames.append(newSerial.portName());
  }

   if(newSerialPortNames != this->serialPortNames){

      this->serialPortNames.clear();
      this->serialNamebox->clear();
      this->serialPortNames = newSerialPortNames;
      this->serialNamebox->addItems(newSerialPortNames);
      emit updateSerialPortNames();
   }

}

void SerialWindow:: send(QByteArray data){

    if(this->receiver.isOpen()){

      this->receiver.write(data);
    }
}


