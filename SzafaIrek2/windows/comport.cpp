#include <QtGui>
#include "window.h"
#include "comport.h"


ComPort::ComPort(QWidget *parent) :
    QWidget(parent)
{    
    //ComPortNumber = "/dev/ttyS0";
    ComPortNumber = ((Window*)parentWidget())->setup->settings.value("Setup/ComPort", "/dev/ttyS0").toString();

    port = new QextSerialPort(ComPortNumber);
    port->setBaudRate(BAUD57600);
    connect(port, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    OpenComPort(ComPortNumber);
    resetCounter = 0;
    decrCredit = 0;
    incrCredit = 0;
    setLedProgram = 0;
}



void ComPort::onDataAvailable()
{
    QByteArray readBuffer = port->readAll();
    if (GetDataFromBuffer(readBuffer)) ProcessFrame();
}

bool ComPort::OpenComPort(QString ComPortNumber)
{
    port->setPortName(ComPortNumber);
    if (port->open(QIODevice::ReadWrite)) {
        qDebug() << " COM PORT OPEN " << ComPortNumber;
        if (port->isOpen()) qDebug() << " COM PORT OPEN ";
        if (port->isWritable()) qDebug() << " COM PORT isWritable ";

        return true; //ok
    }
    else {
        qDebug() << " BLAD OTWARCIA PORTU " << ComPortNumber;
        return false; //blad
    }
}

void ComPort::SendFrame(const char *data)
{
    port->write(data);
}

void ComPort::SendFrame(QString data)
{
    port->write(data.toLocal8Bit());
}

void ComPort::SendRequest()
{
    SendFrame(":01FF02000002\r\n");
}

bool ComPort::GetDataFromBuffer(QByteArray readBuffer)
{
    for(int i = 0; i<readBuffer.size(); i++)
    {
        if(bStartFrame)
        {
            comPortFrame[frameCounter] = readBuffer[i];
            frameCounter++;
            if (readBuffer[i]==10) {
                comPortFrame[frameCounter]=0;
                return true;
            }
            if(frameCounter>255) { //ta ramka jest chyba za dluga
                bStartFrame = 0;
                frameCounter = 0;
            }
        }
        else {
            comPortFrame.clear();
            frameCounter=0;
            if (readBuffer[i]==':') {
                bStartFrame=1;
                frameCounter=0;
            }
        }
    }
    return false;
}

void ComPort::ProcessFrame(void)
{
    quint8 crc=0;
    //check crc
    int i;
    char temp[10];
    quint8 data[255];
    quint8 dataCnt=0;

    for (i=0; i < (comPortFrame.size()-2); i += 2) {
        if (!comPortFrame[i] || !comPortFrame[i+1]) break;
        temp[0] = comPortFrame[i];
        temp[1] = comPortFrame[i+1];
        temp[2] = 0;

        data[dataCnt] = strtol(temp, 0, 16);
        dataCnt++;
    }

    for(i=0;i<dataCnt-2;i++) {
        crc += data[i];
    }

    if (crc==data[dataCnt-2]) { //crc ok

        int key=~data[1];
        ((Window*)parentWidget())->creditWidget->setCredit(data[2]);
        totalCounter = (data[3]<<24) + (data[4]<<16) + (data[5]<<8) + (data[6]<<0);
        currentCounter = (data[7]<<24) + (data[8]<<16) + (data[9]<<8) + (data[10]<<0);
        //key=0;
        if (key&0x01) {
             ((Window*)parentWidget())->enterMenuSetup();
        }
        if (key&0x02) {
            //((Window*)parentWidget())->enterMenuSetup();
        }
        if (key&0x04) {
             //((Window*)parentWidget())->enterMenuSetup();
        }
        if (key&0x08) {
             //((Window*)parentWidget())->enterMenuSetup();
        }
        if (key&0x10) {
             //((Window*)parentWidget())->enterMenuSetup();
        }
        if (key&0x20) {
            //((Window*)parentWidget())->enterMenuSetup();
        }
        if (key&0x40) {
            //((Window*)parentWidget())->enterMenuSetup();
        }
        if (key&0x80) {
            //((Window*)parentWidget())->enterMenuSetup();
        }

        SendAck();
    }
    else { //crc error - do not sent Ack

    }
    bStartFrame = 0;
}

void ComPort::SendAck()
{
    QString send_buffer = ":";
    QString temp;
    quint8 i,crc=0;
    quint8 data[255] = ":01ff01000000\r\n";
    data[0] = 1; //rozkaz
    data[1] = 0xff;//zarowki
    if (resetCounter) { //1 - kasowanie licznika, 2 - decr kredyt
        data[2] = 0x01;
        resetCounter = 0;
    }
    else {
        if (decrCredit) {
            data[2] = 0x02;
            decrCredit--;
        }
        else {
            if (incrCredit) {
                data[2] = 0x04;
                incrCredit--;
            }
            else {
                data[2] = 0x00;
            }
        }
    }
	//data[2] = 0x04;
    //if(setLedProgram)
   // {
    //    setLedProgram = 0;
        LedProgram = ((Window*)parentWidget())->setup->settings.value("Setup/LedProgram").toInt();
    //}
    data[3]=LedProgram;
    data[4]=0;//dummy
    data[5]=0;

    for (i=0;i<5;i++) {
        if (data[i]) crc += data[i];
        temp.sprintf("%02x", data[i]);
        send_buffer.append(temp);
    }

    temp.sprintf("%02x", crc);  //crc
    send_buffer.append(temp);
    send_buffer.append("\r\n");

    SendFrame(send_buffer);

}

