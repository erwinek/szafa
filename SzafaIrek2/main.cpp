#include <QApplication>
#include <QtGui>
#include "window.h"
#include "init.h"

QString Window::SoftwareVersion = "v1.06";

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    app.setApplicationName("Music Player");
    app.setQuitOnLastWindowClosed(true);
    app.setOverrideCursor( QCursor( Qt::BlankCursor ) );
    Init StartupScreen;
    StartupScreen.resize(1024, 768);
    StartupScreen.showFullScreen();


    QPixmap pixmap("gfx/blackBackground.jpg");
    QSplashScreen *splash = new QSplashScreen(pixmap);

    //splash->showMessage("LICENCE ERROR", Qt::AlignCenter, Qt::red);

    splash->showFullScreen();

    app.processEvents();
    app.setOrganizationName("ipsystem");

    Window window;
    window.resize(1024, 768);

    if(window.NoLicence == false) {
        StartupScreen.hide();
        window.showFullScreen();
        delete splash;
    }
    else {
        QFont splashFont;
        splashFont.setFamily("Arial");
        splashFont.setBold(true);
        splashFont.setPixelSize(90);
        splashFont.setStretch(125);

        splash->setFont(splashFont);
        QString hwId = QString::number(window.diskNo);
        hwId += QString("\n No Licence");
        splash->showMessage(hwId, Qt::AlignCenter, Qt::red);
    }

    return app.exec();
}
