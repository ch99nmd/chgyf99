#include "mainwindow.h"
#include"mainpage.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPen>
#include<QPaintEvent>
#include<QLabel>
#include<QBitmap>
#include<QPixmap>
#include<QPushButton>
#include<qmath.h>
#include<QBrush>
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#include<QMenuBar>
#include<QMenu>
#include<QIcon>
#include<qtimer.h>



int chessboard_size=21;  //棋盘线条数
int boundary=40;  //棋盘距离边缘的距离
int square_length=40;  //棋盘格子大小
int mouseOk=30; //鼠标的有效点击距离
int flag_length=11; //落子标记边长
int r=17; //棋子半径

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(2*boundary+(chessboard_size-1)*square_length+400,2*boundary+(chessboard_size-1)*square_length);


    ui->pushButton->setText("双人对决");
    ui->pushButton->setFont(QFont("微软雅黑",30,1000));
    ui->pushButton->setGeometry(900,200,300,70); //设置按钮位置和尺寸

    ui->pushButton->setFlat(true);  //设置按钮透明

    back=new QPushButton(this);
    back->setGeometry(900,600,300,70);
    back->setText("关闭游戏");
    back->setFont(QFont("微软雅黑",30,1000));
    back->setFlat(true);


    initgame();  //默认初始化
    this->hide();
    page.show();
    connect(back,&QPushButton::clicked,this,&MainWindow::close);   //连接信号和槽

    connect(&page,&mainpage::mysignal,this,&MainWindow::myslot);


}

void MainWindow::initgame()   //初始化
{

        game=new chess;
}
void MainWindow::init()
{
    if(game)
    {
        delete game;
    }
    game=new chess;

    game->state=1;

    clickPosX=-1;
    clickPosY=-1;
    game->startgame();
    update();
}

void MainWindow::myslot()
{
    this->show();  //游戏界面显示
    page.hide();   //子窗口隐藏
}

MainWindow::~MainWindow()
{
    delete ui;
    if(game)   //撤销游戏指针
    {
        delete game;
        game = nullptr;
    }

}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //画家
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/pic/p.png"));
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿,防止图像走样

    QPen pen; //画笔
    pen.setWidth(2);  //画笔的线条宽度
    pen.setColor(Qt::black);
    painter.setPen(pen);  //将画笔交给画家
    for(int i=0;i<chessboard_size;i++)
    {
        painter.drawLine(boundary,boundary+i*square_length,boundary+(chessboard_size-1)*square_length,boundary+i*square_length);  //画横线
        painter.drawLine(boundary+i*square_length,boundary,boundary+i*square_length,boundary+(chessboard_size-1)*square_length);//画竖线

    }
    QBrush brush; //笔刷
    brush.setStyle(Qt::SolidPattern);
    if(clickPosX>=0&&clickPosX<chessboard_size&&clickPosY>=0&&clickPosY<chessboard_size&&game->state==1&&game->board[clickPosX][clickPosY]==0)  //范围内有效，绘制鼠标将要落子的标记点
    {

            brush.setColor(Qt::magenta);
            painter.setBrush(brush);
            painter.drawRect(boundary + square_length * clickPosX - flag_length / 2, boundary + square_length * clickPosY  - flag_length / 2, flag_length, flag_length);


    }
    //根据数组情况绘制黑白棋子
    for(int i=0;i<chessboard_size;i++)
    {
        for(int j=0;j<chessboard_size;j++)
        {

            if(game->board[i][j]==1&&game->state==1) //游戏进行中才允许绘制棋子
           {
              brush.setColor(Qt::black);
              painter.setBrush(brush);
              painter.drawEllipse(QPoint(boundary + square_length * i ,boundary + square_length * j),r,r);
           }
            else if(game->board[i][j]==-1&&game->state==1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(boundary + square_length * i ,boundary + square_length * j),r,r);
            }
        }
    }
    update();

}






void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    int x=event->x();
    int y=event->y();

    //保证鼠标在有效范围内,且棋盘边缘不落子
    if (x >= boundary-mouseOk  &&
            x <= boundary+(chessboard_size-1)*square_length+mouseOk  &&
            y >= boundary-mouseOk  &&
            y <= boundary+(chessboard_size-1)*square_length+mouseOk&&game->state==1)
    {

        // 获取距离最近的左上角的点
        int row = (x) / square_length;
        int col =( y) / square_length;


        int leftTopPosX = boundary + square_length * row;
        int leftTopPosY = boundary + square_length * col;
        //qDebug()<<leftTopPosX<<" "<<leftTopPosY;
        // 根据距离算出合适的点击位置,一共四个点，根据两点距离选最近的
        clickPosX = -1; // 初始化
        clickPosY = -1;
        int len = 0;

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));//sqrt开方
        if (len < mouseOk)  //在有效点范围内
        {
            clickPosX = row;
            clickPosY = col;
        }
        len = sqrt((x - leftTopPosX - square_length) * (x - leftTopPosX - square_length) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < mouseOk)
        {
            clickPosX = row+1;
            clickPosY = col;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - square_length) * (y - leftTopPosY - square_length));
        if (len < mouseOk)
        {
            clickPosX = row;
            clickPosY = col+1;
        }
        len = sqrt((x - leftTopPosX - square_length) * (x - leftTopPosX - square_length) + (y - leftTopPosY - square_length) * (y - leftTopPosY - square_length));
        if (len < mouseOk)
        {
            clickPosX = row + 1;
            clickPosY = col + 1;
        }

    }
        update();

}

    // 存了坐标后更新界面



void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{


      if (clickPosX != -1 && clickPosY != -1&&game->state==1)
      {
             play();  //人执行
      }
      update();
     //人操作

}

void MainWindow::play()
{

    if (clickPosX != -1 && clickPosY != -1 && game->board[clickPosX][clickPosY] == 0)
    {
        game->actionByPerson(clickPosX,clickPosY); //人进行下棋

        isEnd();
        update(); //更新界面
    }
}

void MainWindow::isEnd()
{
    if(clickPosX>=0&&clickPosX<chessboard_size&&clickPosY>=0&&clickPosY<chessboard_size&&game->board[clickPosX][clickPosY]!=0) //判断游戏输赢
    {
        if(game->board[clickPosX][clickPosY]==1&&game->jinshou(clickPosX,clickPosY)&&game->state==1)  //判断黑棋落子是否禁手
        {

            QMessageBox::StandardButton standar=QMessageBox::information(this,"游戏结束！","禁手！ White-player win！\n 点击Ok返回主界面！",QMessageBox::Ok);
            if(standar==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("双人对决");

            }
        }
        else if(game->ying(clickPosX,clickPosY)==true&&game->state==1)  //弹出提示框
        {


            QString string;
            if(game->board[clickPosX][clickPosY]==1)
            {
                string="黑棋胜";   //黑棋胜
            }
            else
            {
                string="白棋胜";  //白棋胜
            }
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this," 游戏结束！",string,QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();


            }
        }
        else if(game->pingju()&&game->state==1)
        {

            game->state=0;
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this,"游戏结束！","和棋",QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("双人对决");

            }
        }
    }
}



void MainWindow::on_pushButton_clicked()
{


     ui->centralwidget->setMouseTracking(true); //激活鼠标追踪
     setMouseTracking(true);  //激活整个窗体的鼠标追踪
     ui->pushButton->setMouseTracking(true); //进入某个按钮时，鼠标追踪属性失效，因此我们也需要激活该按钮的鼠标追踪功能

     init();  //初始化



     update();
}




