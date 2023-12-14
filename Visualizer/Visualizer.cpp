#include "stdafx.h"
#include "Visualize.h"
#include "OpenGLWindow.h"
#include "Line.h"
#include "Grid.h"

//#include "SymmetricDDA.h"
//#include "SutherlandandCohenAlgorithm.h"

Visualize::Visualize(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    connect(mPushButton1, &QPushButton::clicked, this, &Visualize::addGrid);
    connect(mPushButton2, &QPushButton::clicked, this, &Visualize::addLine);
    connect(mPushButton3, &QPushButton::clicked, this, &Visualize::bresenhamsLine);
    connect(mPushButton4, &QPushButton::clicked, this, &Visualize::symmetricDDALine);
    connect(mRenderer, SIGNAL(shapeUpdate()), mRenderer, SLOT(update()));
}

Visualize::~Visualize()
{

}

//Slot for Implimentation of Symmetric DDA

//Implimentation of UI
void Visualize::setupUi() {

    mCentralWidget = new QWidget(this);
    mCentralWidget->setObjectName("centralwidget");

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
