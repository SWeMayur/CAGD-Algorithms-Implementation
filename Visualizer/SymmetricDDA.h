#pragma once
#include "Line.h"

class SymmetricDDA
{
public:
	SymmetricDDA(Line l, QVector<QVector2D> &squareVertices);
	~SymmetricDDA();

private:
	void pixelData(Line l, QVector<QVector2D> &squareVertices);
};

