#ifndef AUTO_PLUS_H
#define AUTO_PLUS_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class auto_plus;
}

class auto_plus : public QMainWindow
{
    Q_OBJECT

public:
    explicit auto_plus(QWidget *parent = 0);
    ~auto_plus();
    qint32 srcNum, sum;
    QLabel *sumStr;

private slots:
    void updateSum();

private:
    Ui::auto_plus *ui;
};

#endif // AUTO_PLUS_H
