#include "StdAfx.h"
#include "BS_HEADER.h"

CBlackScholes::CBlackScholes(void) { }
CBlackScholes::~CBlackScholes(void) { }

// Black Scholes prices

// Waissi and Rossin normal cdf approximation
double CBlackScholes::normcdf(double z) {
	if (z <= -7.0)
		return 0.0;
	else if (z >= 7.0)
		return 1.0;
	else {
		double pi = 3.141592653589793;
		double b1 = -0.0004406;
		double b2 =  0.0418198;
		double b3 =  0.9;
		return 1.0 / (1.0 + exp(-sqrt(pi)*(b1*pow(z,5.0) + b2*pow(z,3.0) + b3*z)));
	}
}

// Black Scholes call or put price
double CBlackScholes::BSPrice(double S,double K,double r,double q,double v,double T,char PutCall) {
	double d1 = (log(S/K) + (r-q+v*v/2.0)*T)/v/sqrt(T);
	double d2 = d1 - v*sqrt(T);
	double BSCall = S*exp(-q*T)*normcdf(d1) - K*exp(-r*T)*normcdf(d2);
	if (PutCall=='C')
		return BSCall;
	else
		return BSCall - S*exp(-q*T) + K*exp(-r*T);
}

