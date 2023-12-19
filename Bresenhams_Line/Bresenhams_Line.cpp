// Bresenhams_Line.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Bresenhams_Line.h"


// This is an example of an exported variable
BRESENHAMSLINE_API int nBresenhamsLine=0;

// This is an example of an exported function.
BRESENHAMSLINE_API int fnBresenhamsLine(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CBresenhamsLine::CBresenhamsLine()
{
    return;
}
