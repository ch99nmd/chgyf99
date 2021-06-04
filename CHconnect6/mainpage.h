#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include<QPushButton>


namespace Ui {
class mainpage;
}

class mainpage : public QWidget
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);


    ~mainpage();

private:
    Ui::mainpage *ui;

signals:
    void mysignal();  //自定义信号
public slots:
     void sendslot();  //发出信号
private slots:
     void on_pushButton_clicked();
     void on_pushButton_2_clicked();
};

#endif // MAINPAGE_H
