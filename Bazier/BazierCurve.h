#pragma once
#include "Point2D.h"
#include<vector>
#include "pch.h"

class BAZIER_API BezierCurve
{
public:
	BezierCurve(std::vector<Point2D> points, std::vector<float>& curvePoints);
	~BezierCurve();

private:
	void calculateBezier(std::vector<float>& curvePoints);
	Point2D evaluateBezier(double t);

private:
	std::vector<Point2D> mControlPoints;
};