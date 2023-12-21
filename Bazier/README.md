# BezierCurve Project

## Overview

BezierCurve is a Qt C++ project that implements a Bezier curve calculation algorithm. Bezier curves are widely used in computer graphics and design to model smooth curves.

## Features

- Bezier curve calculation based on control points.
- The project is set up as a Qt project in Visual Studio.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)

### Building and Running

1. Open the `BezierCurve.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt is properly set up.

3. Build the solution.

4. Run the executable to see the Bezier curve in action.

## Project Structure

- `BezierCurve.h` and `BezierCurve.cpp`: Contains the implementation of the `BezierCurve` class, which handles Bezier curve calculation.

- `Point2D.h`: Definition of the `Point2D` class used to represent 2D points.

- `pch.h`: Precompiled header file for faster compilation.

## Usage Example

```cpp
#include "BezierCurve.h"

int main() {
    // Define control points
    std::vector<Point2D> controlPoints = { {0, 0}, {1, 2}, {3, 4}, {5, 6} };
    
    // Create a Bezier curve
    std::vector<float> curvePoints;
    BezierCurve bezierCurve(controlPoints, curvePoints);

    // Do something with the curvePoints...

    return 0;
}
