#define n_inf 1E-9 //bound of density

double KT_ci(double x)
{
	return fabs(x);
}

// Kernal of Current Evolution
// X table derivative with respect to (tau, x, y) direction noted as (pdt_X, pdx_X, pdy_X)
// X table's value at a certain point noted as map_X
int AVFD::Get_dQuantity_dt_2plus1(double *res, int itau, int ieta, int ix, int iy, int flavor)
{
	double Nc = 3.0;
	double CXE = 0.15198177546;// Nc/(2Pi^2)
	double QCharge, Qmass_current;   //Qmass_current is the current quark mass.
	double cBar = 0.0;
	switch(flavor)
	{
		case 1:
					QCharge = 0.66666667;
					Qmass_current=2.3/197.5;
					cBar = 0.166666667;
			break;
		case 2:
					QCharge = -0.33333333;
					Qmass_current=4.8/197.5;
					cBar = 0.166666667;
			break;
		case 3:
					QCharge = -0.33333333;
					Qmass_current=95.0/197.5;
					cBar = 0.0;
			break;
		default:
					QCharge = 0.0;
					Qmass_current=0.0;
					cBar = 0.0;
			break;
	}
	cBar = 0.0; // Turn off CVE
	double tau = tau_start + itau*dt;
	double local_x = ix*dx + x0;
	double local_y = iy*dy + y0;
	//double local_eta = ieta*deta + eta0;
	double local_eta = 0.0;
	double CoshETA = cosh(local_eta);
	double SinhETA = sinh(local_eta);
	int idx = ieta*nx*ny + ix*ny + iy;
	int idx_t = itau*neta*nx*ny + idx;

// BackGround Info	
	// Background temperature: T
	double map_T=BKG_temperature[idx_t];
	if (map_T<0.01) {map_T = 0.01;}
	double pdt_T=MinMod_Derivative(BKG_temperature, 0, itau, ieta, ix, iy);
	double pdx_T=MinMod_Derivative(BKG_temperature, 1, itau, ieta, ix, iy);
	double pdy_T=MinMod_Derivative(BKG_temperature, 2, itau, ieta, ix, iy);
	double pdR_T=MinMod_Derivative(BKG_temperature, 3, itau, ieta, ix, iy) / tau;
	// Background Baryon Number Density: nB
	double map_nB=0.0;//BKG_nB[idx_t];
	double pdt_nB=0.0;//MinMod_Derivative(BKG_nB, 0, itau, ieta, ix, iy);
	double pdx_nB=0.0;//MinMod_Derivative(BKG_nB, 1, itau, ieta, ix, iy);
	double pdy_nB=0.0;//MinMod_Derivative(BKG_nB, 2, itau, ieta, ix, iy);
	double pdR_nB=0.0;//MinMod_Derivative(BKG_nB, 3, itau, ieta, ix, iy) / tau;
	// Background Flow: u^tau
	double map_ut=BKG_ut[idx_t];
	double pdt_ut=MinMod_Derivative(BKG_ut, 0, itau, ieta, ix, iy);
	double pdx_ut=MinMod_Derivative(BKG_ut, 1, itau, ieta, ix, iy);
	double pdy_ut=MinMod_Derivative(BKG_ut, 2, itau, ieta, ix, iy);
	double pdR_ut=MinMod_Derivative(BKG_ut, 3, itau, ieta, ix, iy) / tau;
	// Background Flow: u^x
	double map_ux=BKG_ux[idx_t];
	double pdt_ux=MinMod_Derivative(BKG_ux, 0, itau, ieta, ix, iy);
	double pdx_ux=MinMod_Derivative(BKG_ux, 1, itau, ieta, ix, iy);
	double pdy_ux=MinMod_Derivative(BKG_ux, 2, itau, ieta, ix, iy);
	double pdR_ux=MinMod_Derivative(BKG_ux, 3, itau, ieta, ix, iy) / tau;
	// Background Flow: u^y
	double map_uy=BKG_uy[idx_t];
	double pdt_uy=MinMod_Derivative(BKG_uy, 0, itau, ieta, ix, iy);
	double pdx_uy=MinMod_Derivative(BKG_uy, 1, itau, ieta, ix, iy);
	double pdy_uy=MinMod_Derivative(BKG_uy, 2, itau, ieta, ix, iy);
	double pdR_uy=MinMod_Derivative(BKG_uy, 3, itau, ieta, ix, iy) / tau;
	// Background Flow: tau*u^eta
	double map_uR=0.0;//BKG_uR[idx_t];
	double pdt_uR=0.0;//MinMod_Derivative(BKG_uR, 0, itau, ieta, ix, iy);
	double pdx_uR=0.0;//MinMod_Derivative(BKG_uR, 1, itau, ieta, ix, iy);
	double pdy_uR=0.0;//MinMod_Derivative(BKG_uR, 2, itau, ieta, ix, iy);
	double pdR_uR=0.0;//MinMod_Derivative(BKG_uR, 3, itau, ieta, ix, iy) / tau;
// Evolving Variables
	// Number Density: n_V 
	double map_nv=NumberDensity_v[idx];
	Compute_KT_Derivative(NumberDensity_v, 1, 0, ieta, ix, iy);
	double pdx_nv=KT_MinMod;
	double Pdx_nv=KT_Derivative;
	double Ddx_nv=KT_DisContinuity;
	Compute_KT_Derivative(NumberDensity_v, 2, 0, ieta, ix, iy);
	double pdy_nv=KT_MinMod;
	double Pdy_nv=KT_Derivative;
	double Ddy_nv=KT_DisContinuity;
	Compute_KT_Derivative(NumberDensity_v, 3, 0, ieta, ix, iy);
	double pdR_nv=KT_MinMod;
	double PdR_nv=KT_Derivative / tau;
	double DdR_nv=KT_DisContinuity / tau;
	// Number Density: n_A
	double map_na=NumberDensity_a[idx];
	Compute_KT_Derivative(NumberDensity_a, 1, 0, ieta, ix, iy);
	double pdx_na=KT_MinMod;
	double Pdx_na=KT_Derivative;
	double Ddx_na=KT_DisContinuity;
	Compute_KT_Derivative(NumberDensity_a, 2, 0, ieta, ix, iy);
	double pdy_na=KT_MinMod;
	double Pdy_na=KT_Derivative;
	double Ddy_na=KT_DisContinuity;
	Compute_KT_Derivative(NumberDensity_a, 3, 0, ieta, ix, iy);
	double pdR_na=KT_MinMod;
	double PdR_na=KT_Derivative / tau;
	double DdR_na=KT_DisContinuity / tau;
	// Vector Disspative Current: \nu_v^x 
	double map_NU_v_x=NU_v_x[idx];
	Compute_KT_Derivative(NU_v_x, 1, 0, ieta, ix, iy);
	double pdx_NU_v_x=KT_MinMod;
	double Pdx_NU_v_x=KT_Derivative;
	double Ddx_NU_v_x=KT_DisContinuity;
	Compute_KT_Derivative(NU_v_x, 2, 0, ieta, ix, iy);
	double pdy_NU_v_x=KT_MinMod;
	double Pdy_NU_v_x=KT_Derivative;
	double Ddy_NU_v_x=KT_DisContinuity;
	Compute_KT_Derivative(NU_v_x, 3, 0, ieta, ix, iy);
	double pdR_NU_v_x=KT_MinMod;
	double PdR_NU_v_x=KT_Derivative / tau;
	double DdR_NU_v_x=KT_DisContinuity / tau;
	// Vector Disspative Current: \nu_v^y
	double map_NU_v_y=NU_v_y[idx];
	Compute_KT_Derivative(NU_v_y, 1, 0, ieta, ix, iy);
	double pdx_NU_v_y=KT_MinMod;
	double Pdx_NU_v_y=KT_Derivative;
	double Ddx_NU_v_y=KT_DisContinuity;
	Compute_KT_Derivative(NU_v_y, 2, 0, ieta, ix, iy);
	double pdy_NU_v_y=KT_MinMod;
	double Pdy_NU_v_y=KT_Derivative;
	double Ddy_NU_v_y=KT_DisContinuity;
	Compute_KT_Derivative(NU_v_y, 3, 0, ieta, ix, iy);
	double pdR_NU_v_y=KT_MinMod;
	double PdR_NU_v_y=KT_Derivative / tau;
	double DdR_NU_v_y=KT_DisContinuity / tau;
	// Axial Disspative Current: \nu_a^x 
	double map_NU_a_x=NU_a_x[idx];
	Compute_KT_Derivative(NU_a_x, 1, 0, ieta, ix, iy);
	double pdx_NU_a_x=KT_MinMod;
	double Pdx_NU_a_x=KT_Derivative;
	double Ddx_NU_a_x=KT_DisContinuity;
	Compute_KT_Derivative(NU_a_x, 2, 0, ieta, ix, iy);
	double pdy_NU_a_x=KT_MinMod;
	double Pdy_NU_a_x=KT_Derivative;
	double Ddy_NU_a_x=KT_DisContinuity;
	Compute_KT_Derivative(NU_a_x, 3, 0, ieta, ix, iy);
	double pdR_NU_a_x=KT_MinMod;
	double PdR_NU_a_x=KT_Derivative / tau;
	double DdR_NU_a_x=KT_DisContinuity / tau;
	// Axial Disspative Current: \nu_a^y
	double map_NU_a_y=NU_a_y[idx];
	Compute_KT_Derivative(NU_a_y, 1, 0, ieta, ix, iy);
	double pdx_NU_a_y=KT_MinMod;
	double Pdx_NU_a_y=KT_Derivative;
	double Ddx_NU_a_y=KT_DisContinuity;
	Compute_KT_Derivative(NU_a_y, 2, 0, ieta, ix, iy);
	double pdy_NU_a_y=KT_MinMod;
	double Pdy_NU_a_y=KT_Derivative;
	double Ddy_NU_a_y=KT_DisContinuity;
	Compute_KT_Derivative(NU_a_y, 3, 0, ieta, ix, iy);
	double pdR_NU_a_y=KT_MinMod;
	double PdR_NU_a_y=KT_Derivative / tau;
	double DdR_NU_a_y=KT_DisContinuity / tau;
	/*
	// Axial Disspative Current: \nu_v^R
	double map_NU_v_R=NU_v_R[idx];
	Compute_KT_Derivative(NU_v_R, 1, 0, ieta, ix, iy);
	double pdx_NU_v_R=KT_MinMod;
	double Pdx_NU_v_R=KT_Derivative;
	double Ddx_NU_v_R=KT_DisContinuity;
	Compute_KT_Derivative(NU_v_R, 2, 0, ieta, ix, iy);
	double pdy_NU_v_R=KT_MinMod;
	double Pdy_NU_v_R=KT_Derivative;
	double Ddy_NU_v_R=KT_DisContinuity;
	Compute_KT_Derivative(NU_v_R, 3, 0, ieta, ix, iy);
	double pdR_NU_v_R=KT_MinMod;
	double PdR_NU_v_R=KT_Derivative;
	double DdR_NU_v_R=KT_DisContinuity;
	// Axial Disspative Current: \nu_a^R
	double map_NU_a_R=NU_a_R[idx];
	Compute_KT_Derivative(NU_a_R, 1, 0, ieta, ix, iy);
	double pdx_NU_a_R=KT_MinMod;
	double Pdx_NU_a_R=KT_Derivative;
	double Ddx_NU_a_R=KT_DisContinuity;
	Compute_KT_Derivative(NU_a_R, 2, 0, ieta, ix, iy);
	double pdy_NU_a_R=KT_MinMod;
	double Pdy_NU_a_R=KT_Derivative;
	double Ddy_NU_a_R=KT_DisContinuity;
	Compute_KT_Derivative(NU_a_R, 3, 0, ieta, ix, iy);
	double pdR_NU_a_R=KT_MinMod;
	double PdR_NU_a_R=KT_Derivative;
	double DdR_NU_a_R=KT_DisContinuity;
	*/
	// Axial Disspative Current: \nu_v^R
	double map_NU_v_R=0.0;
	double pdx_NU_v_R=0.0;
	double Ddx_NU_v_R=0.0;
	double Pdx_NU_v_R=0.0;
	double pdy_NU_v_R=0.0;
	double Ddy_NU_v_R=0.0;
	double Pdy_NU_v_R=0.0;
	double pdR_NU_v_R=0.0;
	double DdR_NU_v_R=0.0;
	double PdR_NU_v_R=0.0;
	// Axial Disspative Current: \nu_a^R
	double map_NU_a_R=0.0;
	double pdx_NU_a_R=0.0;
	double Ddx_NU_a_R=0.0;
	double Pdx_NU_a_R=0.0;
	double pdy_NU_a_R=0.0;
	double Ddy_NU_a_R=0.0;
	double Pdy_NU_a_R=0.0;
	double pdR_NU_a_R=0.0;
	double DdR_NU_a_R=0.0;
	double PdR_NU_a_R=0.0;
// chi, sigma, tau_rlx	
	double map_inv_chi_v = inverse_chi_v(map_T);
	double map_inv_chi_a = inverse_chi_a(map_T);
	double map_d_inv_chi_v = d_inverse_chi_dT_v(map_T);
	double map_d_inv_chi_a = d_inverse_chi_dT_a(map_T);
	double map_sigma_v = sigma_v(map_T);
	double map_sigma_a = sigma_a(map_T);
	double RlxTime_v = relaxation_time_v(map_T);
	double RlxTime_a = relaxation_time_a(map_T);
	double dsigmav_dT = map_sigma_v/map_T; // Note:Only for sigma = C*T

	/*
	double pdt_inv_chi_v = map_d_inv_chi_v * pdt_T;
	double pdR_inv_chi_v = map_d_inv_chi_v * pdR_T;
	double pdx_inv_chi_v = map_d_inv_chi_v * pdx_T;
	double pdy_inv_chi_v = map_d_inv_chi_v * pdy_T;
	
	double pdt_inv_chi_a = map_d_inv_chi_a * pdt_T;
	double pdR_inv_chi_a = map_d_inv_chi_a * pdR_T;
	double pdx_inv_chi_a = map_d_inv_chi_a * pdx_T;
	double pdy_inv_chi_a = map_d_inv_chi_a * pdy_T;*/
	
	double d_inv_Tchi_dT = (map_d_inv_chi_v - map_inv_chi_v/map_T)/map_T;
	double pdt_inv_Tchi_v = d_inv_Tchi_dT * pdt_T;
	double pdx_inv_Tchi_v = d_inv_Tchi_dT * pdx_T;
	double pdy_inv_Tchi_v = d_inv_Tchi_dT * pdy_T;
	double pdR_inv_Tchi_v = d_inv_Tchi_dT * pdR_T;
	double pdt_inv_Tchi_a = d_inv_Tchi_dT * pdt_T;
	double pdx_inv_Tchi_a = d_inv_Tchi_dT * pdx_T;
	double pdy_inv_Tchi_a = d_inv_Tchi_dT * pdy_T;
	double pdR_inv_Tchi_a = d_inv_Tchi_dT * pdR_T;
// EM field, Assumes Global Tau-dependence
	double B_at_Tau = B_Tau(tau);
	double dBdTau_at_Tau = dB_dTau(tau);
	double map_Bx = EM_Bx[idx] * B_at_Tau;
	double map_By = EM_By[idx] * B_at_Tau;
	double map_Bz = EM_Bz[idx] * B_at_Tau;
	double map_Ex = EM_Ex[idx] * B_at_Tau;
	double map_Ey = EM_Ey[idx] * B_at_Tau;
	double map_Ez = EM_Ez[idx] * B_at_Tau;
	double pdt_Bx = EM_Bx[idx] * dBdTau_at_Tau;
	double pdt_By = EM_By[idx] * dBdTau_at_Tau;
	double pdt_Bz = EM_Bz[idx] * dBdTau_at_Tau;
	double pdt_Ex = EM_Ex[idx] * dBdTau_at_Tau;
	double pdt_Ey = EM_Ey[idx] * dBdTau_at_Tau;
	double pdt_Ez = EM_Ez[idx] * dBdTau_at_Tau;

	double pdx_Bx = MinMod_Derivative(EM_Bx, 1, 0, ieta, ix, iy) * B_at_Tau;
	double pdx_By = MinMod_Derivative(EM_By, 1, 0, ieta, ix, iy) * B_at_Tau;
	double pdx_Bz = MinMod_Derivative(EM_Bz, 1, 0, ieta, ix, iy) * B_at_Tau;
	double pdx_Ex = MinMod_Derivative(EM_Ex, 1, 0, ieta, ix, iy) * B_at_Tau;
	double pdx_Ey = MinMod_Derivative(EM_Ey, 1, 0, ieta, ix, iy) * B_at_Tau;
	double pdx_Ez = MinMod_Derivative(EM_Ez, 1, 0, ieta, ix, iy) * B_at_Tau;

	double pdy_Bx = MinMod_Derivative(EM_Bx, 2, 0, ieta, ix, iy) * B_at_Tau;
	double pdy_By = MinMod_Derivative(EM_By, 2, 0, ieta, ix, iy) * B_at_Tau;
	double pdy_Bz = MinMod_Derivative(EM_Bz, 2, 0, ieta, ix, iy) * B_at_Tau;
	double pdy_Ex = MinMod_Derivative(EM_Ex, 2, 0, ieta, ix, iy) * B_at_Tau;
	double pdy_Ey = MinMod_Derivative(EM_Ey, 2, 0, ieta, ix, iy) * B_at_Tau;
	double pdy_Ez = MinMod_Derivative(EM_Ez, 2, 0, ieta, ix, iy) * B_at_Tau;

	double pdR_Bx = MinMod_Derivative(EM_Bx, 3, 0, ieta, ix, iy) * B_at_Tau / tau;
	double pdR_By = MinMod_Derivative(EM_By, 3, 0, ieta, ix, iy) * B_at_Tau / tau;
	double pdR_Bz = MinMod_Derivative(EM_Bz, 3, 0, ieta, ix, iy) * B_at_Tau / tau;
	double pdR_Ex = MinMod_Derivative(EM_Ex, 3, 0, ieta, ix, iy) * B_at_Tau / tau;
	double pdR_Ey = MinMod_Derivative(EM_Ey, 3, 0, ieta, ix, iy) * B_at_Tau / tau;
	double pdR_Ez = MinMod_Derivative(EM_Ez, 3, 0, ieta, ix, iy) * B_at_Tau / tau;
// EM field in fluid and their derivativation for space time.
	double map_B4t = map_Bz*map_uR
					+ (map_Bx*map_ux + map_By*map_uy)*CoshETA 
					- (map_Ex*map_uy - map_Ey*map_ux)*SinhETA;
	double map_B4R = map_Bz*map_ut
					+ (map_Ex*map_uy - map_Ey*map_ux)*CoshETA 
					- (map_Bx*map_ux + map_By*map_uy)*SinhETA;
	double map_B4x = -map_Ez*map_uy
					+ (map_Bx*map_ut + map_Ey*map_uR)*CoshETA
					+ (map_Bx*map_uR + map_Ey*map_ut)*SinhETA;
	double map_B4y = map_Ez*map_ux
					+ (map_By*map_ut - map_Ex*map_uR)*CoshETA
					+ (map_By*map_uR - map_Ex*map_ut)*SinhETA;
	double map_E4t =  map_Ez*map_uR
					+ (map_Ex*map_ux + map_Ey*map_uy)*CoshETA 
					+ (map_Bx*map_uy - map_By*map_ux)*SinhETA;
	double map_E4R = map_Ez*map_ut
					- (map_Bx*map_uy - map_By*map_ux)*CoshETA 
					- (map_Ex*map_ux + map_Ey*map_uy)*SinhETA;
	double map_E4x = +map_Bz*map_uy
					+ (map_Ex*map_ut - map_By*map_uR)*CoshETA
					+ (map_Ex*map_uR - map_By*map_ut)*SinhETA;
	double map_E4y = -map_Bz*map_ux
					+ (map_Ey*map_ut + map_Bx*map_uR)*CoshETA
					+ (map_Ey*map_uR + map_Bx*map_ut)*SinhETA;
	
	double E_dot_B = - map_Bx*map_Ex - map_By*map_Ey - map_Bz*map_Ez;
	double D_dot_B = (map_Bz*pdt_uR + pdt_Bz*map_uR + map_Bz*map_uR/tau)
			+ (map_Bx*pdt_ux+map_By*pdt_uy + pdt_Bx*map_ux+pdt_By*map_uy)*CoshETA
			- (map_Ex*pdt_uy-map_Ey*pdt_ux + pdt_Ex*map_uy-pdt_Ey*map_ux)*SinhETA
			+ (map_Bz*pdR_ut + pdR_Bz*map_ut)
			+ (map_Ex*pdR_uy-map_Ey*pdR_ux + pdR_Ex*map_uy-pdR_Ey*map_ux)*CoshETA 
			- (map_Bx*pdR_ux+map_By*pdR_uy + pdR_Bx*map_ux+pdR_By*map_uy)*SinhETA
			- (map_Ez*pdx_uy + pdx_Ez*map_uy)
			+ (map_Bx*pdx_ut+map_Ey*pdx_uR + pdx_Bx*map_ut+pdx_Ey*map_uR)*CoshETA
			+ (map_Bx*pdx_uR+map_Ey*pdx_ut + pdx_Bx*map_uR+pdx_Ey*map_ut)*SinhETA
			+ (map_Ez*pdy_ux + pdy_Ez*map_ux)
			+ (map_By*pdy_ut-map_Ex*pdy_uR + pdy_By*map_ut-pdy_Ex*map_uR)*CoshETA
			+ (map_By*pdy_uR-map_Ex*pdy_ut + pdy_By*map_uR-pdy_Ex*map_ut)*SinhETA;

	double D_dot_E = (map_Ez*pdt_uR + pdt_Ez*map_uR + map_Ez*map_uR/tau)
			+ (map_Ex*pdt_ux+map_Ey*pdt_uy + pdt_Ex*map_ux+pdt_Ey*map_uy)*CoshETA
			+ (map_Bx*pdt_uy-map_By*pdt_ux + pdt_Bx*map_uy-pdt_By*map_ux)*SinhETA
			+ (map_Ez*pdR_ut + pdR_Ez*map_ut)
			- (map_Bx*pdR_uy-map_By*pdR_ux + pdR_Bx*map_uy-pdR_By*map_ux)*CoshETA 
			- (map_Ex*pdR_ux+map_Ey*pdR_uy + pdR_Ex*map_ux+pdR_Ey*map_uy)*SinhETA
			+ (map_Bz*pdx_uy + pdx_Bz*map_uy)
			+ (map_Ex*pdx_ut-map_By*pdx_uR + pdx_Ex*map_ut-pdx_By*map_uR)*CoshETA
			+ (map_Ex*pdx_uR-map_By*pdx_ut + pdx_Ex*map_uR-pdx_By*map_ut)*SinhETA
			- (map_Bz*pdy_ux + pdy_Bz*map_ux)
			+ (map_Ey*pdy_ut+map_Bx*pdy_uR + pdy_Ey*map_ut+pdy_Bx*map_uR)*CoshETA
			+ (map_Ey*pdy_uR+map_Bx*pdy_ut + pdy_Ey*map_uR+pdy_Bx*map_ut)*SinhETA;

// Velocity and Vorticity
	double D_dot_u = (pdt_ut + pdR_uR + pdx_ux + pdy_uy + map_ut/tau);
	double map_w4t = 0.0;
	double map_w4R = 0.0;
	double map_w4x = 0.0;
	double map_w4y = 0.0;
	double D_dot_w = 0.0;
// nu.a === \nu^{\mu}_{5/v}d(u_{\mu})
	double NU_v_dot_du, NU_a_dot_du;
	NU_v_dot_du = (map_ut*pdt_ut+map_uR*pdR_ut+map_ux*pdx_ut+map_uy*pdy_ut+map_uR*map_uR/tau)
				 	*(map_NU_v_R*map_uR + map_NU_v_x*map_ux + map_NU_v_y*map_uy)/map_ut
				 -(map_ut*pdt_uR+map_uR*pdR_uR+map_ux*pdx_uR+map_uy*pdy_uR+map_ut*map_uR/tau) * map_NU_v_R
				 -(map_ut*pdt_ux+map_uR*pdR_ux+map_ux*pdx_ux+map_uy*pdy_ux) * map_NU_v_x
				 -(map_ut*pdt_uy+map_uR*pdR_uy+map_ux*pdx_uy+map_uy*pdy_uy) * map_NU_v_y;
	
	NU_a_dot_du = (map_ut*pdt_ut+map_uR*pdR_ut+map_ux*pdx_ut+map_uy*pdy_ut+map_uR*map_uR/tau)
				 	*(map_NU_a_R*map_uR + map_NU_a_x*map_ux + map_NU_a_y*map_uy)/map_ut
				 -(map_ut*pdt_uR+map_uR*pdR_uR+map_ux*pdx_uR+map_uy*pdy_uR+map_ut*map_uR/tau) * map_NU_a_R
				 -(map_ut*pdt_ux+map_uR*pdR_ux+map_ux*pdx_ux+map_uy*pdy_ux) * map_NU_a_x
				 -(map_ut*pdt_uy+map_uR*pdR_uy+map_ux*pdx_uy+map_uy*pdy_uy) * map_NU_a_y;

// Navier-Stokes current
	double u_dot_inv_Tchi_v = (map_ut*pdt_inv_Tchi_v + map_uR*pdR_inv_Tchi_v + map_ux*pdx_inv_Tchi_v + map_uy*pdy_inv_Tchi_v);
	double u_dot_inv_Tchi_a = (map_ut*pdt_inv_Tchi_a + map_uR*pdR_inv_Tchi_a + map_ux*pdx_inv_Tchi_a + map_uy*pdy_inv_Tchi_a);
	double nu_NS_v_x = - map_sigma_v *
		(
			  map_nv * pdx_inv_Tchi_v * map_T
			+ map_nv * map_ux * map_T * u_dot_inv_Tchi_v
			+ map_inv_chi_v * (1+map_ux*map_ux) * pdx_nv
			+ map_inv_chi_v * map_ux * (map_uR*pdR_nv + map_uy*pdy_nv)
		);
	double nu_NS_v_y = - map_sigma_v *
		(
			  map_nv * pdy_inv_Tchi_v * map_T
			+ map_nv * map_uy * map_T * u_dot_inv_Tchi_v
			+ map_inv_chi_v * (1+map_uy*map_uy) * pdy_nv
			+ map_inv_chi_v * map_uy * (map_uR*pdR_nv + map_ux*pdx_nv)
		);
	double nu_NS_v_R = - map_sigma_v *
		(
			  map_nv * pdR_inv_Tchi_v * map_T
			+ map_nv * map_uR * map_T * u_dot_inv_Tchi_v
			+ map_inv_chi_v * (1+map_uR*map_uR) * pdR_nv
			+ map_inv_chi_v * map_uR * (map_ux*pdx_nv + map_uy*pdy_nv)
		);
	double nu_NS_a_x = - map_sigma_a *
		(
			  map_na * pdx_inv_Tchi_a * map_T
			+ map_na * map_ux * map_T * u_dot_inv_Tchi_a
			+ map_inv_chi_a * (1+map_ux*map_ux) * pdx_na
			+ map_inv_chi_a * map_ux * (map_uR*pdR_na + map_uy*pdy_na)
		);
	double nu_NS_a_y = - map_sigma_a *
		(
			  map_na * pdy_inv_Tchi_a * map_T
			+ map_na * map_uy * map_T * u_dot_inv_Tchi_a
			+ map_inv_chi_a * (1+map_uy*map_uy) * pdy_na
			+ map_inv_chi_a * map_uy * (map_uR*pdR_na + map_ux*pdx_na)
		);
	double nu_NS_a_R = - map_sigma_a *
		(
			  map_na * pdR_inv_Tchi_a * map_T
			+ map_na * map_uR * map_T * u_dot_inv_Tchi_a
			+ map_inv_chi_a * (1+map_uR*map_uR) * pdR_na
			+ map_inv_chi_a * map_uR * (map_ux*pdx_na + map_uy*pdy_na)
		);
// Disspative Electric (Ohm) current
	double nu_Ohm_v_x = QCharge * SE * map_sigma_v * map_E4x;
	double nu_Ohm_v_y = QCharge * SE * map_sigma_v * map_E4y;
	double nu_Ohm_v_R = QCharge * SE * map_sigma_v * map_E4R;
	double nu_Ohm_a_x = 0.0;
	double nu_Ohm_a_y = 0.0;
	double nu_Ohm_a_R = 0.0;
// Disspative CME current
	double nu_CME_v_x = SB * QCharge*CXE * map_na * map_inv_chi_a * map_B4x;
	double nu_CME_v_y = SB * QCharge*CXE * map_na * map_inv_chi_a * map_B4y;
	double nu_CME_v_R = SB * QCharge*CXE * map_na * map_inv_chi_a * map_B4R;
	double nu_CME_a_x = SB * QCharge*CXE * (map_nv + map_nB*cBar) * map_inv_chi_v * map_B4x;
	double nu_CME_a_y = SB * QCharge*CXE * (map_nv + map_nB*cBar) * map_inv_chi_v * map_B4y;
	double nu_CME_a_R = SB * QCharge*CXE * (map_nv + map_nB*cBar) * map_inv_chi_v * map_B4R;
// Disspative CVE current
	double nu_CVE_v_x = SW * 2*CXE*map_inv_chi_v*map_inv_chi_a*cBar*map_nB * map_na * map_w4x;
	double nu_CVE_v_y = SW * 2*CXE*map_inv_chi_v*map_inv_chi_a*cBar*map_nB * map_na * map_w4y;
	double nu_CVE_v_R = SW * 2*CXE*map_inv_chi_v*map_inv_chi_a*cBar*map_nB * map_na * map_w4R;
	double nu_CVE_a_x = SW * CXE*map_inv_chi_v*map_inv_chi_v*cBar*map_nB * (2*map_na+cBar*map_nB) * map_w4x 
						+ SW*Nc*map_T*map_T*map_w4x/6.0;
	double nu_CVE_a_y = SW * CXE*map_inv_chi_v*map_inv_chi_v*cBar*map_nB * (2*map_na+cBar*map_nB) * map_w4y
						+ SW*Nc*map_T*map_T*map_w4y/6.0;
	double nu_CVE_a_R = SW * CXE*map_inv_chi_v*map_inv_chi_v*cBar*map_nB * (2*map_na+cBar*map_nB) * map_w4R
						+ SW*Nc*map_T*map_T*map_w4R/6.0;

// the right hand side of conserved equation, not include the time derivative of n and \nu.
	
	double tau_sph_a = tau_axialdamping(map_T, Qmass_current);
	double axial_noise = axial_noise_mean(map_T);
 
 // velocity & acceleration
	double vel_x = map_ux/map_ut;
	double vel_y = map_uy/map_ut;
	double vel_R = map_uR/map_ut;
	double acc_x = (pdt_ux - vel_x * pdt_ut)/map_ut;
	double acc_y = (pdt_uy - vel_y * pdt_ut)/map_ut;
	double acc_R = (pdt_uR - vel_R * pdt_ut + map_uR/tau)/map_ut;
//The right side of the all of conserved equations, but not include the time derivative to \nu^{\mu}_{5/v} and 	n_{5/v}

	double eq_n_v, eq_n_a;
	double Deq_n_v, Deq_n_a;
	double eq_NU_v_x, eq_NU_v_y, eq_NU_v_R, eq_NU_a_x, eq_NU_a_y, eq_NU_a_R;
	double Deq_NU_v_x, Deq_NU_v_y, Deq_NU_v_R, Deq_NU_a_x, Deq_NU_a_y, Deq_NU_a_R;

	double w_dot_dnB = (map_w4t*pdt_nB + map_w4R*pdR_nB + map_w4x*pdx_nB + map_w4y*pdy_nB);
	double B_dot_dnB = (map_B4t*pdt_nB + map_B4R*pdR_nB + map_B4x*pdx_nB + map_B4y*pdy_nB);
	double w_dot_dT  = (map_w4t*pdt_T  + map_w4R*pdR_T  + map_w4x*pdx_T  + map_w4y*pdy_T );
	double B_dot_dT  = (map_B4t*pdt_T  + map_B4R*pdR_T  + map_B4x*pdx_T  + map_B4y*pdy_T );
	double E_dot_dT  = (map_E4t*pdt_T  + map_E4R*pdR_T  + map_E4x*pdx_T  + map_E4y*pdy_T );

	eq_n_v = - map_nv*D_dot_u 
			 - (map_uR*PdR_nv + map_ux*Pdx_nv + map_uy*Pdy_nv)
			 - (map_uR*map_NU_v_R + map_ux*map_NU_v_x + map_uy*map_NU_v_y)/tau/map_ut
			 - (acc_R*map_NU_v_R + acc_x*map_NU_v_x + acc_y*map_NU_v_y)
			 - (pdR_NU_v_R + pdx_NU_v_x + pdy_NU_v_y)
			 - (1-SE) * QCharge * map_sigma_v * D_dot_E
			 - (1-SE) * QCharge * E_dot_dT * dsigmav_dT
			 - (1-SB) * QCharge*CXE * D_dot_B * map_inv_chi_a * map_na
			 - (1-SB) * QCharge*CXE * B_dot_dT * map_d_inv_chi_a * map_na
			 - (1-SB) * QCharge*CXE * map_inv_chi_a * (map_B4R*pdR_na + map_B4x*pdx_na + map_B4y*pdy_na)
			 - (1-SW) * 2*CXE*cBar* (map_nB*map_inv_chi_a*map_inv_chi_v*D_dot_w) * map_na
			 - (1-SW) * 2*CXE*cBar* map_inv_chi_a*map_inv_chi_v * map_na * w_dot_dnB
			 - (1-SW) * 2*CXE*cBar* map_nB * map_na * w_dot_dT * (map_inv_chi_v*map_d_inv_chi_a + map_inv_chi_a*map_d_inv_chi_v)
			 - (1-SW) * 2*CXE*cBar*map_nB*map_inv_chi_a*map_inv_chi_v * (map_w4R*pdR_na+map_w4x*pdx_na+map_w4y*pdy_na);

	eq_n_a = - map_na*D_dot_u 
			 - (map_uR*PdR_na + map_ux*Pdx_na + map_uy*Pdy_na)
			 - (map_uR*map_NU_a_R + map_ux*map_NU_a_x + map_uy*map_NU_a_y)/tau/map_ut
			 - (acc_R*map_NU_a_R + acc_x*map_NU_a_x + acc_y*map_NU_a_y)
			 - (pdR_NU_a_R + pdx_NU_a_x + pdy_NU_a_y)
			 - (1-SB) * QCharge*CXE * D_dot_B * (map_nv+cBar*map_nB) * map_inv_chi_v
			 - (1-SB) * QCharge*CXE * (map_nv+cBar*map_nB) *  B_dot_dT * map_d_inv_chi_v
			 - (1-SB) * QCharge*CXE * map_inv_chi_v * (map_B4R*pdR_nv + map_B4x*pdx_nv + map_B4y*pdy_nv)
			 - (1-SB) * QCharge*CXE * map_inv_chi_v * cBar*B_dot_dnB
			 - (1-SW) * D_dot_w * (Nc*map_T*map_T/6.0)
			 - (1-SW) * w_dot_dT * (Nc*map_T/3.0)
			 - (1-SW) * CXE * cBar*map_nB * D_dot_w * map_inv_chi_v*map_inv_chi_v * (2*map_nv+cBar*map_nB)
			 - (1-SW) * 2*CXE*cBar*w_dot_dnB * map_inv_chi_v*map_inv_chi_v * (map_nv+cBar*map_nB)
			 - (1-SW) * 2*CXE*cBar*map_nB * w_dot_dT * map_inv_chi_v*map_d_inv_chi_v * (2*map_nv+cBar*map_nB)
			 - (1-SW) * 2*CXE*cBar*map_nB*map_inv_chi_v*map_inv_chi_v * (map_w4R*pdR_nv+map_w4x*pdx_nv+map_w4y*pdy_nv)
			 + CXE*QCharge*QCharge * E_dot_B
			 - Switch_Damping * ((map_na - axial_noise) / tau_sph_a);   
			 //include the axial charge fluctuation with the relaxation time tau_sph_a

	eq_NU_v_x = - (map_ux * Pdx_NU_v_x + map_uy * Pdy_NU_v_x + map_uR * PdR_NU_v_x)
			- (map_ux * NU_v_dot_du)
			- (map_NU_v_x / RlxTime_v)
			+ (nu_NS_v_x + nu_Ohm_v_x + nu_CME_v_x + nu_CVE_v_x) / RlxTime_v;
	eq_NU_v_y = - (map_ux * Pdx_NU_v_y + map_uy * Pdy_NU_v_y + map_uR * PdR_NU_v_y)
			- (map_uy * NU_v_dot_du)
			- (map_NU_v_y / RlxTime_v)
			+ (nu_NS_v_y + nu_Ohm_v_y + nu_CME_v_y + nu_CVE_v_y) / RlxTime_v;
	eq_NU_v_R = - (map_ux * Pdx_NU_v_R + map_uy * Pdy_NU_v_R + map_uR * PdR_NU_v_R)
			- (map_uR * NU_v_dot_du)
			- (map_NU_v_R / RlxTime_v)
			+ (nu_NS_v_R + nu_Ohm_v_R + nu_CME_v_R + nu_CVE_v_R) / RlxTime_v;
	eq_NU_a_x = - (map_ux * Pdx_NU_a_x + map_uy * Pdy_NU_a_x + map_uR * PdR_NU_a_x)
			- (map_ux * NU_a_dot_du)
			- (map_NU_a_x / RlxTime_a)
			+ (nu_NS_a_x + nu_Ohm_a_x + nu_CME_a_x + nu_CVE_a_x) / RlxTime_a;
	eq_NU_a_y = - (map_ux * Pdx_NU_a_y + map_uy * Pdy_NU_a_y + map_uR * PdR_NU_a_y)
			- (map_uy * NU_a_dot_du)
			- (map_NU_a_y / RlxTime_a)
			+ (nu_NS_a_y + nu_Ohm_a_y + nu_CME_a_y + nu_CVE_a_y) / RlxTime_a;
	eq_NU_a_R = - (map_ux * Pdx_NU_a_R + map_uy * Pdy_NU_a_R + map_uR * PdR_NU_a_R)
			- (map_uR * NU_a_dot_du)
			- (map_NU_a_R / RlxTime_a)
			+ (nu_NS_a_R + nu_Ohm_a_R + nu_CME_a_R + nu_CVE_a_R) / RlxTime_a;

	Deq_n_v = 0*(DdR_NU_v_R + Ddx_NU_v_x + Ddy_NU_v_y)
			 + (KT_ci(map_uR)*DdR_nv + KT_ci(map_ux)*Ddx_nv + KT_ci(map_uy)*Ddy_nv)
			 + 0*CXE*map_inv_chi_a*
			 	( KT_ci((1-SB)*QCharge*map_B4R + (1-SW)*2*cBar*map_nB*map_inv_chi_v*map_w4R)*DdR_na 
			 	+ KT_ci((1-SB)*QCharge*map_B4x + (1-SW)*2*cBar*map_nB*map_inv_chi_v*map_w4x)*Ddx_na 
			 	+ KT_ci((1-SB)*QCharge*map_B4y + (1-SW)*2*cBar*map_nB*map_inv_chi_v*map_w4y)*Ddy_na);
	Deq_n_a = 0*(DdR_NU_a_R + Ddx_NU_a_x + Ddy_NU_a_y)
			 + (KT_ci(map_uR)*DdR_na + KT_ci(map_ux)*Ddx_na + KT_ci(map_uy)*Ddy_na)
			 + 0*CXE*map_inv_chi_v*
			 	( KT_ci((1-SB)*QCharge*map_B4R + (1-SW)*2*cBar*map_nB*map_inv_chi_v*map_w4R)*DdR_nv 
			 	+ KT_ci((1-SB)*QCharge*map_B4x + (1-SW)*2*cBar*map_nB*map_inv_chi_v*map_w4x)*Ddx_nv 
			 	+ KT_ci((1-SB)*QCharge*map_B4y + (1-SW)*2*cBar*map_nB*map_inv_chi_v*map_w4y)*Ddy_nv);

	Deq_NU_v_x = KT_ci(map_ux)*Ddx_NU_v_x + KT_ci(map_uy)*Ddy_NU_v_x + KT_ci(map_uR)*pdR_NU_v_x
				+ 0*map_sigma_v * map_inv_chi_v / RlxTime_v * 
				((1+map_ux*map_ux)*Ddx_nv + KT_ci(map_ux*map_uR)*DdR_nv + KT_ci(map_ux*map_uy)*Ddy_nv);
	Deq_NU_v_y = KT_ci(map_ux)*Ddx_NU_v_y + KT_ci(map_uy)*Ddy_NU_v_y + KT_ci(map_uR)*pdR_NU_v_y
				+ 0*map_sigma_v * map_inv_chi_v / RlxTime_v * 
				((1+map_uy*map_uy)*Ddy_nv + KT_ci(map_uy*map_uR)*DdR_nv + KT_ci(map_uy*map_ux)*Ddx_nv);
	Deq_NU_v_R = KT_ci(map_ux)*Ddx_NU_v_R + KT_ci(map_uy)*Ddy_NU_v_R + KT_ci(map_uR)*pdR_NU_v_R
				+ 0*map_sigma_v * map_inv_chi_v / RlxTime_v *
				((1+map_uR*map_uR)*DdR_nv + KT_ci(map_uR*map_ux)*Ddx_nv + KT_ci(map_uR*map_uy)*Ddy_nv);
	Deq_NU_a_x = KT_ci(map_ux)*Ddx_NU_a_x + KT_ci(map_uy)*Ddy_NU_a_x + KT_ci(map_uR)*pdR_NU_a_x
				+ 0*map_sigma_a * map_inv_chi_a / RlxTime_a * 
				((1+map_ux*map_ux)*Ddx_na + KT_ci(map_ux*map_uR)*DdR_na + KT_ci(map_ux*map_uy)*Ddy_na);
	Deq_NU_a_y = KT_ci(map_ux)*Ddx_NU_a_y + KT_ci(map_uy)*Ddy_NU_a_y + KT_ci(map_uR)*pdR_NU_a_y
				+ 0*map_sigma_a * map_inv_chi_a / RlxTime_a * 
				((1+map_uy*map_uy)*Ddy_na + KT_ci(map_uy*map_uR)*DdR_na + KT_ci(map_uy*map_ux)*Ddx_na);
	Deq_NU_a_R = KT_ci(map_ux)*Ddx_NU_a_R + KT_ci(map_uy)*Ddy_NU_a_R + KT_ci(map_uR)*pdR_NU_a_R
				+ 0*map_sigma_a * map_inv_chi_a / RlxTime_a *
				((1+map_uR*map_uR)*DdR_na + KT_ci(map_uR*map_ux)*Ddx_na + KT_ci(map_uR*map_uy)*Ddy_na);
	
	double rhs[6]={0.0}, incoe[36]={0.0};
	double DisFactor = 1.0;// Factor of discontinuity
	rhs[0] = eq_n_v + DisFactor*Deq_n_v;
	rhs[1] = eq_n_a + DisFactor*Deq_n_a;
	rhs[2] = eq_NU_v_x + DisFactor*Deq_NU_v_x;
	rhs[3] = eq_NU_v_y + DisFactor*Deq_NU_v_y;
	rhs[4] = eq_NU_a_x + DisFactor*Deq_NU_a_x;
	rhs[5] = eq_NU_a_y + DisFactor*Deq_NU_a_y;
	for (int ii=0; ii<6; ii++){ if (isnan(rhs[ii])){cerr << "\t current is nan @" <<ii<< endl;} }

	double xi = map_B4t;
	double da = map_inv_chi_a * map_sigma_a / RlxTime_a;
	double dv = map_inv_chi_v * map_sigma_v / RlxTime_v;
	double ca = CXE * QCharge * map_inv_chi_a * (1.0-SB);
	double cv = CXE * QCharge * map_inv_chi_v * (1.0-SB);
	
	double ut1 = map_ut, ut2=ut1*ut1;
	
	incoe[0]=da * (-ut1 + 1.0/ut1) + ut1;
	incoe[1]=-ca * xi;
	incoe[2]=vel_x * (da * (1.0 - 1.0/ut2) - 1.0);
	incoe[3]=vel_y * (da * (1.0 - 1.0/ut2) - 1.0);
	incoe[4]=ca * vel_x * xi / ut1;
	incoe[5]=ca * vel_y * xi / ut1;
	
	incoe[6]=-cv * xi;
	incoe[7]=dv * (-ut1 + 1.0/ut1) + ut1;
	incoe[8]=cv * vel_x * xi / ut1;
	incoe[9]=cv * vel_y * xi / ut1;
	incoe[10]=vel_x * (dv * (1.0 - 1.0/ut2) - 1.0);
	incoe[11]=vel_y * (dv * (1.0 - 1.0/ut2) - 1.0);
	
	incoe[12]=dv * map_ux * (da * (ut1 - 1.0/ut1) - ut1);
	incoe[13]=ca * dv * map_ux * xi;
	incoe[14]=dv * map_uy * vel_y * (da * ( 1.0 - 1.0/ut2) - 1.0) + da * (-ut1 + 1.0/ut1) + ut1 - ca * cv * xi * xi / ut1;
	incoe[15]=dv * map_ux * vel_y * (da * (-1.0 + 1.0/ut2) + 1.0);
	incoe[16]=-ca * dv * map_ux * vel_x * xi / ut1;
	incoe[17]=-ca * dv * map_ux * vel_y * xi / ut1;
	
	incoe[18]=dv * map_uy * (da * (ut1 - 1.0/ut1) - ut1);
	incoe[19]=ca * dv * map_uy * xi;
	incoe[20]=dv * map_uy * vel_x * (da * (-1.0 + 1.0/ut2) + 1.0);
	incoe[21]=dv * map_ux * vel_x * (da * (1.0 - 1.0/ut2) - 1.0) + da * (-ut1 + 1.0/ut1) + ut1 - ca * cv * xi * xi / ut1;
	incoe[22]=-ca * dv * map_uy * vel_x * xi / ut1;
	incoe[23]=-ca * dv * map_uy * vel_y * xi / ut1;
	
	incoe[24]=cv * da * map_ux * xi;
	incoe[25]=da * map_ux * (dv * (ut1 - 1.0/ut1) - ut1);
	incoe[26]=-cv * da * map_ux * vel_x * xi / ut1;
	incoe[27]=-cv * da * map_ux * vel_y * xi / ut1;
	incoe[28]=da * map_uy * vel_y * (dv * (1.0 - 1.0/ut2) - 1.0) + dv * (-ut1 + 1.0/ut1) + ut1 - ca * cv * xi * xi / ut1;
	incoe[29]=da * map_ux * vel_y * (dv * (-1.0 + 1.0/ut2) + 1.0);
	
	incoe[30]=cv * da * map_uy * xi;
	incoe[31]=da * map_uy * (dv * (ut1 - 1.0/ut1) - ut1);
	incoe[32]=-cv * da * map_uy * vel_x * xi / ut1;
	incoe[33]=-cv * da * map_uy * vel_y * xi / ut1;
	incoe[34]=da * map_uy * vel_x * (dv * (-1.0 + 1.0/ut2) + 1.0);
	incoe[35]=da * map_ux * vel_x * (dv * (1.0 - 1.0/ut2) - 1.0) + dv * (-ut1 + 1.0/ut1) + ut1 - ca * cv * xi * xi/ut1;
	
	double det_coe = (-ca * cv * xi * xi + da * dv * (ut2 + 1.0/ut2 - 2 ) + (da + dv) * (1 - ut2) + ut2);
	if (fabs(det_coe)<1E-6) { cerr << "\tDeterminant Too Small!" << endl; det_coe = 1; }
	if (isnan(det_coe)) { cerr << "\tDeterminant is nan!" << endl; det_coe = 1; }

	for(int i=0; i<6; i++)
	{
		double tmp=0.0;

		for(int j=0; j<6; j++)
		{
			tmp=tmp+incoe[6*i + j] * rhs[j];
		}
		
		res[i] = tmp/det_coe;
	}
	return 0;
}


