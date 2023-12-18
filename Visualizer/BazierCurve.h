#pragma once
#include "Point2D.h"
#include<vector>

class BezierCurve
{
public:
	BezierCurve(std::vector<Point2D> points, QVector<GLfloat> &curvePoints);
	~BezierCurve();
	
private:
	void calculateBezier(QVector<GLfloat>& curvePoints);
	Point2D evaluateBezier(double t);

private:
	std::vector<Point2D> mControlPoints;
};