#include "pch.h"
#include "Bresenhams.h"

Bresenhams::Bresenhams(Line l, std::vector<std::vector<float>>& pixelVertices)
{
    pixelData(l, pixelVertices);
}

Bresenhams::~Bresenhams()
{
}

void Bresenhams::pixelData(Line l, std::vector<std::vector<float>>& pixelVertices)
{
    // Bresenham's line drawing algorithm
    float x1 = l.getP1().x();
    float y1 = l.getP1().y();
    float x2 = l.getP2().x();
    float y2 = l.getP2().y();

    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);
    float sx = (x1 < x2) ? 1.0f : -1.0f;
    float sy = (y1 < y2) ? 1.0f : -1.0f;
    float err = dx - dy;

    while (x1 < x2 || y1 < y2) {
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

        float e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
            x1 = round(x1);
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
            y1 = round(y1);
        }
    }
}