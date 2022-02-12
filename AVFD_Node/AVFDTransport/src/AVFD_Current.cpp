#define n_inf 1E-9 //bound of density

//Tables: multi-dimensional array would be an issue when using cuda
//we will use X[ntau*nx*ny] to replace X[ntau][nx][ny], and X[itau][ix][iy]=X[itau*nx*ny+ix*ny+iy];

AVFD::AVFD(int MaxNtau, double tau_0)
{
	ntau = MaxNtau;
	tau_start = tau_0;
	nx = 261;
	ny = 261;
	neta = 1;
	dt = 0.02;
	dx = 0.1;
	dy = 0.1;
	deta = 0.01;
	x0 = -0.5*(nx-1)*dx;
	y0 = -0.5*(ny-1)*dy;
	eta0 = -0.5*(neta-1)*deta;
	SB = 0.0;
	SE = 1.0;
	SW = 0.0;
	Switch_Damping = 1;
}

AVFD::~AVFD()
{
}

// Initializing the Charge Distribution & NS Current
void AVFD::Initialize(int flavor)
{
	double NV_fraction, NA_fraction, CV_fraction, CA_fraction;
	double QCharge;
	switch(flavor)
	{
		case 1:
		{
			QCharge = 0.66666667;
			NV_fraction = NV_U_fraction;
			NA_fraction = NA_U_fraction;
			CV_fraction = CV_U_fraction;
			CA_fraction = CA_U_fraction;
			break;
		}
		case 2:
		{
			QCharge = -0.3333333;
			NV_fraction = NV_D_fraction;
			NA_fraction = NA_D_fraction;
			CV_fraction = CV_D_fraction;
			CA_fraction = CA_D_fraction;
			break;
		}
		case 3:
		{
			QCharge = -0.3333333;
			NV_fraction = NV_S_fraction;
			NA_fraction = NA_S_fraction;
			CV_fraction = CV_S_fraction;
			CA_fraction = CA_S_fraction;
			break;
		}
		default:
		{
			NV_fraction = 0.0;
			NA_fraction = 0.0;
			CV_fraction = 0.0;
			CA_fraction = 0.0;
			break;
		}
	}

	ifstream nain;
	if (Switch_Read_NA==1)
	{
		nain.open("./NADistribution.dat");
		if (!nain.is_open())
		{
			cerr << "Failed to open file: " << "./NADistribution.dat" << endl; 
			return;
		}
	}

	for(int ieta=0; ieta<neta; ieta++) for(int ix=0; ix<nx; ix++) for(int iy=0; iy<ny; iy++)
	{
		int idx = ieta*nx*ny+ix*ny+iy;
		double x = ix*dx + x0;
		double y = iy*dy + y0;
		double eta = ieta*deta + eta0;
		double temperature = BKG_temperature[idx];
		// Vector & Axial Number Density
		NumberDensity_v[idx] = entropy_density(temperature) * ( NV_fraction + nv_multipole(flavor,x,y) );

		if (Switch_Read_NA==1)
		{
			double eta_buffer, x_buffer, y_buffer, na_buffer;
			nain >> x_buffer >> y_buffer >> na_buffer;
			//nain >> eta_buffer >> x_buffer >> y_buffer >> na_buffer;
			NumberDensity_a[idx] = na_buffer;
		}
		else
		{
			NumberDensity_a[idx] = entropy_density(temperature) * ( NA_fraction + na_multipole(flavor,x,y) );
		}

		double muv = inverse_chi_v(temperature) * NumberDensity_v[idx];
		double mua = inverse_chi_a(temperature) * NumberDensity_a[idx];
		// NavierStokes Current
		NU_v_x[idx] = 0.0;
		NU_v_y[idx] = CV_fraction * entropy_density(temperature);
		NU_v_R[idx] = 0.0;
		NU_a_x[idx] = 0.0;
		NU_a_y[idx] = CA_fraction * entropy_density(temperature);
		NU_a_R[idx] = 0.0;
	}

	if (Switch_Read_NA==1)
	{
		nain.close();
		cout << "EbE Flavor " << flavor << " Initialized Successfully!" << endl;
	}
	else
	{
		cout << "Smooth Flavor " << flavor << " Initialized Successfully!" << endl;
	}
	return;
}

