#ifndef CHESS_H
#define CHESS_H



class chess
{

public:
    chess();

    int state; //游戏状态，1为正在进行，0为未进行
    bool player; //下棋方
    void clear();  //清理棋盘
    bool ying(int x,int y);//判断是否输赢
    bool pingju();  //判断是否和棋

    bool jinshou(int x,int y); //判断是否禁手
    void startgame();  //开始游戏
    void updateMap(int x, int y); //更新棋盘

    void actionByPerson(int x,int  y); //人进行操作

    int board[21][21];  //数组记录棋盘棋子，空白为0，白子为-1，黑子为1


    int white,black;

};

#endif // GAME_H
