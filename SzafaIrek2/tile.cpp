#include "window.h"
#include "tile.h"

const QSize Tile::Size = QSize(130, 130);
Songs * Tile::songsPtr = 0;

Tile::Tile( QWidget *parent, QString path, QString Artist, QString title, QPixmap okladka) :
    QWidget(parent),
    albumPath(path)
{

    QString buttonStyle = " \
            background-color: rgba(10,20,30,0);";
    button = new QPushButton(this);
    button->setFocusPolicy(Qt::NoFocus);
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClick()));
    button->setStyleSheet( buttonStyle);
    button->resize(Size); //width, height.
    button->setIconSize(Size);

    QString styleLabel;
    styleLabel = styleLabel.sprintf("QLabel { \
        background-color: rgba(10,20,30,0); \
        font: 12px; \
        color: white;\
    }");
    Wykonawca = new QLabel(Artist, this);
    albumArtist = Artist;
    Wykonawca->resize(Size.width()+20,20);
    Wykonawca->move(0,Size.height());
    Wykonawca->setStyleSheet(styleLabel);
    Tytul = new QLabel(title, this);
    albumTitle = title;
    Tytul->resize(Size.width()+20,20);
    Tytul->move(0,Size.height()+20);
    Tytul->setStyleSheet(styleLabel);

    loadImagesTimer = new QTimer(this);
    loadImagesTimer->start(10);
    loadImagesTimer->setSingleShot(true);
    connect(loadImagesTimer, SIGNAL(timeout()), this, SLOT(loadImages()));
}


void Tile::buttonClick()
{
    qDebug() << "Tile::buttonClick";
}

void Tile::loadImages()
{
    qDebug() << "loadImages";
    QPixmap pm(albumPath + "/pic.png");

    button->move(0,0);
    button->setIcon(pm);
}

void SongTile::buttonClick()
{
    qDebug() << "albumPath" << albumPath;

}

void AlbumTile::buttonClick()
{
    qDebug() << "albumPath" << albumPath;
    songsPtr->showSongs(albumPath);
    parentWidget()->hide();

}

