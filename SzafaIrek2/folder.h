#ifndef FOLDER_H
#define FOLDER_H

#include <qwidget.h>
#include <qlistwidget.h>
#include <phonon>
#include <qfiledialog.h>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <phonon/videowidget.h>
#include <QUrl>
#include <QQueue>
#include <QLabel>
#include "scroll.h"

class Plyta
{
public:
    QString artist;
    QString title;
    QString path;
};

using namespace Phonon;

class Song
{
public:
    QString artist;
    QString title;
    QString path;
    QString CdPath;
    QString songLength;
};


class folder : public QWidget
{
    Q_OBJECT

public:
    void AddToQueue(Song &song);
    void FindAlbum(QString name);
    int RemoveFromQueueCounter;
    folder(QWidget *parent);
    QString CurentPath;
    int AlbumSelector;
    int SongSelector;
    QQueue<Song> Kolejka;
    Song Playing;

    QList<Plyta> listPlytyWszystkie;
    QList<Plyta> listPlytyPolskie;

    void setVolume(int Volume); //0-99
    bool isPlaying;
    bool isPlayingVideo;

    MediaObject *obj;
    MediaObject *obj2;

private:

    QList <Plyta> listMuzykaPolska;
    QList <Plyta> listMuzykaZagraniczna;
    QList <Plyta> listMuzykaNowosci;
    QList <Plyta> listMuzykaBiesiadna;
    QList <Plyta> listMuzykaSkladanki;
    QList <Plyta> listMuzykaKaraoke;
    QList <Plyta> listMuzykaItalo;

    QTimer *timer500ms;
    qreal volume;
    bool fadeState;
    bool KaraokeFullScreen;
    bool KaraokeFullScreenBak;
    bool StopState;
    QString styleLabelCredit;
    QString styleLabelSongTime;

    QString styleListAlbum;
    QString styleListWidget;
    AudioOutput *audio;
    AudioOutput *audio2;

    void PrintAlbums(QRect *rect);
    void PrintSongs(QRect *rect);    
    void RecurseDirectory(const QString& sDir);
    QString PathMp3;
    QStringList AlbumList;
    QStringList SongList;
    QStringList SongListDisplay;
    QStringList mp3SongListDisplay;
    QStringList Queque;
    VideoWidget *videoWidget;
    VideoWidget *videoWidget2;
    MediaSource src;
    MediaSource src2;
    qint32 fadeTimeMs;
    int fadeTimer;

public slots:    
    void volFadeInOut();
    void handlePrefinishMark(qint32 msecToEnd);
    void MuzykaWszystkie();
    void MuzykaPolska();
    void MuzykaItalo();
    void MuzykaBiesiadna();
    void MuzykaZagraniczna();
    void Nowosci();
    void Skladanki();
    void TimerTick();

private slots:    
    void EndOfMovie();
    void Karaoke();
    void SlotStateChanged1(Phonon::State, Phonon::State);
    void SlotStateChanged2(Phonon::State, Phonon::State);

};


#endif // FOLDER_H
