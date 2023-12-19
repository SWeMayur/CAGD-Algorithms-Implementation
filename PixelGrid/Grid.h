#pragma once
#include <vector>
#include "pch.h"

class PIXELGRID_API Grid
{
public:
    Grid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize);
    ~Grid();
private:
    void storeGrid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize);
};
