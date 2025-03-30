#include "slideshow.h"
#include "window.h"


#include <QThread>

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

qreal opacity;

Slideshow::Slideshow(QWidget *parent) :
    QWidget(parent)
{
    demoSongIntervalMinutes = ((Window*)parentWidget())->settings->value("DemoSongIntervalMinutes").toInt();
    if ((demoSongIntervalMinutes < 5) || (demoSongIntervalMinutes>60000)) {
        demoSongIntervalMinutes = 40;
        ((Window*)parentWidget())->settings->setValue("DemoSongIntervalMinutes", demoSongIntervalMinutes);
    }
    demoSongVolume = ((Window*)parentWidget())->settings->value("DemoSongVolume").toInt();
    if ((demoSongVolume < 1) || (demoSongVolume>30)) {
        demoSongVolume = 8;
        ((Window*)parentWidget())->settings->setValue("DemoSongVolume", demoSongVolume);
    }
    demoSongIntervalSecCnter = demoSongIntervalMinutes*60; //resetuj licznik
    OnOff = 0;
    QDir SelectedDir(ZDJECIA_PATH);
    imageList = SelectedDir.entryList ();
    if (imageList.length() < 3) qDebug("brak zdjec");
    else {
    imageList.removeFirst();  // pomijamy poczatek listy \. i \..
    imageList.removeFirst();
    imageList.removeFirst();

    imageCounter = 0;

    imageLabel = new QLabel(this);
    imageLabel->resize(1024-230,768);

    imageTimer = new QTimer(this);
    imageTimer->start(5000);
    connect(imageTimer, SIGNAL(timeout()), this, SLOT(nextImage()));

    this->resize(1024-230, 768);
    this->move(230, 0);

    counter = 0;
    }
}

void Slideshow::SwitchOn()
{
    if (counter < MIN_IDLE_TIME) counter++;
    else {
        if(!OnOff) {
            OnOff = 1;
            ((Window*)parentWidget())->hideAll();
            showSlideshow();
        }
    }
}

void Slideshow::SwitchOff()
{
    if(OnOff) {
        OnOff=0;
        this->hide();
        ((Window*)parentWidget())->homeScreen->raise();
        ((Window*)parentWidget())->homeScreen->show();
        ((Window*)parentWidget())->menu->raise();
        ((Window*)parentWidget())->menu->show();
        if(!((Window*)parentWidget())->setup->freePlayOnOff) {
            ((Window*)parentWidget())->creditWidget->raise();
            ((Window*)parentWidget())->creditWidget->show();
        }
    }
}

void Slideshow::showSlideshow()
{
    imageTimer->start(10000); //długość wyświetlania obrazka
    opacity = 0;
    repaint();
    this->raise();
    this->show();
    //pokazanie
    for (qreal i=0;i<1;i+=0.10) {
        opacity = i;
        Sleeper::msleep(10);
        repaint();
    }

    ((Window*)parentWidget())->menu->raise();
    ((Window*)parentWidget())->menu->show();

}

void Slideshow::resetCounter()
{
    qDebug() << "Slideshow::resetCounter()";
    if(OnOff) SwitchOff();
    counter=0;
    demoSongIntervalSecCnter = demoSongIntervalMinutes*60; //resetuj licznik
    ((Window*)parentWidget())->playerMp3Obj->stop();

}

void Slideshow::nextImage()
{


    if (demoSongIntervalSecCnter > 5) {
        demoSongIntervalSecCnter-=5;
        qDebug()<< "demoSongIntervalSecCnter" << demoSongIntervalSecCnter;
    }
    else if (OnOff){
        demoSongIntervalSecCnter = demoSongIntervalMinutes*60; //resetuj licznik
        QString songPath = ((Window*)parentWidget())->top20->GetTopSongPath();
        qDebug() << "songPath=" << songPath;
        ((Window*)parentWidget())->playerMp3Obj->playSong(songPath);
    }

    //wygaszenie
    for (qreal i=1.0; i>0 ;i-=0.1) {
        opacity = i;
        repaint();
        Sleeper::msleep(10);
    }

    QString imgPath = ZDJECIA_PATH + imageList[imageCounter];

    image.load(imgPath);

    //pokazanie
    for (qreal i=0;i<1;i+=0.10) {
        opacity = i;
        Sleeper::msleep(10);
        repaint();
    }

    if(imageCounter<(imageList.length()-1)) imageCounter++;
    else imageCounter=0;
    imageLabel->hide();
}

void Slideshow::paintEvent(QPaintEvent *event)
{
    event=event;
    QPainter paint( this );

    paint.setRenderHints(QPainter::Antialiasing, 1);
    paint.setRenderHints(QPainter::SmoothPixmapTransform, 1);

    paint.setOpacity(opacity);
    if (!image.isNull()) paint.drawImage(QRect(0, 0, 1024-230, 768), image);

    paint.end();
}