void AVFD::Create_Fields()
{
	BKG_ut = (double *) calloc (ntau*neta*nx*ny, sizeof(double));
	BKG_ux = (double *) calloc (ntau*neta*nx*ny, sizeof(double));
	BKG_uy = (double *) calloc (ntau*neta*nx*ny, sizeof(double));
	BKG_uR = (double *) calloc (ntau*neta*nx*ny, sizeof(double));
	BKG_nB = (double *) calloc (ntau*neta*nx*ny, sizeof(double));
	BKG_temperature = (double *) calloc (ntau*neta*nx*ny, sizeof(double));
	EM_Bx = (double *) calloc (neta*nx*ny, sizeof(double));
	EM_By = (double *) calloc (neta*nx*ny, sizeof(double));
	EM_Bz = (double *) calloc (neta*nx*ny, sizeof(double));
	EM_Ex = (double *) calloc (neta*nx*ny, sizeof(double));
	EM_Ey = (double *) calloc (neta*nx*ny, sizeof(double));
	EM_Ez = (double *) calloc (neta*nx*ny, sizeof(double));
	mu_u = (float *) calloc (ntau*neta*nx*ny, sizeof(float));
	mu_d = (float *) calloc (ntau*neta*nx*ny, sizeof(float));
	mu_s = (float *) calloc (ntau*neta*nx*ny, sizeof(float));
	cout << "BackGround Profile Generated Successfully!" << endl;
}

void AVFD::Release_Fields()
{
	free(BKG_ut);
	free(BKG_ux);
	free(BKG_uy);
	free(BKG_uR);
	free(BKG_nB);
	free(BKG_temperature);
	free(EM_Bx);
	free(EM_By);
	free(EM_Bz);
	free(EM_Ex);
	free(EM_Ey);
	free(EM_Ez);
	free(mu_u);
	free(mu_d);
	free(mu_s);
	cout << "BackGround Profile Released Successfully!" << endl;
}

void AVFD::Create_Charges()
{
	NumberDensity_v = (double *) calloc (neta*nx*ny, sizeof(double));
	NumberDensity_a = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NumberDensity_v = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NumberDensity_a = (double *) calloc (neta*nx*ny, sizeof(double));
	NU_v_x = (double *) calloc (neta*nx*ny, sizeof(double));
	NU_v_y = (double *) calloc (neta*nx*ny, sizeof(double));
	NU_v_R = (double *) calloc (neta*nx*ny, sizeof(double));
	NU_a_x = (double *) calloc (neta*nx*ny, sizeof(double));
	NU_a_y = (double *) calloc (neta*nx*ny, sizeof(double));
	NU_a_R = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NU_v_x = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NU_v_y = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NU_v_R = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NU_a_x = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NU_a_y = (double *) calloc (neta*nx*ny, sizeof(double));
	d_NU_a_R = (double *) calloc (neta*nx*ny, sizeof(double));
	cout << "Current Profile Generated Successfully!" << endl;
	return;
}

void AVFD::Release_Charges()
{
	free(NumberDensity_v);
	free(NumberDensity_a);
	free(d_NumberDensity_v);
	free(d_NumberDensity_a);
	free(NU_v_x);
	free(NU_v_y);
	free(NU_v_R);
	free(NU_a_x);
	free(NU_a_y);
	free(NU_a_R);
	free(d_NU_v_x);
	free(d_NU_v_y);
	free(d_NU_v_R);
	free(d_NU_a_x);
	free(d_NU_a_y);
	free(d_NU_a_R);
	cout << "Current Profile Released Successfully!" << endl;
	return;
}

