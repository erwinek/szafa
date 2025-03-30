#ifndef VOLSETUP_H
#define VOLSETUP_H

#include <QWidget>
#include <QtGui>

const int MAX_VOL = 30;
const int MIN_VOL = 1;

class VolSetup : public QWidget
{
    Q_OBJECT
public:

    explicit VolSetup(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    int GetVolume()
    {
        return volume;
    }

private:
    QPushButton *bVolumeMinus;
    QPushButton *bVolumePlus;
    QSlider *sVolume;

    QPushButton *bLedMinus;
    QPushButton *bLedPlus;
    QLCDNumber *dLed;
    QLCDNumber *dVol;

    int volume;
    int led;

    QImage VolSetupImage;
signals:

public slots:
    void LedPlus();
    void LedMinus();
    void VolPlus();
    void VolMinus();

public slots:
    void Exit();

};

#endif // VOLSETUP_H
