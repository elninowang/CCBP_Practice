// CCBP.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CCBP.h"
#include "resource.h"

#include "math.h"
#define INITGUID
#include "ddraw.h"

#include "var.h"
#include "View.h"
#include "Vector3D.h"
#include "Lines.h"
#include "mmsystem.h"
#include "Draw.h"
#include "DirectX.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
BOOL notDone = FALSE;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Physics(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	View(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CCBP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_CCBP);

	// Main message loop:
	while( notDone == TRUE )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE ))
		{
			if ( msg.message == WM_QUIT ) 
				notDone = FALSE;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			V.GlobalNext();
			DrawDirectX( hWnd );
		}
	}
	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_CCBP);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_CCBP;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
      0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
	
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	

	switch (message) 
	{
	case WM_CREATE:
		if( InitDirectX( hWnd ) == FALSE )
		{
			MessageBox(hWnd, "DirectDraw Error!", "ERROE", NULL );
			SendMessage(hWnd, WM_DESTROY, 0, 0 ); 
		}
		DrawDirectX( hWnd );
		notDone = TRUE;
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_PHYSICS:
			DialogBox(hInst, (LPCTSTR)IDD_PHYSICS, hWnd, (DLGPROC)Physics);
			break;
		case IDM_SCREEN:
			DialogBox(hInst, (LPCTSTR)IDD_VIEW, hWnd, (DLGPROC)View);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_VIEW1:
			V.nView = 1;
			DrawDirectX( hWnd );
			break;
		case IDM_VIEW2:
			V.nView = 2;
			DrawDirectX( hWnd );
			break;
		case IDM_FIRSTVIEW:
			V.FirstView();
			DrawDirectX( hWnd );
			break;
		case IDM_SECONDVIEW:
			V.SecondView();
			DrawDirectX( hWnd );
			break;
		case IDM_THIRDVIEW:
			V.ThirdView();
			DrawDirectX( hWnd );
			break;
		case IDM_STOP:
			V.Stop();
			DrawDirectX( hWnd );
			break;
		case IDM_COLOR1:				
			ZeroMemory(&cc, sizeof(CHOOSECOLOR));
			cc.lStructSize = sizeof(CHOOSECOLOR);
			cc.hwndOwner = hWnd;
			cc.lpCustColors = (LPDWORD) acrCustClr;
			cc.rgbResult = rgbHigh;
			cc.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;
 
			if (ChooseColor(&cc)==TRUE) 
			{
				lines.SetHighColor(cc.rgbResult);
				rgbHigh = cc.rgbResult; 
			}
			break;
		case IDM_COLOR2:				
			ZeroMemory(&cc, sizeof(CHOOSECOLOR));
			cc.lStructSize = sizeof(CHOOSECOLOR);
			cc.hwndOwner = hWnd;
			cc.lpCustColors = (LPDWORD) acrCustClr;
			cc.rgbResult = rgbLow;
			cc.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;
 
			if (ChooseColor(&cc)==TRUE) 
			{
				lines.SetLowColor(cc.rgbResult);
				rgbLow = cc.rgbResult; 
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		xMid = cxClient/2;
		yMid = cyClient/2;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawDirectX(  hWnd  );
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_SPACE:
			V.GlobalIn( 20 );
			break;
		case VK_TAB:
			V.GlobalIn( -20 );
			break;
		case VK_LEFT:
			V.dVSeta += 0.01;
			break;
		case VK_RIGHT:
			V.dVSeta -= 0.01;
			break;
		case VK_UP:
			V.dVFai += 0.01;
			break;
		case VK_DOWN:
			V.dVFai -= 0.01;
			break;
		case VK_DELETE:
			V.GlobalTurn( 0.05 );
			break;
		case VK_INSERT:
			V.GlobalTurn( -0.05 );
			break;
		}
		DrawDirectX(  hWnd  );
		break;
	case WM_DESTROY:
		CleanUp();			
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
LRESULT CALLBACK Physics(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static double dR,dr,dQ1,dQ2;
	switch (message)
	{
		case WM_INITDIALOG:
			lines.GetParam( dR, dr, dQ1, dQ2 );

			hScrollQ1 = GetDlgItem( hDlg, IDC_SCROLLBAR_Q1 );
			siQ1.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siQ1.cbSize = sizeof(siQ1);
			siQ1.nMin = -200;
			siQ1.nMax = 200;
			siQ1.nPos = (int)dQ1;
			SetScrollInfo(hScrollQ1,SB_CTL,&siQ1,TRUE);

			hScrollQ2 = GetDlgItem(  hDlg, IDC_SCROLLBAR_Q2 );
			siQ2.cbSize = sizeof(siQ2);
			siQ2.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siQ2.nMin = -200;
			siQ2.nMax = 200;
			siQ2.nPos = (int)dQ2;
			SetScrollInfo(hScrollQ2,SB_CTL,&siQ2,TRUE);

			hScrollR = GetDlgItem(hDlg, IDC_SCROLLBAR_D );
			siR.cbSize = sizeof(siR);
			siR.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siR.nMin = 30;
			siR.nMax = 130;
			siR.nPos = (int)dR;
			SetScrollInfo(hScrollR,SB_CTL,&siR,TRUE);

			hScrollr = GetDlgItem( hDlg, IDC_SCROLLBAR_R );
			sir.cbSize = sizeof(sir);
			sir.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			sir.nMin = 1;
			sir.nMax = 29;
			sir.nPos = (int)dr;
			SetScrollInfo(hScrollr,SB_CTL,&sir,TRUE);

			SetDlgItemInt( hDlg, IDC_EDIT_Q1, (int)dQ1, TRUE );
			SetDlgItemInt( hDlg, IDC_EDIT_Q2, (int)dQ2, TRUE ); 
			SetDlgItemInt( hDlg, IDC_EDIT_D, (int)dR, TRUE ); 
			SetDlgItemInt( hDlg, IDC_EDIT_R, (int)dr, TRUE ); 
			return TRUE;

		case WM_HSCROLL:
			if( (HWND)lParam == hScrollQ1 )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siQ1.nPos = siQ1.nMin;
					break;
				case SB_RIGHT:
					siQ1.nPos = siQ1.nMax ;
					break;
				case SB_LINELEFT:
					siQ1.nPos--;
					if( siQ1.nPos < siQ1.nMin )
						siQ1.nPos = siQ1.nMin;
					break;
				case SB_LINERIGHT:
					siQ1.nPos++;
					if( siQ1.nPos > siQ1.nMax )
						siQ1.nPos = siQ1.nMax;
					break;
				case SB_PAGELEFT:
					siQ1.nPos -= (siQ1.nMax-siQ2.nMin)/10;
					if( siQ1.nPos < siQ1.nMin )
						siQ1.nPos = siQ1.nMin;
					break;
				case SB_PAGERIGHT:
					siQ1.nPos += (siQ1.nMax-siQ2.nMin)/10;
					if( siQ1.nPos > siQ1.nMax )
						siQ1.nPos = siQ1.nMax;
					break;
				case SB_THUMBPOSITION:
					siQ1.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollQ1, SB_CTL, &siQ1, TRUE );
				dQ1 = siQ1.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_Q1, (int)dQ1, TRUE );
			}
			else if( (HWND)lParam == hScrollQ2 )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siQ2.nPos = siQ2.nMin;
					break;
				case SB_RIGHT:
					siQ2.nPos = siQ2.nMax ;
					break;
				case SB_LINELEFT:
					siQ2.nPos--;
					if( siQ2.nPos < siQ2.nMin )
						siQ2.nPos = siQ2.nMin;
					break;
				case SB_LINERIGHT:
					siQ2.nPos++;
					if( siQ2.nPos > siQ2.nMax )
						siQ2.nPos = siQ2.nMax;
					break;
				case SB_PAGELEFT:
					siQ2.nPos -= (siQ2.nMax-siQ2.nMin)/10;
					if( siQ2.nPos < siQ2.nMin )
						siQ2.nPos = siQ2.nMin;
					break;
				case SB_PAGERIGHT:
					siQ2.nPos += (siQ2.nMax-siQ2.nMin)/10;
					if( siQ2.nPos > siQ2.nMax )
						siQ2.nPos = siQ2.nMax;
					break;
				case SB_THUMBPOSITION:
					siQ2.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollQ2, SB_CTL, &siQ2, TRUE );
				dQ2 = siQ2.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_Q2, (int)dQ2, TRUE );
			}
			else if( (HWND)lParam == hScrollR )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siR.nPos = siR.nMin;
					break;
				case SB_RIGHT:
					siR.nPos = siR.nMax ;
					break;
				case SB_LINELEFT:
					siR.nPos--;
					if( siR.nPos < siR.nMin )
						siR.nPos = siR.nMin;
					break;
				case SB_LINERIGHT:
					siR.nPos++;
					if( siR.nPos > siR.nMax )
						siR.nPos = siR.nMax;
					break;
				case SB_PAGELEFT:
					siR.nPos -= (siR.nMax-siR.nMin)/10;
					if( siR.nPos < siR.nMin )
						siR.nPos = siR.nMin;
					break;
				case SB_PAGERIGHT:
					siR.nPos += (siR.nMax-siR.nMin)/10;
					if( siR.nPos > siR.nMax )
						siR.nPos = siR.nMax;
					break;
				case SB_THUMBPOSITION:
					siR.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollR, SB_CTL, &siR, TRUE );
				dR = siR.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_D, (int)dR, TRUE );
			}
			else if( (HWND)lParam == hScrollr )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					sir.nPos = sir.nMin;
					break;
				case SB_RIGHT:
					sir.nPos = sir.nMax ;
					break;
				case SB_LINELEFT:
					sir.nPos--;
					if( sir.nPos < sir.nMin )
						sir.nPos = sir.nMin;
					break;
				case SB_LINERIGHT:
					sir.nPos++;
					if( sir.nPos > sir.nMax )
						sir.nPos = sir.nMax;
					break;
				case SB_PAGELEFT:
					sir.nPos -= (sir.nMax-sir.nMin)/10;
					if( sir.nPos < sir.nMin )
						sir.nPos = sir.nMin;
					break;
				case SB_PAGERIGHT:
					sir.nPos += (sir.nMax-sir.nMin)/10;
					if( sir.nPos > sir.nMax )
						sir.nPos = sir.nMax;
					break;
				case SB_THUMBPOSITION:
					sir.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollr, SB_CTL, &sir, TRUE );
				dr = sir.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_R, (int)dr, TRUE );
			}
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK ) 
			{
				lines.SetParam( dR, dr, dQ1, dQ2 );
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			else if( LOWORD(wParam) == IDCANCEL )
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
LRESULT CALLBACK View(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int nX,nY,nCX,nCY,nP;
	switch (message)
	{
		case WM_INITDIALOG:
			lines.GetParam( nX, nY, nCX, nCY, nP );

			hScrollX = GetDlgItem( hDlg, IDC_SCROLLBAR_X );
			siX.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siX.cbSize = sizeof(siX);
			siX.nMin = 50;
			siX.nMax = 200;
			siX.nPos = nX;
			SetScrollInfo(hScrollX,SB_CTL,&siX,TRUE);

			hScrollY = GetDlgItem(  hDlg, IDC_SCROLLBAR_Y );
			siY.cbSize = sizeof(siY);
			siY.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siY.nMin = 50;
			siY.nMax = 200;
			siY.nPos = nY;
			SetScrollInfo(hScrollY,SB_CTL,&siY,TRUE);

			hScrollCX = GetDlgItem(hDlg, IDC_SCROLLBAR_CX );
			siCX.cbSize = sizeof(siCX);
			siCX.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siCX.nMin = 11;
			siCX.nMax = 201;
			siCX.nPos = nCX;
			SetScrollInfo(hScrollCX,SB_CTL,&siCX,TRUE);

			hScrollCY = GetDlgItem( hDlg, IDC_SCROLLBAR_CY);
			siCY.cbSize = sizeof(siCY);
			siCY.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siCY.nMin = 11;
			siCY.nMax = 201;
			siCY.nPos = nCY;
			SetScrollInfo(hScrollCY,SB_CTL,&siCY,TRUE);

			hScrollP = GetDlgItem( hDlg, IDC_SCROLLBAR_P);
			siP.cbSize = sizeof(siP);
			siP.fMask = SIF_POS|SIF_RANGE|SIF_PAGE|SIF_TRACKPOS;
			siP.nMin = 51;
			siP.nMax = 501;
			siP.nPos = nP;
			SetScrollInfo(hScrollP,SB_CTL,&siP,TRUE);

			SetDlgItemInt( hDlg, IDC_EDIT_X, nX, TRUE );
			SetDlgItemInt( hDlg, IDC_EDIT_Y, nY, TRUE ); 
			SetDlgItemInt( hDlg, IDC_EDIT_CX, nCX, TRUE ); 
			SetDlgItemInt( hDlg, IDC_EDIT_CY, nCY, TRUE );
			SetDlgItemInt( hDlg, IDC_EDIT_P, nP, TRUE );
			return TRUE;
		case WM_HSCROLL:
			if( (HWND)lParam == hScrollX )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siX.nPos = siX.nMin;
					break;
				case SB_RIGHT:
					siX.nPos = siX.nMax ;
					break;
				case SB_LINELEFT:
					siX.nPos--;
					if( siX.nPos < siX.nMin )
						siX.nPos = siX.nMin;
					break;
				case SB_LINERIGHT:
					siX.nPos++;
					if( siX.nPos > siX.nMax )
						siX.nPos = siX.nMax;
					break;
				case SB_PAGELEFT:
					siX.nPos -= (siX.nMax-siQ2.nMin)/10;
					if( siX.nPos < siX.nMin )
						siX.nPos = siX.nMin;
					break;
				case SB_PAGERIGHT:
					siX.nPos += (siX.nMax-siQ2.nMin)/10;
					if( siX.nPos > siX.nMax )
						siX.nPos = siX.nMax;
					break;
				case SB_THUMBPOSITION:
					siX.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollX, SB_CTL, &siX, TRUE );
				nX = siX.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_X, nX, TRUE );
			}
			else if( (HWND)lParam == hScrollY )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siY.nPos = siY.nMin;
					break;
				case SB_RIGHT:
					siY.nPos = siY.nMax ;
					break;
				case SB_LINELEFT:
					siY.nPos--;
					if( siY.nPos < siY.nMin )
						siY.nPos = siY.nMin;
					break;
				case SB_LINERIGHT:
					siY.nPos++;
					if( siY.nPos > siY.nMax )
						siY.nPos = siY.nMax;
					break;
				case SB_PAGELEFT:
					siY.nPos -= (siY.nMax-siQ2.nMin)/10;
					if( siY.nPos < siY.nMin )
						siY.nPos = siY.nMin;
					break;
				case SB_PAGERIGHT:
					siY.nPos += (siY.nMax-siQ2.nMin)/10;
					if( siY.nPos > siY.nMax )
						siY.nPos = siY.nMax;
					break;
				case SB_THUMBPOSITION:
					siY.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollY, SB_CTL, &siY, TRUE );
				nY = siY.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_Y, nY, TRUE );
			}
			else if( (HWND)lParam == hScrollCX )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siCX.nPos = siCX.nMin;
					break;
				case SB_RIGHT:
					siCX.nPos = siCX.nMax ;
					break;
				case SB_LINELEFT:
					siCX.nPos--;
					if( siCX.nPos < siCX.nMin )
						siCX.nPos = siCX.nMin;
					break;
				case SB_LINERIGHT:
					siCX.nPos++;
					if( siCX.nPos > siCX.nMax )
						siCX.nPos = siCX.nMax;
					break;
				case SB_PAGELEFT:
					siCX.nPos -= (siCX.nMax-siQ2.nMin)/10;
					if( siCX.nPos < siCX.nMin )
						siCX.nPos = siCX.nMin;
					break;
				case SB_PAGERIGHT:
					siCX.nPos += (siCX.nMax-siQ2.nMin)/10;
					if( siCX.nPos > siCX.nMax )
						siCX.nPos = siCX.nMax;
					break;
				case SB_THUMBPOSITION:
					siCX.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollCX, SB_CTL, &siCX, TRUE );
				nCX = siCX.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_CX, nCX, TRUE );
			}
			else if( (HWND)lParam == hScrollCY )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siCY.nPos = siCY.nMin;
					break;
				case SB_RIGHT:
					siCY.nPos = siCY.nMax ;
					break;
				case SB_LINELEFT:
					siCY.nPos--;
					if( siCY.nPos < siCY.nMin )
						siCY.nPos = siCY.nMin;
					break;
				case SB_LINERIGHT:
					siCY.nPos++;
					if( siCY.nPos > siCY.nMax )
						siCY.nPos = siCY.nMax;
					break;
				case SB_PAGELEFT:
					siCY.nPos -= (siCY.nMax-siQ2.nMin)/10;
					if( siCY.nPos < siCY.nMin )
						siCY.nPos = siCY.nMin;
					break;
				case SB_PAGERIGHT:
					siCY.nPos += (siCY.nMax-siQ2.nMin)/10;
					if( siCY.nPos > siCY.nMax )
						siCY.nPos = siCY.nMax;
					break;
				case SB_THUMBPOSITION:
					siCY.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollCY, SB_CTL, &siCY, TRUE );
				nCY = siCY.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_CY, nCY, TRUE );
			}
			else if( (HWND)lParam == hScrollP )
			{
				switch( LOWORD(wParam) )
				{
				case SB_LEFT:
					siP.nPos = siP.nMin;
					break;
				case SB_RIGHT:
					siP.nPos = siP.nMax ;
					break;
				case SB_LINELEFT:
					siP.nPos--;
					if( siP.nPos < siP.nMin )
						siP.nPos = siP.nMin;
					break;
				case SB_LINERIGHT:
					siP.nPos++;
					if( siP.nPos > siP.nMax )
						siP.nPos = siP.nMax;
					break;
				case SB_PAGELEFT:
					siP.nPos -= (siP.nMax-siQ2.nMin)/10;
					if( siP.nPos < siP.nMin )
						siP.nPos = siP.nMin;
					break;
				case SB_PAGERIGHT:
					siP.nPos += (siP.nMax-siQ2.nMin)/10;
					if( siP.nPos > siP.nMax )
						siP.nPos = siP.nMax;
					break;
				case SB_THUMBPOSITION:
					siP.nPos = (short) HIWORD(wParam);
					break;
				}
				SetScrollInfo(hScrollP, SB_CTL, &siP, TRUE );
				nP = siP.nPos;
				SetDlgItemInt(hDlg, IDC_EDIT_P, nP, TRUE );
			}
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK )
			{
				lines.SetParam( nX, nY, nCX, nCY, nP );
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			else if( LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}