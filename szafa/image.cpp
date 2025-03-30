#include <QtGui>
#include <qimage.h>
#include <qpainter.h>
#include "image.h"
#include "window.h"

Image::Image(const QString &filename, QWidget *parent) : QWidget (parent) {
        qimage = new QImage;
        qimage->load(filename);
}

void Image::paintEvent(QPaintEvent*) {

        QDesktopWidget* desktopWidget = qApp->desktop();
        QRect screenGeometry = desktopWidget->screenGeometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();


        QRectF target(0, 0, screenWidth , screenHeight);
        QPainter qpainter(this);
        //qpainter.drawImage(0, 0, *qimage);
        qpainter.drawImage(target, *qimage);

}

RImage::RImage(const QString &filename, QWidget *parent) : QWidget (parent) {
        qimage = new QImage;
        qimage->load(filename);
}

void RImage::paintEvent(QPaintEvent*) {
        QRectF target(0, 0, 500, 500);
        QPainter qpainter(this);

        qpainter.translate(target.width()/2, target.height()/2);
        qpainter.rotate(angle);
        qpainter.translate(-target.width()/2, -target.height()/2);
        qpainter.drawImage(target, *qimage);

}

void RImage::rotate()
{

    if(angle<360) angle++;
    else angle = 0;

    repaint();

}
