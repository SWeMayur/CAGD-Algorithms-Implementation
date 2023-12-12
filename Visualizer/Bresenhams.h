#pragma once
#include "Line.h"
class Bresenhams
{
public:
    Bresenhams(Line l, QVector<QVector2D>& pixelVertices);
    ~Bresenhams();
private:
    void pixelData(Line l, QVector<QVector2D>& pixelVertices);
};