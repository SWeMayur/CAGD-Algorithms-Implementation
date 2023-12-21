# Hermite Curve Project

## Overview

Hermite Curve is a Qt C++ project that implements the Hermite curve interpolation algorithm. The Hermite curve is a mathematical spline used for smooth interpolation between given points, taking into account both the position and tangent information at each control point.

## Features

- Hermite curve calculation based on control points and tangent vectors.
- The project is set up as a Qt project in Visual Studio.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)

### Building and Running

1. Open the `HermiteCurve.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt is properly set up.

3. Build the solution.

4. Run the executable to see the Hermite curve in action.

## Project Structure

- `HermiteCurve.h` and `HermiteCurve.cpp`: Contains the implementation of the `HermiteCurve` class, which handles Hermite curve interpolation.

- `Point2D.h`: Definition of the `Point2D` class used to represent 2D points.

- `pch.h`: Precompiled header file for faster compilation.

## Usage Example

```cpp
#include "HermiteCurve.h"

int main() {
    // Define control points and tangent vectors
    std::vector<Point2D> controlPoints = { {0, 0}, {1, 2}, {3, 4}, {5, 6} };
    
    // Create a Hermite curve
    std::vector<float> curvePoints;
    HermiteCurve hermiteCurve(controlPoints, curvePoints);

    // Do something with the curvePoints...

    return 0;
}
