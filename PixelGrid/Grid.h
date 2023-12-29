#pragma once
#include <vector>
#include "pch.h"

class PIXELGRID_API Grid
{
public:
    Grid(std::vector<float>& vertices, std::vector<float>& colors, const int gridSize);
    ~Grid();
private:
    void initializeGrid(std::vector<float>& vertices, std::vector<float>& colors, const int gridSize);
};
