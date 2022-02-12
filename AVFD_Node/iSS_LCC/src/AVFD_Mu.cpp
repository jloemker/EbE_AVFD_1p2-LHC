#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#include"readindata.h"
using namespace std;

//In VISNEW FreezeoutPro10 is used. surface.dat and decdata2.dat are created. Freezeout positions are recorded in surface.dat. And the normal vectors, tau, Pi and so on are in decdata2.dat. In iS the decdata2.dat is used because only the freezeout direction are necessary in their approach. While every row of decdata2.dat and surface.dat is corresponding to the same ix, iy and itau for they are generated in the same loop. In surface.dat the structure is £¨tau_0, tau_fo, x_fo, y_fo,...£©tau0 is useless which is the one of the corner of the interpolation cube.

// mu_u, mu_d, & mu_s are saved in surface_mu.dat

double AVFD_set_chemical_potential(vector<FO_surf> &FOsurf_ptr, vector<particle_info> &particle_ptr)
{
	int FO_length = FOsurf_ptr.size();
	double mu_max=0.0;
	float fo_muu=0.0, fo_mud=0.0, fo_mus=0.0;
	double mufactor = 1.0;
	
	ifstream f_mu;
	f_mu.open("results/surface_mu.dat");
	if(!f_mu.is_open())
	{
		cerr << "In AVFD_Mu.cpp, surface_mu.dat can not be opend." << endl;
	}
	for(int ifo=0; ifo<FO_length; ifo++)
	{
		f_mu >> fo_muu >> fo_mud >> fo_mus;
		double fo_mu_B = 1.0*fo_muu + 2.0*fo_mud + 0.0*fo_mus;
		double fo_mu_C = 1.0*fo_muu - 1.0*fo_mud + 0.0*fo_mus;
		double fo_mu_S = 0.0*fo_muu + 1.0*fo_mud - 1.0*fo_mus;
		if(fabs(fo_mu_B)>mu_max) { mu_max=fabs(fo_mu_B); }
		if(fabs(fo_mu_C)>mu_max) { mu_max=fabs(fo_mu_C); }
		if(fabs(fo_mu_S)>mu_max) { mu_max=fabs(fo_mu_S); }
		FOsurf_ptr[ifo].muB += mufactor*fo_mu_B;
		FOsurf_ptr[ifo].muC += mufactor*fo_mu_C;
		FOsurf_ptr[ifo].muS += mufactor*fo_mu_S;
	}
	f_mu.close();
	
	return mu_max;
}

