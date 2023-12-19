// PixelGrid.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "PixelGrid.h"


// This is an example of an exported variable
PIXELGRID_API int nPixelGrid=0;

// This is an example of an exported function.
PIXELGRID_API int fnPixelGrid(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CPixelGrid::CPixelGrid()
{
    return;
}
