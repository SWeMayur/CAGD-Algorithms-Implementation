#pragma once

#include <QtWidgets/QMainWindow>
#include "Visualize.h"
#include "OpenGLWindow.h"
//#include "SymmetricDDA.h"

class OpenGLWindow;

class Visualize : public QMainWindow
{
    Q_OBJECT

public:
    Visualize(QWindow* parent = nullptr);
    ~Visualize();

private:
    void setupUi();

public:
    QVector<QVector2D> mPixelVertices;
    QVector<GLfloat>   mVertices;
    QVector<GLfloat>   mColors;

private:
    QWidget* mCentralWidget;
    OpenGLWindow* mRenderer;

    QPushButton* mPushButton1;
    QPushButton* mPushButton2;
    QPushButton* mPushButton3;
    QPushButton* mPushButton4;
   
    QLineEdit* mLineEdit1;
    QLineEdit* mLineEdit2;
    QLineEdit* mLineEdit3;
    QLineEdit* mLineEdit4;
    QLineEdit* mLineEdit5;
   
    QLabel* mLabel1;
    QLabel* mLabel2;
    QLabel* mLabel3;
    QLabel* mLabel4;
    QLabel* mLabel5;

    float xCoordinate;
    float yCoordinate;
    float x1Coordinate;
    float y1Coordinate;
    float xMin;
    float yMin;
    float xMax;
    float yMax;

public slots:
    void addLine();
    void addGrid();
    void bresenhamsLine();
    void symmetricDDALine();
};
