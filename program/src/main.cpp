#include <iostream>
#include <random>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string filename = "histogram.txt";

    long long int cycles = 10e3;
    double startCapotal = 10;
    int Agents = 500;
    double totalCapitol = startCapotal*Agents;

    //Distribute the weath equally to all agents
    double *Agent = new double[Agents];
    for(int i = 0; i<= Agents; i++){
        Agent[i] = startCapotal;
    }
//    for(int j = 0; j<= Agents; j++){
//        cout << Agent[j] << endl;
//    }


    //Setting up histogram vector
    double deltaM = 0.05;
    long long int histLenght = (int) totalCapitol/deltaM;
    int *Histogram = new int[histLenght];
    for(int i = 0; i <= histLenght ; i++) {
        Histogram[i] = 0;
        //cout << Histogram[i] << endl;
    }

    double epsilon, moneyCombined,transaction_i, transaction_j;
    int histogramSpace;

    //Initiate random generator and constants
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomGenerator(0.0,1.0);

    for(int k=0; k<cycles; k++){

        int i = (randomGenerator(gen))*Agents;
        int j = (randomGenerator(gen))*Agents;
        //cout << "initial    " << i << "  " << j << endl;
        if(i != j){
            epsilon = (randomGenerator(gen));
            //cout << epsilon << "    " << i << "   " << j << endl;
            moneyCombined = Agent[i] + Agent[j];
            transaction_i = epsilon*moneyCombined;
            transaction_j = (1-epsilon)*moneyCombined;
            //cout << "pre    " << Agent[i] << "   " << Agent[j] << endl;
            Agent[i] = transaction_i;
            Agent[j] = transaction_j;
            histogramSpace = (int) transaction_i/deltaM;
            Histogram[histogramSpace] += 1;
            histogramSpace = (int) transaction_j/deltaM;
            Histogram[histogramSpace] += 1;
            //cout << Histogram[histogramSpace] << endl;

            //cout << "transaction    " << epsilon*transaction << endl;
            //cout << "post   " << Agent[i] << "   " << Agent[j] << endl;

        }

    }
    //cout << Histogram[histogramSpace] << endl;
    ofstream histFile(filename);
    for (int i = 0; i <= histLenght; i++){
        //cout << Histogram[i] << endl;
        histFile << Histogram[i] << "\n";
    }
    histFile.close();

}
