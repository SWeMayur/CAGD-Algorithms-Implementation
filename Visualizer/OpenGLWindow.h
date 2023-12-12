#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Line.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

protected:
    void paintGL() override;
    void initializeGL() override;
private:
   // void createGeometry();
    void reset();
    void drawGrid(QVector<GLfloat>& vertices, QVector<GLfloat>& colors, float gridSize);
    void fillSquare(const QVector<QVector2D>& squareVertices, const QVector3D& fillColor);
    void bresenhamLinePixels(float x1, float y1, float x2, float y2, QVector<QVector2D>& pixelCoordinates);
    void SymmetricDDA(float x1, float y1, float x2, float y2, QVector<QVector2D>& pixelVertices);
private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    float mFloatInputs[4];
    Line *mLine;
    int gridSize = 0;
   // QInputDialog* mInputBox;
public slots:
    void getUserInput();
    void getGridInput();
};
