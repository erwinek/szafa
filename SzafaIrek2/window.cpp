#include <QtNetwork/QNetworkInterface>
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
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <QUrl>
#include <windows.h>


//#include "tile.h"

//------- Global Settings ----------------
QString MP3_PATH = "c:/szafa/mp3/";
QString ZDJECIA_PATH = "c:/szafa/ZDJECIA/";
QString DEFAULT_SETUP_PASS = "ENTERSETUP";
QSize buttonUpDownSize(160,80);

//----------------------------------------
void updateTag(QString tag, QList<Plyta> *kategoria);

Szukaj *oknoSzukaj;



QString GFX_PATH = "gfx/";
QString BACKGROUNG_IMG = "background.jpg";

#include <fstream>

using namespace std;
ofstream logfile;

void SimpleLoggingHandler(QtMsgType type, const char *msg) {
    switch (type) {
        case QtDebugMsg:
            logfile << QTime::currentTime().toString().toAscii().data() << " Debug: " << msg << "\n";
            break;
        case QtCriticalMsg:
            logfile << QTime::currentTime().toString().toAscii().data() << " Critical: " << msg << "\n";
            break;
        case QtWarningMsg:
            logfile << QTime::currentTime().toString().toAscii().data() << " Warning: " << msg << "\n";
            break;
        case QtFatalMsg:
            logfile << QTime::currentTime().toString().toAscii().data() <<  " Fatal: " << msg << "\n";
            logfile.flush();
            logfile.close();
            abort();
        }
    }

QString buttonStyleSheet = " \
        background-color: rgba(10,20,30,0); \
        font-size: 8px; \
        color: white;\
        border-radius: 6px;";




