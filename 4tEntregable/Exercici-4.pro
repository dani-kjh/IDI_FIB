TEMPLATE    = app
QT         += opengl

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += ./Model

FORMS += MyForm.ui

HEADERS += MyForm.h Ll4GLWidget.h MyGLWidget.h

SOURCES += main.cpp  MyForm.cpp \
        LL4GLWidget.cpp MyGLWidget.cpp ./Model/model.cpp
