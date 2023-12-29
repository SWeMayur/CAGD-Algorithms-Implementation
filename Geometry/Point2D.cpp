#include "pch.h"
#include "Point2D.h"

Point2D::Point2D(float inX, float inY) : mX(0), mY(0)
{
    mX = inX;
    mY = inY;
}

Point2D::~Point2D()
{
}

float Point2D::getX() const
{
    return mX;
}

float Point2D::getY() const
{
    return mY;
}



void Point2D::setX(float x)
{
    mX = x;
}

void Point2D::setY(float y)
{
    mY = y;
}
