#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>

class Sprite : public QWidget
{
    Q_OBJECT
public:
    explicit Sprite(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
private:
    QImage img;
    qreal angle;
    int move_x;
    int move_y;
signals:
    
public slots:
    void moveRandom();
};

#endif // SPRITE_H
