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

void Market::initializeDistribution(double distributionResolution)
{
    m_distributionResolution = distributionResolution;
    int distributionLength = (int) (m_marketCapital/distributionResolution);
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

    double transactionFactor,agentCapitalCombined,agent_i_newCapital,agent_j_newCapital;
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
            agent_i_newCapital = transactionFactor * agentCapitalCombined;
            agent_j_newCapital = agentCapitalCombined - agent_i_newCapital;
            m_agentCaptal[agent_i] = agent_i_newCapital;
            m_agentCaptal[agent_j] = agent_j_newCapital;
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
    cout << endl << "Balle" << endl << endl;
}


void Market::runTransactions(int numberOfCycles) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    double transactionFactor,agentCapitalCombined,agent_i_newCapital,agent_j_newCapital;
    int agent_i,agent_j, transactionNumber;
    double variance, differance;
    int agent_i_inLog,agent_j_inLog;
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

            agent_i_inLog = agent_i_newCapital/m_distributionResolution;
            agent_j_inLog = agent_j_newCapital/m_distributionResolution;
            m_capitalDistribution[agent_i_inLog] += 1;
            m_capitalDistribution[agent_j_inLog] += 1;
        }
    }
}


//void Market::runTransactions(int numberOfCycles) {
//    random_device rd;
//    mt19937_64 gen{rd()};
//    uniform_real_distribution<double> randomNumber(0.0,1.0);

//    double transactionFactor,agentCapitalCombined,agent_i_newCapital,agent_j_newCapital;
//    int agent_i,agent_j, transactionNumber;
//    double correlationFactor, experienceFactor;
//    double correlationStrength, experienceStrength;
//    double capitalDifference;
//    int distributionLocation;

//    correlationStrength = 0;
//    correlationFactor = 1;
//    for (unsigned long cycle = 0; cycle < numberOfCycles; cycle++) {
//        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

//            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
//            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

//            while(agent_j==agent_i) {
//                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
//            }
////            capitalDifference = fabs(m_agentCaptal[agent_i] - m_agentCaptal[agent_j]);
////            if (capitalDifference > 0) {
////                correlationFactor = pow(capitalDifference, -correlationStrength);
////            } else {
////                correlationFactor = 1.0;
////            }

//            //Metropolis test
////            double metropolis = randomNumber(gen);
////            if (correlationFactor >= metropolis) {

//                transactionFactor = randomNumber(gen);
//                agentCapitalCombined = m_agentCaptal[agent_i] + m_agentCaptal[agent_j];

//                agent_i_newCapital = transactionFactor * agentCapitalCombined;
//                agent_j_newCapital = agentCapitalCombined - agent_i_newCapital;


//                m_agentCaptal[agent_i] = agent_i_newCapital;
//                m_agentCaptal[agent_j] = agent_j_newCapital;

////                cout << agentCapitalCombined << "," << agent_i_newCapital << "," << agent_j_newCapital << endl;

//                distributionLocation = (int) (agent_i_newCapital / m_distributionResolution);
//                m_capitalDistribution[distributionLocation] += 1;

//                distributionLocation = (int) (agent_j_newCapital / m_distributionResolution);
//                m_capitalDistribution[distributionLocation] += 1;
////            }
//        }
//    }
//}

void Market::calculateCapitalDistribution(int numberOfCycles, int numberOfTransactions, int distributionResolution) {
    m_distributionResolution = distributionResolution;

}

void Market::writeDistributionToFile(string filename) {
    int distributionLength = m_marketCapital/m_distributionResolution;
    ofstream distributionFile;
    distributionFile.open(filename, ios_base::app);

    for (int i = 0; i < distributionLength; i++) {
        distributionFile << m_capitalDistribution[i] << endl;
    }

    distributionFile.close();
}




/************************************/
/*        Setters & Getters         */
/************************************/

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








