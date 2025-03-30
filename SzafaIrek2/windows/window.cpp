
#include <QtGui>
#include <QDir>
#include "widget.h"
#include "window.h"
#include "sprite.h"
#include "home.h"
#include "menu.h"
#include "stats.h"
#include "folder.h"
#include "szukaj.h"
#include "setup.h"
#include <phonon>
#include <qfiledialog.h>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
//#include <QList>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <QUrl>


//------- Global Settings ----------------
const QString DEFAULT_MP3_PATH = "mp3/";
QString MP3_PATH = "mp3/";
QString DEFAULT_SETUP_PASS = "ENTERSETUP";

QSize buttonUpDownSize(160,80);
QString PathMp3 = "../mp3/";
//----------------------------------------

cd *plytka;
Szukaj *oknoSzukaj;



QString GFX_PATH = "gfx/";
QString BACKGROUNG_IMG = "background.jpg";

QString buttonStyleSheet = " \
        background-color: rgba(10,20,30,0); \
        font-size: 8px; \
        color: white;\
        border-radius: 6px;";


#include <QUrl>
Window::Window()
    : QWidget()
{
    //enablePlayButton = true;

    QLabel *testLabel = new QLabel(this);
    QPixmap testImg("gfx/test.png");
    testLabel->setPixmap(testImg);

    slideshowCounter = 0;

    QDesktopWidget* desktopWidget = qApp->desktop();
    QRect screenGeometry = desktopWidget->screenGeometry();
    screenWidth = screenGeometry.width();
    screenHeight = screenGeometry.height();

    playScreen = new PlaySong(this);
    playScreen->hide();


    tlo = new Image("gfx\\1\\background.jpg",this);
    setup = new Setup(this);
    setup->setGeometry(0, 0, 1024, 768);
    setup->setWindowOpacity(0.1);
    setup->hide();

    serialPort = new ComPort(this);
    serialPort->SendFrame("HELLO World !!!!!");


    VolSetupScreen = new VolSetup(this);
    VolSetupScreen->hide();

    MenuSetupScreen = new MenuSetup(this);
    MenuSetupScreen->hide();

    statScreen = new Stats(this);
    statScreen->hide();

    setupCounterScreen = new SetupCounter(this);
    setupCounterScreen->hide();

    insertCoinScreen = new InsertCoin(this);
    insertCoinScreen->hide();

    top20 = new Toplist(statScreen->strListSongsStat, this);
    top20->hide();

    QString *StyleNum = new QString();
    StyleNum->setNum(setup->Screen);
    gfxPath = GFX_PATH + *StyleNum + "\\";

    tlo->qimage->load(gfxPath + BACKGROUNG_IMG);

    tlo->setFixedHeight(screenHeight);
    tlo->setFixedWidth(screenWidth);
    //tlo->resize(1024, 768);
    tlo->show();

    plytka = new cd(this);
    plytka->setGeometry(0,0,500,500);
    plytka->raise();    
    plytka->show();
    plytka->raise();


    albumsScreen = new Albums(this);
    albumsScreen->hide();

    songScreen = new Songs(this);
    songScreen->hide();

    oknoSzukaj = new Szukaj(this, albumsScreen, songScreen);
    oknoSzukaj->setGeometry(0, 0, 1024, 768);
    oknoSzukaj->setWindowOpacity(0.1);
    oknoSzukaj->hide();
    QString tempStr;
    oknoSzukaj->SearchTagsAndMakeLinks(DEFAULT_MP3_PATH, "MuzykaPolska", tempStr);
    oknoSzukaj->SearchTagsAndMakeLinks(DEFAULT_MP3_PATH, "MuzykaZagraniczna", tempStr);
    oknoSzukaj->SearchTagsAndMakeLinks(DEFAULT_MP3_PATH, "Nowosci", tempStr);
    oknoSzukaj->SearchTagsAndMakeLinks(DEFAULT_MP3_PATH, "MuzykaBiesiadna", tempStr);
    oknoSzukaj->SearchTagsAndMakeLinks(DEFAULT_MP3_PATH, "Skladanki", tempStr);
    oknoSzukaj->SearchTagsAndMakeLinks(DEFAULT_MP3_PATH, "Karaoke", tempStr);

    albums = new folder(this);
    albums->raise();
    albums->show();

    QTimer *timer = new QTimer(this);    
    connect(timer, SIGNAL(timeout()), plytka, SLOT(rotate()));

    timer->start(100);

    timerAddQueueDelay = new QTimer(this);
    timerAddQueueDelay->start(1000);

    QTimer *timer500ms = new QTimer(this);
    connect(timer500ms, SIGNAL(timeout()), albums, SLOT(TimerTick()));
    timer500ms->start(1000);

    slideshowScreen = new Slideshow(this);
    slideshowScreen->hide();

    QTimer *timerSlideShow = new QTimer(this);
    timerSlideShow->start(1000);
    connect(timerSlideShow, SIGNAL(timeout()), this, SLOT(showSlideshow()));

    albums->setVolume(setup->settings.value("Setup/Volume").toInt());

    homeScreen = new Home(this);
    homeScreen->raise();
    homeScreen->show();

    albums->hide();//TODO - remove
    plytka->hide();

    creditWidget = new Credit(this);
    if ((setup->freePlayOnOff == true) || (slideshowScreen->OnOff == true)) creditWidget->hide();
    else creditWidget->show();

    menu = new Menu(this);
    menu->show();


}

