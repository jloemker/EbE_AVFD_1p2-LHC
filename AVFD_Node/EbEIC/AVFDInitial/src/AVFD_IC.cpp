#include "AVFD_IC.h"
#include "AVFD_MagneticField.cpp"
#include "AVFD_S.cpp"
//#include "AVFD_N5.cpp"

int main(int argc, char* argv[])
{
	int Nmax = 1;
	int AProjTarg = 208;
	int ZProjTarg = 82;
	double sqrt_sNN = 5200;
	stringstream n_ss, a_ss, z_ss, s_ss;
	n_ss << argv[1];
	n_ss >> Nmax;
	a_ss << argv[2];
	a_ss >> AProjTarg;
	z_ss << argv[3];
	z_ss >> ZProjTarg;
	s_ss << argv[4];
	s_ss >> sqrt_sNN;

	srand48(time(NULL));
	MagneticFieldGenerator MFG(AProjTarg, ZProjTarg, sqrt_sNN);
	//AxialChargeGenerator ACG;
	for(int ievent=1; ievent <= Nmax; ievent++)
	{
		ostringstream ssevent;
		ssevent << ievent;
		Convert_Entropy(ssevent.str());
		MFG.GetSingleEvent(ssevent.str());
	//	ACG.GetSingleEvent(ssevent.str());
	}
	cout << "E-by-E Magnetic Field Generated!" << endl;
	//cout << "E-by-E Magnetic Field + Axial Charge Generated!" << endl;
	return 0;
}
