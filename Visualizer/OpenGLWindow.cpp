#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include "Grid.h"
#include "Bresenhams.h"
#include "Line.h"
#include "SymmetricDDA.h"
#include "BazierCurve.h"
#include "HermiteCurve.h"

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) : mBackground(background)
{
    setParent(parent);
    setMinimumSize(720, 550);
    const QStringList list = {"vertexShader.glsl" , "fragmentShader.glsl"};
    mShaderWatcher = new QFileSystemWatcher(list, this);
    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);
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
   // matrix.rotate(rotationAngle);
    mProgram->setUniformValue(m_matrixUniform, matrix);
    std::vector<float> vert;
    std::vector<float> col;
    Grid grid(vert, col, gridSize);

    mProgram->setUniformValue("r", r);
    mProgram->setUniformValue("g", g);
    mProgram->setUniformValue("b", b);
    mProgram->setUniformValue("angle", angle);


    for (int i = 0; i < vert.size(); i++) {
        vertices.append(vert[i]);
    }
    for (int i = 0; i < col.size(); i++) {
        colors.append(col[i]);
    }

    colorSqr(mPixelVertices);

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());


    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size() / 2);

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

QString OpenGLWindow::readShader(QString filePath){
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid file";

    QTextStream stream(&file);
    QString line = stream.readLine();

    while (!stream.atEnd()) {
        line.append(stream.readLine());
    }
    file.close();
    return line;
}

void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");
    
    mProgram->release();
    mProgram->removeAllShaders();
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
}

void OpenGLWindow::initializeGL()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");
    
    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);

    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
  //  Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void OpenGLWindow::selectCurveColor()
{
    QColorDialog colorDialog(this);
    QColor selectedColor = colorDialog.getColor();

    if (selectedColor.isValid()){
        // Set the selected color to the curves or store it for later use
         r = selectedColor.redF();
         g = selectedColor.greenF();
         b = selectedColor.blueF();
        emit shapeUpdate();  // Trigger an update to redraw the curves with the new color
    }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
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
    std::vector<std::vector<float>> mPV;
    Bresenhams b(l, mPV);
    for (std::vector<float> vect1D : mPV)
    {
        QVector2D q;
        q.setX(vect1D[0]);
        q.setY(vect1D[1]);
        mPixelVertices.append(q);
    }
    colorSqr(mPixelVertices);
    emit shapeUpdate();
}

void OpenGLWindow::symmetricDDA(Line l)
{
    mPixelVertices.clear();
    std::vector<std::vector<float>> mPV;
    SymmetricDDA b(l, mPV);
    for (std::vector<float> vect1D : mPV)
    {
        QVector2D q;
        q.setX(vect1D[0]);
        q.setY(vect1D[1]);
        mPixelVertices.append(q);
    }
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

void OpenGLWindow::rotateObject(GLfloat rotationAngle)
{
    angle = rotationAngle;
}
