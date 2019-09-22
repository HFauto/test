#ifndef WRENCH_H
#define WRENCH_H

#include <QWidget>
#include <QString>
#include <Serialwindow.h>
#include <wrechversion1.h>
namespace Ui {
class Wrench;
}

class Wrench : public QWidget
{
    Q_OBJECT

public:
    explicit Wrench(QWidget *parent = 0);
    ~Wrench();

private:
    Ui::Wrench *ui;
    SerialWindow serialWindow;
    Version1 version1;
    int numOfWrench = 0;
private:
  void setConnect(void);

public slots:
   void replayWrech(QByteArray data);
   void setNumOfWrench();
private slots:
   void on_wrechSpinBox_editingFinished();
   void on_CountspinBox_editingFinished();
   void on_pageSpinBox_editingFinished();
};

#endif // WRENCH_H
