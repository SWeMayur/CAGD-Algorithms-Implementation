// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the PIXELGRID_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// PIXELGRID_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

// This class is exported from the dll
class PIXELGRID_API CPixelGrid {
public:
	CPixelGrid(void);
	// TODO: add your methods here.
};

extern PIXELGRID_API int nPixelGrid;

PIXELGRID_API int fnPixelGrid(void);
