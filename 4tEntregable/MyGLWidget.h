// MyGLWidget.h
#include "Ll4GLWidget.h"

class MyGLWidget : public Ll4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : Ll4GLWidget(parent) {}
    ~MyGLWidget();
    public slots:
    void canviaFocus();
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);

    virtual void initializeGL();
    virtual void iniParams();
    virtual void paintGL();
    virtual void modelTransformPatricio();
    virtual void calculPosiPatricio();
    virtual void carregaShaders();
    virtual void iniFoco();

    glm::vec3 posiPatricio;
    float angle;
    float rotaPatri;
    glm::vec3 centreCircu;
    int radi;

    GLuint posFocoSecu, colFocoSecu, tipoFocus;
    glm::vec3 posicionFoco;
    glm::vec3 colorFoco;
    bool tipoFoco;



  private:
    int printOglError(const char file[], int line, const char func[]);
};
