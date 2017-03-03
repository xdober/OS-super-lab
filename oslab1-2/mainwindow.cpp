#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QTime>
#include <QDate>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timestr = new QLabel(this);
    QFont ft;
    ft.setPointSize(13);
    timestr->setFont(ft);
    QDateTime dateTime;
    QString currentTime;
    dateTime = QDateTime::currentDateTime();
    currentTime = dateTime.toString("yyyy-MM-dd hh:mm:ss dddd");
    timestr->setText(currentTime);
    timestr->setGeometry(80,100,240,40);
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    //获取系统现在的时间
     QDateTime time = QDateTime::currentDateTime();
     //设置系统时间显示格式
     QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
     //在标签上显示时间
     timestr->setText(str);
}

