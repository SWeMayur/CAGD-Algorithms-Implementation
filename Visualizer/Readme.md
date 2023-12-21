# Graphical Algorithms Visualizer

## Overview

The Graphical Algorithms Visualizer is a Qt C++ project that provides a graphical representation of various algorithms, including Bresenham's Line Drawing Algorithm, Bezier Curve, Hermite Curve, Symmetric DDA Line Drawing Algorithm, and more.

## Features

- Utilizes OpenGL for graphical rendering.
- Incorporates various algorithms to visualize lines, curves, and grids.
- Modular architecture allows easy addition of new algorithms.

## Getting Started

### Prerequisites

- Visual Studio (Recommended version: Visual Studio 2019)
- Qt for Visual Studio (Qt 5 or later)
- OpenGL

### Building and Running

1. Open the `Visualizer.sln` solution file in Visual Studio.

2. Configure the project settings, ensuring that Qt and OpenGL are properly set up.

3. Build the solution.

4. Run the executable to visualize the algorithms graphically.

## Project Structure

- `Visualizer.h` and `Visualizer.cpp`: Contains the implementation of the `Visualizer` class, responsible for coordinating and rendering various algorithms.

- `OpenGLWindow.h` and `OpenGLWindow.cpp`: Implements the `OpenGLWindow` class, which provides an OpenGL context for rendering.

- `Bresenhams.h` and `Bresenhams.cpp`: Implementation of the Bresenham's Line Drawing Algorithm.

- `BezierCurve.h` and `BezierCurve.cpp`: Implementation of the Bezier Curve algorithm.

- `HermiteCurve.h` and `HermiteCurve.cpp`: Implementation of the Hermite Curve algorithm.

- `SymmetricDDA.h` and `SymmetricDDA.cpp`: Implementation of the Symmetric DDA Line Drawing Algorithm.

- `Grid.h` and `Grid.cpp`: Implementation of the grid generation for visualization.

- `pch.h`: Precompiled header file for faster compilation.

## Usage

1. Instantiate the `Visualizer` class and add the desired algorithms for visualization.

2. Run the `Visualizer` to display the graphical representation of the algorithms.

