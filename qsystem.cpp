
// The file contains program to calculate the theoretical value
// of EN, E[S], Blocking probability, Utilization


#include <iostream>
#include "qsystem.h"

using namespace std;
// Construct the queueing system
QSystem::QSystem(double LL, double mm, int KK, double mmu, double rrho){
    L = LL;                      // Number of terminals
    m = mm;                      // Number of CPUs
    K = KK;                      // System capacity
    mu = mmu;                    // Service rate
    rho = rrho;
    lambda = rho * m * mu;       // Arrival rate
    
    frac = 1;
    fracSum = 0; 
    lambdaEff = 0;
    lambdaNP = 0;

    p = new double[K+1];
    lambdaN = new double[K+1];
    muN = new double[K+1];
}

// Expected number of customer
double QSystem::EN_theo()
{ 
   for (int n=1; n<=K; n++){                  // Set mu[n]
    if(n < m){
      muN[n] = n * mu;
    }
    else{
      muN[n] = m * mu;
    }
    lambdaN[n-1] = (L - n + 1) * lambda;      // Set lambda[n]
    if(n==K){lambdaN[n] = (L - n) * lambda;}
    frac *= (lambdaN[n-1] / muN[n]);
    fracSum += frac;
  }
  p[0] = 1 / (1 + fracSum);                  // Calculate P[0]
  for(int n=1; n<=K; n++){         
    p[n] = (lambdaN[n-1]/muN[n]) * p[n-1];   // Calculate P[1] to P[K]
  }
  for(int n=0; n<=K; n++){        
    EN += n * p[n];                          // Theoretical E[N]
  }

   return EN;
}

// Expected service time
double QSystem::ES_theo()
{
  for(int n=0; n<K; n++){
    lambdaEff += lambdaN[n] * p[n]; 
  }
  ES = EN / lambdaEff;             // Theoretical E[S]

	return ES;
}

// Blocking probability
double QSystem::PB_theo()
{

  for(int n=0; n<=K; n++){
    lambdaNP += lambdaN[n] * p[n]; 
  }
  PB = lambdaN[K] * p[K] / lambdaNP;  // Theoretical blocking probability

	return PB;
}

// Utilization
double QSystem::U_theo()
{
  for(int n=0; n<=K; n++){
    if(n<m)
      U += (n/m) * p[n];            // Theoretical Utilization
    else
      U += p[n];
  }

	return U;
}