#include "widget.h"
#include "ui_widget.h"
#include "expl.h"
#include<QPainter>
#include<QString>
#include<cstring>
#include<cerrno>
#include<unistd.h>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::getDir);

}

void Widget::paintEvent(QPaintEvent *)
{
    //实例化画家对象
    QPainter painter(this);
    painter.drawPixmap(410,31,310,180,QPixmap(":/Image/cimg.png"));
}

void Widget::getDir()
{
    QString qstr = ui->textEdit->toPlainText();
    string filePath = qstr.toStdString();
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    fstream inputFile;    //读取文件类
    inputFile.open(filePath,ios::in);
    if(!inputFile){
         ui->textBrowser_3->setText("该文件不存在");
         return;
    }
    ui->textBrowser_3->setText("读取该文件成功");
    cout<<filePath<<endl;
    string line;
    this->str="";
    while(getline(inputFile,line)){
        ui->textBrowser->append(QString::fromStdString(line));
        this->str.append(line);
        this->str.append("\n");
    }
    this->my_expL->AssignStr(str);
    this->my_expL->beginExpL();
    ui->textBrowser_2->setText(QString::fromStdString(this->my_expL->ExpLResult()));
}

Widget::~Widget()
{
    delete ui;
}

