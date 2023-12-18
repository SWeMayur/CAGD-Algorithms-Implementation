#include "stdafx.h"
#include "Visualize.h"
#include "OpenGLWindow.h"
#include "Line.h"
#include "Grid.h"
#include "vector"


Visualize::Visualize(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    connect(mPushButton1, &QPushButton::clicked, this, &Visualize::addGrid);
    connect(mPushButton2, &QPushButton::clicked, this, &Visualize::addLine);
    connect(mPushButton3, &QPushButton::clicked, this, &Visualize::bresenhamsLine);
    connect(mPushButton4, &QPushButton::clicked, this, &Visualize::symmetricDDALine);
    connect(mPushButton5, &QPushButton::clicked, this, &Visualize::bazier);
    connect(mPushButton6, &QPushButton::clicked, this, &Visualize::hermite);
    connect(mRenderer, SIGNAL(shapeUpdate()), mRenderer, SLOT(update()));
}

Visualize::~Visualize()
{

}


//Implimentation of UI
void Visualize::setupUi() {
    resize(1530, 785);
    mLabel1 = new QLabel(this);
    mLabel1->setObjectName("label");
    mLabel1->setText("Grid Size");
    mLabel1->setGeometry(QRect(160, 0, 85, 20));

    mLineEdit1 = new QLineEdit(this);
    mLineEdit1->setObjectName("lineEdit_6");
    mLineEdit1->setGeometry(QRect(140, 25, 85, 20));

    mPushButton1 = new QPushButton(this);
    mPushButton1->setObjectName("pushButton");
    mPushButton1->setText("Draw Grid");
    mPushButton1->setGeometry(QRect(240, 0, 85, 50));


    mLabel2 = new QLabel(this);
    mLabel2->setObjectName("label");
    mLabel2->setText("X1");
    mLabel2->setGeometry(QRect(505, 0, 85, 20));

    mLineEdit2 = new QLineEdit(this);
    mLineEdit2->setObjectName("lineEdit_6");
    mLineEdit2->setGeometry(QRect(470, 25, 85, 20));

    mLabel3 = new QLabel(this);
    mLabel3->setObjectName("label");
    mLabel3->setText("Y1");
    mLabel3->setGeometry(QRect(605, 0, 85, 20));

    mLineEdit3 = new QLineEdit(this);
    mLineEdit3->setObjectName("lineEdit_6");
    mLineEdit3->setGeometry(QRect(570, 25, 85, 20));

    mLabel4 = new QLabel(this);
    mLabel4->setObjectName("label");
    mLabel4->setText("X2");
    mLabel4->setGeometry(QRect(705, 0, 85, 20));

    mLineEdit4 = new QLineEdit(this);
    mLineEdit4->setObjectName("lineEdit_6");
    mLineEdit4->setGeometry(QRect(670, 25, 85, 20));

    mLabel5 = new QLabel(this);
    mLabel5->setObjectName("label");
    mLabel5->setText("Y2");
    mLabel5->setGeometry(QRect(805, 0, 85, 20));

    mLineEdit5 = new QLineEdit(this);
    mLineEdit5->setObjectName("lineEdit_6");
    mLineEdit5->setGeometry(QRect(770, 25, 85, 20));

    mPushButton2 = new QPushButton(this);
    mPushButton2->setObjectName("pushButton");
    mPushButton2->setText("Draw Line");
    mPushButton2->setGeometry(QRect(870, 0, 85, 50));

    mPushButton3 = new QPushButton(this);
    mPushButton3->setObjectName("pushButton");
    mPushButton3->setText("Draw Line (Bresenhams)");
    mPushButton3->setGeometry(QRect(140, 80, 200, 30));

    mPushButton4 = new QPushButton(this);
    mPushButton4->setObjectName("pushButton");
    mPushButton4->setText("Draw Line (Symmetric DDA)");
    mPushButton4->setGeometry(QRect(870, 80, 200, 30));
    
    mPushButton5 = new QPushButton(this);
    mPushButton5->setObjectName("pushButton");
    mPushButton5->setText("Bazier Curve");
    mPushButton5->setGeometry(QRect(1100, 80, 200, 30));

    mPushButton6 = new QPushButton(this);
    mPushButton6->setObjectName("pushButton");
    mPushButton6->setText("Hermite Curve");
    mPushButton6->setGeometry(QRect(1330, 80, 200, 30));

    mLabel6 = new QLabel(this);
    mLabel6->setObjectName("label");
    mLabel6->setText("X1");
    mLabel6->setGeometry(QRect(1130, 170, 85, 30));

    mLineEdit6 = new QLineEdit(this);
    mLineEdit6->setObjectName("lineEdit_7");
    mLineEdit6->setGeometry(QRect(1100, 200, 85, 30));
    
    mLabel7 = new QLabel(this);
    mLabel7->setObjectName("label");
    mLabel7->setText("Y1");
    mLabel7->setGeometry(QRect(1230, 170, 85, 30));

    mLineEdit7 = new QLineEdit(this);
    mLineEdit7->setObjectName("lineEdit_8");
    mLineEdit7->setGeometry(QRect(1200, 200, 85, 30));

    mLabel8 = new QLabel(this);
    mLabel8->setObjectName("label");
    mLabel8->setText("X2");
    mLabel8->setGeometry(QRect(1130, 270, 85, 30));

    mLineEdit8 = new QLineEdit(this);
    mLineEdit8->setObjectName("lineEdit_9");
    mLineEdit8->setGeometry(QRect(1100, 300, 85, 30));
    
    mLabel9 = new QLabel(this);
    mLabel9->setObjectName("label");
    mLabel9->setText("Y2");
    mLabel9->setGeometry(QRect(1230, 270, 85, 30));

    mLineEdit9 = new QLineEdit(this);
    mLineEdit9->setObjectName("lineEdit_10");
    mLineEdit9->setGeometry(QRect(1200, 300, 85, 30));

    mLabel10 = new QLabel(this);
    mLabel10->setObjectName("label");
    mLabel10->setText("X3");
    mLabel10->setGeometry(QRect(1130, 370, 85, 30));

    mLineEdit10 = new QLineEdit(this);
    mLineEdit10->setObjectName("lineEdit_11");
    mLineEdit10->setGeometry(QRect(1100, 400, 85, 30));
    
    mLabel11 = new QLabel(this);
    mLabel11->setObjectName("label");
    mLabel11->setText("Y3");
    mLabel11->setGeometry(QRect(1230, 370, 85, 30));

    mLineEdit11 = new QLineEdit(this);
    mLineEdit11->setObjectName("lineEdit_12");
    mLineEdit11->setGeometry(QRect(1200, 400, 85, 30)); 

    mLabel12 = new QLabel(this);
    mLabel12->setObjectName("label");
    mLabel12->setText("X4");
    mLabel12->setGeometry(QRect(1130, 470, 85, 30));

    mLineEdit12 = new QLineEdit(this);
    mLineEdit12->setObjectName("lineEdit_13");
    mLineEdit12->setGeometry(QRect(1100, 500, 85, 30));

    mLabel13 = new QLabel(this);
    mLabel13->setObjectName("label");
    mLabel13->setText("Y4");
    mLabel13->setGeometry(QRect(1230, 470, 85, 30));

    mLineEdit13 = new QLineEdit(this);
    mLineEdit13->setObjectName("lineEdit_13");
    mLineEdit13->setGeometry(QRect(1200, 500, 85, 30));



    

    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mRenderer->setGeometry(QRect(90, 140, 1000, 600));

    setWindowTitle(QCoreApplication::translate("Bresenham's and Symmetric DDA", "Bresenham's and Symmetric DDA", nullptr));

}

