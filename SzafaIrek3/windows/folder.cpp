#include <QtGui>
#include "folder.h"
#include "window.h"
#include "scroll.h"
#include "volsetup.h"

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


void RecurseDirectory(const QString& sDir);



folder::folder(QWidget *parent) : QWidget (parent)
{
    isPlaying=0;
    fadeTimer=0;
    fadeState=0;
    AlbumSelector = 0;
    SongSelector = 0;
    //PathMp3 = "/home/szafa/mp3/";

    //  PHONON
   using namespace Phonon;
    fadeTimeMs = 10000; //10sekund
   obj = new Phonon::MediaObject(this);
    //audioLevel = new AudioDataOutput(obj);
   audio=new AudioOutput(Phonon::MusicCategory, this);
   obj->setPrefinishMark(fadeTimeMs);
   connect(obj, SIGNAL(prefinishMarkReached(qint32)), this, SLOT(handlePrefinishMark(qint32)));

    Phonon::createPath(obj,  audio );
    videoWidget = new Phonon::VideoWidget(this);
    videoWidget->setGeometry(0,0,1024,768);
    videoWidget->hide();

    videoWidget2 = new Phonon::VideoWidget(this);
    videoWidget2->setGeometry(0,0,1024,768);
    videoWidget2->hide();

   Phonon::createPath(obj, videoWidget);

   obj2 = new MediaObject(this);
   obj2->setPrefinishMark(fadeTimeMs);
   connect(obj2, SIGNAL(prefinishMarkReached(qint32)), this, SLOT(handlePrefinishMark(qint32)));
   audio2=new AudioOutput(Phonon::MusicCategory, this);
   Phonon::createPath( obj2, audio2 );
   Phonon::createPath(obj2, videoWidget2);

    obj->setTickInterval(1000);

    QTimer *Tokladka = new QTimer(this);
    connect(Tokladka, SIGNAL(timeout()), this, SLOT(TimerOkladkaTimeout()));
    Tokladka->setInterval(5000);
    Tokladka->start();
    TimerOkladka = Tokladka;


    QDir myDir(PathMp3);
    AlbumList = myDir.entryList ();

    QTimer *timerFadeOut = new QTimer(this);
    connect(timerFadeOut, SIGNAL(timeout()), this, SLOT(volFadeInOut()));
    timerFadeOut->start(1000);

   QSettings settings("/home/szafa/queue.ini", QSettings::IniFormat);
   int size = settings.beginReadArray("kolejka");
   for (int i = 0; i < size; ++i) {
       settings.setArrayIndex(i);
       Song piosenka;
       piosenka.artist = settings.value("artist").toString();
       piosenka.title = settings.value("title").toString();
       piosenka.path = settings.value("path").toString();
       piosenka.CdPath = settings.value("CdPath").toString();
       piosenka.songLength = settings.value("songLength").toString();
       Kolejka.enqueue(piosenka);
   }
   settings.endArray();


}

void folder::MuzykaWszystkie()
{
    PathMp3 = DEFAULT_MP3_PATH;
    if (((Window*)parentWidget())->homeScreen && ((Window*)parentWidget())->albumsScreen) {
        ((Window*)parentWidget())->slideshowScreen->resetCounter();
        ((Window*)parentWidget())->homeScreen->hide();
        ((Window*)parentWidget())->songScreen->hide();
        ((Window*)parentWidget())->playScreen->hide();
        ((Window*)parentWidget())->albumsScreen->header->setText("WSZYSTKIE");        
        ((Window*)parentWidget())->albumsScreen->ShowAlbums(PathMp3);
        ((Window*)parentWidget())->creditWidget->raise();


    }
}


