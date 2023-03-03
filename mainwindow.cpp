#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timeUpdate();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeUpdate()
{
    //timer0 =new QTimer;

    //LCDNUMER部分
    ui->lcdNumber->setDigitCount(5);
    ui->lcdNumber_2->setDigitCount(20);
    // 设置显示外观
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    // 设置样式
    ui->lcdNumber->setStyleSheet("border: 1px solid green; color: green; background: silver;");
    ui->lcdNumber_2->setStyleSheet("border: 1px solid green; color: green; background: silver;");

    ui->lcdNumber->display(countdown.toString("mm:ss"));
    ui->lcdNumber_2->display(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
   //qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //qDebug()<<countdown.addMSecs(-10).toString("mm:ss");


    //TIMEEDIT部分
    ui->timeEdit->setDisplayFormat("mm:ss");
    ui->timeEdit->setDateTime(countdown);

    ui->timeEdit_2->setDisplayFormat("mm:ss");
    ui->timeEdit_2->setDateTime(QDateTime::fromString( "03:00", "mm:ss"));




   countdown=QDateTime::fromString(ui->timeEdit->dateTime().time().toString("mm:ss"), "mm:ss");


   connect(ui->pushButton,&QPushButton::clicked,[this](){
       if(iscounting==0)
       {//开始计时
           ui->pushButton->setText("暂停");
           timer1->start(1000);
           iscounting=1;
           //文件的路径可以是资源文件路径也可以是本地文件系统路径
           QSound::play(":/new/prefix1/计时开始.wav");
       }
       else if(iscounting==1)
       {
           ui->pushButton->setText("继续");
            timer1->stop();
            iscounting=2;
            ui->lcdNumber->setStyleSheet("border: 1px solid red; color: red; background: silver;");
       }
       else if(iscounting==2)
       {
           ui->pushButton->setText("暂停");
            timer1->start(1000);
            iscounting=1;
            ui->lcdNumber->setStyleSheet("border: 1px solid green; color: green; background: silver;");
       }
   });

   connect(ui->timeEdit,&QTimeEdit::timeChanged,[this](){
       if(iscounting==0)
       {
           countdown=QDateTime::fromString(ui->timeEdit->dateTime().time().toString("mm:ss"), "mm:ss");
           ui->lcdNumber->display(countdown.toString("mm:ss"));

       }

   });

   connect(ui->pushButton_3,&QPushButton::clicked,[this](){
           countdown=QDateTime::fromString(ui->timeEdit->dateTime().time().toString("mm:ss"), "mm:ss");
           ui->lcdNumber->display(countdown.toString("mm:ss"));
           timer1->stop();
           //timer1->start(1000);
           iscounting=0;
           ui->pushButton->setText("开始");
           ui->lcdNumber->setStyleSheet("border: 1px solid green; color: green; background: silver;");
           sec_count=-1;




   });


   connect(timer0,SIGNAL(timeout()),this,SLOT(chTime()));
   connect(timer1,SIGNAL(timeout()),this,SLOT(Timecountdown()));



   timer0->start(1000);

}

void MainWindow::chTime()
{

    ui->lcdNumber_2->display(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

}

void MainWindow::Timecountdown()
{

//    sec_count++;
//    qDebug()<<sec_count;

    countdown=countdown.addSecs(sec_count);


    //计时结束
    if (countdown.operator == (QDateTime::fromString( "00:00", "mm:ss")))
    {
         QSound::play(":/new/prefix1/计时结束.wav");
        if(!ui->checkBox->isChecked())
        {   qDebug()<<"stop";
             timer1->stop();
             ui->pushButton->setText("开始");
             iscounting=0;
             countdown=QDateTime::fromString(ui->timeEdit->dateTime().time().toString("mm:ss"), "mm:ss");
             ui->lcdNumber->display(countdown.toString("mm:ss"));


          }
        else
        {
            sec_count=1;
        }
    }

    if(ui->checkBox->isChecked()&&sec_count==1)
    {

        static bool state=true;
        if (state)
        {
        ui->lcdNumber->setStyleSheet("border: 1px solid green; color: red; background: silver;");
        state=false;
        }
        else
         {
        ui->lcdNumber->setStyleSheet("border: 1px solid green; color: white; background: silver;");
        state=true;
        }
       static int times=0;
       times++;
       if(times%5==0)
        QSound::play(":/new/prefix1/超时.wav");

    }


    //倒计时提醒
     QString alarm=ui->timeEdit_2->dateTime().time().toString("mm:ss");

     if (countdown.operator == (QDateTime::fromString( alarm, "mm:ss")))
     {
              qDebug()<<"alarm";
               QSound::play(":/new/prefix1/提醒.wav");

     }


    ui->lcdNumber->display(countdown.toString("mm:ss"));

}