void Visualize::addLine()
{
    float x1 = mLineEdit2->text().toFloat();
    float y1 = mLineEdit3->text().toFloat();
    float x2 = mLineEdit4->text().toFloat();
    float y2 = mLineEdit5->text().toFloat();

    Line l(Point2D(x1, y1), Point2D(x2, y2));

    mRenderer->addLine(l);
}

void Visualize::addGrid()
{
    int gridSize = mLineEdit1->text().toInt();
    mRenderer->addGrid(gridSize);
}

void Visualize::bresenhamsLine()
{
    float x1 = mLineEdit2->text().toFloat();
    float y1 = mLineEdit3->text().toFloat();
    float x2 = mLineEdit4->text().toFloat();
    float y2 = mLineEdit5->text().toFloat();

    Line l(Point2D(x1, y1), Point2D(x2, y2));
    mRenderer->bresenhams(l);
}
void Visualize::symmetricDDALine()
{
    float x1 = mLineEdit2->text().toFloat();
    float y1 = mLineEdit3->text().toFloat();
    float x2 = mLineEdit4->text().toFloat();
    float y2 = mLineEdit5->text().toFloat();

    Line l(Point2D(x1, y1), Point2D(x2, y2));

    mRenderer->symmetricDDA(l);
}

void Visualize::bazier() {
    float x1 = mLineEdit6->text().toFloat();
    float y1 = mLineEdit7->text().toFloat();
    float x2 = mLineEdit8->text().toFloat();
    float y2 = mLineEdit9->text().toFloat();
    float x3 = mLineEdit10->text().toFloat();
    float y3 = mLineEdit11->text().toFloat();
    float x4 = mLineEdit12->text().toFloat();
    float y4 = mLineEdit13->text().toFloat();

    std::vector<Point2D> v;
    v.push_back(Point2D(x1, y1));
    v.push_back(Point2D(x2, y2));
    v.push_back(Point2D(x3, y3));
    v.push_back(Point2D(x4, y4));
    
    mRenderer->bazierCurve(v);
}

void Visualize::hermite() {
    float x1 = mLineEdit6->text().toFloat();
    float y1 = mLineEdit7->text().toFloat();
    float x2 = mLineEdit8->text().toFloat();
    float y2 = mLineEdit9->text().toFloat();
    float x3 = mLineEdit10->text().toFloat();
    float y3 = mLineEdit11->text().toFloat();
    float x4 = mLineEdit12->text().toFloat();
    float y4 = mLineEdit13->text().toFloat();

    std::vector<Point2D> v;
    v.push_back(Point2D(x1, y1));
    v.push_back(Point2D(x2, y2));
    v.push_back(Point2D(x3, y3));
    v.push_back(Point2D(x4, y4));
    
    mRenderer->hermiteCurve(v);
}
