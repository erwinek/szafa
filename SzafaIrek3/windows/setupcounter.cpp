#include "setupcounter.h"
#include "window.h"

SetupCounter::SetupCounter(QWidget *parent) :
    QWidget(parent)
{
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->resize(1024,768);
    backgroundLabel->move(0,0);
    backgroundLabel->setPixmap(QPixmap("gfx/3/background.jpg"));

    const QString& labeCss = "\
            QLabel { \
                background-color: rgba(10,10,10,150); \
                font: bold 20px; \
                color: red;\
                border-radius: 16px; \
            }";


    //--- Counter
    QLabel *lCounter = new QLabel("Licznik", this);
    lCounter->resize(200,100);
    lCounter->move(300,125);
    lCounter->setStyleSheet(labeCss);
    lCounter->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    lcdCounter=new QLCDNumber(this);
    lcdCounter->resize(200,100);
    lcdCounter->setDigitCount(10);
    lcdCounter->move(500,125);

    QPushButton *buttonResetCounter= new QPushButton("RESET", this);
    buttonResetCounter->resize(200,100); //width, height.
    buttonResetCounter->move(700, 125);
    buttonResetCounter->setStyleSheet("");
    connect(buttonResetCounter, SIGNAL(clicked()),this, SLOT(ResetCounter()));

    //--- Total Counter
    QLabel *lLicznikTotal = new QLabel("Total", this);
    lLicznikTotal->resize(200,100);
    lLicznikTotal->move(300,400);
    lLicznikTotal->setStyleSheet(labeCss);
    lLicznikTotal->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    lcdTotalCounter=new QLCDNumber(this);
    lcdTotalCounter->resize(200,100);
    lcdTotalCounter->setDigitCount(10);
    lcdTotalCounter->move(500,400);

    QPushButton *buttonExit= new QPushButton("Exit", this);
    buttonExit->resize(200,100); //width, height.
    buttonExit->move(500, 600);
    buttonExit->setStyleSheet("");
    connect(buttonExit, SIGNAL(clicked()),this, SLOT(Exit()));

    lcdCounter->display((int)((Window*)parentWidget())->serialPort->currentCounter);
    lcdTotalCounter->display((int)((Window*)parentWidget())->serialPort->totalCounter);
}

void SetupCounter::Refresh()
{
    lcdCounter->display((int)((Window*)parentWidget())->serialPort->currentCounter);
    lcdTotalCounter->display((int)((Window*)parentWidget())->serialPort->totalCounter);

    this->show();
}

void SetupCounter::Exit()
{
    this->hide();
}

void SetupCounter::ResetCounter()
{
    ((Window*)parentWidget())->serialPort->resetCounter=1;
    lcdCounter->display((int)((Window*)parentWidget())->serialPort->currentCounter);
    lcdTotalCounter->display((int)((Window*)parentWidget())->serialPort->totalCounter);

}
