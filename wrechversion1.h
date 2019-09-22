#ifndef WRENCH_VERSION_1_H
#define WRENCH_VERSION_1_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QByteArray>
#include <QList>
#include <theThread.h>

class Version1: public QObject{

    Q_OBJECT
public:
    QByteArray  searchPacket;//连线包
    QByteArray  countSettingPacket;//计数设定包
protected:
    //bool isCreateNextStore = true;
    bool isEmpty = true;//扳手数量是否为空
private:

  QList<QByteArray>  dataPacket;//组合好的数据
  QList<QByteArray>  FilterAfterPacket;//过滤后的包
  QSerialPort *receiver;

public:
     Version1(QWidget *parent = 0);
     void bindReceiver(QSerialPort *receiver);
     ~Version1();
     ReadData readDataThread;//组和数据 需要串口提供数据源
     Replay   replayThread;  //根据处理 发射连接成功信号与回复信号
     Unpacket unPacketThread;//解好的信息在这里面
protected:
   uchar count0Code(QByteArray&object,int startPos,int endAfterPos/*位后*/);//计算校验码
private:
     void setConnect();

public slots:
  void startThread(bool isOk);
  void closeReadThread();
  void closeReplayThread();
  void closeUnpacketThread();
  void sendConnectPacket();
  void sendCountSettingPacket();
  void getDataToBuffer();
};



#endif
