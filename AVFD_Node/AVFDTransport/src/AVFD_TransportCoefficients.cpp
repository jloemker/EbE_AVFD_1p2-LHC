// ++++++++++++++++++++++++++++++++++++++++++++++++++ //
// 			   AVFD Transport Coefficients			  //
// ++++++++++++++++++++++++++++++++++++++++++++++++++ //


// vector relaxation time
double AVFD::relaxation_time_v(double temperature) //from Song's paper 0.5~5fm
{
	return TauV/(temperature+0.001);
} // in the unit of fm(1)

// axial relaxation time
double AVFD::relaxation_time_a(double temperature)
{
	return TauA/(temperature+0.001);
} // in the unit of fm(1)

// vector sigma
double AVFD::sigma_v(double temperature)
{
	return SigmaV*temperature;//*(0.5+0.5*tanh(5.0*(temperature-0.7)));
}// in the unit of fm(-1)

// axial sigma
double AVFD::sigma_a(double temperature)
{
	return SigmaA*temperature;//*(0.5+0.5*tanh(5.0*(temperature-0.7)));
}// in the unit of fm(-1)

/* ==============================
   MultiPole of Charge Density
 ============================= */
// Eccentricity of vector charge distribution
double AVFD::nv_multipole(int flavor, double x, double y)
{
	double E1, E2;
	switch(flavor)
	{
		case 1:  { E1 = E1V_U; E2 = E2V_U; break; }
		case 2:  { E1 = E1V_D; E2 = E2V_D; break; }
		case 3:  { E1 = E1V_S; E2 = E2V_S; break; }
		default: { E1 = 0.000; E2 = 0.000; break; }
	}
	double res;
	double r = sqrt(x*x + y*y + 1E-2);
	res = 2.0*E1 * y/r * tanh(r/0.1) + 2.0*E2 * (x*x-y*y)/r/r * tanh(r/0.3) ;
	return res;
}
// Eccentricity of axial charge distribution
double AVFD::na_multipole(int flavor, double x, double y)
{
	double E1, E2;
	switch(flavor)
	{
		case 1:  { E1 = E1A_U; E2 = E2A_U; break; }
		case 2:  { E1 = E1A_D; E2 = E2A_D; break; }
		case 3:  { E1 = E1A_S; E2 = E2A_S; break; }
		default: { E1 = 0.000; E2 = 0.000; break; }
	}
	double res;
	double r = sqrt(x*x + y*y + 1E-2);
	res = 2.0*E1 * y/r * tanh(r/0.1) + 2.0*E2 * (x*x-y*y)/r/r * tanh(r/0.3) ;
	return res;
}

/* ==============================
	 Damping of Axial Charge 
 ============================= */
double AVFD::tau_axialdamping(double temperature, double quark_mass)
{
	// the axial charge damping time (or the relaxation time) based on [PhysRevD.98.054014]
	double alpha_s = 0.3;  
		//alpha_s is the running constant of QCD
	double Qmass_f = temperature;  
		//Qmass_f is the thermal mass, where we take the lattice measured thermal mass
	double Qmass_current = quark_mass;
	double map_Gamma_mass = 0.013*Qmass_current*Qmass_current*Qmass_f*Qmass_f;   
		//map_Gamma_mass denotes the rate of fluctuation of axial charge induced by the quark mass effect
	double map_Gamma_cs = 30.0 * (alpha_s*alpha_s*alpha_s*alpha_s) * (temperature*temperature*temperature*temperature); 
		//map_Gamma_cs 
	double map_Gamma_total = map_Gamma_mass + map_Gamma_cs;
		//map_Gamma_total is the total fluctuation rate
	double tau_sph_a = temperature/(2*inverse_chi_a(temperature)*map_Gamma_total);
		// tau_sph is the relaxation time of axial charge
	return tau_sph_a;
}

double AVFD::axial_noise_mean(double temperature)
{
	return 0.0;
}

double AVFD::axial_noise_generate(double temperature)
{
	return 0.0;
}

/* ==============================
			E & M Field
 ============================= */
// Proper time dependence of magnetic field
double AVFD::B_Tau(double tau)
{
	return TauB*TauB/(tau*tau+TauB*TauB);
}
// Tau derivative of the function above.
double AVFD::dB_dTau(double tau)
{
	return -2*tau*TauB*TauB/(tau*tau+TauB*TauB)/(tau*tau+TauB*TauB);
}

