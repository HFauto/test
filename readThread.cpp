#include "theThread.h"
#include <QDebug>
QMutex SetOfPackageslocker;//组包锁
QMutex FilterPacketlocker;//滤包锁
QSemaphore thePacketNum(0);//组合包数量
QSemaphore FilterAfterPacketNum(0);//过滤包的数量

ReadData:: ReadData(QObject *parent):QThread(parent){

  const char code[5] = {(char)0XA5,(char)0XA5,(char)0X10,(char)0X01,(char)0X02};
  this->headCheckCode.append(code,5);
  quitCode = false;
}

void ReadData:: setQuitCode(bool isQuit){

   this->quitCode = isQuit;
}

void ReadData:: bindDataPacket(QList<QByteArray> *object){

   this->theDataPackets = object;
}

void ReadData:: run(){

while(1){

 static QByteArray temp(0);
 QByteArray buffer(0);
 static bool isok = false;
 static int  size = 48;
 int i = 0;
 QMutexLocker bufferLocker(&operatorBuffer);//BUFFER加锁
 buffer.append(this->BUFFER);
 this->BUFFER.clear();
 bufferLocker.unlock();//提前解锁 //实际

//char data0[48] ={(char)0xA5,(char)0xA5,(char)0x20,(char)0x01,(char)0x00,(char)0x00,(char)0x80};
//buffer.append(data0,48);//调试

// char data1[48] = {
//     (char)0xA5,(char)0xA5,(char)0x10,(char)0x01,(char)0x64,(char)0x02,(char)0x02,
//     (char)0x1F,(char)0x00,(char)0x0D,(char)0x11,(char)0x02,(char)0x01,(char)0x00,(char)0x03,(char)0x2D,
//     (char)0x62,(char)0x01,(char)0x02,(char)0x02,(char)0x36,(char)0x00,(char)0x02,(char)0x00,
//     (char)0x2E,(char)0x79,(char)0x11,(char)0x00,(char)0x00,(char)0x00,(char)0x00,(char)0x00,(char)0x00,
//     (char)0x00,(char)0x00,(char)0x00,(char)0x00,(char)0x00,(char)0x00,(char)0x00,
//     (char)0x00,(char)0x00,(char)0x00,(char)0x7A,(char)0x01,(char)0x10,(char)0x01,(char)0x00};
//  buffer.append(data1,48);

 if(buffer.isEmpty()){

      if(quitCode){
          isok = false;
          size = 48;
         return;//退出线程
      }

  }
  else{
   qDebug()<<buffer;
   if((true == isok)){

      while(size){
      temp.append(buffer.at(i));
      i++;
      size--;
     };
     QMutexLocker dataPacketLocker(&SetOfPackageslocker);//组合数据加锁
     theDataPackets->append(temp);
     thePacketNum.release(1);//增加一个组合包数据
     qDebug()<<"temp = "<<temp;
     temp.clear();
     size = 48;
     isok = false;
     dataPacketLocker.unlock();//组合数据解锁
  }//弥补上一次缺少的数据

do{
     for(i;i<buffer.size();i++){

       if((uchar)buffer.at(i+0) == (uchar)headCheckCode.at(0)){

        if((uchar)buffer.at(i+1) == (uchar)headCheckCode.at(1)&&
           (uchar)buffer.at(i+2) == (uchar)headCheckCode.at(2)&&
           (uchar)buffer.at(i+3) == (uchar)headCheckCode.at(3)&&
           (uchar)buffer.at(i+6) == (uchar)headCheckCode.at(4)){
           isok = true;
           break;
        }//判断是否为资料包
        else if( 0XA5 == (uchar)buffer.at(i+1)&&
                 0X20 == (uchar)buffer.at(i+2)&&
                 0X01 == (uchar)buffer.at(i+3)&&
                 0X80 == (uchar)buffer.at(i+6)){
           isok = true;
           break;
        }//判断是否为连线包

       }
     }//获得开头码的第一个数据的位置

     if(isok){
       while(i<buffer.size()){
       temp.append(buffer.at(i));
       i++;
       size--;
       if(0 == size)break;
       }

       if(0 == size){
           QMutexLocker dataPacketLocker(&SetOfPackageslocker);//
           theDataPackets->append(temp);
           thePacketNum.release(1);//增加一个组合包数据
           qDebug()<<"temp = "<<temp;
           temp.clear();
           size = 48;
           isok = false;
           //return;//调试
       }//存储 开头码开始的48个数据//并初始化静态变量;
       //数据不够则下一次读数据弥补
     }
  }while(i<buffer.size());//此次数据组合结束
 }
 }
}




