#pragma once
#include "Line.h"
#include "pch.h"
#include <vector>

class SYMMETRICLINE_API SymmetricDDA
{
public:
	SymmetricDDA(Line l, std::vector<std::vector<float>>& squareVertices);
	~SymmetricDDA();

private:
	void pixelData(Line l, std::vector<std::vector<float>>& squareVertices);
};

