
class Vector3D
{
private:
	double dx;
	double dy;
	double dz;
protected:	
	double drx;
	double dry;
	double drz;
	COLORREF color;
public:
	Vector3D(double _dx,double _dy, double _dz);
	Vector3D();
	void in(double _dx,double _dy, double _dz,COLORREF _color);
	double GetX();
	double GetY();
	double GetZ();
	double GetRX();
	double GetRY();
	double GetRZ();
	void Move(double da, double db, double dz );
	void RomateXY(double dAlpha);
	void RomateXY(double dcos, double dsin);
	void RomateXZ(double dBeta);
	void RomateXZ(double dcos, double dsin);
	void RomateYZ(double dGarma);
	void RomateYZ(double dcos, double dsin);
	bool Check();
	//Vector3D View(double da, double db, double dz );
	void View(double da, double db, double dz, double dAlpha, double dGarma, double dBeta );
	void View(double da, double db, double dc, double dAlphaCos,
				double dAlphasin, double dGarmaCos, double dGarmaSin,
				double dBetaCos, double dBetaSin );
	void View();
	COLORREF GetColor();
};
Vector3D::Vector3D(double _dx,double _dy, double _dz)
{
	drx = dx = _dx;
	dry = dy = _dy;
	drz = dz = _dz;
}
Vector3D::Vector3D()
{
	drx = dx = 0.0;
	dry = dy = 0.0;
	drz = dz = 0.0;
}
void Vector3D::in(double _dx,double _dy, double _dz,COLORREF _color)
{
	drx = dx = _dx;
	dry = dy = _dy;
	drz = dz = _dz;
	color = _color;
}
double Vector3D::GetX()
{
	return dx;
}
double Vector3D::GetY()
{
	return dy;
}
double Vector3D::GetZ()
{
	return dz;
}
void Vector3D::Move(double da,double db,double dc)
{
	drx = drx+da;
	dry = dry+db;
	drz = drz+dc;
}
void Vector3D::RomateXY(double dAlpha)
{
	double _dry=dry,_drx=drx; 
	dry = _dry*cos(dAlpha)-_drx*sin(dAlpha);
	drx = _dry*sin(dAlpha)+_drx*cos(dAlpha);
}
void Vector3D::RomateXY(double dcos, double dsin)
{
	double _dry=dry,_drx=drx;
	dry = _dry*dcos - _drx*dsin;
	drx = _dry*dsin + _drx*dcos;
}
void Vector3D::RomateXZ(double dBeta)
{
	double _drx=drx,_drz=drz;
	drx = _drx*cos(dBeta)-_drz*sin(dBeta);
	drz = _drx*sin(dBeta)+_drz*cos(dBeta);
}
void Vector3D::RomateXZ(double dcos, double dsin)
{
	double _drx=drx,_drz=drz;
	drx = _drx*dcos - _drz*dsin;
	drz = _drx*dsin + _drz*dcos;
}
void Vector3D::RomateYZ(double dGarma)
{
	double _dry=dry,_drz=drz;
	dry = _dry*cos(dGarma)-_drz*sin(dGarma);
	drz = _dry*sin(dGarma)+_drz*cos(dGarma);
}
void Vector3D::RomateYZ(double dcos, double dsin)
{
	double _dry=dry,_drz=drz;
	dry = _dry*dcos - _drz*dsin;
	drz = _dry*dsin + _drz*dcos;
}
double Vector3D::GetRX()
{
	View();
	return drx;
}
double Vector3D::GetRY()
{
	View();
	return dry;
}
double Vector3D::GetRZ()
{
	View();
	return drz;
}
bool Vector3D::Check()
{
	if( GetRY() <= 0 )
		return false;
	else 
		return true;
}
 
void Vector3D::View(double da, double db, double dc, double dAlpha,  double dGarma, double dBeta)
{
	drx = dx;
	dry = dy;
	drz = dz;
	Move(-da, -db, -dc );
	RomateXY(dAlpha);
	RomateYZ(dGarma);
	//RomateXZ(dBeta);
}
void Vector3D::View(double da, double db, double dc, double dAlphaCos,
				double dAlphaSin, double dGarmaCos, double dGarmaSin,
				double dBetaCos, double dBetaSin )
{
	drx = dx;
	dry = dy;
	drz = dz;
	Move(-da, -db, -dc );
	
	RomateXY(dAlphaCos, dAlphaSin );
	RomateYZ(dGarmaCos, dGarmaSin );
	RomateXZ(dBetaCos, dBetaSin );
}
void Vector3D::View()
{
	View(V.dxMe, V.dyMe, V.dzMe, V.dAlphaCos, V.dAlphaSin,
		V.dGarmaCos, V.dGarmaSin, V.dBetaCos, V.dBetaSin );
}
COLORREF Vector3D::GetColor()
{
	return color;
}

