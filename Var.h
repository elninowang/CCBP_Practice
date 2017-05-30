#define		PI		3.1415926 
//Windows And DC
HWND hWnd;
HDC hdc;
HPEN hpen;
HPEN hOldPen;
HBRUSH hbrush;
HBRUSH hOldBrush;
POINT pointOld;

//The Position of The Windows
int cxClient;
int cyClient;
int xMid;
int yMid;

//Color Param
CHOOSECOLOR cc;                 // common dialog box structure 
COLORREF acrCustClr[16]={ RGB(255,0,0), RGB(255,255,0), RGB(0,255,0), RGB(0,255,255),
						RGB(0,0,255), RGB(255,0,255), RGB(255,255,255),RGB(0,0,0),
						RGB(255,191,0), RGB(191,255,0), RGB(0,255,191), RGB(0,191,255),
						RGB(191,0,255), RGB(255,0,191), RGB(191,191,191),RGB(127,127,127),
						};
//COLORREF rgbCurrent ;        // initial color selection
COLORREF rgbHigh;
COLORREF rgbLow;

//Dialog
HWND hScrollQ1;
HWND hScrollQ2;
HWND hScrollR;
HWND hScrollr;
SCROLLINFO siQ1;
SCROLLINFO siQ2;
SCROLLINFO siR;
SCROLLINFO sir;
int iPosQ1;
int iPosQ2;
int iPosR;
int iPosr;
//
HWND hScrollX;
HWND hScrollY;
HWND hScrollCX;
HWND hScrollCY;
HWND hScrollP;
SCROLLINFO siX;
SCROLLINFO siY;
SCROLLINFO siCX;
SCROLLINFO siCY;
SCROLLINFO siP;
int iPosX;
int iPosY;
int iPosCX;
int iPosCY;
int iPosP;



