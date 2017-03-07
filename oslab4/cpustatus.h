#ifndef CPUSTATUS_H
#define CPUSTATUS_H

#include <QWidget>
#include <QTimer>
#include <QLabel>

namespace Ui {
class cpuStatus;
}

class cpuStatus : public QWidget
{
    Q_OBJECT

public:
    explicit cpuStatus(QWidget *parent = 0);
    ~cpuStatus();
    FILE *fp;
    double user[2], nice[2], system[2], idle[2], total[2];
    char info[200], cpu[20][2];
    QLabel *cpuStr;
    char cstat[100];
    QTimer *timer;
    QFont ft;

private slots:
    void updateStatus();
private:
    Ui::cpuStatus *ui;
};

#endif // CPUSTATUS_H
