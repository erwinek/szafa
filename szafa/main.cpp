#include <QApplication>
#include <QtGui>
#include "window.h"
#include "cd.h"
//#include "glwidg.h"



int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    app.setApplicationName("Music Player");
    app.setQuitOnLastWindowClosed(true);

    Window window;


    window.setStyleSheet("QPushButton { \
                                            background-color: rgba(10,20,30,150); \
                                            font-size: 22px; \
    color: white;\
                                            border-radius: 6px; \
                                    }");
    window.resize(1024, 768);
    window.show();
    window.showFullScreen();
    //antialiasingCheckBox.setChecked(true);

    return app.exec();
}