void folder::MuzykaPolska()
{    
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("MUZYKA POLSKA");
    ((Window*)parentWidget())->albumsScreen->ShowAlbums("/home/szafa/KATEGORIE/MuzykaPolska/");
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::MuzykaBiesiadna()
{

    PathMp3 = DEFAULT_MP3_PATH + "/home/szafa/KATEGORIE/MuzykaBiesiadna/";
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("MUZYKA BIESIADNA");
    ((Window*)parentWidget())->albumsScreen->ShowAlbums(PathMp3);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::MuzykaZagraniczna()
{

    PathMp3 = "/home/szafa/KATEGORIE/MuzykaZagraniczna/";
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("MUZYKA ZAGRANICZNA");
    ((Window*)parentWidget())->albumsScreen->ShowAlbums(PathMp3);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::Nowosci()
{
    PathMp3 = "/home/szafa/KATEGORIE/Nowosci/";
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("NOWOŚCI");
    ((Window*)parentWidget())->albumsScreen->ShowAlbums(PathMp3);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::Karaoke()
{
    PathMp3 = "/home/szafa/KATEGORIE/Karaoke/";
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("KARAOKE");
    ((Window*)parentWidget())->albumsScreen->ShowAlbums(PathMp3);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::Skladanki()
{
    PathMp3 = "/home/szafa/KATEGORIE/Skladanki/";
    ((Window*)parentWidget())->slideshowScreen->resetCounter();
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("SKŁADANKI");    
    ((Window*)parentWidget())->albumsScreen->ShowAlbums(PathMp3);
    ((Window*)parentWidget())->creditWidget->raise();
}


void folder::TimerTick()
{
    //if (!Kolejka.isEmpty() && (obj->state() != PlayingState))


    if ((obj->state() == PlayingState) && (obj->hasVideo()))
    {
        ((Window*)parentWidget())->slideshowScreen->resetCounter();
        videoWidget->raise();        
        videoWidget->show();
        this->show();
        this->raise();
        isPlaying=true;
        if (KaraokeFullScreen) {
            if(KaraokeFullScreen != KaraokeFullScreenBak) {
                KaraokeFullScreenBak = KaraokeFullScreen;
                videoWidget->setGeometry(0,0,1024,768);
            }
        }
        else {
            if(KaraokeFullScreen != KaraokeFullScreenBak) {
                KaraokeFullScreenBak = KaraokeFullScreen;
                videoWidget->setGeometry(200,20,260,260);

            }
        }
    }
    else {
        videoWidget->hide();
    }

    if ((obj2->state() == PlayingState) && (obj2->hasVideo()))
    {
        ((Window*)parentWidget())->slideshowScreen->resetCounter();
        videoWidget2->raise();
        videoWidget2->show();
        this->show();
        this->raise();
        isPlaying=true;
        if (KaraokeFullScreen) {
            if(KaraokeFullScreen != KaraokeFullScreenBak) {
                KaraokeFullScreenBak = KaraokeFullScreen;
                videoWidget->setGeometry(0,0,1024,768);
            }
        }
        else {
            if(KaraokeFullScreen != KaraokeFullScreenBak) {
                KaraokeFullScreenBak = KaraokeFullScreen;
                videoWidget2->setGeometry(200,20,260,260);
            }
        }

    }
    else videoWidget2->hide();


    if((obj->state() != PlayingState) && (obj2->state() != PlayingState))
    {        
        KaraokeFullScreen = true;
        if (KaraokeFullScreenBak == true) {
            KaraokeFullScreenBak = false;
        }
        if (!Kolejka.isEmpty())
        {
            Playing = Kolejka.dequeue();
            src = Playing.path;

            obj->setCurrentSource( src );
            obj->play();
            isPlaying = true;
            KaraokeFullScreen = 1;
            plytka->cd_okladka = 1; //wyswietl cd
            plytka->loadCdImage(Playing.CdPath);
            repaint();

            ((Window*)parentWidget())->homeScreen->updateQueue();

        }
        else
        {
            if (isPlaying) {

                isPlaying = false;
                plytka->cd_okladka = 0; //wyswietl okladke
                videoWidget->hide();
                videoWidget2->hide();
                this->lower();
                this->hide();
                ((Window*)parentWidget())->homeScreen->updateQueue();
                ((Window*)parentWidget())->homeScreen->repaint();

            }
        }
        //displayQueue();
    }
    if(fadeState==0) {

        qint64 sekundy = obj->remainingTime()/1000;
        qint64 minuty = sekundy / 60;
        sekundy = sekundy % 60;
        QString secStr;
        secStr.sprintf("%02d", (int)sekundy);

        QString czasUtworu = QString::number(minuty) + ":" + secStr;


        ((Window*)parentWidget())->homeScreen->CzasOdtwarzania->setText(czasUtworu);
    }
    else {
        if((obj2->state() == PlayingState)) {
            isPlaying = true;
            qint64 sekundy = obj2->remainingTime()/1000;
            qint64 minuty = sekundy / 60;
            sekundy = sekundy % 60;
            QString secStr;
            secStr.sprintf("%02d", (int)sekundy);

            QString czasUtworu = QString::number(minuty) + ":" + secStr;

            ((Window*)parentWidget())->homeScreen->CzasOdtwarzania->setText(czasUtworu);
        }

    }

}


void folder::TimerOkladkaTimeout()
{
    if((obj->state() == PlayingState)) plytka->cd_okladka = 1; //wyswietl cd
}



void folder::FindAlbum(QString name)
{
    MuzykaWszystkie();
    for (int i=0;i<AlbumList.size();i++) {
        if (AlbumList[i]==name) {
            //listAlbum->setCurrentRow(i);
            break;
        }
    }
}

void folder::setVolume(int Volume)
{
    volume = Volume;
    volume /= MAX_VOL;
    audio->setVolume(volume);
    audio2->setVolume(volume);
}


void folder::volFadeInOut()
{
    float diff_vol;
    float new_vol;

    if (fadeTimer)
    {
        fadeTimer--;
        diff_vol = volume/(fadeTimeMs/1000);
        if(fadeState)
        {
            new_vol = audio->volume() - diff_vol;
            if(new_vol>0)  audio->setVolume(new_vol);
            else audio->setVolume(0);
            new_vol = audio2->volume() + diff_vol;
            audio2->setVolume(new_vol);
        }
        else {
            new_vol = audio->volume() + diff_vol;
            audio->setVolume(new_vol);
            new_vol = audio2->volume() - diff_vol;
            if(new_vol>0) audio2->setVolume(new_vol);
            else audio2->setVolume(0);
        }
    }
}


void folder::handlePrefinishMark(qint32 msecToEnd)
{
    qDebug() << " PREFINISH MARK " << msecToEnd;
    qDebug() << " WANTED PREFINISH MARK -> " << obj->prefinishMark();
    qDebug() << " TOTAL TIME-> " << obj->totalTime();
    qDebug() << " CURRENT TIME " << obj->currentTime();



    if((obj->state() == PlayingState) && (obj->hasVideo()==false))
    {
        if (!Kolejka.isEmpty())
        {

            Playing = Kolejka.dequeue();
            src2 = Playing.path;

            obj2->setCurrentSource( src2 );

            obj2->play();
            isPlaying=true;

            repaint();
            plytka->cd_okladka = 1; //wyswietl cd
            plytka->loadCdImage(Playing.CdPath);

            fadeState=1;
            audio2->setVolume(0);
            fadeTimer = (fadeTimeMs/1000);

        }
    }
    else {
        if((obj2->state() == PlayingState) && (obj2->hasVideo()==false))
        {
            if (!Kolejka.isEmpty())
            {
                Playing = Kolejka.dequeue();
                src = Playing.path;

                obj->setCurrentSource( src );

                obj->play();
                isPlaying=true;

                repaint();
                plytka->cd_okladka = 1; //wyswietl cd
                plytka->loadCdImage(Playing.CdPath);

                fadeState = 0;
                audio->setVolume(0);
                fadeTimer = (fadeTimeMs/1000);
            }
        }
    }
    ((Window*)parentWidget())->homeScreen->updateQueue();
    ((Window*)parentWidget())->homeScreen->repaint();

}

void folder::AddToQueue(Song &song)
{
    if (((Window*)parentWidget())->setup->freePlayOnOff)
    {
        Kolejka.enqueue(song);
        ((Window*)parentWidget())->homeScreen->updateQueue();
    }
    else {
        if (((Window*)parentWidget())->creditWidget->isCredit()) {
            ((Window*)parentWidget())->statScreen->SaveSongHistory(song.title);
            ((Window*)parentWidget())->statScreen->incrSongStats(song.title);
            ((Window*)parentWidget())->creditWidget->decrCredit();
            Kolejka.enqueue(song);
            ((Window*)parentWidget())->homeScreen->updateQueue();
        }
    }

}
