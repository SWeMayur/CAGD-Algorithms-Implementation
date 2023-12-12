#include "stdafx.h"
#include "Point2D.h"

Point2D::Point2D(double inX, double inY)
    : mX(0),
    mY(0)
{
    mX = inX;
    mY = inY;
}

Point2D::~Point2D()
{
}

double Point2D::x()
{
    return mX;
}

double Point2D::y()
{
    return mY;
}



void Point2D::setX(double x)
{
    mX = x;
}

void Point2D::setY(double y)
{
    mY = y;
}