Window::Window() : QWidget()
{
    QTime startupTime;
    startupTime.start();

    /************* LOGGER ************/
    QDir dir("c:\\log\\");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString sDate = QDate::currentDate().toString("yyyy.MM.dd").toAscii();
    QString pth = "c:\\log\\" + sDate;

    const char *fileName = pth.toStdString().c_str();

    logfile.open(fileName, ios::app);
#ifdef QT_DEBUG
  qDebug() << "Running a debug build";
#else
    qInstallMsgHandler(SimpleLoggingHandler);
#endif
    qWarning() << "\n!!!!!! START !!!!!! " << QDate::currentDate().toString("yyyy.MM.dd").toAscii().data();


    /*********** SETTING FILE **********/
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(settings->value("backup").toString() != "OK")
    {
        qWarning("settings.bak");
        delete settings;

        QFile::copy("settings.bak", "settings.ini");
        settings = new QSettings("settings.ini", QSettings::IniFormat);
        settings->setValue("backup", "OK");
    }

    settings->setIniCodec("Windows-1250");
    QSettings *setupPath = new QSettings("setupPath.ini", QSettings::IniFormat);
    MP3_PATH = setupPath->value("MP3_PATH").toString();
    qDebug() << "MP3_PATH.value=" << MP3_PATH ;
    if (MP3_PATH.length()==0) {
        qDebug() << "SetupPath empty";
        MP3_PATH = "c:/szafa/mp3/";
        setupPath->setValue("MP3_PATH", MP3_PATH);
    }
    ZDJECIA_PATH = setupPath->value("ZDJECIA_PATH").toString();
    if (ZDJECIA_PATH.length()==0) {
        ZDJECIA_PATH = "c:/szafa/ZDJECIA/";
        setupPath->setValue("ZDJECIA_PATH", ZDJECIA_PATH);
    }

    int KaraokeCredit = setupPath->value("KaraokeCredit").toInt();
    if(KaraokeCredit==0) {
        KaraokeCredit = 1;
        setupPath->setValue("KaraokeCredit", KaraokeCredit);
    }


    volEnable = setupPath->value("Setup/VolumeEnable", 1).toInt();
    setupPath->setValue("Setup/VolumeEnable", volEnable);


    slideshowCounter = 0;

    QDesktopWidget* desktopWidget = qApp->desktop();
    QRect screenGeometry = desktopWidget->screenGeometry();
    screenWidth = screenGeometry.width();
    screenHeight = screenGeometry.height();



    playScreen = new PlaySong(this);
    playScreen->hide();
qDebug() << "playScreen =" <<    startupTime.elapsed();

    tlo = new Image("gfx\\1\\background.jpg",this);
    setup = new Setup(this);
    setup->setGeometry(0, 0, 1024, 768);
    setup->setWindowOpacity(0.1);
    setup->hide();
qDebug() << "setup =" <<    startupTime.elapsed();
    serialPort = new ComPort(this);
    serialPort->SendFrame("HELLO World !!!!!");


    VolSetupScreen = new VolSetup(this);
    VolSetupScreen->hide();

    MenuSetupScreen = new MenuSetup(this);
    MenuSetupScreen->hide();

    qDebug() << "Stats1 =" <<    startupTime.elapsed();
    statScreen = new Stats(this);
    qDebug() << "Stats2 =" <<    startupTime.elapsed();
    statScreen->hide();

    setupCounterScreen = new SetupCounter(this);
    setupCounterScreen->hide();

    insertCoinScreen = new InsertCoin(this);
    insertCoinScreen->hide();

    playerMp3Obj = new PlayerMp3();

    top20 = new Toplist(statScreen->strListSongsStat, this);
    top20->hide();
    qDebug() << "top20 =" <<    startupTime.elapsed();
    QString *StyleNum = new QString();
    StyleNum->setNum(setup->Screen);
    gfxPath = GFX_PATH + *StyleNum + "\\";

    tlo->qimage->load(gfxPath + BACKGROUNG_IMG);

    tlo->setFixedHeight(screenHeight);
    tlo->setFixedWidth(screenWidth);
    //tlo->resize(1024, 768);
    tlo->show();

    albumsScreen = new Albums(this);
    albumsScreen->hide();

    songScreen = new Songs(this);
    songScreen->hide();

    oknoSzukaj = new Szukaj(this, albumsScreen, songScreen);
    oknoSzukaj->setGeometry(0, 0, 1024, 768);
    oknoSzukaj->setWindowOpacity(0.1);
    oknoSzukaj->hide();
    qDebug() << "oknoSzukaj =" <<    startupTime.elapsed();
    /*
    updateTag("MuzykaPolska", &listMuzykaPolska);
    updateTag("MuzykaZagraniczna", &listMuzykaZagraniczna);
    updateTag("MuzykaNowosci", &listMuzykaNowosci);
    updateTag("MuzykaBiesiadna", &listMuzykaBiesiadna);
    updateTag("MuzykaSkladanki", &listMuzykaSkladanki);
    updateTag("MuzykaKaraoke", &listMuzykaKaraoke);
*/
    albums = new folder(this);
    albums->raise();
    albums->show();

    int volume = settings->value("Setup/Volume").toInt();
    if (volume==0) {
        volume = 30;
        settings->setValue("Setup/Volume", volume);
    }
    albums->setVolume(volume);

qDebug() << "albums =" <<    startupTime.elapsed();
    timerAddQueueDelay = new QTimer(this);
    timerAddQueueDelay->start(1000);

    slideshowScreen = new Slideshow(this);
    slideshowScreen->hide();
qDebug() << "slideshow =" <<    startupTime.elapsed();
    QTimer *timerSlideShow = new QTimer(this);
    timerSlideShow->start(1000);
    connect(timerSlideShow, SIGNAL(timeout()), this, SLOT(showSlideshow()));

    QTimer *testTimer = new QTimer(this);
    testTimer->start(1);
    //connect(testTimer, SIGNAL(timeout()), this, SLOT(runTest()));

    timeoutNotTouched = 120000;
    tNotTouched = new QTimer(this);
    tNotTouched->start(timeoutNotTouched);
    connect(tNotTouched, SIGNAL(timeout()), this, SLOT(slotNotTouched()));



    playerMp3Obj->setVol(settings->value("DemoSongVolume").toInt());
    creditWidget = new Credit(this);

    creditWidget->KaraokeCredit = KaraokeCredit;

    homeScreen = new Home(this);
    homeScreen->raise();
    homeScreen->show();

    albums->hide();//TODO - remove

    if ((setup->freePlayOnOff == true) || (slideshowScreen->OnOff == true)) creditWidget->hide();
    else {
        creditWidget->raise();
        creditWidget->show();
    }


    menu = new Menu(this);
    menu->show();
qDebug() << "menu =" <<    startupTime.elapsed();
    QString styleLabelRound = "QLabel { \
        background-color: rgba(255,255,255,200); \
        font: 40px; \
        color: red;\
    }";

    ipSystem = new QLabel("NO CARD", this);
    ipSystem->resize(1024, 768);
    ipSystem->raise();
    ipSystem->hide();
    ipSystem->setStyleSheet(styleLabelRound);
    ipSystem->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);


    DWORD dwVolSerial;
    quint32 pass = 0x5a5fa59a;
    BOOL bIsRetrieved;

    bIsRetrieved = GetVolumeInformationA("C:\\", NULL, NULL, &dwVolSerial, NULL, NULL, NULL, NULL);
    if(bIsRetrieved==true) {
        diskNo = dwVolSerial;
    }

    qlonglong macId = 0;
    qlonglong hwId = 0;

    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); // now you have interfaces list
    foreach (QNetworkInterface iface, list)  // this should print all interfaces' names
    {
        QString mac = iface.hardwareAddress();
        bool ok;
        mac.remove(':');
        qlonglong macNo = mac.toLongLong(&ok, 16);
        macId += macNo;
    }

    hwId = macId + diskNo;
    diskNo = hwId;//prezentowany na stronie

    quint32 hash = ((hwId * hwId) ^ pass ) * pass;

    QSettings *settingsLic = new QSettings("lic.ini", QSettings::IniFormat);
    settingsLic->setValue("hwId", diskNo);
    quint32 serialNo = settingsLic->value("SerialNo").toUInt();
    if (serialNo != hash) {
        NoLicence = true;
    }
    else NoLicence = false;

    qDebug() << "EndWindowConstructor =" <<    startupTime.elapsed();
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
        VolSetupScreen->VolMinus();
   }
   if (event->key() == Qt::Key_F5) {
        VolSetupScreen->VolPlus();
   }
   if (event->key() == Qt::Key_F7) {
        VolSetupScreen->LedMinus();
   }
   if (event->key() == Qt::Key_F8) {
        VolSetupScreen->LedPlus();
   }
   if (event->key() == Qt::Key_F9) {
       //playerMp3Obj->setVol(10);
       playerMp3Obj->playSong("1.mp3");
   }
   if (event->key() == Qt::Key_F) {
        serialPort->SendFrame("HELLO World !!!!!");
   }

   if (event->key() == Qt::Key_F12) {
       creditWidget->incrCredit();
   }
   if (event->key() == Qt::Key_F10) { //nabijanie kredytow z pilota
       creditWidget->incrLimited();
   }
   if (event->key() == Qt::Key_F11) {
       if (albums->obj2->state() == PlayingState)
       {
           albums->obj2->stop();
           homeScreen->updateQueue();
       }
       else if (albums->obj->state() == PlayingState)
       {
           albums->obj->stop();
           homeScreen->updateQueue();
       }

   }
   if (event->key() == Qt::Key_P) {
       VolSetupScreen->VolPlus();
   }
   if (event->key() == Qt::Key_L) {
       VolSetupScreen->VolMinus();
   }

   repaint();
}

