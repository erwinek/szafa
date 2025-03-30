#include "songwidget.h"
#include "szukaj.h"

const QSize AlbumSize(130,130);

SongWidget::SongWidget( QWidget *parent, QString path, QString title) :
    QWidget(parent)

{
    albumPath = path;
    songsPtr = (Songs*)parent;
    QString buttonStyle = " \
            background-color: rgba(10,20,30,0);";
    QPushButton *button = new QPushButton(this);
    QImage bOkladkaImg;
    if (!bOkladkaImg.load(path + "pic.png")) {
        bOkladkaImg.load("gfx/pusta_okladka.jpg");
    }
    static int cnt = 0;
    cnt++;

    button->resize(AlbumSize); //width, height.
    button->move(0,0);
    button->setIcon(QPixmap::fromImage(bOkladkaImg));
    button->setIconSize(AlbumSize);
    button->setFocusPolicy(Qt::NoFocus);
    connect(button, SIGNAL(clicked()), this, SLOT(clickSong()));
    button->setStyleSheet( buttonStyle);

    QString styleLabel;
    styleLabel = styleLabel.sprintf("QLabel { \
        background-color: rgba(10,20,30,0); \
        font: 12px; \
        color: white;\
    }");
    songTitle = title;

    QString titleLine1;
    QString titleLine2;

    int przelam = songTitle.lastIndexOf("-");
    if (przelam>5) {
        titleLine1 = songTitle.left(przelam);
        titleLine2 = songTitle.mid(przelam, songTitle.length()-przelam);
    }
    else {
        titleLine1 = songTitle;
        titleLine2 = "";
    }

    Tytul = new QLabel(titleLine1, this);
    Tytul->resize(AlbumSize.width(),20);
    Tytul->move(0,AlbumSize.height());
    Tytul->setStyleSheet(styleLabel);

    Tytul2 = new QLabel(titleLine2, this);
    Tytul2->resize(AlbumSize.width(),20);
    Tytul2->move(0,AlbumSize.height()+20);
    Tytul2->setStyleSheet(styleLabel);

}

void SongWidget::clickSong()
{
    songsPtr->songClick(this);
}
