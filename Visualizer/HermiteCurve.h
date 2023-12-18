#pragma once
#include "Point2D.h"
#include<vector>

class HermiteCurve
{
public:
	HermiteCurve(std::vector<Point2D> points, QVector<GLfloat> &curvePoints);
	~HermiteCurve();
	
private:
	void calculateHermite(QVector<GLfloat>& curvePoints);
	Point2D evaluateHermite(double t);
private:
	std::vector<Point2D> mControlPoints;
}; 