#ifndef INIT_H
#define INIT_H

#include <QWidget>
#include <QtGui>

class Init : public QWidget
{
    Q_OBJECT
public:
    explicit Init(QWidget *parent = 0);
    
signals:
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
public slots:
    void progress();
private:
    QProgressBar *progressBar;
    QImage BackgroundImage;
};

#endif // INIT_H
