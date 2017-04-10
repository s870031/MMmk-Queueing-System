#ifndef QSYSTEM_H
#define QSYSTEM_H

class QSystem {
  public:
    QSystem(double LL, double mm, int KK, double mmu, double rrho);
    double EN_theo();
    double ES_theo();
    double PB_theo();
    double U_theo();
    double EN;
   	double ES;
   	double PB;
    double U;
  private:
  	double L;
   	double m;
   	int    K;
   	double mu;
   	double rho;
   	double lambda;
   	
   	double* p;
   	double* lambdaN;
   	double* muN;
   	double frac;
    double fracSum; 
    double lambdaEff;
    double lambdaNP;
};

#endif