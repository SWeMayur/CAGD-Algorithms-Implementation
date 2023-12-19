// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SYMMETRICLINE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SYMMETRICLINE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


// This class is exported from the dll
class SYMMETRICLINE_API CSymmetricLine {
public:
	CSymmetricLine(void);
	// TODO: add your methods here.
};

extern SYMMETRICLINE_API int nSymmetricLine;

SYMMETRICLINE_API int fnSymmetricLine(void);
