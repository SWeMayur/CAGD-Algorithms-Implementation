#pragma once

#include <QtWidgets/QMainWindow>
#include "Visualize.h"
#include "OpenGLWindow.h"

class OpenGLWindow;

class Visualize : public QMainWindow
{
    Q_OBJECT

public:
    Visualize(QWindow* parent = nullptr);
    ~Visualize();

public slots:
    void addLine();
    void addGrid();
    void bresenhamsLine();
    void symmetricDDALine();
    void bazier();
    void hermite();
    void rotationAngle();


public:
    QVector<QVector2D> mPixelVertices;
    QVector<GLfloat>   mVertices;
    QVector<GLfloat>   mColors;


private:
    void setupUi();

private:
    OpenGLWindow* mRenderer;

    QPushButton* mPushButton1;
    QPushButton* mPushButton2;
    QPushButton* mPushButton3;
    QPushButton* mPushButton4;
    QPushButton* mPushButton5;
    QPushButton* mPushButton6;
    QPushButton* mColorSelector;
    QPushButton* mRotationAngle;
   
    QLineEdit* mLineEdit1;
    QLineEdit* mLineEdit2;
    QLineEdit* mLineEdit3;
    QLineEdit* mLineEdit4;
    QLineEdit* mLineEdit5;
    QLineEdit* mLineEdit6;
    QLineEdit* mLineEdit7;
    QLineEdit* mLineEdit8;
    QLineEdit* mLineEdit9;
    QLineEdit* mLineEdit10;
    QLineEdit* mLineEdit11;
    QLineEdit* mLineEdit12;
    QLineEdit* mLineEdit13;
    QLineEdit* mAngleInput;
   
    QLabel* mLabel1;
    QLabel* mLabel2;
    QLabel* mLabel3;
    QLabel* mLabel4;
    QLabel* mLabel5;
    QLabel* mLabel6;
    QLabel* mLabel7;
    QLabel* mLabel8;
    QLabel* mLabel9;
    QLabel* mLabel10;
    QLabel* mLabel11;
    QLabel* mLabel12;
    QLabel* mLabel13;
    QLabel* mAngleInputLabel;


};