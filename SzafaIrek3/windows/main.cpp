#include <QApplication>
#include <QtGui>
#include "window.h"
#include "init.h"
//#include "cd.h"
//#include "glwidg.h"





int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    app.setApplicationName("Music Player");
    app.setQuitOnLastWindowClosed(true);
    //app.setOverrideCursor( QCursor( Qt::BlankCursor ) );
    Init StartupScreen;
    StartupScreen.resize(1024, 768);
    StartupScreen.showFullScreen();


    QPixmap pixmap("gfx/blackBackground.jpg");
    QSplashScreen *splash = new QSplashScreen(pixmap);

    splash->showFullScreen();

    app.processEvents();
    app.setOrganizationName("ipsystem");

    Window window;
    window.resize(1024, 768);

    StartupScreen.hide();
    window.showFullScreen();

    delete splash;

    return app.exec();
}
