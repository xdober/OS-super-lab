#include "mainwindow.h"
#include "auto_plus.h"
#include "cpustatus.h"
#include <QApplication>
#include <QLabel>
#include <unistd.h>

pid_t childpid1, childpid2;
int main(int argc, char *argv[])
{

    while((childpid1 = fork()) == -1);
    if(childpid1 == 0) {
        QApplication b(argc, argv);
        auto_plus sum;
        sum.setWindowTitle("auto plus");
        sum.show();
        sum.move(860,300);
        sum.setMinimumSize(400,300);
        sum.setMaximumSize(400,300);
        return b.exec();
    }
    else {
        while((childpid2 = fork()) == -1);
        if(childpid2 == 0) {
            QApplication c(argc, argv);
            cpuStatus status;
            status.setWindowTitle("CPU status");
            status.show();
            status.move(440,300);
            status.setMinimumSize(400,300);
            status.setMaximumSize(400,300);
            return c.exec();
        }
        else{
            QApplication a(argc, argv);
            MainWindow w;
            w.setWindowTitle("system time");
            w.show();
            w.move(20,300);
            w.setMinimumSize(400,300);
            w.setMaximumSize(400,300);
            return a.exec();
        }
    }
}
