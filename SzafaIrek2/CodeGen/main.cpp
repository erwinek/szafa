#include <QCoreApplication>
#include <QtCore>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkInterface>

int main(int argc, char *argv[])
{
    QString str(argv[1]);

    quint32 pass = 0x5a5fa59a;
    bool ok;

    qlonglong hwId = str.toULongLong(&ok);
    std::cout << "diskNo=" << hwId << std::endl;

    if(hwId==0) {
        qlonglong diskNo;
        DWORD dwVolSerial;
        BOOL bIsRetrieved;

        bIsRetrieved = GetVolumeInformationA("C:\\", NULL, NULL, &dwVolSerial, NULL, NULL, NULL, NULL);

        if(bIsRetrieved) {
            diskNo = dwVolSerial;
            std::cout << "diskNo=" << diskNo << std::endl;
        }
        else {
            std::cout << "GetVolumeInformationA fail"  << std::endl;
            return 0;
        }

        qlonglong macId = 0;


        QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); // now you have interfaces list
        foreach (QNetworkInterface iface, list)  // this should print all interfaces' names
        {
            QString mac = iface.hardwareAddress();
            bool ok;
            mac.remove(':');
            qlonglong macNo = mac.toLongLong(&ok, 16);
            macId += macNo;
        }

        hwId = macId + diskNo;

    }
	

    std::cout << "hwId=" << hwId << std::endl;

    quint32 hash = ((hwId * hwId) ^ pass ) * pass;
    std::cout << "SerialNo=" << hash << std::endl;

    QSettings *settingsLic = new QSettings("lic.ini", QSettings::IniFormat);

    settingsLic->setValue("serialNo", hash);
    settingsLic->setValue("hwId", hwId);
    settingsLic->sync();

}
