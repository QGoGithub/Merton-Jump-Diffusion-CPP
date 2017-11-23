#pragma once
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include <iostream>
using namespace std;

class CMertonJDsim {
public:
	CMertonJDsim(void);
	~CMertonJDsim(void);

	// Merton (1976) jump diffusion by simulation
	double JDsim(char PutCall,double S0,double K,double rf,double q,double sigma,double T,double lambdaJ,double muJ,double sigmaJ,int NT,int NS);

};

