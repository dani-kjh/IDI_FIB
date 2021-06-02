// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}
void MyGLWidget::paintGL () 
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el terra 
  glBindVertexArray (VAO_Terra);

  Ll4GLWidget::modelTransformTerra ();

  // pintem
  glDrawArrays(GL_TRIANGLES, 0, 12);

  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patr);

  modelTransformPatricio ();

  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  
  glBindVertexArray(0);
}

void MyGLWidget::initializeGL(){
  
  

  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  MyGLWidget::carregaShaders();
  Ll4GLWidget::creaBuffersPatricio();
  Ll4GLWidget::creaBuffersTerraIParet();
  iniParams();
  iniFoco();
  Ll4GLWidget::iniEscena();
  Ll4GLWidget::iniCamera();
}

void MyGLWidget::modelTransformPatricio(){
  TG = glm::mat4(1.f);
  TG = glm::translate(TG, posiPatricio);
  TG = glm::rotate(TG, rotaPatri, glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  TG = glm::translate(TG, -centreBasePatr);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);

}
void MyGLWidget::iniFoco(){
  posicionFoco = glm::vec3(5.0, 3.0, 2.0);
  glUniform3fv(posFocoSecu,1 ,&posicionFoco[0]);
  colorFoco = glm::vec3(0.5,1.0,0);
  glUniform3fv(colFocoSecu, 1, &colorFoco[0]);
  tipoFoco = true;
  glUniform1i(tipoFocus, tipoFoco);
}
void MyGLWidget::iniParams(){
  posiPatricio = glm::vec3(5,0,2);
  angle = 270.0;
  rotaPatri =  0.0;
  centreCircu = glm::vec3(5,0,5);
  radi = 3;

}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_F: {
      tipoFoco = !tipoFoco;
      glUniform1i(tipoFocus, tipoFoco);
    break;
	}
  case Qt::Key_Right: {
      angle += 30.0f;
      rotaPatri -= 0.5f;
      if(rotaPatri < -5.5f)
      rotaPatri = 0.0f;
      calculPosiPatricio();
    break;
	}
  case Qt::Key_Left: {
      angle -= 30.0f;
      rotaPatri += 0.5f;
      if(rotaPatri > 5.5f)
      rotaPatri = 0.0f;
      calculPosiPatricio();
    break;
	}
  default: Ll4GLWidget::keyPressEvent(event); break;
  }
  update();
}


void MyGLWidget::calculPosiPatricio(){
  float incX = posiPatricio.x;
  float incZ = posiPatricio.z;

  posiPatricio.x = centreCircu.x + radi*glm::cos(glm::radians(angle));
  posiPatricio.z = centreCircu.z + radi*glm::sin(glm::radians(angle));

  incX = posiPatricio.x - incX;
  incZ = posiPatricio.z - incZ;

  posicionFoco.x += incX;
  posicionFoco.z += incZ;
  glUniform3fv(posFocoSecu,1 ,&posicionFoco[0]);

}

void MyGLWidget::carregaShaders(){
  Ll4GLWidget::carregaShaders();
    posFocoSecu = glGetUniformLocation(program->programId(), "posFSecu");
    colFocoSecu = glGetUniformLocation(program->programId(), "colFSecu");
    tipoFocus = glGetUniformLocation(program->programId(), "tipoFoco");
}

void MyGLWidget::canviaFocus(){
  makeCurrent();
  tipoFoco = !tipoFoco;
  glUniform1i(tipoFocus, tipoFoco);
  update();

}