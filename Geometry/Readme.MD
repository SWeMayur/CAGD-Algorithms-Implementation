# Geometry API Project

## Overview

Geometry API is a Qt C++ project that provides basic geometric functionality, including the definition of 2D points (`Point2D`) and line segments (`Line`). It is designed to be a modular and reusable component for handling geometric entities.

## Features

- **Point2D Class:**
  - Represents a 2D point with `x` and `y` coordinates.
  - Provides methods to get and set the coordinates.

- **Line Class:**
  - Represents a line segment defined by two `Point2D` endpoints.
  - Offers methods to get and set the endpoints.

- **Modularity:**
  - Each geometric entity is encapsulated in its own class for easy integration and reuse.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)

### Building and Running

1. Open the `GeometryAPI.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt is properly set up.

3. Build the solution.

4. Run the executable or incorporate the Geometry API into your own projects.

## Project Structure

- `Point2D.h` and `Point2D.cpp`: Definition and implementation of the `Point2D` class.

- `Line.h` and `Line.cpp`: Definition and implementation of the `Line` class.

- `pch.h`: Precompiled header file for faster compilation.

## Usage Example

```cpp
#include "Point2D.h"
#include "Line.h"

int main() {
    // Create a 2D point
    Point2D point(3.0, 4.0);

    // Create a line segment
    Line line(Point2D(1.0, 2.0), Point2D(5.0, 6.0));

    // Access and modify coordinates
    point.setX(5.0);
    line.setP1(Point2D(0.0, 0.0));

    // Do something with the points and lines...

    return 0;
}
