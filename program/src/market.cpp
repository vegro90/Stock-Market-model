#include "market.h"

Market::Market() {
    m_numberOfAgents = 0;
    m_averageCapital = 0;
    m_marketCapital = 0;
    m_agentSavingFactor = 0;
    m_agentSpendingFactor = 1;
    m_distributionResolution = 0.01;
}

Market::Market(int numberOfAgents, double agentCapital) {
    m_numberOfAgents = numberOfAgents;
    m_averageCapital = agentCapital;
    m_marketCapital = m_numberOfAgents * m_averageCapital;
    m_agentSavingFactor = 0;
    m_agentSpendingFactor = 1;
}

void Market::initialzeMarket(int numberOfAgents, double agentCapital) {
    m_numberOfAgents = numberOfAgents;
    m_averageCapital = agentCapital;
    m_marketCapital = m_numberOfAgents * m_averageCapital;

    m_agentCaptal = new double[m_numberOfAgents];
    for (int i = 0; i < m_numberOfAgents; i++) {
        m_agentCaptal[i] = agentCapital;
    }
}

void Market::initializeDistribution(int distributionResolution)
{
    m_distributionResolution = distributionResolution;
    int distributionLength = m_marketCapital/m_distributionResolution;
    m_capitalDistribution = new unsigned long[distributionLength];
    for (int i = 0; i < distributionLength; i++) {
        m_capitalDistribution[i] = 0;
    }
}

void Market::logEquilibriumState(string filename) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    ofstream ofile;
    ofile.open(filename, ofstream::app);

    double transactionFactor,agentCapitalCombined,agent1_newCapital,agent2_newCapital;
    int agent_i,agent_j, cycle;
    double variance, differance;
    cycle = 0;
    //Calculate equilibrium
    while (variance < m_averageCapital*m_averageCapital) {
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {
            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }
            transactionFactor = randomNumber(gen);
            agentCapitalCombined = m_agentCaptal[agent_i] + m_agentCaptal[agent_j];
            agent1_newCapital = transactionFactor * agentCapitalCombined;
            agent2_newCapital = agentCapitalCombined - agent1_newCapital;
            if (agent1_newCapital > 0 && agent2_newCapital > 0) {
                m_agentCaptal[agent_i] = agent1_newCapital;
                m_agentCaptal[agent_j] = agent2_newCapital;
            }
        }
        variance = 0;
        for (int i = 0; i < m_numberOfAgents; i++) {
            differance = (m_agentCaptal[i]-m_averageCapital);
            variance += differance*differance;
        }
        variance = variance/m_numberOfAgents;
        cycle ++;
    }
    ofile << cycle << endl;
    ofile.close();
}


//void Market::calculateEquilibriumState() {
//    random_device rd;
//    mt19937_64 gen{rd()};
//    uniform_real_distribution<double> randomNumber(0.0,1.0);

//    double transactionFactor,agentCapitalCombined,agent_i_newCapital,agent_j_newCapital;
//    int agent_i,agent_j, transactionNumber;
//    double variance, differance;

//    for (unsigned long cycle = 0; cycle < numberOfCycles; cycle++) {
//        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

//            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
//            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

//            while(agent_j==agent_i) {
//                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
//            }

//            transactionFactor = randomNumber(gen);
//            agentCapitalCombined = m_agentCaptal[agent_i] + m_agentCaptal[agent_j];

//            agent_i_newCapital = transactionFactor * agentCapitalCombined;
//            agent_j_newCapital = agentCapitalCombined - agent_i_newCapital;

//            if (agent_i_newCapital > 0 && agent_j_newCapital > 0) {
//                m_agentCaptal[agent_i] = agent_i_newCapital;
//                m_agentCaptal[agent_j] = agent_j_newCapital;
//            }

//            agent_i = (int) (agent_i_newCapital/m_distributionResolution);
//        }
//    }
//}


void Market::runTransactions(int numberOfCycles) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    double transactionFactor, agentCapitalCombined, agent_i_newCapital, agent_j_newCapital;
    int agent_i,agent_j, transactionNumber;
    double variance, differance;

    for (unsigned long cycle = 0; cycle < numberOfCycles; cycle++) {
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }

            transactionFactor = randomNumber(gen);
            agentCapitalCombined = m_agentCaptal[agent_i] + m_agentCaptal[agent_j];

            agent_i_newCapital = transactionFactor * agentCapitalCombined;
            agent_j_newCapital = agentCapitalCombined - agent_i_newCapital;

            if (agent_i_newCapital > 0 && agent_j_newCapital > 0) {
                m_agentCaptal[agent_i] = agent_i_newCapital;
                m_agentCaptal[agent_j] = agent_j_newCapital;
            }

            agent_i = (int) (agent_i_newCapital/m_distributionResolution);
        }
    }
}

