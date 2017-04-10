// Author: Hsin Hua Chen

// Simulates an M/M/m/K queueing system.  The simulation terminates
// once 100000 customers depart from the system.

#include <iostream>
#include "rv.h"
#include "event.h"
#include "qsystem.h"

int main()
{
  using namespace std;
  EventList Elist;                // Create event list
  enum {ARR,DEP};                 // Define the event types

  double L;                       // Number of Termianals
  double m;                       // Number of CPUs
  int    K;                       // Number of System capacity
  
  double rho;                     // rho = lambda / (m * mu)
  double mu;                      // Service rate
  double lambda;                  // Arrival rate
  
  double clock = 0.0;             // System clock
  int N = 0;                      // Number of customers in system
  int Ndep = 0;                   // Number of departures from system
  double EN = 0.0;                // For calculating E[N]
  double U = 0.0;

  int ARRNum = 0;                 // number of Arrival
  int BlockNum = 0;               // number of Block

  int done = 0;                   // End condition satisfied?

  Event* CurrentEvent;

  // ****** Input Setting ******
  cout << "L  : "; cin >> L;
  cout << "m  : "; cin >> m;
  cout << "K  : "; cin >> K;
  cout << "mu : "; cin >> mu;
  cout << "rho: "; cin >> rho;

  lambda = rho * m * mu;

  // ******* Simulation ******* 
  for(int n=0; n<L; n++)
    Elist.insert(clock+exp_rv(lambda),ARR);   // Generate first arrival event

  while (!done)
  {
    CurrentEvent = Elist.get();               // Get next Event from list
    double prev = clock;                      // Store old clock value
    clock=CurrentEvent->time;                 // Update system clock 

    switch (CurrentEvent->type) {
    // Arrival
    case ARR:                                     // If arrival
      EN += N*(clock-prev);                       //   update system statistics      
      if(N < K)                                   //   System has capacity:
      {
        N++;                                      //     update system size
        ARRNum++;                                 //     calculate number of arrival
        if (N <= m){                              //     If there's idle server                                   
          Elist.insert(clock+exp_rv(mu),DEP);     //      generate next departure

          U += (N/m) * (clock-prev);              //      calculate utilization
        }
        else
          U += (clock-prev);                      //      calculate utilization
      }
      else                                        //   System full (block):
      {
        Elist.insert(clock+exp_rv(lambda),ARR);   //     generate next arrival, if applicable     
		BlockNum++;                               //     increment number of block
        U += (clock-prev);                        //     calculate utilization
      }

      break;
    
    // Depature
    case DEP:                                 // If departure
      EN += N*(clock-prev);                   //  update system statistics
      N--;                                    //  decrement system size
      Ndep++;                                 //  increment num. of departures

      if (N >= m) {                           //  If customers waiting in queue and a server is available
        Elist.insert(clock+exp_rv(mu),DEP);   //   generate next departure
        U += (clock-prev);                    // calculate utilization
      }
      else{
        U += (N/m) * (clock-prev);            // calculate utilization
      }
      Elist.insert(clock+exp_rv(lambda),ARR); // generate next arrival
      break;
    }
    delete CurrentEvent;
    if (Ndep > 100000) done=1;        // End condition
  }

  // ****** Theoretical value *****
  QSystem MMmK_queue(L,m,K,mu,rho);

  double EN_theo = MMmK_queue.EN_theo();
  double ES_theo = MMmK_queue.ES_theo();
  double PB_theo = MMmK_queue.PB_theo();
  double U_theo = MMmK_queue.U_theo();

  // ******* OUTPUT *********
  cout << endl;
  cout << "Current number of customers in system    : " << N << endl;
  cout << "Expected number of customers (simulation): " << EN/clock << endl;
  cout << "Expected number of customers (analysis)  : " << EN_theo << endl;

  cout << "Expected service time (simulation)       : " << EN/ARRNum << endl;
  cout << "Expected service time (analysis)         : " << ES_theo << endl;

  cout << "Blocking probability (simulation)        : " << (double)BlockNum / (double)(ARRNum+BlockNum) << endl;
  cout << "Blocking probability (analysis)          : " << PB_theo << endl;

  cout << "Utilization (simulation)                 : " << U/clock << endl;
  cout << "Utilization (analysis)                   : " << U_theo << endl << endl;

}

