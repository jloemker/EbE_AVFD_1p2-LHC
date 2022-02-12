// ++++++++++++++++++++++++++++++++++++++++++++++++++ //
//			 Read Hydro & EMField Profile		   //
// ++++++++++++++++++++++++++++++++++++++++++++++++++ //

void AVFD::Read_VISHNU_Hydro()
{
	ifstream vishnu_hydro_in;
	vishnu_hydro_in.open("./OSCAR2008H.dat");
	if(!vishnu_hydro_in.is_open())
	{
		cerr << "File Not Found: OSCAR2008H.dat" << endl;
		return;
	}
	double temperature, vx, vy;
	double T_max, gamma_max;
	for(int itau=0; itau<ntau; itau++)
	{
		for(int ix=0; ix<nx; ix++)
		{
			for(int iy=0; iy<ny; iy++)
			{
				vishnu_hydro_in >> temperature >> vx >> vy;
				// 1+2 Velocity Field
				double gamma=1.0/sqrt(1-(vx*vx+vy*vy)*0.999);
				if (isnan(gamma)) {cerr << "Error! gamma nan" << endl; return;}
				if (gamma > gamma_max) { gamma_max = gamma; }
				if (temperature > T_max) { T_max = temperature; }
				// 1+2 Velocity fields
				BKG_ut[itau*nx*ny+ix*ny+iy]=gamma;
				BKG_ux[itau*nx*ny+ix*ny+iy]=vx*gamma;
				BKG_uy[itau*nx*ny+ix*ny+iy]=vy*gamma;
				BKG_temperature[itau*nx*ny+ix*ny+iy]=temperature/0.197;// to convert GeV to fm^-1
				BKG_uR[itau*nx*ny+ix*ny+iy] = 0;
				BKG_nB[itau*nx*ny+ix*ny+iy] = 0;
			}
		}
	}
	vishnu_hydro_in.close();
	cout << "VISHNU Hydro Profile Read Successfully! Max_T = " << T_max << " GeV, Max_u0 = " << gamma_max << endl;
}

void AVFD::Read_MUSIC_Hydro()
{
	ifstream music_hydro_in;
	music_hydro_in.open("./evolution_yxeta.dat");
	if(!music_hydro_in.is_open())
	{
		cerr << "File Not Found: evolution_yxeta.dat" << endl;
		return;
	}
	double tauin, temperature, vx, vy, veta;
	int ix_in, iy_in;
	double tau_in_min = 10.0;
	double tau_in_max = 0.0;
	for(int itau=0; itau<ntau; itau++)
	{
		for(int ix=0; ix<nx; ix++)
		{
			for(int iy=0; iy<ny; iy++)
			{
				stringstream ssin;
				string hydro_profile_line;
				getline(music_hydro_in, hydro_profile_line);
				ssin << hydro_profile_line;
				ssin >> tauin >> ix_in >> iy_in >> temperature >> vx >> vy >> veta;
				if (tauin < tau_in_min) { tau_in_min = tauin; }
				if (tauin > tau_in_max) { tau_in_max = tauin; }
				if ((ix_in!=ix)||(iy_in!=iy)) { cerr << "Wrong Grid Read in MUSIC" << endl; return;}
				double gamma=1.0/sqrt(1-(vx*vx+vy*vy)*0.999);
				// 1+2 Velocity Field
				BKG_ut[itau*nx*ny+ix*ny+iy]=gamma;
				BKG_ux[itau*nx*ny+ix*ny+iy]=vx*gamma;
				BKG_uy[itau*nx*ny+ix*ny+iy]=vy*gamma;
				//BKG_uR[itau*nx*ny+ix*ny+iy]=veta;
				BKG_uR[itau*nx*ny+ix*ny+iy] = 0;
				BKG_nB[itau*nx*ny+ix*ny+iy] = 0;
				BKG_temperature[itau*nx*ny+ix*ny+iy]=temperature/0.197;// to convert GeV to fm^-1
			}
		}
	}
	music_hydro_in.close();
	tau_start = tau_in_min;
	cout << "MUSIC 2+1 Hydro Profile Read Successfully!" << endl;
}

