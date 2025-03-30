// glwidg.cpp
#include "glwidg.h"
GLfloat r;
QTimer *Timer;

GLKwad::GLKwad( QWidget *parent, const char *name )
            : QGLWidget(parent, name)
{
    r = 0.0;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initializeGL();
    Timer = new QTimer( this, "Timer" );
    connect( Timer, SIGNAL( timeout() ), SLOT( updateGL() ) );
    Timer->start(10);
}

GLKwad::~GLKwad()
{
}

void GLKwad::initializeGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
}


void GLKwad::resizeGL( int w, int h )
{
  glViewport( 0, 0, (GLint)w, (GLint)h );
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
}

void GLKwad::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  glRotatef( r,  1.0,  1.0,  1.0 );  // kazdy 1 odpowiada za jedna skale
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
  glEnd();
  glFlush();
  r -= 0.15;
}
