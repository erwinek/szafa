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

bool LoadPlytyFromFile(QString fileName, QList<Plyta> &listaAlbumowNaPlycie)
{
    //odczyt bazy plyt z pliku
    QSettings AlbumsDatabase(fileName, QSettings::IniFormat);
    int size = AlbumsDatabase.beginReadArray("ALBUMY");
    if(size>0) {
        qDebug() << "albumy size=" << size;
        for (int i = 0; i < size; ++i) {

            AlbumsDatabase.setArrayIndex(i);
            Plyta *plyta = new Plyta();
            plyta->artist = AlbumsDatabase.value("artist").toString();
            plyta->title = AlbumsDatabase.value("title").toString();
            plyta->path = AlbumsDatabase.value("path").toString();
            listaAlbumowNaPlycie.append(*plyta);
        }
        AlbumsDatabase.endArray();

        return true;
    }
    return false;
}



void SavePlytyToFile(QString nazwaListy, QList<Plyta> listaAlbumowNaPlycie) {
    QSettings *albumsFile = new QSettings(nazwaListy, QSettings::IniFormat);
    albumsFile->clear();
    albumsFile->beginWriteArray("ALBUMY");
    albumsFile->sync();

    for(int i=0;(i<listaAlbumowNaPlycie.length());i++)
    {
        albumsFile->setArrayIndex(i);
        albumsFile->setValue("artist", listaAlbumowNaPlycie.at(i).artist);
        albumsFile->setValue("title", listaAlbumowNaPlycie.at(i).title);
        albumsFile->setValue("path", listaAlbumowNaPlycie.at(i).path);
    }
    albumsFile->endArray();
    albumsFile->sync();
}

// 1. Lecimy po wszystkich dodajemy do listy wszytskie
// 2. Lecimy po


folder::folder(QWidget *parent) : QWidget (parent)
{
    isPlayingVideo=0;
    isPlaying=0;
    fadeTimer=0;
    fadeState=0;
    AlbumSelector = 0;
    SongSelector = 0;

    //  PHONON
   using namespace Phonon;
    fadeTimeMs = 10000; //10sekund
   obj = new Phonon::MediaObject(this);
    //audioLevel = new AudioDataOutput(obj);
   audio=new AudioOutput(Phonon::MusicCategory, this);
   obj->setPrefinishMark(fadeTimeMs);
   connect(obj, SIGNAL(prefinishMarkReached(qint32)), this, SLOT(handlePrefinishMark(qint32)));
   connect(obj, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(SlotStateChanged1(Phonon::State, Phonon::State)));

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
   connect(obj2, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(SlotStateChanged2(Phonon::State, Phonon::State)));
   audio2=new AudioOutput(Phonon::MusicCategory, this);
   Phonon::createPath( obj2, audio2 );
   Phonon::createPath(obj2, videoWidget2);

    obj->setTickInterval(1000);

    QDir myDir(PathMp3);
    AlbumList = myDir.entryList ();

    QTimer *timerFadeOut = new QTimer(this);
    connect(timerFadeOut, SIGNAL(timeout()), this, SLOT(volFadeInOut()));
    timerFadeOut->start(1000);

   QSettings settings("queue.ini", QSettings::IniFormat);
   int size = settings.beginReadArray("kolejka");
   qDebug() << "kolejka size=" << size;
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


   if (LoadPlytyFromFile("ALBUMY.ini", listPlytyWszystkie) )
   {
       LoadPlytyFromFile("MuzykaPolska.ini", listMuzykaPolska);
       LoadPlytyFromFile("MuzykaZagraniczna.ini", listMuzykaZagraniczna);
       LoadPlytyFromFile("MuzykaNowosci.ini", listMuzykaNowosci);
       LoadPlytyFromFile("MuzykaBiesiadna.ini", listMuzykaBiesiadna);
       LoadPlytyFromFile("MuzykaSkladanki.ini", listMuzykaSkladanki);
       LoadPlytyFromFile("MuzykaKaraoke.ini", listMuzykaKaraoke);
       LoadPlytyFromFile("MuzykaItalo.ini", listMuzykaItalo);
   }
   else
   {
       QDir DirList(MP3_PATH);
       qDebug() << "MP3_PATH=" << MP3_PATH;
       QStringList AlbumList = DirList.entryList ();
       AlbumList.removeFirst();  // pomijamy poczatek listy \. i \..
       AlbumList.removeFirst();

       qDebug() << "NEW MP3 BASE=" << size;
       foreach (QString album, AlbumList) {
           Plyta *plyta = new Plyta();
           plyta->artist = album.left(album.indexOf("-"));
           plyta->title = album.mid(album.indexOf("-")+1);
           plyta->path = MP3_PATH + album + "/";
           listPlytyWszystkie.append(*plyta);

           QDir AlbumDir(plyta->path);
           QStringList AlbumList = AlbumDir.entryList ();
           if ( AlbumList.contains("MuzykaPolska") ) {
               listMuzykaPolska.append(*plyta);
           }
           if ( AlbumList.contains("MuzykaZagraniczna") ) {
               listMuzykaZagraniczna.append(*plyta);
           }
           if ( AlbumList.contains("MuzykaNowosci") ) {
               listMuzykaNowosci.append(*plyta);
           }
           if ( AlbumList.contains("MuzykaBiesiadna") ) {
               listMuzykaBiesiadna.append(*plyta);
           }
           if ( AlbumList.contains("MuzykaSkladanki") ) {
               listMuzykaSkladanki.append(*plyta);
           }
           if ( AlbumList.contains("MuzykaKaraoke") ) {
               listMuzykaKaraoke.append(*plyta);
           }
           if ( AlbumList.contains("MuzykaItalo") ) {
               listMuzykaItalo.append(*plyta);
           }
       }

       SavePlytyToFile("ALBUMY.ini", listPlytyWszystkie);
       SavePlytyToFile("MuzykaPolska.ini", listMuzykaPolska);
       SavePlytyToFile("MuzykaZagraniczna.ini", listMuzykaZagraniczna);
       SavePlytyToFile("MuzykaNowosci.ini", listMuzykaNowosci);
       SavePlytyToFile("MuzykaBiesiadna.ini", listMuzykaBiesiadna);
       SavePlytyToFile("MuzykaSkladanki.ini", listMuzykaSkladanki);
       SavePlytyToFile("MuzykaKaraoke.ini", listMuzykaKaraoke);
       SavePlytyToFile("MuzykaItalo.ini", listMuzykaItalo);
    }

    timer500ms = new QTimer(this);
    connect(timer500ms, SIGNAL(timeout()), this, SLOT(TimerTick()));
    timer500ms->start(300);
}

