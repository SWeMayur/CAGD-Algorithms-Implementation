#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include "Grid.h"
#include "Bresenhams.h"
#include "SymmetricDDA.h"
#include "BazierCurve.h"
#include "HermiteCurve.h"

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent):
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(720, 550);
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    // And now release all OpenGL resources.
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(-3.0f - (gridSize / 2), 3.0f + (gridSize / 2), -3.0f - (gridSize / 2), 3.0f + (gridSize / 2), 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    Grid grid(vertices, colors, gridSize);
    colorSqr(mPixelVertices);


    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, curveVertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, curveColors.data());


    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, curveVertices.size() / 2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}

void OpenGLWindow::colorSqr(QVector<QVector2D>& pixels)
{
    int i = 0;
    while (i < pixels.size()) {
        QVector<QVector2D> qv;
        qv.append(pixels[i]);
        i++;
        qv.append(pixels[i]);
        i++;
        qv.append(pixels[i]);
        i++;
        qv.append(pixels[i]);
        i++;
        QVector3D fillColor(1.0f, 1.0f, 0.0f);
        fillSquare(qv, fillColor);
    }
}

void OpenGLWindow::fillSquare(const QVector<QVector2D>& squareVertices, const QVector3D& fillColor)
{

    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;

    // Convert QVector<QVector2D> to QVector<GLfloat>
    for (const auto& vertex : squareVertices)
    {
        vertices << vertex.x();
        vertices << vertex.y();
        colors << fillColor.x() << fillColor.y() << fillColor.z();
    }

    // Prepare the data for rendering
    GLfloat* verticesData = vertices.data();
    GLfloat* colorsData = colors.data();

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}

void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void OpenGLWindow::addLine(Line l)
{

    vertices.push_back(l.getP1().x());
    vertices.push_back(l.getP1().y());
    vertices.push_back(l.getP2().x());
    vertices.push_back(l.getP2().y());

    colors << 1.0f << 0.0f << 0.0f;
    colors << 1.0f << 0.0f << 0.0f;

    emit shapeUpdate();
}

void OpenGLWindow::addGrid(int size)
{
    gridSize = size;
    emit shapeUpdate();
}

void OpenGLWindow::bresenhams(Line l)
{
    mPixelVertices.clear();
    Bresenhams b(l, mPixelVertices);
    colorSqr(mPixelVertices);
    emit shapeUpdate();
}

void OpenGLWindow::symmetricDDA(Line l)
{
    mPixelVertices.clear();
    SymmetricDDA s(l, mPixelVertices);
    colorSqr(mPixelVertices);
    emit shapeUpdate();
}

void OpenGLWindow::bazierCurve(std::vector<Point2D> v)
{

    curveColors.clear();
    curveVertices.clear();
    BezierCurve baz(v, baC);
    float maxSize = 0;
    for (int i = 0; i < v.size(); i++) {
        gridSize = std::max(maxSize, std::max(v[i].x(), v[i].y()));
    }
    gridSize *= 2;
    for (int i = 0; i < baC.size() / 2; i++) {
        curveColors << 1.0f << 0.0f << 0.0f;
    }
    for (int i = 0; i < baC.size(); i++) {
        curveVertices.push_back(baC[i]);
    }
    emit shapeUpdate();
}

void OpenGLWindow::hermiteCurve(std::vector<Point2D> v)
{
    curveColors.clear();
    curveVertices.clear();
    HermiteCurve her(v, heC);
    float maxSize = 0;
    for (int i = 0; i < v.size(); i++) {
        gridSize = std::max(maxSize, std::max(v[i].x(), v[i].y()));
    }
    gridSize *= 2;
    for (int i = 0; i < heC.size()/2; i++) {
        curveColors << 1.0f << 1.0f << 0.0f;
    }
    for (int i = 0; i < heC.size(); i++) {
        curveVertices.push_back(heC[i]);
    }
    emit shapeUpdate();
}
