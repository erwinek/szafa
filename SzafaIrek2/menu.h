#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QtGui>

class   Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);
    void ReloadButtonImage();
    void mousePressEvent(QMouseEvent *event);
private:
    QPushButton *buttonSzukaj;
    QPushButton *buttonWszystkie;
    QPushButton *buttonMpolska;
    QPushButton *buttonMitalo;
    QPushButton *buttonMbiesiadna;
    QPushButton *buttonMzagraniczna;
    QPushButton *buttonKaraoke;
    QPushButton *buttonSkladanki;
    QPushButton *buttonNowosci;
    QPushButton *buttonTop10;

    QPushButton *buttonUp;
    QPushButton *buttonDown;

    QLabel *lSoftwareVersion;

    QList<QPushButton*> buttonList;

    //QVBoxLayout *layout;
    int startButton;
    void ReloadButtons( );

    QPixmap picUp1;
    QPixmap picUp2;

    QPixmap picDown1;
    QPixmap picDown2;


signals:
private slots:
    void flashUpDpwnArrow();
public slots:
    void MenuUp();
    void MenuDown();
    
};

#endif // MENU_H
