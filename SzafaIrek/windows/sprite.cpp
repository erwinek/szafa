#include <QtGui>
#include "sprite.h"

Sprite::Sprite(QWidget *parent) :
    QWidget(parent)
{
    img.load("gfx/6.png");
    move_x = 0;
    move_y = 0;

}

void Sprite::paintEvent(QPaintEvent *event)
{

    QPainter paint( this );

    paint.setRenderHints(QPainter::Antialiasing, 1);
    paint.setRenderHints(QPainter::SmoothPixmapTransform, 1);
    paint.translate(1024/2+move_x, 768/2+move_y);
    paint.rotate(angle);
    paint.translate(-(768/2+move_y), -(768/2+move_y));
    paint.drawImage(QRect(1024/2+move_x, 768/2+move_y, 100, 100), img);
    paint.end();
}

void Sprite::moveRandom()
{

    //qrand() % ((high + 1) - low) + low;
    angle = angle + qrand() % ((10 + 1) - 1);

    move_x = move_x + (qrand() % 4) - 2;
    move_y = move_y + (qrand() % 4)  - 2;
    if (move_x > 100) move_x = -move_x;
    if (move_y > 100) move_y = -move_y;


    repaint();

}
