
class AxialChargeGenerator
{
private:
	double factor;
	double *BC;
	int BClength;
	void ReadBinaryCollision(string event);
	void AxialChargeForSingleEvent(string event);
	double Stt;
	double QSsq = 1.0;			// QSsq : saturation factor Q_s^2, in the unit of GeV^2. 1 ~ 1.5.
	double sigmaTube = 1.0;		// sigmaTube : Gaussian Width of Smeared Color Tube, in the unit of (fm)
public:
	AxialChargeGenerator();
	void GetSingleEvent(string event);
	void GetStatistic(int number);
};

AxialChargeGenerator::AxialChargeGenerator()
{
	double SpreadFactor = sigmaTube/0.71;
	factor = QSsq*QSsq*2.37472/SpreadFactor/SpreadFactor;
	// factor = (1/16pi^2) * tau_in * QSsq^2, in the unit of fm^{-3}
}

void AxialChargeGenerator::GetSingleEvent(string event)
{
	BC = (double *) calloc (40000*3, sizeof(double));
	ReadBinaryCollision(event);
	AxialChargeForSingleEvent(event);
	free(BC);
	return;
}

void AxialChargeGenerator::ReadBinaryCollision(string event)
{
	int ir = 0;
	double x,y;
	BClength=0;
	int na_sign_sum = 0;
	string filename;
	filename ="./data/BinaryCollisionTable_event_"+event+".dat";
	ifstream fin;
	fin.open(filename.c_str());
	if(!fin.is_open())
	{
		cerr << "Error: Failed to open: " << filename << endl;
		return;
	}
	while ( fin.good() )
	{
		int na_sign = 2*(lrand48() % 2) - 1;
		na_sign_sum += na_sign;
		fin >> x >> y;
		BC[ir*3+0]=x;
		BC[ir*3+1]=y;
		BC[ir*3+2]=(double) na_sign;
		ir +=1;
	}
	fin.close();
	// Let "+" Being Majority
	if(na_sign_sum<0)
	{
		for(int i=0; i<ir; i++) BC[i*3+2] *= -1;
	}
	BClength=ir;
	return;
}

void AxialChargeGenerator::AxialChargeForSingleEvent(string event)
{
	double x1, y1;
	ofstream bout;
	string NAfilename="./data/NADistribution_event_"+event+".dat";
	bout.open(NAfilename.c_str());
	int ir;

	for(int ix=0; ix < Nx; ix++)
	{
		for(int iy = 0; iy < Ny; iy++)
		{
			double x=x0+ix*dx;
			double y=y0+iy*dy;
			double na=0.0;
			for(ir=0; ir<BClength; ir++)
			{
				x1=BC[ir*3+0];
				y1=BC[ir*3+1];
				double dis_sq = (x-x1)*(x-x1) + (y-y1)*(y-y1);
				na += BC[ir*3+2]*factor*exp(-0.5*dis_sq/sigmaTube/sigmaTube);
			}
			if (0<=na && na<1E-8) na = 1E-8;
			if (-1E-8<na && na<0) na = -1E-8;
			bout << x << "\t" << y << "\t" << na << endl;
		}
		//bout << endl;
	}
	bout.close();
	return;
}


