class View
{
private:
	double dR;
	double dFai;
	double dSeta;
	double dDerta;

public:
	double dxMe;
	double dyMe;
	double dzMe;
	double dAlphaMe;
	double dBetaMe;
	double dGarmaMe;
	double dtMe;
	double dtPlane;

	double dVFai;
	double dVSeta;

	int nView;
	double dK;
	
	double dAlphaSin;
	double dAlphaCos;
	double dBetaSin;
	double dBetaCos;
	double dGarmaSin;
	double dGarmaCos;
public:
	View();
	void FirstView();
	void SecondView();
	void ThirdView();
	void Stop();
	void Alpha(double dd);
	void Beta(double dd);
	void Garma(double dd);
	void GetABC();
	void GlobalUp(double dArc );
	void GlobalLeft(double dArc );
	void GlobalIn(double dDistance );
	void GlobalTurn(double dArc );
	void GlobalNext();
	void Get();
};
View::View()
{
	dR = 1000;
	dFai = 3*PI/8;
	dSeta = PI/8;
	dDerta = 0;

	dVFai = 0.00;
	dVSeta = 0.04;

	GetABC();
	dtMe = 3500;
	dtPlane = 0.0001;
	nView = 1;

	dK = 3.5;
	dBetaMe = 0;
	dBetaSin = 0;
	dBetaCos = 1;
}
void View::FirstView()
{
	dFai = PI/2;
	dSeta = 0;
	dVSeta = 0;
	dDerta = 0;
	GetABC();
}
void View::SecondView()
{
	dFai = PI/2;
	dSeta = -PI/2;
	dVSeta = 0;
	dDerta = 0;
	GetABC();
}
void View::ThirdView()
{
	dFai = 0;
	dVFai = 0;
	dDerta = 0;
	GetABC();
}
void View::Stop()
{
	dVFai = 0;
	dVSeta = 0;
	GetABC();
}	
void View::GetABC()
{
	dyMe = dR*sin(dFai)*cos(dSeta);
	dxMe = dR*sin(dFai)*sin(dSeta);
	dzMe = dR*cos(dFai);

	dGarmaMe =  PI/2 - dFai;
	dAlphaMe =  PI - dSeta;

	dGarmaCos = cos( dGarmaMe );
	dGarmaSin = sin( dGarmaMe );
	
	dAlphaCos = cos( dAlphaMe );
	dAlphaSin = sin( dAlphaMe );

	dBetaMe = dDerta;
	dBetaCos = cos( dBetaMe );
	dBetaSin = sin( dBetaMe );
}
void View::GlobalUp(double dArc )
{
	dFai -= dArc;
	GetABC();
}
void View::GlobalLeft(double dArc)
{
	dSeta += dArc;
	GetABC();
}
void View::GlobalNext()
{
	dFai -= dVFai;
	dSeta += dVSeta;
	GetABC();
}

void View::GlobalIn(double dDistance)
{
	if( nView == 1 )
	{
		dR -= dDistance;
		if( dR < 300 )
		{
			dR += dDistance;
			GetABC();
		}
		GetABC();
	}
	else
	{
		double dOff;
		dOff = (dDistance > 0 )? -0.05 : 0.05;
		dK -= dOff;
		if( dK < 0 )
		{
			dK += dOff;
			GetABC();
		}
	}
}

void View::GlobalTurn(double dArc)
{
	dDerta += dArc;
	GetABC();
}
/////////////////////////////////////
View V;