void Convert_FO_Surface_MUSIC_2_AVFD(string inputDir, string outputDir, int *value_int, double *value_double)
{
	string inputFileName, outputFileName1, outputFileName2;
	inputFileName = inputDir + "/surface_MUSIC2plus1.dat";
	outputFileName1 = outputDir + "/surface.dat";
	outputFileName2 = outputDir + "/decdat2.dat";
	ifstream fin(inputFileName.c_str());
	ofstream sout(outputFileName1.c_str());
	ofstream decout(outputFileName2.c_str());
	double tau0, rho0, tau, xpt, ypt, eta, da0, da1, da2, da3, u0, u1, u2, u3, vx, vy;
	double Edec, Tdec, Sdec, Pdec, muB, muS, Bn;
	double pi00, pi01, pi02, pi03, pi11, pi12, pi13, pi22, pi23, pi33, bulkPi;
	string file_line;
	int FO_length = 0;
	double tau_min = 1.0;
	double tau_max = 0.6;
	while (getline(fin,file_line))
	{
		FO_length += 1;
		stringstream ss;
		ss << file_line;
		ss >> tau >> xpt >> ypt >> eta;
		ss >> da0 >> da1 >> da2 >> da3;
		ss >> u0 >> u1 >> u2 >> u3;
		ss >> Edec >> Tdec >> muB >> Sdec;
		ss >> pi00 >> pi01 >> pi02 >> pi03;
		ss >> pi11 >> pi12 >> pi13;
		ss >> pi22 >> pi23 >> pi33;
		ss >> bulkPi;

		tau0 = 0.1*round(10*tau)-0.02;
		rho0 = sqrt(xpt*xpt+ypt*ypt);
		vx = u1/u0;
		vy = u2/u0;

		Edec *= 0.197;
		Tdec *= 0.197;
		muB  *= 0.197;
		pi00 *= 0.197;
		pi01 *= 0.197;
		pi02 *= 0.197;
		pi03 *= 0.197;
		pi11 *= 0.197;
		pi12 *= 0.197;
		pi13 *= 0.197;
		pi22 *= 0.197;
		pi23 *= 0.197;
		pi33 *= 0.197;
		bulkPi *= 0.197;

		muS = 0.0;
		Bn = 0.0;
		Pdec = Sdec*Tdec - Edec;
		double EPSILON = 1.0E-10;
		if (tau0 < EPSILON && tau0 > -EPSILON) { tau0 = 0.0; }
		if (tau  < EPSILON && tau  > -EPSILON) { tau  = 0.0; }
		if (xpt  < EPSILON && xpt  > -EPSILON) { xpt  = 0.0; }
		if (ypt  < EPSILON && ypt  > -EPSILON) { ypt  = 0.0; }
		if (rho0 < EPSILON && rho0 > -EPSILON) { rho0 = 0.0; }
		if (da0  < EPSILON && da0  > -EPSILON) { da0  = 0.0; }
		if (da1  < EPSILON && da1  > -EPSILON) { da1  = 0.0; }
		if (da2  < EPSILON && da2  > -EPSILON) { da2  = 0.0; }
		if (vx   < EPSILON && vx   > -EPSILON) { vx   = 0.0; }
		if (vy   < EPSILON && vy   > -EPSILON) { vy   = 0.0; }
		if (Edec < EPSILON && Edec > -EPSILON) { Edec = 0.0; }
		if (Tdec < EPSILON && Tdec > -EPSILON) { Tdec = 0.0; }
		if (Pdec < EPSILON && Pdec > -EPSILON) { Pdec = 0.0; }
		if (muB  < EPSILON && muB  > -EPSILON) { muB  = 0.0; }
		if (muS  < EPSILON && muS  > -EPSILON) { muS  = 0.0; }
		if (pi33 < EPSILON && pi33 > -EPSILON) { pi33 = 0.0; }
		if (pi00 < EPSILON && pi00 > -EPSILON) { pi00 = 0.0; }
		if (pi01 < EPSILON && pi01 > -EPSILON) { pi01 = 0.0; }
		if (pi02 < EPSILON && pi02 > -EPSILON) { pi02 = 0.0; }
		if (pi11 < EPSILON && pi11 > -EPSILON) { pi11 = 0.0; }
		if (pi12 < EPSILON && pi12 > -EPSILON) { pi12 = 0.0; }
		if (pi22 < EPSILON && pi22 > -EPSILON) { pi22 = 0.0; }
		if (bulkPi<EPSILON && bulkPi>-EPSILON) {bulkPi= 0.0; }

		// OutPut
		sout << tau0 <<"\t"<< tau <<"\t"<< xpt <<"\t"<< ypt <<"\t"<< rho0 <<"\t"<< 54.0 <<"\t"<< 0.050 << endl;
		decout << tau <<"\t"<< da0 <<"\t"<< da1 <<"\t"<< da2 <<"\t"<< vx <<"\t"<< vy <<"\t";
		decout << Edec <<"\t"<< Bn <<"\t"<< Tdec <<"\t"<< muB <<"\t"<< muS <<"\t"<< Pdec <<"\t";
		decout << pi33 <<"\t"<< pi00 <<"\t"<< pi01 <<"\t"<< pi02 <<"\t"<< pi11 <<"\t"<< pi12  <<"\t"<< pi22 <<"\t"<< bulkPi << endl;

		// Max and Min
		if (tau > tau_max) { tau_max = tau; }
		if (tau < tau_min) { tau_min = tau; }
	}
	fin.close();
	sout.close();
	decout.close();
	tau_min += 0.02;
	tau_min = 0.1*round(tau_min*10);
	int ntau = floor((tau_max-tau_min)/0.02);
	value_int[0] = FO_length;
	value_int[1] = ntau;
	value_double[0] = tau_min;
	value_double[1] = tau_max;
	cout <<"We find ntau = "<< ntau <<", tau = [ " << tau_min <<" , "<< tau_max <<" ]." << endl;
	return;
}

