#ifndef RDATATHREAD_H
#define RDATATHREAD_H
#include <QThread>
#include <QIODevice>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include <QSemaphore>
#include <QVariant>
#include <iterator>
#include <QDebug>

extern QMutex SetOfPackageslocker;//组包锁
extern QSemaphore thePacketNum;//组合包数量
extern QMutex FilterPacketlocker;//滤包锁
extern QSemaphore FilterAfterPacketNum;//过滤包的数量

typedef enum{
   N_m   = 0,
   In_lb = 1,
   Ft_lb = 2,
   kg_cm = 3
 }UnitCode;

typedef enum{
   Inferror  = 0X00,
   ThirdInf  = 0X03,
   FourthInf = 0X04
 }InfKind;

typedef struct {
QString targetTorque;
QString torqueUnit;
QString meaSureTorque;
}Information3;
Q_DECLARE_METATYPE(Information3);

typedef struct {
QString targetAngle;//目标角度
QString triggerTorque;//这个数据固定单位N.m
QString meaSureTorqueUnit;//量测侧扭力单位
QString meaSureAngle;
QString meaSureTorque;//量测侧扭力
}Information4;
Q_DECLARE_METATYPE(Information4);

typedef struct{
uchar receiverId;//接收器ID
uchar wrenchId;//扳手ID
uchar ppNumber;//封包序号
InfKind infKindCode = Inferror;//数据种类
uchar boltNumber;
QVariant dataInfor;
}Information;

class ReadData : public QThread
{
   Q_OBJECT

private:
      QByteArray  headCheckCode;//头检查码
     bool quitCode;
public:
    QByteArray BUFFER;
    ReadData(QObject *parent = 0);

    void setReceiver(QSerialPort *object);
    void bindDataPacket(QList<QByteArray> *object);
    void setQuitCode(bool isQuit);
    QMutex operatorBuffer;     
protected:
    void run();

private:

   QList<QByteArray> *theDataPackets = NULL;//组合数据包

signals:
     void closeRead();

};

class Replay : public QThread{

   Q_OBJECT
public:

      Replay(QObject *parent = 0);

      void setQuitCode(bool isQuit);
      void bindDataPacket(QList<QByteArray> *object);
      void bindFiltePacket(QList<QByteArray> *object);
      bool count0Check(QByteArray&object,int startPos,int endAfterPos/*位后*/);//校验和检查
private:
   QList<QByteArray> *theDataPackets = NULL;//组合数据包
   QList<QByteArray> *FilterAfter_DataPacket = NULL;//过滤后的包
   QByteArray  replayPacket;//回复包
   bool quitCode;
protected:
      void run();
signals:
   void  receiveIsOk(QByteArray replayContent);
   void  connectIsOk();
   void  tryCloseReplay();

};

class Unpacket :public QThread{

    Q_OBJECT  

protected:
    QMutex opreationInfor;
    QSemaphore numberOfInfor;
public:
      Unpacket(QObject *parent = 0);

      void setQuitCode(bool isQuit);
      void bindFiltePacket(QList<QByteArray> *object);
      QList<Information> getInforList(int number,bool &isok);
      Information checkInfor(int pos);
      uchar count0Code(QByteArray &object, int startPos, int endAfterPos);
      float countTorqueF(uchar lByte,uchar hByte,uchar point);//计算扭力
      int   countAngle(uchar lByte,uchar hByte );//计算角度
      int getNumOfInf();//获取可用信息数目,这个信息数目不可能为负数

private:
   QList<QByteArray> *FilterAfter_DataPacket = NULL;//过滤后的包
   QList<Information> theDataPacket_Infs;//数据包信息表
   bool quitCode;
protected:
      void run();
signals:
      void tryCloseUnpacket();

};



#endif // RDATATHREAD_H