void Window::reloadPictures()
{
    QString *StyleNum = new QString();
    StyleNum->setNum(setup->Screen);
    gfxPath = GFX_PATH + *StyleNum + "/";

    tlo->qimage->load(gfxPath + BACKGROUNG_IMG);

    oknoSzukaj->SzukajImage.load((gfxPath + "background.jpg"));
    repaint();
}


void Window::resizeEvent(QResizeEvent *event)
{
    albums->resize(event->size());
    event->accept();

}

void Window::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Escape) {
       qApp->quit();
   }
   if (event->key() == Qt::Key_F1) {
        enterSetup();
   }
   if (event->key() == Qt::Key_F2) {
        enterVolumeSetup();
   }
   if (event->key() == Qt::Key_F3) {
        enterMenuSetup();
   }
   if (event->key() == Qt::Key_F4) {

   }
   if (event->key() == Qt::Key_F) {
    serialPort->SendFrame("HELLO World !!!!!");
   }

   if (event->key() == Qt::Key_F12) {
       creditWidget->incrCredit();
   }

   repaint();
}

void Window::szukanie()
{
    slideshowScreen->resetCounter();
    songScreen->hide();
    albumsScreen->hide();
    homeScreen->hide();    
    oknoSzukaj->raise();
    oknoSzukaj->show();
    oknoSzukaj->txtSzukany->setFocus();
    oknoSzukaj->lTrwaWyszukiwanie->hide();

}

void Window::enterSetup()
{
    slideshowScreen->resetCounter();
    setup->raise();
    songScreen->hide();
    albumsScreen->hide();
    setup->show();
}

void Window::enterVolumeSetup()
{
    slideshowScreen->resetCounter();
    VolSetupScreen->raise();
    songScreen->hide();
    albumsScreen->hide();
    VolSetupScreen->show();
}

void Window::enterMenuSetup()
{
    slideshowScreen->resetCounter();
    songScreen->hide();
    albumsScreen->hide();
    VolSetupScreen->hide();
    MenuSetupScreen->raise();
    MenuSetupScreen->show();
}

void Window::enterSetupCounter()
{
    slideshowScreen->resetCounter();
    songScreen->hide();
    albumsScreen->hide();
    VolSetupScreen->hide();
    MenuSetupScreen->hide();
    setupCounterScreen->raise();
    setupCounterScreen->Refresh();
}



void Window::enterStat()
{
    slideshowScreen->resetCounter();
    songScreen->hide();
    albumsScreen->hide();
    VolSetupScreen->hide();
    MenuSetupScreen->hide();
    statScreen->raise();
    statScreen->show();
}

void Window::showSlideshow()
{
    static QPoint posBackup = QCursor::pos();

    if (posBackup != QCursor::pos()) {
        posBackup = QCursor::pos();
        slideshowScreen->resetCounter();
    }
    if (albums->isPlaying == 0) {
        slideshowScreen->SwitchOn();
    }
    else {
        slideshowScreen->SwitchOff();
    }
}






void Window::mousePressEvent(QMouseEvent *)
{
    slideshowScreen->resetCounter();
}

void Window::hideAll()
{
    playScreen->hide();
    homeScreen->hide();
    albumsScreen->hide();
    songScreen->hide();
    oknoSzukaj->hide();
    statScreen->hide();
    setup->hide();
    creditWidget->hide();
    VolSetupScreen->hide();
}
