void Convert_Entropy(string event)
{
	string filename;
	filename ="./data/sd_event_"+event+"_block.dat";
	ifstream fin;
	fin.open(filename.c_str());
	if(!fin.is_open())
	{
		cerr << "Error: Failed to open: " << filename << endl;
		return;
	}
	filename ="./data/MCGlb_entropy_IC_event_"+event+".dat";
	ofstream fout;
	fout.open(filename.c_str());
	if(!fout.is_open())
	{
		cerr << "Error: Failed to open: " << filename << endl;
		return;
	}
	fout << "#Smoothed-MCGlauber. Tau= 0.6	N_eta= 1	N_x= 261	N_y= 261	deta= 0	dx= 0.1	dy= 0.1" << endl;
	for(int ix=0; ix < Nx; ix++) for(int iy = 0; iy < Ny; iy++)
	{
		double x=x0+ix*dx;
		double y=y0+iy*dy;
		double entropy;
		fin >> entropy;
		fout << "0.6\t"<< x << "\t" << y << "\t" << entropy <<"\t1\t0\t0"<< endl;
	}
	fin.close();
	fout.close();
	return;
}