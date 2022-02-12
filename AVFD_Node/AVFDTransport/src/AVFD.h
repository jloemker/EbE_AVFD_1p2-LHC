class AVFD
{
private:
	//double CME_Coefficient; // coefficient of anomalous current: Nc \sum_f q_f/(2Pi^2); q_f=1/3, cme=-0.051
	int Switch_Number_Output;
	int Switch_Read_NA;
	int Switch_Read_EMField;
// Controlling the fluctuation Begin
	void PrintFile(const char *FileName, double *Data);
	double KT_Derivative;
	double KT_DisContinuity;
	double KT_MinMod;
	void Compute_KT_Derivative(double *Var, int direction, int itau, int ieta, int ix, int iy);
	double MinMod_Derivative(double *Var, int direction, int itau, int ieta, int ix, int iy);
// Controlling the fluctuation End
// Geometrical Parameters Begin
	int ntau;
	int nx;
	int ny;
	int neta;
	double tau_start;
	double dt;
	double dx;
	double dy;
	double deta;
	double SB;
	double SE;
	double SW;
	double x0;
	double y0;
	double eta0;
// Geometrical Parameters End
// Transportation Parameters Begin
	double eB0;				// initial intensity of B field, in the unit of GeV^2
	double TauB;			// effective life-time for B field, in the unit of fm/c
	double TauV;			// Vector current relaxation time, in the unit of fm/c.
	double TauA;			// Axial  current relaxation time, in the unit of fm/c.
	double SigmaV;			// sigma_v / Temperature.
	double SigmaA;			// sigma_a / Temperature.
	double NV_U_fraction;	// n_{V,U} / EntropyDensity in the initial stage.
	double NV_D_fraction;	// n_{V,D} / EntropyDensity in the initial stage.
	double NV_S_fraction;	// n_{V,S} / EntropyDensity in the initial stage.
	double NA_U_fraction;	// n_{A,U} / EntropyDensity in the initial stage.
	double NA_D_fraction;	// n_{V,D} / EntropyDensity in the initial stage.
	double NA_S_fraction;	// n_{V,S} / EntropyDensity in the initial stage.
	double CV_U_fraction;	// J/mu B in the initial stage.
	double CV_D_fraction;	// J/mu B in the initial stage.
	double CV_S_fraction;	// J/mu B in the initial stage.
	double CA_U_fraction;	// J/mu B in the initial stage.
	double CA_D_fraction;	// J/mu B in the initial stage.
	double CA_S_fraction;	// J/mu B in the initial stage.
	double E1V_U;			// U Vector Charge Eccentricity, E_1
	double E1V_D;			// D Vector Charge Eccentricity, E_1
	double E1V_S;			// S Vector Charge Eccentricity, E_1
	double E2V_U;			// U Vector Charge Eccentricity, E_2
	double E2V_D;			// D Vector Charge Eccentricity, E_2
	double E2V_S;			// S Vector Charge Eccentricity, E_2
	double E1A_U;			// U Axial  Charge Eccentricity, E_1
	double E1A_D;			// D Axial  Charge Eccentricity, E_1
	double E1A_S;			// S Axial  Charge Eccentricity, E_1
	double E2A_U;			// U Axial  Charge Eccentricity, E_2
	double E2A_D;			// D Axial  Charge Eccentricity, E_2
	double E2A_S;			// S Axial  Charge Eccentricity, E_2
// Transportation Parameters End
// Begin Reading Transportation Parameters
	double ScanParameter(string parameter_key, double defaulted_value);
// Finish Reading Transportation Parameters
// Transportation Functions Begin
	double sigma_v(double temperature);
	double sigma_a(double temperature);
	double relaxation_time_v(double temperature);
	double relaxation_time_a(double temperature);
// Transportation Functions End
// Eccentricity of Charge Distribution Begin
	double nv_multipole(int flavor, double x, double y);
	double na_multipole(int flavor, double x, double y);
// Eccentricity of Charge Distribution End
// E&M Fields Begin
	void Read_VISHNU_Hydro();
	void Read_MUSIC_Hydro();
	double B_Tau(double tau);
	double dB_dTau(double tau);
	double *EM_Bx;//initial eB_x, in the lab-frame, in the unit of fm(-2)
	double *EM_By;//initial eB_y, in the lab-frame, in the unit of fm(-2)
	double *EM_Bz;//initial eB_z, in the lab-frame, in the unit of fm(-2)
	double *EM_Ex;//initial eE_x, in the lab-frame, in the unit of fm(-2)
	double *EM_Ey;//initial eE_y, in the lab-frame, in the unit of fm(-2)
	double *EM_Ez;//initial eE_z, in the lab-frame, in the unit of fm(-2)
// E&M Fields End
// Evolution Functions Begin
	int Get_dQuantity_dt_2plus1(double *res, int itau, int ieta, int ix, int iy, int flavor);
	int Get_dQuantity_dt_3plus1(double *res, int itau, int ieta, int ix, int iy, int flavor);
	void Initialize(int flavor);
	void Create_Charges();
	void Release_Charges();
	// BackGround
	double *BKG_ut;
	double *BKG_ux;
	double *BKG_uy;
	double *BKG_uR;
	double *BKG_temperature;
	double *BKG_nB;
	// Chemical Potential
	float *mu_u;
	float *mu_d;
	float *mu_s;
	// Quark Number & Current
	double *NumberDensity_v;
	double *NumberDensity_a;
	double *NU_v_x;
	double *NU_v_y;
	double *NU_v_R;
	double *NU_a_x;
	double *NU_a_y;
	double *NU_a_R;
	double *d_NumberDensity_v;
	double *d_NumberDensity_a;
	double *d_NU_v_x;
	double *d_NU_v_y;
	double *d_NU_v_R;
	double *d_NU_a_x;
	double *d_NU_a_y;
	double *d_NU_a_R;
// Evolution Functions End
// Axial Damping & Noise Begin
	double tau_axialdamping(double temperature, double quark_mass);
	double axial_noise_mean(double temperature);
	double axial_noise_generate(double temperature);
	int Switch_Damping;
// Axial Damping & Noise End
public:
	AVFD(int MaxNtau, double tau_0);
	~AVFD();
	// Begin Reading Transportation Parameters
	void Read_AVFD_Parameter();
	// Finish Reading Transportation Parameters
	// Evolution Functions Begin
	int Density_Evolution(int flavor);
	void Read_Hydro(string mode);
	void Read_EMField();
	void Create_Fields();
	void Release_Fields();
	void PrintFOChemicalPotential(int FO_length);
	// Evolution Functions End
};


