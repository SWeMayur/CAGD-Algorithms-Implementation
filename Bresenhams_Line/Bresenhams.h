#pragma once
#include "Line.h"
#include <vector>
#include "pch.h"

class BRESENHAMSLINE_API Bresenhams
{
public:
    Bresenhams(Line l, std::vector<std::vector<float>>& pixelVertices);
    ~Bresenhams();
private:
    void pixelData(Line l, std::vector<std::vector<float>>& pixelVertices);
};