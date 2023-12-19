// Bazier.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Bazier.h"


// This is an example of an exported variable
BAZIER_API int nBazier=0;

// This is an example of an exported function.
BAZIER_API int fnBazier(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CBazier::CBazier()
{
    return;
}
