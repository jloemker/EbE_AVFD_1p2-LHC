//	This file defines the form of the transportation coefficients & external fields,
//	as well as the functions to read the related parameters.


double AVFD::ScanParameter(string parameter_key, double defaulted_value)
{
	string inputname = "./AVFD_Parameter.py";
	string endkey = "End_of_Parameter";
	string para_name = parameter_key;
	double para_val = defaulted_value;

	// pass checking, now read in the parameter file
	string temp_string;
	ifstream input(inputname.c_str());
	if(!input.is_open())
	{
		cerr << "The file named " << inputname << " is absent." << endl;
		return defaulted_value;
	}
	getline(input, temp_string);  // read in the first entry
	int ind = 0;
	while(temp_string.compare(endkey) != 0)  // check whether it is the end of the file
	{
		string para_string;
		stringstream temp_ss(temp_string);
		getline(temp_ss, para_string, '#');  // remove the comments
		int key_position = para_string.find(parameter_key); // Find Position of KeyWord
		if (key_position != std::string::npos) // find the desired parameter
		{
			ind++;
			input.close();
			int delimeter_position = para_string.find(":"); // Find Position of ":"
			para_string.erase(0,delimeter_position+1);
			stringstream para_value_stream(para_string);
			para_value_stream >> para_val;
			return para_val;
		}
		getline(input, temp_string);  // read in the next entry
	}/* while */

	input.close(); // finish read in and close the file

	// the desired parameter is not in the parameter file, then return defaulted value
	if(ind == 0) return defaulted_value;

	// should not cross here !!!
	cerr << "Error in ScanParameter !!!" << endl;
	return defaulted_value;
}

void AVFD::Read_AVFD_Parameter()
{
	//	Initialize
	Switch_Read_NA = (int)ScanParameter("Read N5 From File", 0.0);
	Switch_Read_EMField = (int)ScanParameter("Read EM Field From File", 0.0);
	Switch_Number_Output = (int)ScanParameter("Print Number Density", 0.0);
	Switch_Damping = (int)ScanParameter("Axial Charge Damping", 0.0);
	eB0 = ScanParameter("B Field Strength", 0.08);
	TauB = ScanParameter("B Field LifeTime", 0.6);
	TauV = ScanParameter("Vector Relaxation Time", 0.5);
	TauA = ScanParameter("Axial Relaxation Time", 0.5);
	SigmaV = ScanParameter("Vector Conductivity", 0.3);
	SigmaA = ScanParameter("Axial Conductivity", 0.3);
	NV_U_fraction = ScanParameter("u Vector Charge", 0.00);
	NV_D_fraction = ScanParameter("d Vector Charge", 0.00);
	NV_S_fraction = ScanParameter("s Vector Charge", 0.00);
	NA_U_fraction = ScanParameter("u Axial Charge", 0.00);
	NA_D_fraction = ScanParameter("d Axial Charge", 0.00);
	NA_S_fraction = ScanParameter("s Axial Charge", 0.00);
	CV_U_fraction = ScanParameter("u Vector Current", 0.00);
	CV_D_fraction = ScanParameter("d Vector Current", 0.00);
	CV_S_fraction = ScanParameter("s Vector Current", 0.00);
	CA_U_fraction = ScanParameter("u Axial Current", 0.00);
	CA_D_fraction = ScanParameter("d Axial Current", 0.00);
	CA_S_fraction = ScanParameter("s Axial Current", 0.00);
	E1V_U = ScanParameter("u Vector 1st Eccentricity", 0.00);
	E1V_D = ScanParameter("d Vector 1st Eccentricity", 0.00);
	E1V_S = ScanParameter("s Vector 1st Eccentricity", 0.00);
	E2V_U = ScanParameter("u Vector 2nd Eccentricity", 0.00);
	E2V_D = ScanParameter("d Vector 2nd Eccentricity", 0.00);
	E2V_S = ScanParameter("s Vector 2nd Eccentricity", 0.00);
	E1A_U = ScanParameter("u Axial 1st Eccentricity", 0.00);
	E1A_D = ScanParameter("d Axial 1st Eccentricity", 0.00);
	E1A_S = ScanParameter("s Axial 1st Eccentricity", 0.00);
	E2A_U = ScanParameter("u Axial 2nd Eccentricity", 0.00);
	E2A_D = ScanParameter("d Axial 2nd Eccentricity", 0.00);
	E2A_S = ScanParameter("s Axial 2nd Eccentricity", 0.00);
	// Print Set-Up
	cout << "====================================" << endl;
	cout << "   Anomalous Transport Parameters" << endl;
	cout << "------------------------------------" << endl;
	cout << "  Rlx. CME Ratio:\t" << SB << endl; 
	cout << "  N_axial Damping:\t" << Switch_Damping << " [0=off,1=on]" << endl;
	cout << "  Read Axial Chg:\t" << Switch_Read_NA << " [0=off,1=on]" << endl;
	cout << "  Read E&M Field:\t" << Switch_Read_EMField << " [0=off,1=on]" << endl;
	cout << "  Print N_Density:\t" << Switch_Number_Output << " [0=off,1=on]" << endl;
	cout << "  Initial B field:\t" << eB0 <<" GeV(2)"<< endl;
	cout << "  B field LifeTime:\t" << TauB <<" fm/c"<< endl;
	cout << "  RlxT_V*Tmpt:\t\t" << TauV << endl;
	cout << "  RlxT_A*Tmpt:\t\t" << TauA << endl;
	cout << "  Sigm_V/Tmpt:\t\t" << SigmaV << endl;
	cout << "  Sigm_V/Tmpt:\t\t" << SigmaA << endl;
	cout << "  N_Vu / S:\t\t" << NV_U_fraction << endl;
	cout << "  N_Vd / S:\t\t" << NV_D_fraction << endl;
	cout << "  N_Vs / S:\t\t" << NV_S_fraction << endl;
	cout << "  N_Au / S:\t\t" << NA_U_fraction << endl;
	cout << "  N_Ad / S:\t\t" << NA_D_fraction << endl;
	cout << "  N_As / S:\t\t" << NA_S_fraction << endl;
	cout << "  J_Vu / B mu_A:\t" << CV_U_fraction << endl;
	cout << "  J_Vd / B mu_A:\t" << CV_D_fraction << endl;
	cout << "  J_Vs / B mu_A:\t" << CV_S_fraction << endl;
	cout << "  J_Au / B mu_V:\t" << CA_U_fraction << endl;
	cout << "  J_Ad / B mu_V:\t" << CA_D_fraction << endl;
	cout << "  J_As / B mu_V:\t" << CA_S_fraction << endl;
	cout << "  E1_Vu:\t\t" << E1V_U << endl;
	cout << "  E1_Vd:\t\t" << E1V_D << endl;
	cout << "  E1_Vd:\t\t" << E1V_S << endl;
	cout << "  E2_Vu:\t\t" << E2V_U << endl;
	cout << "  E2_Vd:\t\t" << E2V_D << endl;
	cout << "  E2_Vd:\t\t" << E2V_S << endl;
	cout << "  E1_Au:\t\t" << E1A_U << endl;
	cout << "  E1_Ad:\t\t" << E1A_D << endl;
	cout << "  E1_Ad:\t\t" << E1A_S << endl;
	cout << "  E2_Au:\t\t" << E2A_U << endl;
	cout << "  E2_Ad:\t\t" << E2A_D << endl;
	cout << "  E2_Ad:\t\t" << E2A_S << endl;
	cout << "====================================" << endl;
	return;
}
