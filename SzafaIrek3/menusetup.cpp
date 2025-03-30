#include "menusetup.h"
#include "window.h"

MenuSetup::MenuSetup(QWidget *parent) :
    QWidget(parent)
{
    QString buttonStyleSheet = " \
        color: yellow;\
        background-color: rgba(50,50,50,200); \
        font-size: 24px; \
        border-radius: 6px; \
                               ";

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->resize(1024,768);
    backgroundLabel->move(0,0);
    backgroundLabel->setPixmap(QPixmap("gfx/3/background.jpg"));

    bLiczniki = new QPushButton("Counters", this);
    bLiczniki->resize(200,200);
    bLiczniki->move(100,100);
    bLiczniki->setStyleSheet(buttonStyleSheet);
    bLiczniki->setFocusPolicy(Qt::NoFocus);
    connect(bLiczniki, SIGNAL(clicked()),this, SLOT(GoCounters()));

    bVolume = new QPushButton("Volume", this);
    bVolume->resize(200,200);
    bVolume->move(350,100);
    bVolume->setStyleSheet(buttonStyleSheet);
    bVolume->setFocusPolicy(Qt::NoFocus);
    connect(bVolume, SIGNAL(clicked()),this, SLOT(GoVolume()));

    bSetup = new QPushButton("Setup", this);
    bSetup->resize(200,200);
    bSetup->move(600,100);
    bSetup->setStyleSheet(buttonStyleSheet);
    bSetup->setFocusPolicy(Qt::NoFocus);
    connect(bSetup, SIGNAL(clicked()),this, SLOT(GoSetup()));

    bStat = new QPushButton("Stats", this);
    bStat->resize(200,200);
    bStat->move(100,350);
    bStat->setStyleSheet(buttonStyleSheet);
    bStat->setFocusPolicy(Qt::NoFocus);
    connect(bStat, SIGNAL(clicked()),this, SLOT(GoStat()));


}


void MenuSetup::GoCounters()
{
    this->hide();
    ((Window*)parentWidget())->enterSetupCounter();
}

void MenuSetup::GoVolume()
{
    this->hide();
    ((Window*)parentWidget())->enterVolumeSetup();
}

void MenuSetup::GoSetup()
{
    this->hide();
    ((Window*)parentWidget())->enterSetup();
}

void MenuSetup::GoStat()
{
    this->hide();
    ((Window*)parentWidget())->enterStat();
}
