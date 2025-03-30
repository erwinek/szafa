#ifndef SETUPCOUNTER_H
#define SETUPCOUNTER_H

#include <QWidget>
#include <QtGui>

class SetupCounter : public QWidget
{
    Q_OBJECT
public:
    explicit SetupCounter(QWidget *parent = 0);
    void Refresh();
private:
    QLCDNumber *lcdCounter;
    QLCDNumber *lcdTotalCounter;
signals:
    
private slots:
    void Exit();
    void ResetCounter();
};

#endif // SETUPCOUNTER_H
