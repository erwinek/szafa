#include "playsong.h"
#include "window.h"

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

PlaySong::PlaySong(QWidget *parent) :
    QWidget(parent)
{
    QString styleLabelCzyZagrac = "QLabel { \
        font: bold 30px; \
        color: white;\
    }";
    QLabel *labelCzyZagrac = new QLabel(this);
    labelCzyZagrac->setText("TO JEST TWOJA WYBRANA PIOSENKA\nCZY ZAGRAC TEN UTWÓR ?");
    labelCzyZagrac->resize(800, 100);
    labelCzyZagrac->move(110, 778-200);
    labelCzyZagrac->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    labelCzyZagrac->setStyleSheet( styleLabelCzyZagrac);

    QString styleLabelHeader = "QLabel { \
        font: bold 22px; \
        color: white;\
        background-image: url(gfx/Background_play_title.png);\
    }";

    QImage headerImg("gfx/Background_play_title.png");
    header = new QLabel("", this);
    header->resize(headerImg.size());
    header->move(170, 100);
    header->setStyleSheet(styleLabelHeader);
    header->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);


    QString labelOkladkaStyle = " background-color: rgba(0,0,0,0); \
                                border: 8px solid #ffffff; ";
    labelOkladka = new QLabel(this);
    labelOkladka->resize(300,300);
    labelOkladka->move(365, 250);
    labelOkladka->setStyleSheet(labelOkladkaStyle);
    labelOkladka->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);


    QString buttonStyleSheet = " background-color: rgba(0,0,0,0); ";

    playButton = new QPushButton(this);
    playButton->resize(250,300); //width, height.
    playButton->move(85,250);
    QImage bPlayImg("gfx/accept_button.png");
    playButton->setIcon(QPixmap::fromImage(bPlayImg));
    playButton->setIconSize(QSize(300,300));
    playButton->setFocusPolicy(Qt::NoFocus);
    connect(playButton, SIGNAL(clicked()),this, SLOT(play()));
    playButton->setStyleSheet( buttonStyleSheet);

    cancelButton = new QPushButton(this);
    cancelButton->resize(250,300); //width, height.
    cancelButton->move(695,250);
    QImage bCancelImg("gfx/decline_button.png");
    cancelButton->setIcon(QPixmap::fromImage(bCancelImg));
    cancelButton->setIconSize(QSize(300,300));
    cancelButton->setFocusPolicy(Qt::NoFocus);
    connect(cancelButton, SIGNAL(clicked()),this, SLOT(cancel()));
    cancelButton->setStyleSheet( buttonStyleSheet);

    this->resize(1024,768);
    this->move(0, 0);

}

void PlaySong::play()
{
    ((Window*)parentWidget())->restartTimeNotTouched();
    ((Window*)parentWidget())->albums->AddToQueue(currentSong);
    qWarning() << "PlaySong::play()";
    qWarning() << "currentSong.path=" << currentSong.path;
    qWarning() << "currentSong.songLength=" << currentSong.songLength;
    this->hide();
    ((Window*)parentWidget())->songScreen->show();
    ((Window*)parentWidget())->menu->show();
    ((Window*)parentWidget())->creditWidget->raise();
}

void PlaySong::cancel()
{
    ((Window*)parentWidget())->restartTimeNotTouched();
    this->hide();
    ((Window*)parentWidget())->songScreen->show();
    ((Window*)parentWidget())->menu->show();
    ((Window*)parentWidget())->creditWidget->raise();
}


void PlaySong::showSong(Song piosenka)
{
    ((Window*)parentWidget())->restartTimeNotTouched();
    currentSong = piosenka;
    QString headerTxt = currentSong.artist + "\n" + currentSong.title;
    header->setText(headerTxt);
    currentSong.songLength = "3:20";
    obj3 = new Phonon::MediaObject(this);
    MediaSource src3;
    QString song_path =  currentSong.path;
    src3 = song_path;
    obj3->setCurrentSource( src3 );
    AudioOutput *audio=new AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(obj3,  audio );
    obj3->setTickInterval(1000);

    connect(obj3, SIGNAL(totalTimeChanged ( qint64)), this, SLOT(handleTotalTimeChanged(qint64)));

    QString imgPath = currentSong.CdPath;
    imgPath.chop(3);
    imgPath += "bmp";
    QImage imgOkladka;
    imgOkladka.load(imgPath);
    labelOkladka->setPixmap(QPixmap::fromImage(imgOkladka).scaled(labelOkladka->size()));

    ((Window*)parentWidget())->creditWidget->lower();
    this->show();
    this->raise();


}

void PlaySong::handleTotalTimeChanged(qint64 val)
{

    qint64 min = val/1000/60;
    qint64 sek = val/1000 - (min*60);

    QString minStr;
    minStr.sprintf("%d", (int)min);
    QString secStr;
    secStr.sprintf("%02d", (int)sek);

    currentSong.songLength = minStr + ":" + secStr;

}