void Market::calculateCapitalDistribution(int numberOfCycles, int numberOfTransactions, int distributionResolution) {
    m_distributionResolution = distributionResolution;

}

/************************************/
/*        Assignment C              */
/************************************/

void Market::runTransactionsWithSavings(int numberOfCycles, double savingFactor, string filename) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    ofstream ofile;
    ofile.open(filename, ofstream::app);

    double transactionFactor, agentCapitalCombined, agent_i_newCapital, agent_j_newCapital;
    int agent_i, agent_j, transactionNumber, MC_cycles, histogramSpace;
    double variance, differance, agentCapitolChange;
    double savingsFactorUsed = 1 - savingFactor;

    //Vector for calculating histogtam
    double *histogramVector = new double[m_numberOfAgents];
    for(int i = 0; i <= m_numberOfAgents; i++) {
        histogramVector[i] = 0;
    }

    //Loop for all transactions
    for (unsigned long cycle = 0; cycle < numberOfCycles; cycle++) {
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }

            transactionFactor = randomNumber(gen);

            agentCapitalCombined = m_agentCaptal[agent_i] + m_agentCaptal[agent_j];
            agentCapitolChange = savingsFactorUsed*(transactionFactor*agentCapitalCombined - m_agentCaptal[agent_i]);


            agent_i_newCapital = m_agentCaptal[agent_i] + agentCapitolChange;
            agent_j_newCapital = m_agentCaptal[agent_j] - agentCapitolChange;

            m_agentCaptal[agent_i] = agent_i_newCapital;
            m_agentCaptal[agent_j] = agent_j_newCapital;


            histogramSpace = (int) (agent_i_newCapital/m_distributionResolution);
            histogramVector[histogramSpace] += 1;
        }
        variance = 0;
        for (int i = 0; i < m_numberOfAgents; i++) {
            differance = (m_agentCaptal[i]-m_averageCapital);
            variance += differance*differance;
        }
        variance = variance/m_numberOfAgents;
        MC_cycles ++;
        //ofile << variance << endl;
    }
    //ofile << MC_cycle << "  " << variance << endl;

    //Printing histogram vector to file
    for(int i = 0; i<= m_numberOfAgents; i++) {
        ofile << histogramVector[i] << "\n";
    }

    ofile.close();
}



/************************************/
/*        Setters & Getters         */
/************************************/

//GETTERS

int Market::numberOfAgents() const {
    return m_numberOfAgents;
}

double Market::marketCapital() const {
    return m_marketCapital;
}

double Market::averageCapital() const {
    return m_averageCapital;
}

double *Market::agentCaptal() const {
    return m_agentCaptal;
}

double Market::agentSavingFactor() const {
    return m_agentSavingFactor;
}

double Market::agentSpendingFactor() const {
    return m_agentSpendingFactor;
}

unsigned long *Market::capitalOccurencies() const {
    return m_capitalDistribution;
}

//SETTERS

void Market::setNumberOfAgents(int numberOfAgents) {
    m_numberOfAgents = numberOfAgents;
}

void Market::setMarketCapital(double marketCapital) {
    m_marketCapital = marketCapital;
}

void Market::setAverageCapital(double averageCapital) {
    m_averageCapital = averageCapital;
}

void Market::setAgentCaptal(double *agentCaptal) {
    m_agentCaptal = agentCaptal;
}

void Market::setAgentSavingFactor(double agentSavingFactor) {
    m_agentSavingFactor = agentSavingFactor;
    m_agentSpendingFactor = 1.0 - agentSavingFactor;
}

void Market::setAgentSpendingFactor(double agentSpendingFactor) {
    m_agentSpendingFactor = agentSpendingFactor;
    m_agentSavingFactor = 1.0 - agentSpendingFactor;
}

void Market::setCapitalOccurencies(unsigned long *capitalOccurencies) {
    m_capitalDistribution = capitalOccurencies;
}








