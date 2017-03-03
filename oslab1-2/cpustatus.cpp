#include "cpustatus.h"
#include "ui_cpustatus.h"
#include <QLabel>
#include <QTimer>
#include <unistd.h>

cpuStatus::cpuStatus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cpuStatus)
{
    ui->setupUi(this);
    cpuStr = new QLabel(this);
    QFont ft;
    ft.setPointSize(13);
    cpuStr->setFont(ft);
    cpuStr->setGeometry(80,100,220,40);
    sprintf(cstat,"CPU usage :………… %%");
    cpuStr->setText(cstat);
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateStatus()));
    timer->start(2000);

}

cpuStatus::~cpuStatus()
{
    delete ui;
}

void cpuStatus::updateStatus()
{
    fp = fopen("/proc/stat","r");
    fgets(info, 200, fp);
    sscanf(info, "%s%lf%lf%lf%lf", cpu[0], &user[0], &nice[0], &system[0], &idle[0]);
    fclose(fp);
    total[0] = (user[0] + nice[0] + system[0] + idle[0]);
    sleep(1);
    fp = fopen("/proc/stat","r");
    fgets(info, 200, fp);
    sscanf(info, "%s%lf%lf%lf%lf", cpu[1], &user[1], &nice[1], &system[1], &idle[1]);
    fclose(fp);
    total[1] = (user[1] + nice[1] + system[1] + idle[1]);
    sprintf(cstat,"CPU usage : %.8f %%", (1-(idle[1]-idle[0])/(total[1]-total[0]))*100);
    cpuStr->setText(cstat);
}
