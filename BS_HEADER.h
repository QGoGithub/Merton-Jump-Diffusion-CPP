#pragma once
#include <math.h>
#include <complex>
#include <vector>
using namespace std;

class CBlackScholes {
public:
	CBlackScholes(void);
	~CBlackScholes(void);

	// Waissi and Rossin normal cdf approximation
	double CBlackScholes::normcdf(double z);

	// Black Scholes price
	double CBlackScholes::BSPrice(double S,double K,double r,double q,double v,double T,char PutCall);
};

