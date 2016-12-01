//#include "mpi.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <math.h>
#include "market.h"

using namespace std;

ofstream ofile;

int main(int argc, char *argv[]) {
    int numberOfAgents;
    double initialCapital;
    numberOfAgents = 500;
    initialCapital = 1;

    Market market;

    //Initialize market and reach equilibrium
    market.initialzeMarket(numberOfAgents,initialCapital);
    market.calculateEquilibriumState();


    return 0;
}

