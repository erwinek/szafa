// glwidg.h
#ifndef GLWIDG_H
#define GLWIDG_H
//#include <Qgl.h>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/qgl.h>
#include <qwidget.h>
#include <qtimer.h>

class GLKwad : public QGLWidget
 {
   Q_OBJECT
public:
  GLKwad( QWidget *parent, const char *name );
  ~GLKwad();
protected:
  void initializeGL();
  void paintGL();
  void resizeGL( int w, int h );
};
#endif
