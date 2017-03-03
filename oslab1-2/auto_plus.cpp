#include "auto_plus.h"
#include "ui_auto_plus.h"
#include <QTimer>

auto_plus::auto_plus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::auto_plus),
    srcNum(0),
    sum(0)
{
    ui->setupUi(this);
    sumStr = new QLabel(this);
    QFont ft;
    ft.setPointSize(13);
    sumStr->setFont(ft);
    sumStr->setText(QString::number(sum,10));
    sumStr->setGeometry(180,100,100,40);
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSum()));
    timer->start(3000);
}

auto_plus::~auto_plus()
{
    delete ui;
}

void auto_plus::updateSum()
{
    if(srcNum <= 100){
        sum = sum + srcNum;
        srcNum = srcNum + 1;
        sumStr->setText(QString::number(sum,10));
    }
}