int AVFD::Density_Evolution(int flavor)//u: flavor=1, d: flavor=2, s: flavor=3
{
	Create_Charges();
	Initialize(flavor);
	
	string QuarkName[3];
	QuarkName[0] = "u";
	QuarkName[1] = "d";
	QuarkName[2] = "s";

	string FileName;
	ofstream nv_out;
	ofstream na_out;
	if (Switch_Number_Output==1)
	{
		FileName="./NumberDensity_Vector_"+QuarkName[flavor-1]+".dat";
		nv_out.open(FileName.c_str());
		if(!nv_out.is_open())
		{
			cerr << "In current.cpp N_q.dat can not be opend." << endl;
			return 1;
		}
		FileName="./NumberDensity_Axial_"+QuarkName[flavor-1]+".dat";
		na_out.open(FileName.c_str());
		if(!na_out.is_open())
		{
			cerr << "In current.cpp N_q.dat can not be opend." << endl;
			return 1;
		}
	}
	
	//dQuantity_dt used to save the six evolution terms
	double dQuantity_dt[6]={0.0};
	//double dQuantity_dt[8]={0.0};
	for(int itau=0; itau<ntau-1; itau++)
	{
		for(int ieta=0; ieta<neta; ieta++) for(int ix=0; ix<nx; ix++) for(int iy=0; iy<ny; iy++)
		{
			int idx = ieta*nx*ny + ix*ny + iy;
			Get_dQuantity_dt_2plus1(dQuantity_dt, itau, ieta, ix, iy, flavor);
			//Get_dQuantity_dt_3plus1(dQuantity_dt, itau, ix, iy, flavor);
			d_NumberDensity_v[idx] = dt * dQuantity_dt[0];
			d_NumberDensity_a[idx] = dt * dQuantity_dt[1];
			d_NU_v_x[idx] = dt * dQuantity_dt[2];
			d_NU_v_y[idx] = dt * dQuantity_dt[3];
			d_NU_a_x[idx] = dt * dQuantity_dt[4];
			d_NU_a_y[idx] = dt * dQuantity_dt[5];
			//d_NU_v_R[idx] = dt * dQuantity_dt[6];
			//d_NU_a_R[idx] = dt * dQuantity_dt[7];
		}
		
		// Print NumberDensity
		if (Switch_Number_Output==1)
		{
			for(int ieta=0; ieta<neta; ieta++)
			{
				//nv_out << "# i_R = "<< ieta << "\teta = "<< eta0 + ieta*deta << endl;
				//na_out << "# i_R = "<< ieta << "\teta = "<< eta0 + ieta*deta << endl;
				for(int ix=0;ix<nx; ix++) 
				{
					for(int iy=0; iy<ny; iy++)
					{
						int idx = ieta*nx*ny + ix*ny + iy;
						nv_out << NumberDensity_v[idx] <<"\t";
						na_out << NumberDensity_a[idx] <<"\t";
					}
					nv_out << endl;
					na_out << endl;
				}
			}
		}
		
		for(int ieta=0; ieta<neta; ieta++) for(int ix=0; ix<nx; ix++) for(int iy=0; iy<ny; iy++)
		{
			int idx = ieta*nx*ny + ix*ny + iy;
			int idx_t = itau*neta*nx*ny + idx;
			// Assign Chemical Potential
			double quarkchemicalpotential = 0.197*inverse_chi_v(BKG_temperature[idx_t])*NumberDensity_v[idx];
			switch(flavor)
			{
				case 1:
				{
					mu_u[idx_t] = quarkchemicalpotential;
					break;
				}
				case 2:
				{
					mu_d[idx_t] = quarkchemicalpotential;
					break;
				}
				case 3:
				{
					mu_s[idx_t] = quarkchemicalpotential;
					break;
				}
				default:
				{
					break;
				}
			}
			// Evolve the Charge Densities
			NumberDensity_v[idx] += d_NumberDensity_v[idx];
			NumberDensity_a[idx] += d_NumberDensity_a[idx];
			NU_v_x[idx] += d_NU_v_x[idx];
			NU_v_y[idx] += d_NU_v_y[idx];
			//NU_v_R[idx] += d_NU_v_R[idx];
			NU_a_x[idx] += d_NU_a_x[idx];
			NU_a_y[idx] += d_NU_a_y[idx];
			//NU_a_R[idx] += d_NU_a_R[idx];

		}
	}
	cout << "Flavor " << flavor << " Evolves Successfully!" << endl;
	//PrintNumberDensity Close File
	//#ifdef PRINTNUMBERDENSITY
	if (Switch_Number_Output==1)
	{
		nv_out.close();
		na_out.close();
	}
	//#endif
	cout << QuarkName[flavor-1] << "-Quark Evolution Completed!"<< endl;
	Release_Charges();
	return 0;
}
