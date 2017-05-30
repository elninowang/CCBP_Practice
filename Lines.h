#define		LMAXCX		201
#define		LMAXCY		201
#define		LMAXPRE		501
#define		e0			0.1

class Lines
{
private:
	int nMide;
	double xBound;
	double yBound;

	double dR;
	double dr;
	double dQ1;
	double dQ2;

	BYTE color1r;
	BYTE color1g;
	BYTE color1b;
	BYTE color2r;
	BYTE color2g;
	BYTE color2b;
	double dcHigh;
	double dcLow;
	
	int nMaxCX;
	int nMaxCY;
	int nMaxPre;
protected:
	Vector3D VectorX[LMAXCX][LMAXPRE];
	Vector3D VectorY[LMAXCY][LMAXPRE];
	void ColorSet();
	COLORREF FindColor(double dz);
	double f(double dx,double dy);
	void DrawLine(Vector3D v1, Vector3D v2);
public:
	Lines(double _xBound, double _yBound, double _dR, double _dr, double _dQ1, double _dQ2 );
	void MakeView();
	void Draw();
	void GetParam(double &_dR,double &_dr,double &_dQ1,double &_dQ2);
	void GetParam(int &_xBound,int &_yBound,int &_nMaxCX,int &_nMaxCY,int &_nMaxPre);
	void SetParam(double _dR,double _dr,double _dQ1,double _dQ2);
	void SetParam(int _xBound,int _yBound,int _nMaxCX,int _nMaxCY,int _nMaxPre);
	void SetHighColor(COLORREF color);
	void SetLowColor(COLORREF color);
};

