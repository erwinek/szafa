#include <QtGui>
#include "cd.h"

cd::cd(QWidget *parent) :
    QWidget(parent)
{
    angle = 0;
    cd_okladka = 0; //okladka
    Okladka.load("gfx/pusta_okladka.jpg");
    CdImage.load("gfx/puste_cd.png");
}


void cd::paintEvent(QPaintEvent *event)
{

    QPainter paint( this );
    //QPainter::Antialiasing	0x01	Indicates that the engine should antialias edges of primitives if possible.
    //QPainter::TextAntialiasing	0x02	Indicates that the engine should antialias text if possible. To forcibly disable antialiasing for text, do not use this hint. Instead, set QFont::NoAntialias on your font's style strategy.
    //QPainter::SmoothPixmapTransform	0x04	Indicates that the engine should use a smooth pixmap transformation algorithm (such as bilinear) rather than nearest neighbor.

    if(cd_okladka)
    {

        paint.setRenderHints(QPainter::Antialiasing, 1);
        paint.setRenderHints(QPainter::SmoothPixmapTransform, 1);
        paint.translate(200+130, 20+130);
        paint.rotate(angle);
        paint.translate(-200-130, -20-130);
        //paint.drawImage(QRect(200, 20, 260, 260), CdImage);
        paint.drawImage(QRect(200, 20, 260, 260), resultImage);

    }
    else
    {
        paint.drawImage(QRect(200, 20, 260, 260), Okladka);
    }
    paint.end();
}


void cd::NewOkladka(QString path)
{
    if(!Okladka.load(path)) //jesli brak okladki plyty
    {
        Okladka.load("gfx/pusta_okladka.jpg");
    }


    //repaint();
}

void cd::rotate()
{

    if(angle<360) angle++;
    else angle = 0;

    repaint();

}

bool cd::loadCdImage(QString path) {

    QString cdPngFile = path + "/cd.png";
    if (!resultImage.load(cdPngFile))
    {
        static const QSize resultSize(400, 400);
        sourceImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        destinationImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);
        sourceImage.load("gfx/cd_mask.png");
        cdPngFile = path + "/pic.bmp";

        if (destinationImage.load(cdPngFile))
        {
            sourceImage = sourceImage.scaledToWidth(400);
            sourceImage = sourceImage.scaledToHeight(400);
            destinationImage = destinationImage.scaledToWidth(400);
            destinationImage = destinationImage.scaledToHeight(400);

            resultImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);

            QPainter::CompositionMode mode = QPainter::CompositionMode_DestinationIn;

            QPainter painter(&resultImage);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.fillRect(resultImage.rect(), Qt::transparent);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.drawImage(0, 0, destinationImage);
            painter.setCompositionMode(mode);
            painter.drawImage(0, 0, sourceImage);
            painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);

            painter.end();
        }
        else {  //jesli nie ma ani cd ani okladki

            resultImage.load("gfx/puste_cd.png");
        }
    }

    return true;
}



