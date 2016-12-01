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
    Market market = Market();
    for (int i = 1; i < 6; i++) {
        int numberOfAgents = 100*i;
        market.initialzeMarket(numberOfAgents,10);
        int bais = market.calculateEquilibriumState();
        cout << bais << endl;
    }
    return 0;
}

