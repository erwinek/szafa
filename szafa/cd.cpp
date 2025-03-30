#include <QtGui>
#include "cd.h"

cd::cd(QWidget *parent) :
    QWidget(parent)

{

    //setFixedSize(400, 400);
    CdImage.load("gfx/cd.jpg");
    Okladka.load("gfx/elektryczne-gitary-nic-mnie-nie-rusza.jpg");
    cd_okladka = 0; //okladka
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
        paint.translate(180+130, 20+130);
        paint.rotate(angle);
        paint.translate(-180-130, -20-130);

        //CdImage.load("gfx/cd.jpg");
        //CdImage.setAlphaChannel(CdImage.createMaskFromColor(Qt::white, Qt::MaskOutColor));
        //paint.drawImage(QRect(0, 0, 400, 400), CdImage, Qt::OrderedAlphaDither);
        paint.drawImage(QRect(180, 20, 260, 260), CdImage);


        //CdPixmap.setMask(CdPixmap.createMaskFromColor(Qt::white));     // use transparent instead of white
        //CdPixmap.setMask(CdPixmap.createHeuristicMask(false));
        //paint.drawPixmap(0,0,400,400,CdPixmap);

    }
    else
    {
        paint.drawImage(QRect(180, 20, 260, 260), Okladka);
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
