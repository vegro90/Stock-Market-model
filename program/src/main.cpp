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

    for (int i = 0; i < 1000000; i++) {
        market.initialzeMarket(500,554);
        int bais = market.calculateEquilibriumState();
        cout << bais << endl;
    }
    return 0;
}

