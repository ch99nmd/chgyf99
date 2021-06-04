#include "chess.h"
#include"mainwindow.h"
#include <utility>
#include <stdlib.h>
#include <time.h>
#include<QDebug>
#include<QApplication>
#include<iostream>
#include<vector>
#include<QTimer>

using namespace std;

const int chessboard_size=21;  //棋盘尺寸

chess::chess()
{
   black=1;
   white=-1;
   state=0;
}

void chess::startgame()//开始游戏    函数返回值为void，无参数
{
    clear();//清理棋盘
    player=true;//黑棋先下

}

void chess::clear()//清理棋盘函数   函数返回值void,无参数
{
    for(int i=0;i<chessboard_size;i++)
    {
        for(int j=0;j<chessboard_size;j++)
        {
            board[i][j]=0;  //数组初始化置0
        }
    }
}

void chess::actionByPerson(int x, int y)//人操作函数，返回值void，参数为下棋点
{
    updateMap(x,y); //重绘
}

void chess::updateMap(int x,int y)
{
    if(player)  //根据下棋方填充数组
    {
        board[x][y]=1;
    }
    else
    {
         board[x][y]=-1;
    }
    player=!player;//交换下棋方


}





bool chess::ying(int clickX,int clickY)  //判断游戏输赢
{

    for (int i = 0; i < 6; i++)
    {
         if (clickY - i >= 0 &&
            clickY - i + 5 < chessboard_size &&
            board[clickX][clickY - i] == board[clickX][clickY - i + 1] &&
            board[clickX][clickY - i] == board[clickX][clickY - i + 2] &&
            board[clickX][clickY - i] == board[clickX][clickY - i + 3] &&
            board[clickX][clickY - i] == board[clickX][clickY - i + 4]&&
            board[clickX][clickY-i]==board[clickX][clickY-i+5])  //竖直方向
         {
           return true;
         }
         else if (clickX - i >= 0 &&
             clickX - i + 5 < chessboard_size &&
             board[clickX - i][clickY] == board[clickX - i + 1][clickY] &&
             board[clickX - i][clickY] == board[clickX - i + 2][clickY] &&
             board[clickX - i][clickY] == board[clickX - i + 3][clickY] &&
             board[clickX - i][clickY] == board[clickX - i + 4][clickY]&&
             board[clickX - i][clickY] == board[clickX - i + 5][clickY])  //水平方向
         {
             return true;
         }
         else if(clickX+i<chessboard_size&&clickX+i-5>=0&&clickY-i>=0&&clickY-i+5<chessboard_size&&
                 board[clickX+i][clickY-i]==board[clickX+i-1][clickY-i+1]&&
                 board[clickX+i][clickY-i]==board[clickX+i-2][clickY-i+2]&&
                 board[clickX+i][clickY-i]==board[clickX+i-3][clickY-i+3]&&
                 board[clickX+i][clickY-i]==board[clickX+i-4][clickY-i+4]&&
                 board[clickX+i][clickY-i]==board[clickX+i-5][clickY-i+5])  //斜向左下
         {
             return true;
         }
         else if (clickX - i >= 0 &&
                  clickX - i + 5 < chessboard_size &&
                  clickY - i >= 0 &&
                  clickY - i + 5 < chessboard_size &&
                  board[clickX - i][clickY - i] == board[clickX - i + 1][clickY - i + 1] &&
                  board[clickX - i][clickY - i] == board[clickX - i + 2][clickY - i + 2] &&
                  board[clickX - i][clickY - i] == board[clickX - i + 3][clickY - i + 3] &&
                  board[clickX - i][clickY - i] == board[clickX - i + 4][clickY - i + 4]&&
                  board[clickX - i][clickY - i] == board[clickX - i + 5][clickY - i + 5]) //斜向右下
              {
                  return true;
              }

    }
    return false;
}
bool chess::pingju()
{
    //棋盘全部占满棋子则和棋，有空位则不是和棋
    for(int i=0;i<chessboard_size;i++)
    {
        for(int j=0;j<chessboard_size;j++)
        {
            if(board[i][j]==0)
            {
                return false;
            }
        }
    }
    return true;
}

bool chess::jinshou(int x,int y)  //发生四四禁手和五五禁手都属于禁手
{
    int num=0,k=0;
    k=0;
    //向上
    for(int i=0;i<6;i++)
    {
        if(y+i<chessboard_size)
        {
            if(board[x][y+i]==1)
            {
                k++;
            }
            else if(board[x][y+i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    //qDebug()<<num;
    if(k>=4)
    {
        num++;
    }
    k=0;
    if(num>=2)
    {
        return true;
    }
    //向下
    for(int i=0;i<6;i++)
    {
        if(y-i>=0)
        {
            if(board[x][y-i]==1)
            {
                k++;
            }
            else if(board[x][y-i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向左
    for(int i=0;i<6;i++)
    {
        if(x-i>=0)
        {
            if(board[x-i][y]==1)
            {
                k++;
            }
            else if(board[x-i][y]==white)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向右

    for(int i=0;i<6;i++)
    {
        if(x+i<chessboard_size)
        {
            if(board[x+i][y]==1)
            {
                k++;
            }
            else if(board[x+i][y]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向左上
    for(int i=0;i<6;i++)
    {
        if(x-i>=0&&y-i>=0)
        {
            if(board[x-i][y-i]==1)
            {
                k++;
            }
            else if(board[x-i][y-i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向左下
    for(int i=0;i<6;i++)
    {
        if(x-i>=0&&y+i<chessboard_size)
        {
            if(board[x-i][y+i]==1)
            {
                k++;
            }
            else if(board[x-i][y+i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向右上
    for(int i=0;i<6;i++)
    {
        if(x+i<chessboard_size&&y-i>=0)
        {
            if(board[x+i][y-i]==1)
            {
                k++;
            }
            else if(board[x+i][y-i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    k=0;
    //向右下
    for(int i=0;i<6;i++)
    {
        if(x+i<chessboard_size&&y+i<chessboard_size)
        {
            if(board[x+i][y+i]==1)
            {
                k++;
            }
            else if(board[x+i][y+i]==-1)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    if(k>=4)
    {
        num++;
    }
    if(num>=2)
    {
        return true;
    }
    return false;


}
