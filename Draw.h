
void ClearScreen()
{
	::hbrush = CreateSolidBrush( RGB(0, 0, 0) );
	::hOldBrush = (HBRUSH) SelectObject( ::hdc,::hbrush);
	Rectangle(hdc, 0, 0, cxClient, cyClient );
	SelectObject(::hdc, ::hOldBrush );
	DeleteObject( ::hbrush );
}

void DrawCamera()
{
	static int Left,Top,Bottom,Right,Height;
	char sTemp[100];
	Left = 10;
	Right = 145;
	Top = 10;
	Bottom = 280;
	Height = 20;
	hpen = CreatePen( PS_SOLID, 1, RGB(255,191,0) );
	hbrush = CreateSolidBrush( RGB(0, 0, 0) );
	hOldPen = (HPEN) SelectObject(hdc, hpen );
	hOldBrush = (HBRUSH)SelectObject(hdc, hbrush );
	Rectangle(hdc, Left, Top, Right, Bottom );
	SelectObject( hdc, hOldPen );
	SelectObject( hdc, hOldBrush );
	DeleteObject( hpen );
	DeleteObject( hbrush );
	SetBkColor( hdc, RGB(0,0,0) );
	SetTextColor( hdc, RGB(255,0,0) );
	if( V.nView == 1 )
		wsprintf(sTemp, "͸���ӽ�" );
	else
		wsprintf(sTemp, "��ͶӰ�ӽ�" );
	TextOut(hdc, Left+10, Top+Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );

	wsprintf(sTemp, "���������:" );
	TextOut(hdc, Left+10, Top+3*Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor(hdc, RGB(255,255,0) );
	wsprintf(sTemp, "Xλ��: %d", (int)V.dxMe );
	TextOut(hdc, Left+10, Top+4*Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Yλ��: %d", (int)V.dyMe );
	TextOut(hdc, Left+10, Top+5*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Zλ��: %d", (int)V.dzMe );
	TextOut(hdc, Left+10, Top+6*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Alphaƫ��: %d", (int)(V.dAlphaMe*180/PI)%360 );
	TextOut(hdc, Left+10, Top+7*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Garmaƫ��: %d", (int)(V.dGarmaMe*180/PI)%360 );
	TextOut(hdc, Left+10, Top+8*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Betaƫ��: %d", (int)(V.dBetaMe*180/PI)%360 );
	TextOut(hdc, Left+10, Top+9*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor(hdc, RGB(0,255,0) );
	wsprintf(sTemp, "Alphaת��: %d", (int)(101*V.dVSeta) );
	TextOut(hdc, Left+10, Top+11*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Garmaת��: %d", (int)(101*V.dVFai) );
	TextOut(hdc, Left+10, Top+12*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
}
void DrawControl()
{
	static int Left,Top,Bottom,Right,Height;
	char sTemp[100];
	Left = 10;
	Right = 145;
	Top = 300;
	Bottom = 530;
	Height = 20;
	hpen = CreatePen( PS_SOLID, 1, RGB(255,0,255) );
	hbrush = CreateSolidBrush( RGB(0, 0, 0) );
	hOldPen = (HPEN) SelectObject(hdc, hpen );
	hOldBrush = (HBRUSH)SelectObject(hdc, hbrush );
	Rectangle(hdc, Left, Top, Right, Bottom );
	SelectObject( hdc, hOldPen );
	SelectObject( hdc, hOldBrush );
	DeleteObject( hpen );
	DeleteObject( hbrush );
	SetBkColor( hdc, RGB(0,0,0) );
	SetTextColor( hdc, RGB(255,0,0) );
	wsprintf(sTemp, "���Ʋ���:" );
	TextOut(hdc, Left+10, Top+Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor( hdc, RGB(0,0,255) );
	wsprintf(sTemp, "��: ������ϼ���" );
	TextOut(hdc, Left+10, Top+2*Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "��: ������¼���");
	TextOut(hdc, Left+10, Top+3*Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "��: ����������" );
	TextOut(hdc, Left+10, Top+4*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "��: ������Ҽ���" );
	TextOut(hdc, Left+10, Top+5*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor( hdc, RGB(0,255,255) );
	wsprintf(sTemp, "�ո�: �����ǰ��" );
	TextOut(hdc, Left+10, Top+7*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Tab: ���������" );
	TextOut(hdc, Left+10, Top+8*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Insert: �ӽ���ת" );
	TextOut(hdc, Left+10, Top+9*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	wsprintf(sTemp, "Delete: �ӽ���ת" );
	TextOut(hdc, Left+10, Top+10*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
}	 

void DrawName()
{
	static int Left,Top,Bottom,Right,Height;
	char sTemp[100];
	Left = 10;
	Right = 145;
	Top = 560;
	Bottom = 720;
	Height = 20;
	hpen = CreatePen( PS_SOLID, 1, RGB(0,192,255) );
	hbrush = CreateSolidBrush( RGB(0, 0, 0) );
	hOldPen = (HPEN) SelectObject(hdc, hpen );
	hOldBrush = (HBRUSH)SelectObject(hdc, hbrush );
	Rectangle(hdc, Left, Top, Right, Bottom );
	SelectObject( hdc, hOldPen );
	SelectObject( hdc, hOldBrush );
	DeleteObject( hpen );
	DeleteObject( hbrush );
	SetBkColor( hdc, RGB(0,0,0) );
	SetTextColor( hdc, RGB(255,255,255) );
	wsprintf(sTemp, "����:" );
	TextOut(hdc, Left+10, Top+Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor( hdc, RGB(255,255,0) );
	wsprintf(sTemp, "������" );
	TextOut(hdc, Left+20, Top+2*Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor( hdc, RGB(255,255,255) );
	wsprintf(sTemp, "�༶:");
	TextOut(hdc, Left+10, Top+3*Height,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor( hdc, RGB(255,255,0) );
	wsprintf(sTemp, "�����0108��" );
	TextOut(hdc, Left+20, Top+4*Height ,TEXT(sTemp),lstrlen(TEXT(sTemp)) );
	SetTextColor( hdc, RGB(255,255,255) );
}	 	
void Draw()
{
	char str[1000];
	ClearScreen();
	
	lines.Draw();
	DrawCamera();
	DrawControl();
	DrawName();
}