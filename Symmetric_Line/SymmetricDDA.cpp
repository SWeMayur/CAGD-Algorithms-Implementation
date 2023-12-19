#include "pch.h"
#include "SymmetricDDA.h"

SymmetricDDA::SymmetricDDA(Line l, std::vector<std::vector<float>>& squareVertices)
{
    pixelData(l, squareVertices);
}

SymmetricDDA::~SymmetricDDA()
{
}

void SymmetricDDA::pixelData(Line l, std::vector<std::vector<float>>& pixelVertices)
{
    float x1 = l.getP1().x();
    float y1 = l.getP1().y();
    float x2 = l.getP2().x();
    float y2 = l.getP2().y();

    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);
    float deltaX;
    float deltaY;
    if (dy > dx)
    {
        deltaX = dx / dy;
        deltaY = dy / dy;
    }
    else
    {
        deltaX = dx / dx;
        deltaY = dy / dx;
    }
    while (x1 < x2)
    {
        std::vector<float> v1;
        v1.push_back(round(x1));
        v1.push_back(round(y1));
        pixelVertices.push_back(v1);

        std::vector<float> v2;
        v2.push_back(round(x1) + 1);
        v2.push_back(round(y1));
        pixelVertices.push_back(v2);

        std::vector<float> v3;
        v3.push_back(round(x1) + 1);
        v3.push_back(round(y1) + 1);
        pixelVertices.push_back(v3);

        std::vector<float> v4;
        v4.push_back(round(x1));
        v4.push_back(round(y1) + 1);
        pixelVertices.push_back(v4);

        x1 = deltaX + x1;
        y1 = deltaY + y1;
    }
}