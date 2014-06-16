// =====================================================================================
// 
//       Filename:  viewport.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/14/2014 04:15:14 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "viewport.hpp"

// this is the grid 
GLfloat gridpoints[2][2][3] = {
    {
        {2,0,2}, // top right
        {2,0,-2} // bottom right
    },
    {
        {-2,0,2}, // top left
        {-2,0,-2} // bottom left
    }
};

float graphres = 200.0;

    Viewport::Viewport()
    : m_program(0)
    , m_t(0)
      , m_thread_t(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void Viewport::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void Viewport::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        // Connect the beforeRendering signal to our paint function.
        // Since this call is executed on the rendering thread it must be
        // a Qt::DirectConnection
        connect(win, SIGNAL(beforeRendering()), this, SLOT(paint()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);

        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}

void Viewport::paint()
{
    if (!m_program) {
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                "attribute highp vec4 vertex;\n"
                "attribute mediump vec3 normal;\n"
                "uniform mediump mat4 matrix;\n"
                "varying mediump vec4 color;\n"
                "void main(void)\n"
                "{\n"
                " vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
                " float angle = max(dot(normal, toLight), 0.0);\n"
                " vec3 col = vec3(0.40, 1.0, 0.0);\n"
                " color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
                " color = clamp(color, 0.0, 1.0);\n"
                " gl_Position = matrix * vertex;\n"
                "}\n"
                );
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                "varying mediump vec4 color;\n"
                "void main(void)\n"
                "{\n"
                " gl_FragColor = color;\n"
                "}\n"
                );

        m_program->bindAttributeLocation("vertices", 0);
        m_program->link();

        connect(window()->openglContext(), SIGNAL(aboutToBeDestroyed()),
                this, SLOT(cleanup()), Qt::DirectConnection);
    }
    m_program->bind();

    m_program->enableAttributeArray(0);

    float values[] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
    };
    m_program->setAttributeArray(0, GL_FLOAT, values, 2);
    m_program->setUniformValue("t", (float) m_thread_t);

    qreal ratio = window()->devicePixelRatio();
    int w = int(ratio * window()->width());
    int h = int(ratio * window()->height());
    glViewport(0, 0, w, h);

    glDisable(GL_DEPTH_TEST);

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->disableAttributeArray(0);
    m_program->release();
}

void Viewport::cleanup()
{
    if (m_program) {
        delete m_program;
        m_program = 0;
    }
}

void Viewport::sync()
{
    m_thread_t = m_t;
}