void Count_VISHNU_FO_Surface(string inputDir, int *value_int, double *value_double)
{
	string inputFileName, outputFileName1, outputFileName2;
	inputFileName = inputDir + "/surface.dat";
	ifstream fin(inputFileName.c_str());
	double tau0, tau, buffer;
	string file_line;
	int FO_length = 0;
	double tau_min = 1.0;
	double tau_max = 0.6;
	while (getline(fin,file_line))
	{
		FO_length += 1;
		stringstream ss;
		ss << file_line;
		ss >> tau0 >> tau >> buffer >> buffer >> buffer >> buffer >> buffer;
		// Max and Min
		if (tau > tau_max) { tau_max = tau; }
		if (tau < tau_min) { tau_min = tau; }
	}
	fin.close();
	tau_min += 0.05;
	tau_min = 0.1*round(tau_min*10);
	int ntau = floor((tau_max-tau_min)/0.02);
	value_int[0] = FO_length;
	value_int[1] = ntau;
	value_double[0] = tau_min;
	value_double[1] = tau_max;
	cout <<"We find ntau = "<< ntau <<", tau = [ " << tau_min <<" , "<< tau_max <<" ]." << endl;
	return;
}

void Get_FO_Surface_Info(string Mode, int *value_int, double *value_double)
{
	if(Mode.compare("VISHNU")==0) { Count_VISHNU_FO_Surface(".",value_int,value_double); return;}
	else if(Mode.compare("MUSIC")==0) { Convert_FO_Surface_MUSIC_2_AVFD(".",".",value_int,value_double); return;}
	else {cerr << "Wrong Hydro Mode!" << endl; return;}
}

//  Read Background Hydro Profile
void AVFD::Read_Hydro(string Mode)
{
	if(Mode.compare("VISHNU")==0) { Read_VISHNU_Hydro(); return;}
	else if(Mode.compare("MUSIC")==0) { Read_MUSIC_Hydro(); return;}
	else {cerr << "Wrong Hydro Mode!" << endl; return;}
}

//  Read/Define temperal&spatial dependent EM fields here.
void AVFD::Read_EMField()
{
	if (Switch_Read_EMField==1)
	{
		ifstream bfin;
		bfin.open("./EMField.dat");
		if (!bfin.is_open())
		{
			cerr << "File Not Found: " << "./EMField.dat" << endl; 
			return;
		}
		double eBy_max = 0;
		for(int ieta=0; ieta<neta; ieta++) for(int ix=0; ix<nx; ix++) for(int iy=0; iy<ny; iy++)
		{
			double x, y, eta, eBx, eBy, eBz, eEx, eEy, eEz;
			//bfin >> eta >> x >> y >> eBx >> eBy >> eBz >> eEx >> eEy >> eEz;
			bfin >> x >> y >> eBx >> eBy >> eBz >> eEx >> eEy >> eEz;
			EM_Bx[ieta*nx*ny+ix*ny+iy] = eBx;
			EM_By[ieta*nx*ny+ix*ny+iy] = eBy;
			EM_Bz[ieta*nx*ny+ix*ny+iy] = 0.0;
			EM_Ex[ieta*nx*ny+ix*ny+iy] = eEx;
			EM_Ey[ieta*nx*ny+ix*ny+iy] = eEy;
			EM_Ez[ieta*nx*ny+ix*ny+iy] = 0.0;
			if (eBy>eBy_max) { eBy_max = eBy; }
		}
		bfin.close();
		cout << "E-by-E EM Field Read Successfully! Max eB_y = " << eBy_max << " fm^(-2)" << endl;
	}
	else
	{
		for(int ieta=0; ieta<neta; ieta++) for(int ix=0; ix<nx; ix++) for(int iy=0; iy<ny; iy++)
		{
			double x = ix*dx + x0;
			double y = iy*dy + y0;
			EM_Bx[ieta*nx*ny+ix*ny+iy] = 0.0;
			EM_By[ieta*nx*ny+ix*ny+iy] = 25*eB0;
			EM_Bz[ieta*nx*ny+ix*ny+iy] = 0.0;
			EM_Ex[ieta*nx*ny+ix*ny+iy] = 0.0;
			EM_Ey[ieta*nx*ny+ix*ny+iy] = 0.0;
			EM_Ez[ieta*nx*ny+ix*ny+iy] = 0.0;
		}
		cout << "Smooth EM Field Generated Successfully!" << endl;
	}
	return;
}
