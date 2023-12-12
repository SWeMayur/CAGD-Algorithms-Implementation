#include "stdafx.h"
#include "SymmetricDDA.h"

SymmetricDDA::SymmetricDDA(Line l, QVector<QVector2D> &squareVertices)
{
    pixelData(l, squareVertices);
}

SymmetricDDA::~SymmetricDDA()
{
}

void SymmetricDDA::pixelData(Line l, QVector<QVector2D>& pixelVertices)
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
        pixelVertices.append(QVector2D(round(x1), round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1)));
        pixelVertices.append(QVector2D(round(x1) + 1, round(y1) + 1));
        pixelVertices.append(QVector2D(round(x1), round(y1) + 1));
        x1 = deltaX + x1;
        y1 = deltaY + y1;
    }
}