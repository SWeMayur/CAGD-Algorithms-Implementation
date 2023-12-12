#pragma once
class Point2D
{
public:
    Point2D(double inX, double inY);
    ~Point2D();

    double x();
    double y();

    void setX(double x);
    void setY(double y);

private:
    double mX;
    double mY;
};