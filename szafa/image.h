#ifndef IMAGE_H
#define IMAGE_H

#include <qwidget.h>

class QImage;

class Image : public QWidget {
public:
        Image(const QString &filename, QWidget *parent);

protected:
        void paintEvent(QPaintEvent*);

private:
        QImage *qimage;
};

class RImage : public QWidget {

public:
        RImage(const QString &filename, QWidget *parent);

protected:
        void paintEvent(QPaintEvent*);

private:
        QImage *qimage;
        qreal angle;

public slots:
    void rotate();

};

#endif // IMAGE_H
