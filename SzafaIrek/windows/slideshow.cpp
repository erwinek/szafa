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
    OnOff = 0;
    QDir SelectedDir("ZDJECIA");
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
    if(OnOff) SwitchOff();
    counter=0;

}

void Slideshow::nextImage()
{

    //wygaszenie
    for (qreal i=1.0; i>0 ;i-=0.1) {
        opacity = i;
        repaint();
        Sleeper::msleep(10);
    }

    QString imgPath = "/home/szafa/ZDJECIA/" + imageList[imageCounter];

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

    QPainter paint( this );

    paint.setRenderHints(QPainter::Antialiasing, 1);
    paint.setRenderHints(QPainter::SmoothPixmapTransform, 1);

    //  QImage image("/home/szafa/ZDJECIA/162347_morze_fale_zachod_slonca.jpg");
    paint.setOpacity(opacity);
    if (!image.isNull()) paint.drawImage(QRect(0, 0, 1024-230, 768), image);


    paint.end();
}
