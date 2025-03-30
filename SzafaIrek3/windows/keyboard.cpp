#include "setup.h"
#include "keyboard.h"


#define NUM_x 170
#define NUM_y 50

#define Q_x 200
#define Q_y NUM_y+60

#define A_x 230
#define A_y Q_y+60

#define Z_x 260
#define Z_y A_y+60

#define KEY_ODSTEP 60



struct Keyboard::keyboardStruct onScreenKeyboard[40] = {

{  NULL, "1", NUM_x+KEY_ODSTEP*0, NUM_y },
{  NULL, "2", NUM_x+KEY_ODSTEP*1, NUM_y },
{  NULL, "3", NUM_x+KEY_ODSTEP*2, NUM_y },
{  NULL, "4", NUM_x+KEY_ODSTEP*3, NUM_y },
{  NULL, "5", NUM_x+KEY_ODSTEP*4, NUM_y },
{  NULL, "6", NUM_x+KEY_ODSTEP*5, NUM_y },
{  NULL, "7", NUM_x+KEY_ODSTEP*6, NUM_y },
{  NULL, "8", NUM_x+KEY_ODSTEP*7, NUM_y },
{  NULL, "9", NUM_x+KEY_ODSTEP*8, NUM_y },
{  NULL, "0", NUM_x+KEY_ODSTEP*9, NUM_y },



{  NULL, "Q", Q_x+KEY_ODSTEP*0, Q_y },
{  NULL, "W", Q_x+KEY_ODSTEP*1, Q_y },
{  NULL, "E", Q_x+KEY_ODSTEP*2, Q_y },
{  NULL, "R", Q_x+KEY_ODSTEP*3, Q_y },
{  NULL, "T", Q_x+KEY_ODSTEP*4, Q_y },
{  NULL, "Y", Q_x+KEY_ODSTEP*5, Q_y },
{  NULL, "U", Q_x+KEY_ODSTEP*6, Q_y },
{  NULL, "I", Q_x+KEY_ODSTEP*7, Q_y },
{  NULL, "O", Q_x+KEY_ODSTEP*8, Q_y },
{  NULL, "P", Q_x+KEY_ODSTEP*9, Q_y },

{  NULL, "A", A_x+KEY_ODSTEP*0, A_y },
{  NULL, "S", A_x+KEY_ODSTEP*1, A_y },
{  NULL, "D", A_x+KEY_ODSTEP*2, A_y },
{  NULL, "F", A_x+KEY_ODSTEP*3, A_y },
{  NULL, "G", A_x+KEY_ODSTEP*4, A_y },
{  NULL, "H", A_x+KEY_ODSTEP*5, A_y },
{  NULL, "J", A_x+KEY_ODSTEP*6, A_y },
{  NULL, "K", A_x+KEY_ODSTEP*7, A_y },
{  NULL, "L", A_x+KEY_ODSTEP*8, A_y },

{  NULL, "Z", Z_x+KEY_ODSTEP*0, Z_y },
{  NULL, "X", Z_x+KEY_ODSTEP*1, Z_y },
{  NULL, "C", Z_x+KEY_ODSTEP*2, Z_y },
{  NULL, "V", Z_x+KEY_ODSTEP*3, Z_y },
{  NULL, "B", Z_x+KEY_ODSTEP*4, Z_y },
{  NULL, "N", Z_x+KEY_ODSTEP*5, Z_y },
{  NULL, "M", Z_x+KEY_ODSTEP*6, Z_y }


};

Keyboard::Keyboard(QWidget *parent, QLineEdit *textEdit) :
    QWidget(parent)
{
    editText = textEdit;

    QLabel *ramka=new QLabel(this);
    ramka->resize(760, 270); // first argument is width and second is the height.
    ramka->move(NUM_x-20, NUM_y-20);
    ramka->show();
    ramka->setStyleSheet(" \
                         background-color: rgba(230,230,230,200); \
                         border-radius: 6px; \
                         border: 3px solid #FFFFFF; \
                         ");

    QString buttonStyleSheet;
    buttonStyleSheet = buttonStyleSheet.sprintf(" \
                                     color: white;\
                                     background-color: rgba(230,230,230,200); \
                                     font-size: 24px; \
                                     border-radius: 6px; \
                                     border: 2px solid #FFFFFF; \
                                     ");

    for (int i =0;i<36;i++)
    {
        onScreenKeyboard[i].ptr = new QPushButton(onScreenKeyboard[i].txt, this);
        onScreenKeyboard[i].ptr->move(onScreenKeyboard[i].pos_x, onScreenKeyboard[i].pos_y);
        onScreenKeyboard[i].ptr->resize(50,50);
        onScreenKeyboard[i].ptr->setStyleSheet(buttonStyleSheet);
        onScreenKeyboard[i].ptr->setFocusPolicy(Qt::NoFocus);
        connect(onScreenKeyboard[i].ptr, SIGNAL(clicked()),this, SLOT(button_clicked()));
    }

    QPushButton *button_enter = new QPushButton("ENTER",this);
    button_enter->resize(120, 50); // first argument is width and second is the height.
    button_enter->move(A_x+KEY_ODSTEP*9,A_y);
    button_enter->show();
    button_enter->setStyleSheet(buttonStyleSheet);
    button_enter->setFocusPolicy(Qt::NoFocus);
    connect(button_enter, SIGNAL(clicked()),this, SLOT(button_clicked()));

    QPushButton *button_backspace = new QPushButton("BACK",this);
    connect(button_backspace, SIGNAL(clicked()),this, SLOT(button_clicked()));
    button_backspace->resize(120, 50); // first argument is width and second is the height.
    button_backspace->move( NUM_x+KEY_ODSTEP*10,NUM_y);
    button_backspace->show();
    button_backspace->setStyleSheet(buttonStyleSheet);
    button_backspace->setFocusPolicy(Qt::NoFocus);

}

void Keyboard::button_clicked()
{
    QPushButton *nadawca = (QPushButton*)sender();

    for(int i=0;i<36;i++)
    {
        if(nadawca->text() == onScreenKeyboard[i].txt)       editText->insert(onScreenKeyboard[i].txt);
    }

    if(nadawca->text() == "BACK") editText->backspace();

    if(nadawca->text() == "ENTER") ((Setup*)parentWidget())->HideKeyboard();

   // repaint();
}
