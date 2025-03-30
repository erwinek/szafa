#include "album.h"
#include "albums.h"

const QSize AlbumSize(130,130);

Album::Album( QWidget *parent, QString path, QString Artist, QString title) :
    QWidget(parent)
{
    albumPath = path;
    QString buttonStyle = " \
            background-color: rgba(10,20,30,0);";

    QPushButton *button = new QPushButton(this);
    QImage bOkladkaImg;
    if (!bOkladkaImg.load(path + "/pic.jpg")) {
        bOkladkaImg.load("gfx/pusta_okladka.jpg");
    }

    button->resize(AlbumSize); //width, height.
    button->move(0,0);
    button->setIcon(QPixmap::fromImage(bOkladkaImg));
    button->setIconSize(AlbumSize);
    button->setFocusPolicy(Qt::NoFocus);
    connect(button, SIGNAL(clicked()), this, SLOT(openAlbum()));
    button->setStyleSheet( buttonStyle);

    QString styleLabel;
    styleLabel = styleLabel.sprintf("QLabel { \
        background-color: rgba(10,20,30,0); \
        font: 12px; \
        color: white;\
    }");

    Wykonawca = new QLabel(Artist, this);
    albumArtist = Artist;
    Wykonawca->resize(AlbumSize.width()+20,20);
    Wykonawca->move(0,AlbumSize.height());
    Wykonawca->setStyleSheet(styleLabel);

    Tytul = new QLabel(title, this);
    albumTitle = title;
    Tytul->resize(AlbumSize.width()+20,20);
    Tytul->move(0,AlbumSize.height()+20);
    Tytul->setStyleSheet(styleLabel);



}

void Album::openAlbum()
{
    Album::albumsPtr->ShowSongScreen(this);
}
