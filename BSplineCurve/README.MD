# BSplineCurve Project

## Overview

BSplineCurve is a Qt C++ project that implements a B-spline curve evaluation algorithm. B-spline curves are commonly used in computer graphics and geometric modeling to represent smooth and flexible curves.

## Features

- B-spline curve evaluation based on control points and a specified parameter 't'.
- Implementation supports arbitrary degree B-spline curves.
- The project is set up as a Qt project in Visual Studio.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)

### Building and Running

1. Open the `BSplineCurve.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt is properly set up.

3. Build the solution.

4. Run the executable to see the B-spline curve in action.

## Project Structure

- `BSpline.h` and `BSpline.cpp`: Contains the implementation of the `BSpline` class, which handles B-spline curve evaluation.

- `Point2D.h`: Definition of the `Point2D` class used to represent 2D points.

- `pch.h`: Precompiled header file for faster compilation.

## Usage Example

```cpp
#include "BSpline.h"

int main() {
    BSpline bspline(3); // Create a B-spline curve of degree 3
    // Define control points
    std::vector<Point2D> controlPoints = { {0, 0}, {1, 2}, {3, 4}, {5, 6} };
    // Evaluate the B-spline curve at parameter 't'
    std::vector<Point2D> curvePoints = bspline.evaluate(controlPoints, 100);

    // Do something with the curvePoints...

    return 0;
}
