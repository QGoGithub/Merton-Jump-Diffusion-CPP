// Merton Jump-Diffusion price by simulation
// by Fabrice Douglas Rouah, FRouah.com and Volopta.com

#include "StdAfx.h"
#include "MJD_sim.h"

// PutCall = 'P'ut or 'C'
// S0 = spot price
// K  = strike price
// rf = risk free rate
// q  = dividend yield
// sigma = volatillity
// T = maturity
// lambdaJ = jump frequency
// muJ     = jump mean parameter
// sigmaJ  = jump volatility parameter
// NT = number of time steps
// NS = number of stock price paths

CMertonJDsim::CMertonJDsim(void) {}
CMertonJDsim::~CMertonJDsim(void) {}

// Merton (1976) jump diffusion by simulation
double CMertonJDsim::JDsim(char PutCall,double S0,double K,double rf,double q,double sigma,double T,double lambdaJ,double muJ,double sigmaJ,int NT,int NS)
{
	// Time increment
	double dt = T/NT;

	// Random seed
	srand(time(NULL));

	// Random number generator and set the seed
	mt19937_64 rng;
	rng.seed(time(NULL));

	// Define the distributions
	poisson_distribution<double> poissrnd(lambdaJ*dt);
	normal_distribution<double> N01(0.0,1.0);
	normal_distribution<double> Nus(muJ - 0.5*sigmaJ*sigmaJ,sigmaJ);

	// Expected value of k, and drift term
	double kappa = exp(muJ) - 1.0;
	double drift = rf - q - lambdaJ*kappa - 0.5*sigma*sigma;

	// Initialize the stock price paths and the payoff
	double Payoff = 0;
	vector<vector<double> > S(NT,vector<double> (NS));

	// Perform the simulation
	for (int s=0; s<NS; s++) {
		S[0][s] = S0;
		for (int t=1; t<NT; t++) {
			double J = 0.0;
			if (lambdaJ != 0.0) {
				int Nt = poissrnd(rng);
				if (Nt > 0)
					for (int i=0; i<Nt; i++)
						J += Nus(rng);
			}
			double Z = N01(rng);
			S[t][s] = S[t-1][s]*exp(drift*dt + sigma*sqrt(dt)*Z + J);
		}
		// Calculate the payoffs
		if (PutCall == 'C')
			Payoff = Payoff + max(S[NT-1][s] - K, 0.0);
		else if (PutCall =='P')
			Payoff = Payoff + max(K - S[NT-1][s], 0.0);
	}

	return exp(-rf*T)*(Payoff/NS);
}



