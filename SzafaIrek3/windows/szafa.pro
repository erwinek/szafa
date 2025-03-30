QT          += phonon
#include(qextserialport/src/qextserialport.pri)
#include(~/rs232/qextserialport/qextserialport.prl)
# Add more folders to ship with the application, here
folder_01.source = qml/szafa
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01


# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE20E499F

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components



# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    window.cpp \
    cd.cpp \
    image.cpp \
    folder.cpp \
    szukaj.cpp \
    scroll.cpp \
    setup.cpp \
    comport.cpp \
    sprite.cpp \
    init.cpp \
    stats.cpp \
    keyboard.cpp \
    home.cpp \
    credit.cpp \
    albums.cpp \
    album.cpp \
    songs.cpp \
    playsong.cpp \
    menu.cpp \
    songlistwidget.cpp \
    songwidget.cpp \
    toplist.cpp \
    slideshow.cpp \
    volsetup.cpp \
    menusetup.cpp \
    setupcounter.cpp \
    qextserialport/qextserialport.cpp \
	insertcoin.cpp

# Please do not modify the following two lines. Required for deployment.
#include(qmlapplicationviewer/qmlapplicationviewer.pri)
#qtcAddDeployment()

HEADERS += \
    window.h \
    folder.h \
    cd.h \
    image.h \
    szukaj.h \
    scroll.h \
    setup.h \
    comport.h \
    sprite.h \
    init.h \
    stats.h \
    keyboard.h \
    home.h \
    credit.h \
    albums.h \
    album.h \
    songs.h \
    playsong.h \
    menu.h \
    songlistwidget.h \
    songwidget.h \
    toplist.h \
    songlistwidget.h \
    songwidget.h \
    slideshow.h \
    volsetup.h \
    menusetup.h \
    setupcounter.h \
    insertcoin.h


OTHER_FILES +=

