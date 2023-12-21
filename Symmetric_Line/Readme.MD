# Symmetric DDA Line Drawing Algorithm Project

## Overview

Symmetric DDA Line Drawing Algorithm is a Qt C++ project that implements the DDA (Digital Differential Analyzer) line drawing algorithm with symmetry optimization. The algorithm efficiently draws lines in computer graphics by minimizing calculations using symmetry properties.

## Features

- Symmetric DDA line drawing algorithm implementation.
- The project is set up as a Qt project in Visual Studio.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)

### Building and Running

1. Open the `SymmetricDDA.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt is properly set up.

3. Build the solution.

4. Run the executable to see the Symmetric DDA line drawing algorithm in action.

## Project Structure

- `SymmetricDDA.h` and `SymmetricDDA.cpp`: Contains the implementation of the `SymmetricDDA` class, which handles Symmetric DDA line drawing.

- `Line.h`: Definition of the `Line` class used to represent a line segment.

- `pch.h`: Precompiled header file for faster compilation.

## Usage Example

```cpp
#include "SymmetricDDA.h"

int main() {
    // Define a line segment
    Line line({0, 0}, {10, 5});

    // Generate pixel coordinates using Symmetric DDA algorithm
    std::vector<std::vector<float>> pixelVertices;
    SymmetricDDA symmetricDDA(line, pixelVertices);

    // Do something with the pixelVertices...

    return 0;
}
