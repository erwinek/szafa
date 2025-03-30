#ifndef MENUSETUP_H
#define MENUSETUP_H

#include <QWidget>
#include <QtGui>

class MenuSetup : public QWidget
{
    Q_OBJECT
public:
    explicit MenuSetup(QWidget *parent = 0);

private:
    QPushButton *bLiczniki;
    QPushButton *bVolume;
    QPushButton *bSetup;
    QPushButton *bStat;

signals:
    
public slots:
    void GoCounters();
    void GoVolume();
    void GoSetup();
    void GoStat();
};

#endif // MENUSETUP_H
