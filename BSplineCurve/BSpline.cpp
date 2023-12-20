#include "pch.h"
#include "BSpline.h"

BSpline::BSpline(int degree) : degree_(degree) {}

std::vector<float> BSpline::generateUniformKnots(int num_control_points) {
    int num_knots = num_control_points + degree_ + 1;
    std::vector<float> knots(num_knots);

    // Assign the first 'degree + 1' knots as 0
    for (int i = 0; i <= degree_; ++i) {
        knots[i] = 0.0f;
    }

    // Assign the last 'degree + 1' knots as 1
    for (int i = num_knots - degree_ - 1; i < num_knots; ++i) {
        knots[i] = 1.0f;
    }

    // Calculate internal knots
    for (int i = degree_ + 1; i < num_control_points; ++i) {
        knots[i] = static_cast<float>(i - degree_) / (num_control_points - degree_);
    }

    return knots;
}
float BSpline::bSplineBasis(int i, int k, float t, const std::vector<float>& knots) {
    if (k == 1) {
        if (knots[i] <= t && t < knots[i + 1]) {
            return 1.0f;
        }
        return 0.0f;
    }

    double denom1 = knots[i + k - 1] - knots[i];
    double denom2 = knots[i + k] - knots[i + 1];

    double c1 = (denom1 != 0.0f) ? ((t - knots[i]) / denom1 * bSplineBasis(i, k - 1, t, knots)) : 0.0f;
    double c2 = (denom2 != 0.0f) ? ((knots[i + k] - t) / denom2 * bSplineBasis(i + 1, k - 1, t, knots)) : 0.0f;

    return c1 + c2;
}

std::vector<Point2D> BSpline::evaluate(std::vector<Point2D>& control_points, float t) {
    int num_control_points = control_points.size();
    std::vector<float> knots = generateUniformKnots(num_control_points);

    std::vector<Point2D> curve_points;

    // Calculate the step size based on the number of samples
    float step = 1.0f / static_cast<float>(t - 1);

    for (int i = 0; i < t; ++i) {
        float t = static_cast<float>(i) * step; // Calculate the parameter 't' within the range [0, 1]
        Point2D curve_point(0.0f, 0.0f); // Initialize curve_point for this iteration
        for (int j = 0; j < num_control_points; ++j) {
            float basis = bSplineBasis(j, degree_ + 1, t, knots);
            curve_point.setX(curve_point.x() + control_points[j].x() * basis);
            curve_point.setY(curve_point.y() + control_points[j].y() * basis);
        }
        curve_points.push_back(curve_point); // Store the computed point
    }

    return curve_points;
}