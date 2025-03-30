#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <QWidget>
#include <QtGui>

const int MIN_IDLE_TIME = 30;

class   Slideshow : public QWidget
{
    Q_OBJECT
public:
    explicit Slideshow(QWidget *parent = 0);
    void SwitchOff();
    void SwitchOn();
    void resetCounter();
    void paintEvent(QPaintEvent *event);
    bool OnOff;
private:
    QImage image;
    int counter;

    QStringList imageList;
    int imageCounter;
    QLabel *imageLabel;
    QTimer *imageTimer;
    QTimer *delayStartTimer;

private slots:
    void nextImage();
    void showSlideshow();
    
};

#endif // SLIDESHOW_H
