class MagneticFieldGenerator
{
private:
	int Np = 82;//79;				// Np : total number of protons
	int NN = 208;//197;				// NN : total number of nucleons
	double sigma = 0.71;		// sigma (fm): ElectroMagneto Radius of Proton
	double gamma = 106.3;		// gamma : Lorentz gamma factor, gamma = sqrt(s_NN)/m_N/2
	double RQGPsq = 10.0;		// only for statistic purpose, B field averaged over a region with x^2 + y^2 <= RQGPsq (fm^2)
	string rootfolder;
	double v;
	double factor;
	double Ker[20001];
	double WoodsSaxon[1501];
	void readGaussianFieldKernal();
	double getKer(double x);
	double R0Sq(double t, double x, double y, double z, double xp, double yp, double zp);
	double *RN1;
	double *RN2;
	double *PQ1;
	double *PQ2;
	double *R1;
	double *R2;
	void AssignProton(string event);
	void ReadNucleonPosition(string event);
	void MagneticFieldForSingleEvent(string event);
	double Stt;
public:
	MagneticFieldGenerator(int A_in, int Z_in, double sqrt_sNN);
	void GetSingleEvent(string event);
	void GetStatistic(int number);
};

MagneticFieldGenerator::MagneticFieldGenerator(int A_in, int Z_in, double sqrt_sNN)
{
	NN = A_in;
	Np = Z_in;
	gamma = 0.5*sqrt_sNN/0.938;
	v=sqrt(1-1/gamma/gamma);
	double alpha = 0.007299270;	// alpha : alpha_EM = 1/137s
	factor=alpha*gamma;
	readGaussianFieldKernal();
	RN1 = (double *) calloc (3*NN, sizeof(double));
	RN2 = (double *) calloc (3*NN, sizeof(double));
	R1  = (double *) calloc (3*Np, sizeof(double));
	R2  = (double *) calloc (3*Np, sizeof(double));
	PQ1 = (double *) calloc (NN, sizeof(double));
	PQ2 = (double *) calloc (NN, sizeof(double));
}

void MagneticFieldGenerator::GetSingleEvent(string event)
{
	AssignProton(event);
	ReadNucleonPosition(event);
	MagneticFieldForSingleEvent(event);
	return;
}

void MagneticFieldGenerator::readGaussianFieldKernal()
{
	ifstream Fin;
	Fin.open("./tables/GaussianFieldKernal.dat");
	double buffer;
	for(int ix=0; ix<=20000; ix++)
	{
		Fin >> buffer >> Ker[ix];
	}
	Fin.close();
}

double MagneticFieldGenerator::getKer(double x)
{
	double result;
	int i0 = floor(x*100);
	if(x>200)
	{
		result=1/pow(2*x,1.5);
	}
	else
	{
		result=Ker[i0]*((i0+1)-x*100)+Ker[i0+1]*(x*100-i0);
	}
	return result;
}

double MagneticFieldGenerator::R0Sq(double t, double x, double y, double z, double xp, double yp, double zp)
{
	return (x-xp)*(x-xp) + (y-yp)*(y-yp) + gamma*gamma*(z-zp-v*t)*(z-zp-v*t);
}

void MagneticFieldGenerator::AssignProton(string event)
{
	int irandom;
	for(irandom=0;irandom<NN;irandom++)
	{
		PQ1[irandom]=0;
		PQ2[irandom]=0;
	}

	int icount=0;
	while(icount<Np)
	{
		irandom = (lrand48() % NN);
		if(PQ1[irandom]==0)
		{
			PQ1[irandom]=1;
			icount+=1;
		}

	}
	icount = 0;
	while(icount<Np)
	{
		irandom = (lrand48() % NN);
		if(PQ2[irandom]==0)
		{
			PQ2[irandom]=1;
			icount+=1;
		}
	}
	ofstream fout;
	string filename = "./data/ProtonList_event_"+event+".dat";
	fout.open(filename.c_str());
	int ir;
	for(ir=0;ir<NN;ir++)
	{
		fout << PQ1[ir] << endl;
	}
	fout << endl;
	for(ir=0;ir<NN;ir++)
	{
		fout << PQ2[ir] << endl;
	}
	fout.close();
	return;
}