void Window::szukanie()
{
    tNotTouched->start(timeoutNotTouched);
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
    tNotTouched->stop();
    slideshowScreen->resetCounter();
    setup->raise();
    songScreen->hide();
    albumsScreen->hide();
    setup->show();
}

void Window::enterVolumeSetup()
{
    tNotTouched->stop();
    slideshowScreen->resetCounter();
    VolSetupScreen->raise();
    songScreen->hide();
    albumsScreen->hide();
    VolSetupScreen->show();
}

void Window::enterMenuSetup()
{
    tNotTouched->stop();
    slideshowScreen->resetCounter();
    songScreen->hide();
    albumsScreen->hide();
    VolSetupScreen->hide();
    MenuSetupScreen->raise();
    MenuSetupScreen->show();
}

void Window::enterSetupCounter()
{
    tNotTouched->stop();
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
    tNotTouched->stop();
    slideshowScreen->resetCounter();
    songScreen->hide();
    albumsScreen->hide();
    VolSetupScreen->hide();
    MenuSetupScreen->hide();
    statScreen->raise();
    statScreen->show();
}

void Window::runTest()
{
    SongWidget *ptr = new SongWidget(this, "c:/szafa/mp3/ENEJ", "odrobina czasu");

    ptr->show();

    delete ptr;
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


void updateTag(QString tag, QList<Plyta> *kategoria)
{
    QString tempStr;
    QStringList muzykaList;
    muzykaList.clear();
    oknoSzukaj->SearchTagsAndSaveToFiles(MP3_PATH, tag, tempStr, muzykaList);

    foreach (QString album, muzykaList) {
         //qDebug() << "_album=" << album;
         Plyta *plyta = new Plyta();
         plyta->artist = album.left(album.indexOf("-"));
         plyta->title = album.mid(album.indexOf("-")+1);
         plyta->path = MP3_PATH + album + "/";
         kategoria->append(*plyta);
    }

}

void Window::setGameState(state newState)
{    
    restartTimeNotTouched();
    slideshowScreen->resetCounter();

    gameState = newState;

    if(NoLicence) {
        gameState = NO_LICENSE;

    }

    switch(gameState) {
        case(HOME):
            albumsScreen->hide();
            songScreen->hide();
            playScreen->hide();
            top20->hide();
            homeScreen->show();
            menu->show();
        break;
        case(ALBUMS):
            homeScreen->hide();
            songScreen->hide();
            playScreen->hide();
            top20->hide();
            homeScreen->hide();
            albumsScreen->show();
            menu->show();
        break;
        case(SONGS):
        break;
        case(PLAY):
        break;
        case(SLIDESHOW):
        break;
        case(SETUP):
        break;
        case(NO_LICENSE):

        break;
    }
}

void Window::slotNotTouched()
{
    if(gameState != HOME)   setGameState(HOME);
    qDebug() << "slotNotTouched";
}

void Window::restartTimeNotTouched()
{
    tNotTouched->start(timeoutNotTouched);
}
