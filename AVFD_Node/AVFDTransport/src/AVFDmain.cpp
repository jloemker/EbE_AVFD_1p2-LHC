#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>

using namespace std;

#include "AVFD_ThermoDynamics.cpp"
#include "AVFD.h"
#include "AVFD_TransportCoefficients.cpp"
#include "AVFD_ParameterReader.cpp"
#include "AVFD_Current.cpp"
#include "AVFD_ReadProfile.cpp"
#include "AVFD_Differentiate.cpp"
#include "AVFD_Evolution.cpp"

int main(int argc, char const *argv[])
{
	int get_value_int[2];
	double get_value_double[2];
	string HydroType = "VISHNU";
	//string HydroType = "MUSIC";
	
	//Convert_FO_Surface_MUSIC_2_AVFD(".","./results", get_value_int, get_value_double);
	
	Get_FO_Surface_Info(HydroType, get_value_int, get_value_double);
	int FO_length = get_value_int[0];
	int ntau = get_value_int[1];
	double tau_min = get_value_double[0];
	double tau_max = get_value_double[1];
	
	cout <<"All Freeze-out @ ntau = "<< ntau <<", tau = [ " << tau_min <<" , "<< tau_max <<" ]." << endl;
	AVFD AnomalousHydro(ntau+2,tau_min);
	AnomalousHydro.Read_AVFD_Parameter();
	AnomalousHydro.Create_Fields();
	AnomalousHydro.Read_Hydro(HydroType);
	AnomalousHydro.Read_EMField();
	AnomalousHydro.Density_Evolution(1);//for u quark
	AnomalousHydro.Density_Evolution(2);//for d quark
	AnomalousHydro.Density_Evolution(3);//for s quark
	AnomalousHydro.PrintFOChemicalPotential(FO_length);
	AnomalousHydro.Release_Fields();
	return 0;
}