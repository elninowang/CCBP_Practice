
#define			SafeRelease(x)		if(x){x->Release();x=NULL;}
//global variares
LPGUID						lpGUID=NULL;
LPDIRECTDRAW7				lpDD=NULL;
LPDIRECTDRAWCLIPPER			lpClip=NULL;
LPDIRECTDRAWSURFACE7		lpDDPri=NULL;
LPDIRECTDRAWSURFACE7		lpDDBack=NULL;

//global function 
void DrawDirectX(HWND hWnd);
//Create or Delete  
HRESULT	InitDirectX(HWND hWnd)
{
	int ddrval;
	DDSURFACEDESC2 ddsd;
	
	ddrval = DirectDrawCreateEx( lpGUID,(VOID**)(&lpDD),IID_IDirectDraw7,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("DirectDrawCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	ddrval = lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL );
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("CooperativeCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}

	ddrval = lpDD->CreateClipper(NULL,&lpClip,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("ClipperCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	lpClip->SetHWnd(0,hWnd);

	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddrval = lpDD->CreateSurface(&ddsd,&lpDDPri,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("PrimarySurfaceCreateWrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}

	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT ;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth = GetSystemMetrics(SM_CXSCREEN);
	ddsd.dwHeight = GetSystemMetrics(SM_CYSCREEN);

	ddrval=lpDD->CreateSurface(&ddsd,&lpDDBack,NULL);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("Surface Create Wrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	ddrval = lpDDPri->SetClipper(lpClip);
	if( ddrval != DD_OK )
	{
		MessageBox(hWnd,TEXT("Surface Cliper Wrong!"),TEXT("WRONG"),NULL);
		return FALSE;
	}
	DrawDirectX( hWnd );
	return TRUE;
}
void CleanUp()
{
	SafeRelease( lpDDBack );
	SafeRelease( lpDDPri );
	SafeRelease( lpClip );
	//SafeRelease( lpDD );
}
void DrawDirectX(HWND hWnd )
{
	HRESULT ddrval;
	RECT rect,rect1;
	
	POINT point;
	point.x=0;
	point.y=0;
	ClientToScreen(hWnd,&point);
	rect.top=0;
	rect.left=0;
	rect.bottom=cyClient;
	rect.right=cxClient;
	rect1.top=point.y;
	rect1.left=point.x;
	rect1.bottom=point.y+cyClient;
	rect1.right=point.x+cxClient;
	ddrval = lpDDBack->GetDC( &hdc );
	if( ddrval == DD_OK )
	{
		Draw();
		lpDDBack->ReleaseDC( hdc );
	}
	else
		MessageBox(NULL, TEXT("DC Wrong!"), TEXT("WRONG"), NULL );
	lpDDPri->Blt( &rect1, lpDDBack,&rect, DDBLT_WAIT, NULL );
}