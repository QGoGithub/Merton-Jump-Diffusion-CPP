#pragma once
#include <math.h>

class CMertonJDclosed
{
public:
	CMertonJDclosed(void);
	~CMertonJDclosed(void);

	// Closed form Merton (1976) jump diffusion price
	double CMertonJDclosed::JDclosed(char PutCall,double S0,double K,double r,double q,double sigma,double T,double lambdaJ,double muJ,double sigmaJ,int N);

	// Factorial function
	double CMertonJDclosed::factorial(int n);
};

