#include "theThread.h"

Replay:: Replay(QObject *parent):QThread(parent){

 replayPacket.append(2,0X5A);
 replayPacket.append(3,0X00);
 quitCode = false;
}

void Replay:: setQuitCode(bool isQuit){

   this->quitCode = isQuit;
}

void Replay::bindDataPacket(QList<QByteArray> *object){

    this->theDataPackets = object;
}

void Replay::bindFiltePacket(QList<QByteArray> *object){

   this->FilterAfter_DataPacket = object;
}



bool Replay::count0Check(QByteArray&object,int startPos,
                         int endAfterPos/*位后*/){

    uchar check = 0;
       for(;startPos < endAfterPos;startPos++){

          check -= static_cast<uchar>( object.at(startPos) );
       }

      if(0 == check){

       return true;
      }

    return false;
}//校验和检查


void Replay::run(){

  static QByteArray preData(0);//上一个数据 过滤作用
  QByteArray temp(0);

  while(1){

     if(theDataPackets->isEmpty()){

         if(quitCode){

            return;//退出线程
         }
     }
     else{

      QMutexLocker dataPacketLocker(&SetOfPackageslocker);
      thePacketNum.acquire(1);//申请一个组合包资源
      temp = this->theDataPackets->at(0);
      this->theDataPackets->erase(theDataPackets->begin());//删除已读过的组合数据
      dataPacketLocker.unlock();//组合包操作完毕解锁

      if((preData != temp)||temp.at(9)<1){//重发小于1或不等于上次的数据包

        bool headBolckCheck = this->count0Check(temp,0,11);
        //bool endBolckCheck = this->count0Check(temp,11,48);

      if( true == headBolckCheck&&
//          true == endBolckCheck &&
          temp.at(9)>0){

        char *data = replayPacket.data();
        data[2] = temp.at(11+1);//扳手ID
        data[3] = temp.at(11+2);//封包序号
        data[4] = temp.at(7);//记录位置
        emit this->receiveIsOk(replayPacket);
        //回复数据成功接收包  以信号的方式通知

        QMutexLocker filterLocker(&FilterPacketlocker);//过滤锁
        this->FilterAfter_DataPacket->append(temp);
        FilterAfterPacketNum.release(1);//增加一个滤过的数据
        preData = temp;
      }
      else if(0x00 == temp[9]){
       emit this->connectIsOk();
      }//连接成功 以信号的方式通知
     }//数据与上次不同||重发小于1 则进行 检查,回复,挂接操作
   }//非空执行
  }//总循环
}//run


