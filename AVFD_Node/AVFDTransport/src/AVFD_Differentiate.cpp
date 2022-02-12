/*	==================================
 
 Functions in this file are employed
 to avoid numerical unstabilities.
 
 ================================== */

double min3(double x, double y, double z)
{
    if (y>=x&&z>=x) {   return x;   }
    if (x>=y&&z>=y) {   return y;   }
    if (x>=z&&y>=z) {   return z;   }
    return 0.0;
}
double max3(double x, double y, double z)
{
    if (y<=x&&z<=x) {   return x;   }
    if (x<=y&&z<=y) {   return y;   }
    if (x<=z&&y<=z) {   return z;   }
    return 0.0;
}
double min_mod(double step, double f_minus, double f_mid, double f_plus)
{
	double theta = 1.8;
    double db = (f_mid - f_minus)/step;
    double df = (f_plus - f_mid)/step;
    double dm = (db+df)/2.;
    //return dm; // theta -> \infty, equivalently
    if (db*df<=0) { return 0.0; }
    if (db>0) { return min3(theta*db, dm, theta*df); }
    else { return max3(theta*db, dm, theta*df); }    
}

void AVFD::Compute_KT_Derivative(double *Var, int direction, int itau, int ieta, int ix, int iy)
{
	KT_MinMod = 0.0;
	KT_Derivative = 0.0;
	KT_DisContinuity = 0.0;

	if (direction>2) { return; } // no eta dependence
	if (direction==0) { return; }// tau
	int idx_b1, idx_b2, idx, idx_f1, idx_f2;
	double mm_0, mm_f, mm_b;
	double step;
	
	idx = itau*neta*nx*ny + ieta*nx*ny + ix*ny + iy;

	if (direction==1) // x
	{
		if ((ix<2)||(ix>nx-3)) {return;}
		idx_b2 = itau*neta*nx*ny + ieta*nx*ny + (ix-2)*ny + iy;
		idx_b1 = itau*neta*nx*ny + ieta*nx*ny + (ix-1)*ny + iy;
		idx_f1 = itau*neta*nx*ny + ieta*nx*ny + (ix+1)*ny + iy;
		idx_f2 = itau*neta*nx*ny + ieta*nx*ny + (ix+2)*ny + iy;
		step = dx;
	}
	else if (direction==2) // y
	{
		if ((iy<2)||(iy>ny-3)) {return;}
		idx_b2 = itau*neta*nx*ny + ieta*nx*ny + ix*ny + (iy-2);
		idx_b1 = itau*neta*nx*ny + ieta*nx*ny + ix*ny + (iy-1);
		idx_f1 = itau*neta*nx*ny + ieta*nx*ny + ix*ny + (iy+1);
		idx_f2 = itau*neta*nx*ny + ieta*nx*ny + ix*ny + (iy+2);
		step = dy;
	}
	else if (direction==3) // eta
	{
		if ((ieta<2)||(ieta>neta-3)) {return;}
		idx_b2 = itau*neta*nx*ny + (ieta-2)*nx*ny + ix*ny + iy;
		idx_b1 = itau*neta*nx*ny + (ieta-1)*nx*ny + ix*ny + iy;
		idx_f1 = itau*neta*nx*ny + (ieta+1)*nx*ny + ix*ny + iy;
		idx_f2 = itau*neta*nx*ny + (ieta+2)*nx*ny + ix*ny + iy;
		step = deta;
	}
	else { return; }
	mm_b = min_mod(step, Var[idx_b2], Var[idx_b1], Var[idx]);
	mm_0 = min_mod(step, Var[idx_b1], Var[idx], Var[idx_f1]);
	mm_f = min_mod(step, Var[idx], Var[idx_f1], Var[idx_f2]);
	KT_MinMod = mm_0;
	KT_Derivative = 0.5*(Var[idx_f1]-Var[idx_b1])/step - 0.25*(mm_f-2*mm_0+mm_b);
	KT_DisContinuity = 0.5*(Var[idx_f1]-2*Var[idx]+Var[idx_b1])/step - 0.25*(mm_f-mm_b);
	//KT_MinMod = 0.5*(Var[idx_f1]-Var[idx_b1])/step;
	//KT_Derivative = 0.5*(Var[idx_f1]-Var[idx_b1])/step;
	//KT_DisContinuity = 0.0;
	return;
}

double AVFD::MinMod_Derivative(double *Var, int direction, int itau, int ieta, int ix, int iy)
{
	if (direction>2) {return 0.0;} // no eta dependence
	int idx_b3, idx_b2, idx_b1, idx, idx_f1, idx_f2, idx_f3;
	double mm_0, mm_1, mm_2;
	double step;
	
	idx = itau*neta*nx*ny + ieta*nx*ny + ix*ny + iy;

	if (direction==0) // tau
	{
		idx_b3 = (itau-3)*neta*nx*ny + ieta*nx*ny + ix*ny + iy;
		idx_b2 = (itau-2)*neta*nx*ny + ieta*nx*ny + ix*ny + iy;
		idx_b1 = (itau-1)*neta*nx*ny + ieta*nx*ny + ix*ny + iy;
		idx_f1 = (itau+1)*neta*nx*ny + ieta*nx*ny + ix*ny + iy;
		idx_f2 = (itau+2)*neta*nx*ny + ieta*nx*ny + ix*ny + iy;
		idx_f3 = (itau+3)*neta*nx*ny + ieta*nx*ny + ix*ny + iy;
		step = dt;
		if(itau==0)
		{
			mm_1 = min_mod(step, Var[idx], Var[idx_f1], Var[idx_f2]);
			mm_2 = min_mod(step, Var[idx_f1], Var[idx_f2], Var[idx_f3]);
			return (2.0*mm_1-mm_2);
		}
		else if (itau>ntau-2)
		{
			mm_1 = min_mod(step, Var[idx_b2], Var[idx_b1], Var[idx]);
			mm_2 = min_mod(step, Var[idx_b3], Var[idx_b2], Var[idx_b1]);
			return (2.0*mm_1-mm_2);
		}
	}
	else if (direction==1) // x
	{
		if ((ix<1)||(ix>nx-2)) {return 0.0;}
		idx_b1 = itau*neta*nx*ny + ieta*nx*ny + (ix-1)*ny + iy;
		idx_f1 = itau*neta*nx*ny + ieta*nx*ny + (ix+1)*ny + iy;
		step = dx;
	}
	else if (direction==2) // y
	{
		if ((iy<1)||(iy>ny-2)) {return 0.0;}
		idx_b1 = itau*neta*nx*ny + ieta*nx*ny + ix*ny + (iy-1);
		idx_f1 = itau*neta*nx*ny + ieta*nx*ny + ix*ny + (iy+1);
		step = dy;
	}
	else if (direction==3) // eta
	{
		if ((ieta<1)||(ieta>neta-2)) {return 0.0;}
		idx_b1 = itau*neta*nx*ny + (ieta-1)*nx*ny + ix*ny + iy;
		idx_f1 = itau*neta*nx*ny + (ieta+1)*nx*ny + ix*ny + iy;
		step = deta;
	}
	else { return 0.0; }
	mm_0 = min_mod(step, Var[idx_b1], Var[idx], Var[idx_f1]);
	return mm_0;
}
