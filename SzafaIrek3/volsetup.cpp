#include "volsetup.h"
#include "window.h"

VolSetup::VolSetup(QWidget *parent) :
    QWidget(parent)
{

    QString buttonStyleSheet = " \
        color: black;\
        background-color: rgba(255, 255, 255, 255); \
        font-size: 120px; \
        border-radius: 6px; \
    ";

    volume = ((Window*)parentWidget())->settings->value("Setup/Volume").toInt();
    if ((volume > MAX_VOL) || (volume < MIN_VOL)) {
        ((Window*)parentWidget())->RecoverSettings();
        volume = ((Window*)parentWidget())->settings->value("Setup/Volume").toInt();
        if ((volume > MAX_VOL) || (volume < MIN_VOL)) {
            volume = 10;
            ((Window*)parentWidget())->settings->setValue("Setup/Volume", volume);
        }
    }

    led = ((Window*)parentWidget())->settings->value("Setup/LedProgram").toInt();

    QString styleLabel = "QLabel { \
        font: bold 36px; \
        color: white;\
    }";

    QLabel *labelVolume = new QLabel("Volume", this);
    labelVolume->resize(300,50);
    labelVolume->move(390,40);
    labelVolume->setStyleSheet(styleLabel);

    bVolumeMinus = new QPushButton("-", this);
    bVolumeMinus->resize(200,200);
    bVolumeMinus->move(100,100);
    bVolumeMinus->setStyleSheet(buttonStyleSheet);
    bVolumeMinus->setFocusPolicy(Qt::NoFocus);
    connect(bVolumeMinus, SIGNAL(clicked()),this, SLOT(VolMinus()));

    bVolumePlus = new QPushButton("+", this);
    bVolumePlus->resize(200,200);
    bVolumePlus->move(680,100);
    bVolumePlus->setStyleSheet(buttonStyleSheet);
    bVolumePlus->setFocusPolicy(Qt::NoFocus);
    connect(bVolumePlus, SIGNAL(clicked()),this, SLOT(VolPlus()));

    if (! ((Window*)parentWidget())->volEnable) {
        bVolumeMinus->hide();
        bVolumePlus->hide();
    }

    dVol = new QLCDNumber(this);
    dVol->resize(200,200);
    dVol->move(390,100);
    dVol->setStyleSheet(buttonStyleSheet);
    dVol->setDigitCount(4);
    dVol->display(volume);

    QLabel *labelLed = new QLabel("Program LED", this);
    labelLed->resize(300,50);
    labelLed->move(370,340);
    labelLed->setStyleSheet(styleLabel);

    bLedMinus = new QPushButton("-", this);
    bLedMinus->resize(200,200);
    bLedMinus->move(100,400);
    bLedMinus->setStyleSheet(buttonStyleSheet);
    bLedMinus->setFocusPolicy(Qt::NoFocus);
    connect(bLedMinus, SIGNAL(clicked()),this, SLOT(LedMinus()));

    bLedPlus = new QPushButton("+", this);
    bLedPlus->resize(200,200);
    bLedPlus->move(680,400);
    bLedPlus->setStyleSheet(buttonStyleSheet);
    bLedPlus->setFocusPolicy(Qt::NoFocus);
    connect(bLedPlus, SIGNAL(clicked()),this, SLOT(LedPlus()));

    dLed = new QLCDNumber(this);
    dLed->resize(200,200);
    dLed->move(390,400);
    dLed->setStyleSheet(buttonStyleSheet);
    dLed->setDigitCount(4);
    dLed->display(led);

    buttonStyleSheet = " \
                      color: black;\
                      background-color: rgba(255,255,255,255); \
                      font-size: 40px; \
                      border-radius: 6px; \
                       ";

    QPushButton *bExit = new QPushButton("Exit", this);
    bExit->resize(200,100);
    bExit->move(390,650);
    bExit->setStyleSheet(buttonStyleSheet);
    bExit->setFocusPolicy(Qt::NoFocus);
    connect(bExit, SIGNAL(clicked()),this, SLOT(Exit()));

    this->resize(1024,768);
    VolSetupImage.load("gfx/3/background.jpg");
}


void VolSetup::VolPlus()
{
    if (volume < MAX_VOL) volume++;
    dVol->display(volume);
    ((Window*)parentWidget())->albums->setVolume(volume);
    ((Window*)parentWidget())->settings->setValue("Setup/Volume", volume);
}
void VolSetup::VolMinus()
{
    if (volume>0) volume--;
    dVol->display(volume);
    ((Window*)parentWidget())->albums->setVolume(volume);
    ((Window*)parentWidget())->settings->setValue("Setup/Volume", volume);
}


void VolSetup::LedPlus()
{
    if (led<20) led++;
    dLed->display(led);
    if (led != ((Window*)parentWidget())->settings->value("Setup/LedProgram").toInt()) {
        ((Window*)parentWidget())->settings->setValue("Setup/LedProgram", led);
    }
}
void VolSetup::LedMinus()
{
    if (led>0) led--;
    dLed->display(led);
    if (led != ((Window*)parentWidget())->settings->value("Setup/LedProgram").toInt()) {
        ((Window*)parentWidget())->settings->setValue("Setup/LedProgram", led);
    }
}


void VolSetup::paintEvent(QPaintEvent *event)
{
    event=event; //warning

    QPainter paint( this );
    paint.drawImage(QRect(0, 0, 1024, 768), VolSetupImage);
    paint.end();
}

void VolSetup::Exit()
{
    ((Window*)parentWidget())->settings->setValue("Setup/LedProgram", led);
    ((Window*)parentWidget())->settings->setValue("Setup/Volume", volume);
    ((Window*)parentWidget())->serialPort->setLedProgram = true;
    ((Window*)parentWidget())->oknoSzukaj->ClearSzukanyText();

    this->hide();
}

