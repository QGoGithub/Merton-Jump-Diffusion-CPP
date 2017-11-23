#include "StdAfx.h"
#include "MJDclosed.h"
#include "BS_HEADER.h"

// Closed form solution for the Merton (1976) jump diffusion model
/
CMertonJDclosed::CMertonJDclosed(void) { }
CMertonJDclosed::~CMertonJDclosed(void) { }

// PutCall = 'P'ut or 'C'all
// S0 = spot
// K  = strike
// r  = risk free rate
// q = dividend yield
// sigma = stock return volatility
// T = maturity
// lambdaJ = jump frequency
// muJ     = jump mean
// sigmaJ  = jump volatility
// N = number of terms in the sum

// Closed form Merton (1976) jump diffusion price
double CMertonJDclosed::JDclosed(char PutCall,double S0,double K,double r,double q,double sigma,double T,double lambdaJ,double muJ,double sigmaJ,int N)
{
	CBlackScholes BS;

	// Expected jump value
	double kappa = exp(muJ + 0.5*sigmaJ*sigmaJ) - 1.0;

	// Initialize the price
	double Price = 0.0;
	double sigman,rn,BSPrice,lambda,Probability;
	for (int n=0; n<N; n++) {
		sigman = sqrt(sigma*sigma + n*sigmaJ*sigmaJ/T);
		rn = r - lambdaJ*kappa + n*log(1.0+kappa)/T;
		BSPrice = BS.BSPrice(S0,K,rn,q,sigman,T,PutCall);
		lambda = lambdaJ*(1.0+kappa);
		Probability = exp(-lambda*T)*pow(lambda*T,double(n))/factorial(n);
		Price = Price +  Probability*BSPrice;
	}
	return Price;
}

// Factorial function
double CMertonJDclosed::factorial(int n) {
	if (n==0)
		return 1.0;
	else
		return n*factorial(n-1);
}
