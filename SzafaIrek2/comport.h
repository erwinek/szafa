#ifndef COMPORT_H
#define COMPORT_H

#include <QWidget>
#include "qextserialport.h"

class ComPort : public QWidget
{
    Q_OBJECT
public:
    bool setLedProgram;
    bool resetCounter;
    int decrCredit;
    int incrCredit;
    quint32 totalCounter;
    quint32 currentCounter;
    QString ComPortNumber;
    explicit ComPort(QWidget *parent = 0);
    QextSerialPort *port;
    bool OpenComPort(QString ComPortNumber);
private:
    quint8 LedProgram;
    void SendAck();
    QByteArray comPortFrame;
    int frameCounter;
    bool bStartFrame;
    bool GetDataFromBuffer(QByteArray readBuffer);
    void ProcessFrame(void);
signals:

public slots:
     void onDataAvailable();
     void SendFrame(const char *data);
     void SendFrame(QString data);
     void SendRequest();
};

#endif // COMPORT_H
