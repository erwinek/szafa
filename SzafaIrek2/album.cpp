#include "album.h"
#include "albums.h"

const QSize AlbumSize(130,130);

Album::Album( QWidget *parent, QString path, QString Artist, QString title, QImage okladka) :
    QWidget(parent)
{
    albumPath = path;
    QString buttonStyle = " \
            background-color: rgba(10,20,30,0);";
    button = new QPushButton(this);

    button->setFocusPolicy(Qt::NoFocus);
    connect(button, SIGNAL(clicked()), this, SLOT(openAlbum()));
    button->setStyleSheet( buttonStyle);
    button->resize(AlbumSize); //width, height.
    button->setIconSize(AlbumSize);


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

    loadImagesTimer = new QTimer(this);
    loadImagesTimer->start(100);
    loadImagesTimer->setSingleShot(true);
    connect(loadImagesTimer, SIGNAL(timeout()), this, SLOT(loadImages()));

}
    /*
Album::~Album()
{
    loadImagesTimer->stop();
    delete loadImagesTimer;
}*/

void Album::loadImages()
{
    qDebug() << "loadImages";
    pic.load(albumPath + "/pic.png");

    button->move(0,0);
    button->setIcon(pic);

}

void Album::openAlbum()
{
    Album::albumsPtr->ShowSongScreen(this);
}
