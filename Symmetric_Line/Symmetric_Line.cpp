// Symmetric_Line.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Symmetric_Line.h"


// This is an example of an exported variable
SYMMETRICLINE_API int nSymmetricLine=0;

// This is an example of an exported function.
SYMMETRICLINE_API int fnSymmetricLine(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CSymmetricLine::CSymmetricLine()
{
    return;
}
