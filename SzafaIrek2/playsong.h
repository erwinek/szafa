#ifndef PLAYSONG_H
#define PLAYSONG_H

#include <QWidget>
#include <QtGui>
#include "folder.h"

class PlaySong : public QWidget
{
    Q_OBJECT
public:
    explicit PlaySong(QWidget *parent = 0);
    void showSong(Song piosenka);
private:
    QPushButton *playButton;
    QPushButton *cancelButton;
    QLabel *header;
    QLabel *labelOkladka;
    Song currentSong;
    MediaObject obj3;
    QPixmap picOkladka;
    AudioOutput audioOut;
signals:
    
public slots:

private slots:
    void play();
    void cancel();
    void handleTotalTimeChanged(qint64 val);
    
};

#endif // PLAYSONG_H
