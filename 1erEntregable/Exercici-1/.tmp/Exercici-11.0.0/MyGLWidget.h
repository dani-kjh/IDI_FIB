#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);

  private:
    void carregaShaders ();
    void creaBuffersLinia ();
    void creaBuffersAgulla ();
    void modelTransformLinia_H ();
    void modelTransformLinia_V ();
    void modelTransformAgulla_M ();
    void modelTransformAgulla_H ();    

    // attribute locations
    GLuint vertexLoc, colorLoc;

    // uniform locations
    GLuint transLoc;
    GLuint pintarcuad;
    // VAO i VBO names
    GLuint VAO_Linia, VAO_Agulla;

    // Program
    QOpenGLShaderProgram *program;

    GLint ample, alt;

    // Internal vars
    glm::vec3 groc, blau, negre;
    float rotacio, rotacio2;
};

