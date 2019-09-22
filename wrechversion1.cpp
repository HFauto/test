#include "wrechversion1.h"
#include <QDebug>
QList<QByteArray>  dataPacket;//组合好的数据
QList<QByteArray>  FilterAfterPacket;//过滤后的包
Version1:: Version1(QWidget *parent):QObject(parent){

  //绑定数据
  this->readDataThread.setParent(this);
  this->replayThread.setParent(this);
  this->unPacketThread.setParent(this);
  this->readDataThread.bindDataPacket(&this->dataPacket);
  this->replayThread.bindDataPacket(&this->dataPacket);
  this->replayThread.bindFiltePacket(&this->FilterAfterPacket);
  this->unPacketThread.bindFiltePacket(&this->FilterAfterPacket);  
  //初始化包
  char data0[48] ={(char)0xA5,(char)0xA5,(char)0x20,(char)0x01,(char)0x00,(char)0x00,(char)0x80};
  char data1[48] ={(char)0XA5,(char)0XA5,(char)0X20,(char)0X01,(char)0X00,(char)0X00,(char)0X22,char(0x01)};
  searchPacket.append(data0,48);
  countSettingPacket.append(data1,48);
}

void Version1:: startThread(bool isOk){

   if(isOk){

     this->readDataThread.setQuitCode(false);
     this->replayThread.setQuitCode(false);
     this->unPacketThread.setQuitCode(false);

     this->readDataThread.start();
     this->replayThread.start();
     this->unPacketThread.start();
     qDebug()<<"OK";
   }
     qDebug()<<"NO";
}

void Version1:: closeReadThread(){

   this->readDataThread.setQuitCode(true);
   qDebug()<<"退出1OK";
 }


void Version1:: closeReplayThread(){


   this->replayThread.setQuitCode(true);
   qDebug()<<"退出2OK";
}

void Version1:: closeUnpacketThread(){

   this->unPacketThread.setQuitCode(true);
   qDebug()<<"退出3OK";
}

void Version1::setConnect(){

  connect(this->receiver,SIGNAL(aboutToClose()),
          this,SLOT(closeReadThread()));

  connect(&this->readDataThread,SIGNAL(finished()),
          this,SLOT(closeReplayThread()));

  connect(&this->replayThread,SIGNAL(finished()),
          this,SLOT(closeUnpacketThread()));

  connect(this->receiver,SIGNAL(readyRead()),this,SLOT(getDataToBuffer()));
}


void Version1::bindReceiver(QSerialPort *receiver){

    this->receiver = receiver;
   setConnect();
}

void Version1::sendConnectPacket(){

   if(receiver->isOpen()){
     receiver->write(this->searchPacket);
   }
}

void Version1::sendCountSettingPacket(){

    if(this->receiver->isOpen()){

      receiver->write(this->countSettingPacket);
    }
}


void Version1::getDataToBuffer(){

   QMutexLocker bufferLocker(&this->readDataThread.operatorBuffer);
   this->readDataThread.BUFFER.append(this->receiver->readAll());
}

Version1::~Version1(){

}

//待实现
//主线程根据 其他线程信号 通过串口发送数据 ok
//串口正确连接后启动线程 ok
//把处理的数据信息显示到文本宽中
//可以交互的查看未读取的数据信息 上下与跳转
//可以发送连线数据 并判断当前有几个扳手已经连接 ok
//可以显示当前的 组合数据数量,加工后的数据数量,可读取的信息数量,已读取的信息数量
//reply线程根据组合数据的数量来 开启或关闭这个线程 ok
//unpacket线程根据被加工数据的数量来 开启或关闭这个线程 ok
//关闭连接后待数据全部处理完毕后关闭全部线程 ok
