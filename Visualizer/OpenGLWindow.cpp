#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include "Grid.h"
#include "Bresenhams.h"
#include "SymmetricDDA.h"

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) : 
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(900, 550);
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

    // We are done with the current QOpenGLContext, forget it. If there is a
    // subsequent initialize(), that will then connect to the new context.
    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{
    QPushButton* inputButton = new QPushButton("Get User Input", this);
    inputButton->setGeometry(QRect(QPoint(50, 25), QSize(150, 50)));
    connect(inputButton, &QPushButton::released, this, &OpenGLWindow::getUserInput);
    
    QPushButton* gridButton = new QPushButton("Enter Grid Size", this);
    gridButton->setGeometry(QRect(QPoint(250, 25), QSize(150, 50)));
    connect(gridButton, &QPushButton::released, this, &OpenGLWindow::getGridInput);

    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(-3.0f-(gridSize/2), 3.0f+(gridSize/2), -3.0f- (gridSize / 2), 3.0f+ (gridSize / 2), 0.1f, 100.0f);  // Adjust the orthographic projection
    matrix.translate(0, 0, -2);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;

    // Draw the grid
    Grid grid(vertices, colors, gridSize);

    
    float v1 = mFloatInputs[0];
    float v2 = mFloatInputs[1];
    float v3 = mFloatInputs[2];
    float v4 = mFloatInputs[3];
    
    
    vertices << v1 << v2;
    vertices << v3 << v4;
    //vertices << -2.75 << -2.75;
    //vertices << 2.5 << 1.5;

    colors << 1.0f << 0.0f << 0.0f;
    colors << 1.0f << 0.0f << 0.0f;
  
    QVector<QVector2D> squareVertices;

    Line l(Point2D(mFloatInputs[0], mFloatInputs[0]), Point2D(mFloatInputs[2], mFloatInputs[3]));
    Bresenhams bresenhamsLineAlgo(l, squareVertices);

    //SymmetricDDA dda(l, squareVertices);

    int i = 0;
    while (i < squareVertices.size()) {
        QVector<QVector2D> qv;
        qv.append(squareVertices[i]);
        i++;
        qv.append(squareVertices[i]);
        i++;
        qv.append(squareVertices[i]);
        i++;
        qv.append(squareVertices[i]);
        i++;
        QVector3D fillColor(1.0f, 1.0f, 0.0f);  // Yellow color
        fillSquare(qv, fillColor);
    }
    

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size()/2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
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



void OpenGLWindow::getUserInput() {
    bool ok;
    // Get a multi-line text input from the user
    QString inputText = QInputDialog::getMultiLineText(this, "User Input", "Enter 4 float values (separated by spaces):", "", &ok);

    if (ok) {
        // Parse the input string into 4 float values
        QStringList inputList = inputText.split(' ');
        if (inputList.size() == 4) {
            bool conversionOk;
            for (int i = 0; i < 4; ++i) {
                mFloatInputs[i] = inputList[i].toFloat(&conversionOk);
                if (!conversionOk) {
                    return;
                }
            }
        }
    }
    
}
void OpenGLWindow::getGridInput() {
    bool ok;
    // Get a single-line integer input from the user
    int n = QInputDialog::getInt(this, "User Input", "Enter gridSize (integer):", 0, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        gridSize = n;
    }
    else {
        return;
    }
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
