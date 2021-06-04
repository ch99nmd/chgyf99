#include "mainpage.h"
#include "ui_mainpage.h"
#include<QPainter>
#include<QPaintEvent>


mainpage::mainpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainpage)
{
    ui->setupUi(this);

    setWindowTitle("六子棋");

    this->setFixedSize(400,300);



}



void mainpage::sendslot()
{

    emit mysignal();   //发出信号，等待主窗口接收
}



mainpage::~mainpage()
{
    delete ui;
}

void mainpage::on_pushButton_clicked()
{
    sendslot();
}

void mainpage::on_pushButton_2_clicked()
{
    close();
}
