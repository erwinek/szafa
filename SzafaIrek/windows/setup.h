#ifndef SETUP_H
#define SETUP_H

#include <QWidget>
#include <QtGui>
#include "stats.h"
#include "keyboard.h"




class Setup : public QWidget
{
    Q_OBJECT
public:
    bool freePlayOnOff;
    QSettings statsFile;
    QImage *SetupImage;

    explicit Setup(QWidget *parent = 0);
    
    enum Screen {
       FORTEPIAN,
       NUTKI,
       SKRZYPCE,
       CZARNY,
       MENU_KOLOR
    };
    int Screen;
    QSettings settings;

signals:
    
public slots:
    void Init();
    void ExitSetup();    
    void StyleChange();
    void AddCredit();
    void HideKeyboard();
private slots:
    void EditPassword();    
    void ExitSetupWithoutSave();
    void FreePlay();

private:
    Keyboard *keyboard;
    QLabel *lFreePlay;
    QPushButton *bExit;
    QPushButton *bExitWithoutSave;
    QComboBox *styl;
    QComboBox *comPortSelect;
    int current_style;
    QCheckBox *checkboxFreePlay;
    QLineEdit *editPass;
protected:
    void paintEvent(QPaintEvent *event);
    
};

#endif // SETUP_H
