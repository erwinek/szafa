#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QtGui>

class Keyboard : public QWidget
{
    Q_OBJECT
public:
    explicit Keyboard(QWidget *parent = 0, QLineEdit *textEdit = 0);

    struct keyboardStruct
    {
        QPushButton *ptr;
        QString txt;
        int pos_x;
        int pos_y;
    };
    QLineEdit *editText;
private:
signals:
    
private slots:
    void button_clicked();
    
};

#endif // KEYBOARD_H