void folder::MuzykaWszystkie()
{
    ((Window*)parentWidget())->setGameState(ALBUMS);
    PathMp3 = MP3_PATH;
    if (((Window*)parentWidget())->homeScreen && ((Window*)parentWidget())->albumsScreen) {
        ((Window*)parentWidget())->homeScreen->hide();
        ((Window*)parentWidget())->songScreen->hide();
        ((Window*)parentWidget())->playScreen->hide();
        ((Window*)parentWidget())->albumsScreen->header->setText("WSZYSTKIE");        
        ((Window*)parentWidget())->albumsScreen->ShowAlbumsList(listPlytyWszystkie);
        ((Window*)parentWidget())->creditWidget->raise();
    }
}


void folder::MuzykaPolska()
{    
    ((Window*)parentWidget())->setGameState(ALBUMS);
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("MUZYKA POLSKA");
    ((Window*)parentWidget())->albumsScreen->ShowAlbumsList(listMuzykaPolska);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::MuzykaItalo()
{
    ((Window*)parentWidget())->setGameState(ALBUMS);
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("ITALO DISCO");
    ((Window*)parentWidget())->albumsScreen->ShowAlbumsList(listMuzykaItalo);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::MuzykaBiesiadna()
{
    QSettings *muzykaFile = new QSettings("c:/szafa/MuzykaBiesiadna.ini", QSettings::IniFormat);
    QStringList muzykaList = muzykaFile->allKeys();
    ((Window*)parentWidget())->setGameState(ALBUMS);

    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("MUZYKA BIESIADNA");
    ((Window*)parentWidget())->albumsScreen->ShowAlbumsList(listMuzykaBiesiadna);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::MuzykaZagraniczna()
{
    QSettings *muzykaFile = new QSettings("c:/szafa/MuzykaZagraniczna.ini", QSettings::IniFormat);
    ((Window*)parentWidget())->setGameState(ALBUMS);
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("MUZYKA ZAGRANICZNA");
    ((Window*)parentWidget())->albumsScreen->ShowAlbumsList(listMuzykaZagraniczna);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::Nowosci()
{
    ((Window*)parentWidget())->setGameState(ALBUMS);
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("NOWOŚCI");
    ((Window*)parentWidget())->albumsScreen->ShowAlbumsList(listMuzykaNowosci);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::Karaoke()
{
    ((Window*)parentWidget())->setGameState(ALBUMS);
    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("KARAOKE");
    ((Window*)parentWidget())->albumsScreen->ShowAlbumsList(listMuzykaKaraoke);
    ((Window*)parentWidget())->creditWidget->raise();
}

void folder::EndOfMovie()
{
    qDebug() << "EndOfMovie";
    isPlayingVideo=false;
}

void folder::Skladanki()
{
    ((Window*)parentWidget())->setGameState(ALBUMS);

    ((Window*)parentWidget())->homeScreen->hide();
    ((Window*)parentWidget())->songScreen->hide();
    ((Window*)parentWidget())->playScreen->hide();
    ((Window*)parentWidget())->albumsScreen->header->setText("SKŁADANKI");    
    ((Window*)parentWidget())->albumsScreen->ShowAlbumsList( listMuzykaSkladanki );
    ((Window*)parentWidget())->creditWidget->raise();
}


void folder::TimerTick()
{

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
    static int delayNextPlay = 0;


    if((obj->state() != PlayingState) && (obj2->state() != PlayingState) && (isPlayingVideo == false))
    {
        delayNextPlay++;
      if (delayNextPlay>10) // 3s delay
      {
        delayNextPlay = 0;
        qDebug() << "TimerTick, obj1&2 != PlayingState";
        KaraokeFullScreen = true;
        if (KaraokeFullScreenBak == true) {
            KaraokeFullScreenBak = false;
        }
        if (!Kolejka.isEmpty())
        {
            Playing = Kolejka.dequeue();
            src = Playing.path;
            qDebug() << "setCurrentSource=" << Playing.path;

            obj->setCurrentSource( src );
            obj->play();
            fadeState = 0;
            audio->setVolume(volume);
            KaraokeFullScreen = 1;
            repaint();
            isPlaying = true;

            ((Window*)parentWidget())->homeScreen->updateQueue();

        }
        else
        {
            if (isPlaying) {

                isPlaying = false;

                videoWidget->hide();
                videoWidget2->hide();
                this->lower();
                this->hide();
                ((Window*)parentWidget())->homeScreen->updateQueue();
                ((Window*)parentWidget())->homeScreen->repaint();

            }
        }
      }
      else {
          ((Window*)parentWidget())->homeScreen->updateQueue();
          ((Window*)parentWidget())->homeScreen->repaint();
          repaint();
      }
    }

    if(fadeState==0) {
        if((obj->state() == PlayingState)) {
            qDebug() << "obj->state() == PlayingState";
            isPlaying = true;

            qDebug() << "fadeState=0";
            qint64 sekundy = obj->remainingTime()/1000;
            qint64 minuty = sekundy / 60;
            sekundy = sekundy % 60;
            QString secStr;
            secStr.sprintf("%02d", (int)sekundy);

            QString czasUtworu = QString::number(minuty) + ":" + secStr;
            ((Window*)parentWidget())->homeScreen->CzasOdtwarzania->setText(czasUtworu);
        }
    }
    else {
        qDebug() << "fadeState!=0";
        if((obj2->state() == PlayingState)) {
            qDebug() << "obj2->state() == PlayingState";
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
    qDebug() << " handlePrefinishMark " << msecToEnd;

    if((obj->state() == PlayingState) && (obj->hasVideo()==false) && (isPlayingVideo==false))
    {
        qDebug() << "obj->state()";
        if (!Kolejka.isEmpty())
        {
            if(!Kolejka.head().path.contains(".avi")) {
                Playing = Kolejka.dequeue();
                src2 = Playing.path;

                qDebug() << "Playing.path=" << Playing.path;

                obj2->setCurrentSource( src2 );
                obj2->play();
                repaint();
                fadeState=1;
                audio2->setVolume(0);
                fadeTimer = (fadeTimeMs/1000);
                isPlaying=true;
            }

        }
    }
    else {
        if((obj2->state() == PlayingState) && (obj2->hasVideo()==false))
        {
            qDebug() << "obj2->state()";
            if (!Kolejka.isEmpty())
            {
                if(!Kolejka.head().path.contains(".avi")) {
                    Playing = Kolejka.dequeue();
                    src = Playing.path;

                    qDebug() << "Playing.path=" << Playing.path;
                    obj->setCurrentSource( src );
                    obj->play();
                    repaint();
                    fadeState = 0;
                    audio->setVolume(0);
                    fadeTimer = (fadeTimeMs/1000);
                    isPlaying=true;
                }

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
            if(song.path.toLower().contains(".avi")) {
                if (((Window*)parentWidget())->creditWidget->getCredit() >= ((Window*)parentWidget())->creditWidget->KaraokeCredit ) {
                    for (int c=0;c<((Window*)parentWidget())->creditWidget->KaraokeCredit;c++) ((Window*)parentWidget())->creditWidget->decrCredit();
                }
                else {
                    return;
                }
            }
            else {
                ((Window*)parentWidget())->creditWidget->decrCredit();
            }
            //spr czy karaoke
            ((Window*)parentWidget())->statScreen->SaveSongHistory(song.title);
            ((Window*)parentWidget())->statScreen->incrSongStats(song.path);
            Kolejka.enqueue(song);
            ((Window*)parentWidget())->homeScreen->updateQueue();
        }
    }

}

void folder::SlotStateChanged1(Phonon::State newState, Phonon::State oldState)
{
    qDebug() << "obj1 SlotStateChanged1";
    qDebug() << "OldState=" << QString::number(oldState);
    qDebug() << "NewState=" << QString::number(newState);
    qDebug() << obj->errorString();

}


void folder::SlotStateChanged2(Phonon::State newState, Phonon::State oldState)
{
    qDebug() << "obj2 SlotStateChanged1";
    qDebug() << "OldState=" << QString::number(oldState);
    qDebug() << "NewState=" << QString::number(newState);
    qDebug() << obj2->errorString();

}


