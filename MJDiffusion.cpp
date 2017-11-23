// Closed form solution for the Merton (1976) jump diffusion model
// Fabrice Rouah, FRouah.com and Volopta.com

#include "stdafx.h"
#include "MJDclosed.h"
#include "MJD_sim.h"

int main() {

	// Flavor, spot, strike, risk-free rate, dividend,maturity volatility,maturity
	char PutCall = 'C';
	double S0 = 30.0;
	double K  = 30.0;
	double rf = 0.04;
	double q  = 0.0;
	double T  = 0.25;
	double sigma = 0.3;

	// Jump parameters
	double lambdaJ = 0.50;
	double muJ     = 0.05;
	double sigmaJ  = 0.20;

	// Merton price by closed form and by simulation
	// Closed form price
	CMertonJDclosed JD;
	int N = 50;
	double ClosedPrice = JD.JDclosed(PutCall,S0,K,rf,q,sigma,T,lambdaJ,muJ,sigmaJ,N);

	// Number of time steps, number of stock price paths
	int NT = 100;
	int NS = 50000;

	// Simulation price
	CMertonJDsim JDS;
	double SimPrice = JDS.JDsim(PutCall,S0,K,rf,q,sigma,T,lambdaJ,muJ,sigmaJ,NT,NS);

	// Output everything
		printf("Merton (1976) jump diffusion model \n");
		printf("---------------------------------- \n");
		printf("Closed form price %8.4f \n",ClosedPrice);
		printf("Simulation price  %8.4f \n",SimPrice);
		printf("Simulation $error %8.4f \n",ClosedPrice-SimPrice);
		printf("---------------------------------- \n");
}