Lines::Lines(double _xBound, double _yBound, double _dR, double _dr, double _dQ1, double _dQ2 )
{
	xBound = _xBound;
	yBound = _yBound;
	nMaxCX = 71;
	nMaxCY = 71;
	nMaxPre = 101;

	dR = _dR;
	dr = _dr;
	dQ1 = _dQ1;
	dQ2 = _dQ2;
	color1r = 255; 
	color1g = 255;
	color1b = 0;
	color2r = 255;
	color2g = 0;
	color2b = 255;
	rgbHigh = RGB( color1r,  color1g, color1b);
	rgbLow = RGB( color2r,  color2g, color2b);

	ColorSet();
	MakeView();
}
void Lines::ColorSet()
{
	if( dQ1 > 0 && dQ2 > 0 )
	{
		if( dQ1 > dQ2 )
			dcHigh = f( -(dR-dr), 0 );
		else
			dcHigh = f( dR-dr, 0 );
		dcLow = 0;
	}
	else if( dQ1 < 0 && dQ2 < 0 )
	{
		if( dQ1 < dQ2 )
			dcLow = f( -(dR-dr), 0 );
		else
			dcLow = f( dR-dr, 0 );
		dcHigh = 0;
	}
	else if( dQ1 < 0 && dQ2 > 0 )
	{
		dcHigh = f( dR+dr, 0 );
		dcLow = f( -(dR+dr), 0);
	}
	else
	{
		dcHigh = f( -(dR+dr), 0 );
		dcLow = f( dR+dr, 0);
	}
}
COLORREF Lines::FindColor(double dz)
{
	if( dcHigh == dcLow )
		return RGB( (color1r+color2r)/2, (color1g+color2g)/2, (color1b+color2b)/2 );
	return RGB( color2r+((double)color1r-(double)color2r)*(dz-dcLow)/(dcHigh-dcLow),
			color2g+((double)color1g-(double)color2g)*(dz-dcLow)/(dcHigh-dcLow),
			color2b+((double)color1b-(double)color2b)*(dz-dcLow)/(dcHigh-dcLow)	);
}
double Lines::f(double dx, double dy )
{
	double df1 = 0;
	double df2 = 0;

	if( (dx+dR)*(dx+dR)+dy*dy <= dr*dr )
		df1 = dQ1/(e0*dr);
	else
		df1 = dQ1/(e0*sqrt( (dx+dR)*(dx+dR)+dy*dy ));
	if( (dx-dR)*(dx-dR)+dy*dy <= dr*dr )
		df2 = dQ2/(e0*dr);
	else
		df2 = dQ2/(e0*sqrt( (dx-dR)*(dx-dR)+dy*dy ));
	return df1+df2;
}
void Lines::MakeView()
{
	double dTempX, dTempY;
	double dLecX, dLecX1, dLecY, dLecY1;
	int i,j;
	double dz;
	dLecX = 2*xBound/(nMaxCX-1);
	dLecY = 2*yBound/(nMaxCY-1);
	dLecX1 = 2*xBound/(nMaxPre-1);
	dLecY1 = 2*yBound/(nMaxPre-1);

	for( i=0; i<nMaxCX; i++)
		for( j=0; j<nMaxPre; j++)
			VectorX[i][j].in(-xBound+i*dLecX, -yBound+j*dLecY1, dz=f(-xBound+i*dLecX, -yBound+j*dLecY1), FindColor(dz) );
	for( i=0; i<nMaxCY; i++)
		for( j=0; j<nMaxPre; j++)
			VectorY[i][j].in(-xBound+j*dLecX1, -yBound+i*dLecY, dz=f(-xBound+j*dLecX1, -yBound+i*dLecY), FindColor(dz) );
}
void Lines::DrawLine(Vector3D v1,Vector3D v2)
{
	int x1,x2,y1,y2;
	double dxTemp,dzTemp;
	
	::hpen = CreatePen( PS_SOLID, 0, v1.GetColor() );
	::hOldPen = (HPEN) SelectObject(::hdc, ::hpen );
	if( V.nView == 1 )
	{
		if( v1.Check() && v2.Check() )
		{
			x1 = ::xMid + (int)(V.dtMe*v1.GetRX()/v1.GetRY() );
			y1 = ::yMid - (int)(V.dtMe*v1.GetRZ()/v1.GetRY() );
			x2 = ::xMid + (int)(V.dtMe*v2.GetRX()/v2.GetRY() );
			y2 = ::yMid - (int)(V.dtMe*v2.GetRZ()/v2.GetRY() );
			MoveToEx(::hdc, x1, y1, &pointOld );
			LineTo(::hdc, x2, y2 );
		}
	}
	else 
	{
		x1 = ::xMid + (int)( V.dK*v1.GetRX() );
		y1 = ::yMid - (int)( V.dK*v1.GetRZ() );
		x2 = ::xMid + (int)( V.dK*v2.GetRX() );
		y2 = ::yMid - (int)( V.dK*v2.GetRZ() );
		MoveToEx(::hdc, x1, y1, &pointOld );
		LineTo(::hdc, x2, y2 );
	}
	SelectObject(::hdc, ::hOldPen);
	DeleteObject(::hpen);
}
void Lines::Draw()
{
	int i,j;
		
	for( i=0; i<nMaxCX; i++)
		for( j=0; j<nMaxPre-1; j++)
			DrawLine( VectorX[i][j], VectorX[i][j+1] );
	for( i=0; i<nMaxCY; i++)
		for( j=0; j<nMaxPre-1; j++)
			DrawLine( VectorY[i][j], VectorY[i][j+1] );	
}
void Lines::GetParam(double &_dR,double &_dr,double &_dQ1,double &_dQ2)
{
	_dR = dR;
	_dr = dr;
	_dQ1 = dQ1;
	_dQ2 = dQ2;
}
void Lines::GetParam(int &_xBound,int &_yBound,int &_nMaxCX,int &_nMaxCY,int &_nMaxPre)
{
	_xBound = xBound;
	_yBound = yBound;
	_nMaxCX = nMaxCX;
	_nMaxCY = nMaxCY;
	_nMaxPre = nMaxPre;
}
void Lines::SetParam(double _dR,double _dr,double _dQ1,double _dQ2)
{
	dR = _dR;
	dr = _dr;
	dQ1 = _dQ1;
	dQ2 = _dQ2;
	ColorSet();
	MakeView();
}
void Lines::SetParam(int _xBound,int _yBound,int _nMaxCX,int _nMaxCY,int _nMaxPre)
{
	xBound = _xBound;
	yBound = _yBound;
	nMaxCX = _nMaxCX;
	nMaxCY = _nMaxCY;
	nMaxPre = _nMaxPre;
	ColorSet();
	MakeView();
}	
void Lines::SetHighColor(COLORREF color)
{
	color1r = GetRValue( color );
	color1g = GetGValue( color );
	color1b = GetBValue( color );
	ColorSet();
	MakeView();
}
void Lines::SetLowColor(COLORREF color)
{
	color2r = GetRValue( color );
	color2g = GetGValue( color );
	color2b = GetBValue( color );
	ColorSet();
	MakeView();
}
Lines lines(100, 100, 45, 10, 80, -80);

