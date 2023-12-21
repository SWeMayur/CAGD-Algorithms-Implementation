# PixelGrid API Project

## Overview

PixelGrid API is a Qt C++ project that provides functionality for handling pixel grids. The `Grid` class in this project is designed to generate grid data, including vertex positions and colors, which can be used for rendering a grid in a graphical application.

## Features

- **Grid Class:**
  - Generates vertices and colors for rendering a grid.
  - Allows customization of grid size and step.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)

### Building and Running

1. Open the `PixelGrid.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt is properly set up.

3. Build the solution.

4. Run the executable to see the generated grid in action.

## Project Structure

- `Grid.h` and `Grid.cpp`: Contains the implementation of the `Grid` class, responsible for generating grid data.

- `pch.h`: Precompiled header file for faster compilation.

## Usage Example

```cpp
#include "Grid.h"

int main() {
    // Define vectors to store grid vertices and colors
    std::vector<float> vertices;
    std::vector<float> colors;

    // Create a grid with a specified size
    Grid grid(vertices, colors, 8);

    // Do something with the generated grid data...

    return 0;
}
