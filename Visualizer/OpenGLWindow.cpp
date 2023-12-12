#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>

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
    drawGrid(vertices, colors, gridSize);
    
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


    bresenhamLinePixels(v1, v2, v3, v4, squareVertices);
    //SymmetricDDA(v1, v2, v3, v4, squareVertices);
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
    
    // Prepare the data for rendering
    GLfloat* verticesData = vertices.data();
    GLfloat* colorsData = colors.data();

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size()/2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}

void OpenGLWindow::drawGrid(QVector<GLfloat>& vertices, QVector<GLfloat>& colors, float gridSize)
{
    //const float gridSize = 8.0f;  // Adjust the grid size as needed
    const float step = 1.0f;

    // Draw horizontal grid lines
    for (float y = -gridSize / 2.0f; y <= gridSize / 2.0f; y += step)
    {
        vertices << -gridSize / 2.0f << y;
        vertices << gridSize / 2.0f << y;

        colors << 1.0f << 1.0f << 1.0f;
        colors << 1.0f << 1.0f << 1.0f;
    }

    // Draw vertical grid lines
    for (float x = -gridSize / 2.0f; x <= gridSize / 2.0f; x += step)
    {
        vertices << x << -gridSize / 2.0f;
        vertices << x << gridSize / 2.0f;

        colors << 1.0f << 1.0f << 1.0f;
        colors << 1.0f << 1.0f << 1.0f;
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

void OpenGLWindow::bresenhamLinePixels(float x1, float y1, float x2, float y2, QVector<QVector2D>& pixelVertices)
{
    // Bresenham's line drawing algorithm
    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);
    float sx = (x1 < x2) ? 1.0f : -1.0f;
    float sy = (y1 < y2) ? 1.0f : -1.0f;
    float err = dx - dy;

   while (x1 < x2 || y1 < y2) {
        pixelVertices.append(QVector2D(round(x1), round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1) + 1));
        pixelVertices.append(QVector2D(round(x1), round(y1) + 1));

        float e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
            x1 = round(x1);
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
            y1 = round(y1);
        }
    } 
}

void OpenGLWindow::SymmetricDDA(float x1, float y1, float x2, float y2, QVector<QVector2D>& pixelVertices)
{
    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);
    float deltaX;
    float deltaY;
    if (dy > dx)
    {
        deltaX = dx / dy;
        deltaY = dy / dy;
    }
    else
    {
        deltaX = dx / dx;
        deltaY = dy / dx;
    }
    while (x1 < x2)
    {
        pixelVertices.append(QVector2D(round(x1), round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1) + 1));
        pixelVertices.append(QVector2D(round(x1), round(y1) + 1));
        x1 = deltaX + x1;
        y1 = deltaY + y1;
    }
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
    // Get a multi-line text input from the user
    QString inputText = QInputDialog::getMultiLineText(this, "User Input", "Enter gridSize (integer):", "", &ok);
    if (ok) {
        // Parse the input string into 4 float values        
         bool conversionOk;
         gridSize = inputText.toInt(&conversionOk);
         if (!conversionOk) {
               return;
         }
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
//
//void OpenGLWindow::createGeometry()
//{
//   /* mVertices.clear();
//    mNormals.clear();
//
//    mVertices << QVector3D(0.0f, 0.707f, -0.05f);
//    mVertices << QVector3D(-0.5f, -0.5f, -0.05f);
//    mVertices << QVector3D(0.5f, -0.5f, -0.05f);
//    */
//}
