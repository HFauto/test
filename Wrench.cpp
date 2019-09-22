#include "Wrench.h"
#include "ui_Wrench.h"

Wrench::Wrench(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wrench)
{

    this->serialWindow.setWindowTitle(tr("通信窗口"));
    this->serialWindow.show();
    this->version1.bindReceiver(&this->serialWindow.receiver);
    ui->setupUi(this);
    this->resize(395,433);
    setConnect();
}

Wrench::~Wrench(){



  delete ui;

}

void Wrench::replayWrech(QByteArray data){

   this->serialWindow.send(data);
}

void Wrench::setNumOfWrench(){

    this->numOfWrench += 1;
    ui->wrenchLineEdit->setText(QString("%1").arg(this->numOfWrench));
}

void Wrench::setConnect(void){

  connect(&this->serialWindow,SIGNAL(openOrClose(bool)),
          &this->version1,SLOT(startThread(bool)));//串口打开

  connect(&this->version1.replayThread,SIGNAL(receiveIsOk(QByteArray)),
          this,SLOT(replayWrech(QByteArray)));//回复扳手已收到信号

  connect(&this->version1.replayThread,SIGNAL(connectIsOk()),
          this,SLOT(setNumOfWrench()));//扳手告诉Pc连线成功

  connect(ui->searchWrenchBt,SIGNAL(clicked(bool)),
          &this->version1,SLOT(sendConnectPacket()));//pc发送连线信号

  connect(ui->setCountBt,SIGNAL(clicked(bool)),
          &this->version1,SLOT(sendCountSettingPacket()));

}



void Wrench::on_wrechSpinBox_editingFinished(){

    char *data = this->version1.countSettingPacket.data();
    data[8] = ui->wrechSpinBox->text().toUShort();
}//界面槽函数

void Wrench::on_CountspinBox_editingFinished()
{
    char *data = this->version1.countSettingPacket.data();
    data[9] = ui->CountspinBox->text().toUShort();
}//界面槽函数

void Wrench::on_pageSpinBox_editingFinished(){

int numOfPage = this->version1.unPacketThread.getNumOfInf();
int currentPage = ui->pageSpinBox->text().toInt()%numOfPage;
Information temp;
Information3 temp3;
Information4 temp4;
QString string;
  if(numOfPage>0){

    ui->pageLabel->setText(QString("%1%2%3").arg(currentPage).arg('/').arg(numOfPage));
    temp = this->version1.unPacketThread.checkInfor(currentPage);
  }
  if(temp.infKindCode != Inferror){

      string += "螺栓号:"+QString("%1").arg(temp.boltNumber)+"\n";
      string += "接收器ID:"+QString("%1").arg(temp.receiverId)+"\n";
      string += "扳手ID:"+QString("%1").arg(temp.wrenchId)+"\n";
      string += "封包号:"+QString("%1").arg(temp.ppNumber)+"\n";
  }

   if( ThirdInf == temp.infKindCode){

    temp3 = temp.dataInfor.value<Information3>();
    string += "目标扭矩:"+temp3.targetTorque+"\n";
    string += "测量扭矩:"+temp3.meaSureTorque+"\n";
    string += "扭矩单位:"+temp3.torqueUnit+"\n";
  }
  else if(FourthInf == temp.infKindCode){

    temp4 = temp.dataInfor.value<Information4>();
    string += "目标角度:"+temp4.targetAngle+"\n";
    string += "目标扭矩:"+temp4.triggerTorque + "N.m"+"\n";
    string += "测量角度:"+temp4.meaSureAngle+"\n";
    string += "测量扭矩:"+temp4.meaSureTorque+"\n";
    string += "测量扭矩单位:"+temp4.meaSureTorqueUnit+"\n";
  }
  if(!string.isEmpty()){
      ui->infText->setText(string);
  }
}