void MagneticFieldGenerator::ReadNucleonPosition(string event)
{
	int ir;
	ifstream fin;

	int buffer;
	double x,y,z;
	int ip;
	string filenameA = "./data/NucleonPositions_A_event_"+event+".dat";
	fin.open(filenameA.c_str());
	if (!fin.is_open()) cerr << "Fail To Open: " << filenameA << endl;
	fin >>  buffer;
	if(buffer!=NN) {cerr << "Error! Wrong Number of Nucleons For Event " << event << endl;}
	ip = 0;
	for(ir=0; ir<NN; ir++)
	{
		fin >> x >> y >> z;
		RN1[ir*3+0]=x;
		RN1[ir*3+1]=y;
		RN1[ir*3+2]=z/gamma;
		if(PQ1[ir]==1)
		{
			R1[ip*3+0]=x;
			R1[ip*3+1]=y;
			R1[ip*3+2]=z/gamma;
			ip+=1;
		}
	}
	fin.close();

	string filenameB = "./data/NucleonPositions_B_event_"+event+".dat";
	fin.open(filenameB.c_str());
	if (!fin.is_open()) cerr << "Fail To Open: " << filenameB << endl;
	fin >> buffer;
	if(buffer!=NN) {cerr << "Error! Wrong Number of Nucleons For Event " << event << endl;}
	ip=0;
	for(ir=0; ir<NN; ir++)
	{
		fin >> x >> y >> z;
		RN2[ir*3+0]=x;
		RN2[ir*3+1]=y;
		RN2[ir*3+2]=z/gamma;
		if(PQ2[ir]==1)
		{
			R2[ip*3+0]=x;
			R2[ip*3+1]=y;
			R2[ip*3+2]=z/gamma;
			ip+=1;
		}
	}
	fin.close();
	return;
}

void MagneticFieldGenerator::MagneticFieldForSingleEvent(string event)
{
	double x1,x2, y1,y2,z1,z2;
	ofstream bout;
	string EMfilename="./data/EMField_event_"+event+".dat";
	bout.open(EMfilename.c_str());
	int ir;
	double eBySum, eBxSum;
	eBySum = 0;
	eBxSum = 0;
	int Count = 0;

	for(int ix=0; ix < Nx; ix++)
	{
		for(int iy = 0; iy < Ny; iy++)
		{
			double x=x0+ix*dx;
			double y=y0+iy*dy;
			double eBy = 0.0;
			double eBx = 0.0;
			double eEx = 0.0;
			double eEy = 0.0;
			for(ir=0; ir<Np; ir++)
			{
				x1=R1[ir*3+0];
				y1=R1[ir*3+1];
				z1=R1[ir*3+2];
				double eB1 = factor*getKer(0.5*R0Sq(0.0,x,y,0.0,x1,y1,z1)/sigma/sigma)/sigma/sigma/sigma;
				eBx += eB1*(y-y1);
				eBy += -eB1*(x-x1);
				eEx += eB1*(x-x1);
				eEy += eB1*(y-y1);
			}
			for(ir=0; ir<Np; ir++)
			{
				x2=R2[ir*3+0];
				y2=R2[ir*3+1];
				z2=R2[ir*3+2];
				double eB2 = factor*getKer(0.5*R0Sq(0.0,x,y,0.0,x2,y2,z2)/sigma/sigma)/sigma/sigma/sigma;
				eBx += -eB2*(y-y2);
				eBy += eB2*(x-x2);
				eEx += eB2*(x-x2);
				eEy += eB2*(y-y2);
			}
			bout << x << "\t" << y << "\t" << eBx<< "\t" << eBy <<"\t"<< 0.0 <<"\t"<< eEx <<"\t"<< eEy  <<"\t"<< 0.0 << endl;
			if((x*x+y*y)<RQGPsq) // Collect B field in the center
			{
				eBySum += eBy;
				eBxSum += eBx;
				Count += 1;
			}
		}
		//bout << endl;
	}
	bout.close();
	eBySum = eBySum/Count;
	eBxSum = eBxSum/Count;
//	ofstream fout;
//	string MeanBFieldFileName = "./data/MeanBfield_event_"+event+".dat";
//	fout.open(MeanBFieldFileName.c_str());
//	fout << sqrt(eBxSum*eBxSum+eBySum*eBySum) <<"\t"<< atan2(eBySum,eBxSum) <<"\t"<< eBxSum <<"\t"<< eBySum << endl;
//	fout.close();
	return;
}


