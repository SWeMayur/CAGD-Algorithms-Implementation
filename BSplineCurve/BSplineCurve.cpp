// BSplineCurve.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "BSplineCurve.h"


// This is an example of an exported variable
BSPLINECURVE_API int nBSplineCurve=0;

// This is an example of an exported function.
BSPLINECURVE_API int fnBSplineCurve(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CBSplineCurve::CBSplineCurve()
{
    return;
}
