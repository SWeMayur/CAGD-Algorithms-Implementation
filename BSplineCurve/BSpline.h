#include <vector>
#include <utility>
#include "Point2D.h"
#include "pch.h"

class BSPLINECURVE_API BSpline {
public:
    BSpline(int degree);
    std::vector<Point2D> evaluate( std::vector<Point2D>& control_points, float t);

private:
    int degree_;
    std::vector<float> generateUniformKnots(int num_control_points);
    float bSplineBasis(int i, int k, float t, const std::vector<float>& knots);
};