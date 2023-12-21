# Bresenham's Line Drawing Algorithm Project

## Overview

Bresenham's Line Drawing Algorithm is a Qt C++ project that implements the Bresenham's algorithm for drawing lines. The algorithm is widely used in computer graphics for efficient and accurate line rendering.

## Features

- Implementation of Bresenham's line drawing algorithm.
- Accepts two points as input to generate a set of pixel coordinates forming the line.
- The project is set up as a Qt project in Visual Studio.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)

### Building and Running

1. Open the `BresenhamsLine.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt is properly set up.

3. Build the solution.

4. Run the executable to see Bresenham's line drawing algorithm in action.

## Project Structure

- `Bresenhams.h` and `Bresenhams.cpp`: Contains the implementation of the `Bresenhams` class, which handles the Bresenham's line drawing algorithm.

- `Line.h`: Definition of the `Line` class used to represent a line segment.

- `pch.h`: Precompiled header file for faster compilation.

## Usage Example

```cpp
#include "Bresenhams.h"

int main() {
    // Define a line segment
    Line line({0, 0}, {10, 5});

    // Generate pixel coordinates using Bresenham's algorithm
    std::vector<std::vector<float>> pixelVertices;
    Bresenhams bresenham(line, pixelVertices);

    // Do something with the pixelVertices...

    return 0;
}