void AVFD::PrintFOChemicalPotential(int FO_length)
{
	
	// Geometric Parameters Begin
	float start_tau = tau_start;
	float start_x = -0.5*(nx-1)*dx;
	float start_y = -0.5*(ny-1)*dy;
	// Geometric Parameters End
	
	// read freeze-out surface
	ifstream surface_in;
	surface_in.open("./surface.dat");
	if(!surface_in.is_open())
	{
		cerr << "File Not Found! surface.dat can not be opend." << endl;
		return;
	}
	// print mu_u,d,s @ freeze-out surface into surface_mu.dat
	ofstream surface_mu_out;
	surface_mu_out.open("./surface_mu.dat");
	if(!surface_mu_out.is_open())
	{
		cerr << "File Not Found! surface_mu.dat can not be opend." << endl;
		return;
	}
	// read, interpolate, and print
	for(int ifo=0; ifo<FO_length; ifo++)
	{
		float cache=0.0;
		float fo_x=0.0, fo_y=0.0, fo_tau=0.0;
		surface_in >> cache >> fo_tau >> fo_x >> fo_y >> cache >> cache >> cache;
		
		int jtau=(int)floor((fo_tau-start_tau)/dt);
		int jx=(int)floor((fo_x-start_x)/dx);
		int jy=(int)floor((fo_y-start_y)/dy);
		
		float delta_tau=fo_tau-start_tau-jtau*dt;
		float delta_x=fo_x-start_x-jx*dx;
		float delta_y=fo_y-start_y-jy*dy;
		
		// chemical potential for u, d & s quark
		// using linear interpolation
		float fo_muu=0.0, fo_mud=0.0, fo_mus=0.0;
		if(jtau>=0&&jtau<ntau-1&&jx>=0&&jx<nx-1&&jy>=0&&jy<ny-1)
		{
			fo_muu=mu_u[jtau*nx*ny+jx*ny+jy]
			+delta_tau*(mu_u[(jtau+1)*nx*ny+jx*ny+jy]-mu_u[jtau*nx*ny+jx*ny+jy])/dt
			+delta_x*(mu_u[jtau*nx*ny+(jx+1)*ny+jy]-mu_u[jtau*nx*ny+jx*ny+jy])/dx
			+delta_y*(mu_u[jtau*nx*ny+jx*ny+jy+1]-mu_u[jtau*nx*ny+jx*ny+jy])/dy;
			
			fo_mud=mu_d[jtau*nx*ny+jx*ny+jy]
			+delta_tau*(mu_d[(jtau+1)*nx*ny+jx*ny+jy]-mu_d[jtau*nx*ny+jx*ny+jy])/dt
			+delta_x*(mu_d[jtau*nx*ny+(jx+1)*ny+jy]-mu_d[jtau*nx*ny+jx*ny+jy])/dx
			+delta_y*(mu_d[jtau*nx*ny+jx*ny+jy+1]-mu_d[jtau*nx*ny+jx*ny+jy])/dy;
			
			fo_mus=mu_s[jtau*nx*ny+jx*ny+jy]
			+delta_tau*(mu_s[(jtau+1)*nx*ny+jx*ny+jy]-mu_s[jtau*nx*ny+jx*ny+jy])/dt
			+delta_x*(mu_s[jtau*nx*ny+(jx+1)*ny+jy]-mu_s[jtau*nx*ny+jx*ny+jy])/dx
			+delta_y*(mu_s[jtau*nx*ny+jx*ny+jy+1]-mu_s[jtau*nx*ny+jx*ny+jy])/dy;
		}
		else
		{
			fo_muu=0.0;
			fo_mud=0.0;
			fo_mus=0.0;
		}
		double mumax = 0.1;
		if (isnan(fo_muu)) { fo_muu = 0.0; }
		if (isnan(fo_mud)) { fo_mud = 0.0; }
		if (isnan(fo_mus)) { fo_mus = 0.0; }
		if (fo_muu>mumax) { fo_muu = mumax; }
		if (fo_mud>mumax) { fo_mud = mumax; }
		if (fo_mus>mumax) { fo_mus = mumax; }
		if (fo_muu<-mumax) { fo_muu = -mumax; }
		if (fo_mud<-mumax) { fo_mud = -mumax; }
		if (fo_mus<-mumax) { fo_mus = -mumax; }
		// print mu_u,d,s @ freeze-out surface into surface_mu.dat
		surface_mu_out << fo_muu <<"\t"<< fo_mud <<"\t"<< fo_mus << endl;
	}
	surface_in.close();
	surface_mu_out.close();
	return;
}


