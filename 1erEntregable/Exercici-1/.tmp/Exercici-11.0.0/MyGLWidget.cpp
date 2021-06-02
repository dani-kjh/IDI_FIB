#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)

  negre = glm::vec3(0.0, 0.0, 0.0);
  groc  = glm::vec3(1.0, 1.0, 0.0);
  blau  = glm::vec3(0.0, 0.0, 1.0);

  carregaShaders();
  creaBuffersLinia();
  creaBuffersAgulla();
}

void MyGLWidget::paintGL () 
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#endif

// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer
  float pintar = 0.0;
  glUniform1f(pintarcuad, pintar);

  // Dibuix linia horitzontal
  modelTransformLinia_H ();
  glBindVertexArray (VAO_Linia);
  glDrawArrays(GL_TRIANGLES, 0, 6);

// Dibuix linia vertical 
  modelTransformLinia_V ();
  glBindVertexArray(VAO_Linia);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  // Dibuix agulla dels minuts
  modelTransformAgulla_M ();
  glBindVertexArray (VAO_Agulla);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  // Dibuix agulla de les hores
  modelTransformAgulla_H ();
  glBindVertexArray (VAO_Agulla);
  pintar = 1.0;
  glUniform1f(pintarcuad, pintar);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray (0);
}


void MyGLWidget::modelTransformLinia_H () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformAgulla_M() 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  //  transform = glm::scale(transform, glm::vec3(1.0, 1.0, 1.0));
  transform = glm::rotate(transform, rotacio, glm::vec3(0.0,0.0,-1.0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformLinia_V () 
{
  // Codi per a la TG necessària
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, float(M_PI/2) ,glm::vec3(0.0, 0.0, 1.0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}




void MyGLWidget::modelTransformAgulla_H() 
{
  // Codi per a la TG necessària
    // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::rotate(transform, rotacio2, glm::vec3(0.0,0.0,-1.0));
  transform = glm::scale(transform, glm::vec3(1.0, 0.6 , 1.0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  ample = w;
  alt = h;
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_M: {
      rotacio +=  float(M_PI/30);
      if(rotacio >= float(2*M_PI) ){
        rotacio = M_PI/30;
        rotacio2 += float(M_PI/6);
      }
        
      break;
      // tractament de la interacció

    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffersLinia () 
{
  // Vèrtexs de línia horitzontal i centrada a l'origen 
  glm::vec3 caixa[6] = {
    glm::vec3( 0.5, -0.005, 0.0),
    glm::vec3( 0.5,  0.005, 0.0),
    glm::vec3(-0.5, -0.005, 0.0),
    glm::vec3( 0.5,  0.005, 0.0),
    glm::vec3(-0.5,  0.005, 0.0),
    glm::vec3(-0.5, -0.005, 0.0)
  };

  glm::vec3 caixaColor[6] = {
    negre, negre, negre, negre, negre, negre
  };
    
  // Creació del VAO
  glGenVertexArrays(1, &VAO_Linia);
  glBindVertexArray(VAO_Linia);

  // Creació dels Buffers
  GLuint VBO_Linia[2];
  glGenBuffers(2, &VBO_Linia[0]);

  // Buffer de geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Linia[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(caixa), caixa, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Linia[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(caixaColor), caixaColor, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersAgulla () 
{
  // Vèrtexs de l'agulla
  glm::vec3 agulla[6] = {
    glm::vec3( 0.0,  0.0, 0.0),
    glm::vec3( 0.02, 0.1, 0.0),
    glm::vec3(-0.02, 0.1, 0.0),
    glm::vec3( 0.02, 0.1, 0.0),
    glm::vec3( 0.0,  0.4, 0.0),
    glm::vec3(-0.02, 0.1, 0.0)    
  }; 

  glm::vec3 agullaColor[6] = {
    groc, groc, groc, groc, groc, groc
  };

  // Creació del VAO
  glGenVertexArrays(1, &VAO_Agulla);
  glBindVertexArray(VAO_Agulla);
  
  // Creació dels Buffers
  GLuint VBO_Agulla[2];
  glGenBuffers(2, &VBO_Agulla[0]);

  // Buffer de geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Agulla[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(agulla), agulla, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Agulla[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(agullaColor), agullaColor, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li fegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Identificadors pels atributs
  vertexLoc = glGetAttribLocation(program->programId(), "vertex");
  colorLoc  = glGetAttribLocation(program->programId(), "color");
  
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  pintarcuad = glGetUniformLocation(program->programId(), "pintar");

}

