// ++++++++++++++++++++++++++++++++++++++++++++++++++ //
// 		AVFD-Independent ThermoDynamic Quantities	  //
// ++++++++++++++++++++++++++++++++++++++++++++++++++ //

double entropy_density(double temperature) // fitted from Lattice
{
	return 6.51357 * temperature * temperature * temperature
	* (1 + 0.31677*temperature + 0.0632002*temperature*temperature
	   + tanh(23.5148*(-0.181422+0.197*temperature)));
} // entropy in the unit of fm(-3), temperature in the unit of fm(-1)

// inverse chi_v (vector charge susceptibility) as a function of temperature
double inverse_chi_v(double temperature) // fitted from Lattice
{
	return 3.44/(0.0025*exp(6.6*temperature)+1)+0.36;
} // in the unit of fm(2)

// inverse chi_a (vector charge susceptibility) as a function of temperature
double inverse_chi_a(double temperature) // fitted from Lattice
{
	return 3.44/(0.0025*exp(6.6*temperature)+1)+0.36;
} // in the unit of fm(2)

// (inverse chi_v) 1st derivative with respect to temperature
double d_inverse_chi_dT_v(double temperature)
{
	double cache=exp(6.6*temperature);
	return -0.05676*cache/pow(0.0025*cache+1.0, 2);
}

// (inverse chi_a) 1st derivative with respect to temperature
double d_inverse_chi_dT_a(double temperature)
{
	double cache=exp(6.6*temperature);
	return -0.05676*cache/pow(0.0025*cache+1.0, 2);
}
