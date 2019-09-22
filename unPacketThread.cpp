#include "theThread.h"

Unpacket::Unpacket(QObject *parent):QThread(parent){

    quitCode = false;
}

void Unpacket:: setQuitCode(bool isQuit){

   this->quitCode = isQuit;
}

float Unpacket::countTorqueF(uchar lByte,uchar hByte, uchar point){

 float value = 1;

   while(point){
       value *= 10;
       point--;
   }
   return (hByte*256+lByte)/value;
}

int Unpacket::countAngle(uchar lByte,uchar hByte){

    return hByte*256+lByte;
}

uchar Unpacket::count0Code(QByteArray &object, int startPos, int endAfterPos){

    uchar code = 0;

   for(;startPos <= endAfterPos;startPos++){

    code -= static_cast<uchar>( object.at(startPos) );
  }

    return code;
}

void  Unpacket:: bindFiltePacket(QList<QByteArray> *object){

    this->FilterAfter_DataPacket = object;
}

QList<Information> Unpacket:: getInforList(int number,bool &isok){

  QMutexLocker inforLocker(&this->opreationInfor);
  QList<Information> container;
  isok = this->numberOfInfor.tryAcquire(number);//尝试申请不会阻塞
  if(true == isok){

    QList<Information>::iterator beginItrt = this->theDataPacket_Infs.begin();
    for(beginItrt;beginItrt<beginItrt+number;beginItrt++){

    container.append(beginItrt[0]);
    }
    this->theDataPacket_Infs.erase(beginItrt,beginItrt+number);
  }
  return container;
}

void Unpacket::run(){

while(1){
 Information  newInfor;
 Information3 thirdInf;
 Information4 fourthInf;

 if(FilterAfter_DataPacket->isEmpty()){

   if(quitCode){

     return;//退出线程
    }
 }
 else{
     QMutexLocker filterLocker(&FilterPacketlocker);//过滤加锁
     FilterAfterPacketNum.acquire(1);//申请一个滤过的数据包
     QByteArray temp = FilterAfter_DataPacket->at(0);
     FilterAfter_DataPacket->erase(FilterAfter_DataPacket->begin());//删除一个以读数据
     filterLocker.unlock();//过滤解锁
     //开始解析数据

     newInfor.receiverId  = (uchar)temp.at(11+0);
     newInfor.wrenchId    = (uchar)temp.at(11+1);
     newInfor.ppNumber    = (uchar)temp.at(11+2);
     newInfor.infKindCode = (InfKind)temp.at(11+3);
     newInfor.boltNumber  = (uchar)temp.at(15+0);

     if( ThirdInf == newInfor.infKindCode){

       uchar data0[3] = {(uchar)temp.at(15+1),(uchar)temp.at(15+2),(uchar)temp.at(15+3)};
       uchar data1[3] = {(uchar)temp.at(15+5),(uchar)temp.at(15+6),(uchar)temp.at(15+7)};
       float targetTorque= this->countTorqueF(data0[0],data0[1],data0[2]);
       float meaSureTorque = this->countTorqueF(data1[0],data1[1],data1[2]);

       thirdInf.targetTorque = QString("%1").arg(targetTorque);//目标扭矩
       thirdInf.meaSureTorque = QString("%1").arg(meaSureTorque);//实测扭矩
       switch(temp.at(15+4)){

         default:break;
         case N_m:   thirdInf.torqueUnit = "N.m";break;
         case In_lb: thirdInf.torqueUnit = "In.lb";break;
         case Ft_lb: thirdInf.torqueUnit = "Ft_lb";break;
         case kg_cm: thirdInf.torqueUnit = "kg_cm";break;
       }
       newInfor.dataInfor.setValue<Information3>(thirdInf);
       QMutexLocker inforLocker(&this->opreationInfor);//操作信息加锁
       theDataPacket_Infs.append(newInfor);
       this->numberOfInfor.release(1);//增加一个信息
     }//三号资料
     else if( FourthInf == newInfor.infKindCode){

       uchar data0[2] = {(uchar)temp.at(15+1),(uchar)temp.at(15+2)};
       uchar data1[3] = {(uchar)temp.at(15+3),(uchar)temp.at(15+4),(uchar)temp.at(15+5)};
       uchar data2[2] = {(uchar)temp.at(15+7),(uchar)temp.at(15+8)};
       uchar data3[3] = {(uchar)temp.at(15+9),(uchar)temp.at(15+10),(uchar)temp.at(15+11)};

       int   targetAngle = this->countAngle(data0[0],data0[1]);
       float triggerTorque = this->countTorqueF(data1[0],data1[1],data1[2]);
       int   meaSureAngle = this->countAngle(data2[0],data2[1]);
       float meaSureTorque = this->countTorqueF(data3[0],data3[1],data3[2]);
       fourthInf.targetAngle   = QString("%1").arg(targetAngle);
       fourthInf.triggerTorque = QString("%1").arg(triggerTorque);
       fourthInf.meaSureAngle  = QString("%1").arg(meaSureAngle);
       fourthInf.meaSureTorque = QString("%1").arg(meaSureTorque);
       switch(temp.at(15+4)){//判断量侧的扭矩单位 触发扭矩单位固定为N.m

         default:break;
         case N_m:   fourthInf.meaSureTorqueUnit = "N.m";break;
         case In_lb: fourthInf.meaSureTorqueUnit = "In.lb";break;
         case Ft_lb: fourthInf.meaSureTorqueUnit = "Ft_lb";break;
         case kg_cm: fourthInf.meaSureTorqueUnit = "kg_cm";break;
       }
       newInfor.dataInfor.setValue<Information4>(fourthInf);
       QMutexLocker inforLocker(&this->opreationInfor);//操作信息加锁
       theDataPacket_Infs.append(newInfor);
       this->numberOfInfor.release(1);//增加一个信息
    }//四号资料
  }//非空执行
 }//总循环
}


int Unpacket:: getNumOfInf(){

   QMutexLocker inforLocker(&opreationInfor);
   return this->theDataPacket_Infs.count();
}

Information Unpacket:: checkInfor(int pos){

 Information error;
 error.infKindCode = Inferror;

 QMutexLocker inforLocker(&this->opreationInfor);

   if(!this->theDataPacket_Infs.isEmpty()){
      if(pos<theDataPacket_Infs.count()){

        return theDataPacket_Infs.at(pos);
      }
     }
 return error;
}




