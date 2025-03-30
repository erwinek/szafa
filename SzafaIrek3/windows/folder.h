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

    void setVolume(int Volume); //0-99
    bool isPlaying;
private:    
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
    MediaObject *obj;
    MediaObject *obj2;
    QTimer *TimerOkladka;
    qint32 fadeTimeMs;
    int fadeTimer;

public slots:    
    void volFadeInOut();
    void handlePrefinishMark(qint32 msecToEnd);
    void MuzykaWszystkie();
    void MuzykaPolska();
    void MuzykaBiesiadna();
    void MuzykaZagraniczna();
    void Nowosci();
    void Skladanki();
    void TimerTick();
    void TimerOkladkaTimeout();
private slots:    
    void Karaoke();


};


#endif // FOLDER_H
