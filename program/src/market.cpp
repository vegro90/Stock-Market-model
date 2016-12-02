#include "market.h"

Market::Market() {
    m_numberOfAgents = 0;
    m_averageCapital = 0;
    m_marketCapital = 0;
    m_agentSavingFactor = 0;
    m_agentSpendingFactor = 1;
    m_distributionResolution = 0.01;
    m_correlationStrength = 0;
    m_experienceStrength = 0;
}

Market::Market(int numberOfAgents, double agentCapital) {
    m_numberOfAgents = numberOfAgents;
    m_averageCapital = agentCapital;
    m_marketCapital = m_numberOfAgents * m_averageCapital;
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

void Market::resetMarket() {
    for (int i = 0; i < m_numberOfAgents; i++) {
        m_agentCaptal[i] = m_averageCapital;
    }
}

void Market::initializeDistribution(double distributionResolution) {
    m_distributionResolution = distributionResolution;
    m_distributionLength = (int) (m_marketCapital/distributionResolution);
    m_capitalDistribution = new unsigned long[m_distributionLength];
    for (int i = 0; i < m_distributionLength; i++) {
        m_capitalDistribution[i] = 0;
    }
}

void Market::resetDistribution() {

    for (int i = 0; i < m_distributionLength; i++) {
        m_capitalDistribution[i] = 0;
    }
}

void Market::initializeTransactionLog() {
    m_transactionLog = new int*[m_numberOfAgents];
    for (int i = 0; i < m_numberOfAgents; i++) {
        m_transactionLog[i] = new int[m_numberOfAgents];
        for (int j = 0; j < m_numberOfAgents; j++) {
            m_transactionLog[i][j] = 0;
        }
    }
}

void Market::resetTransactionLog() {
    for (int i = 0; i < m_numberOfAgents; i++) {
        for (int j = 0; j < m_numberOfAgents; j++) {
            m_transactionLog[i][j] = 0;
        }
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
}

void Market::runEquilibrium(int numberOfCycles) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    double transactionFactor,agentCapitalCombined, transactionValue; //,agent_i_newCapital,agent_j_newCapital;
    int agent_i,agent_j, transactionNumber;
    double variance, differance;
    int agent_i_inLog,agent_j_inLog;

    //Metropolis and probabilities
    double metropolis, capitalDifference;
    double correlationFactor;
    double experienceFactor;
    for (unsigned long cycle = 0; cycle < numberOfCycles; cycle++) {
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }

            //Calculate probability of an transaction
            capitalDifference = fabs(m_agentCaptal[agent_i] - m_agentCaptal[agent_j]);
            if (capitalDifference > 0) {
                correlationFactor = pow(capitalDifference, -m_correlationStrength);
            } else {
                correlationFactor = 1.0;
            }
            experienceFactor = pow((m_transactionLog[agent_i][agent_j] + 1),m_experienceStrength);

            //Metropolis test
            metropolis = randomNumber(gen);
            if (correlationFactor*experienceFactor >= metropolis) {

                transactionFactor = randomNumber(gen);
                transactionValue = m_agentSpendingFactor*(transactionFactor*m_agentCaptal[agent_j]-(1-transactionFactor)*m_agentCaptal[agent_i]);

                m_agentCaptal[agent_i] += transactionValue;
                m_agentCaptal[agent_j] -= transactionValue;

                m_transactionLog[agent_i][agent_j] +=1;
                m_transactionLog[agent_j][agent_i] +=1;
            }
        }
    }
}


void Market::runTransactions(int numberOfCycles) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    double transactionFactor,agentCapitalCombined, transactionValue; //,agent_i_newCapital,agent_j_newCapital;
    int agent_i,agent_j, transactionNumber;
    double variance, differance;
    int agent_i_inLog,agent_j_inLog;

    //Metropolis and probabilities
    double metropolis, capitalDifference;
    double correlationFactor;
    double experienceFactor;
    for (unsigned long cycle = 0; cycle < numberOfCycles; cycle++) {
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }

            //Calculate probability of an transaction
            capitalDifference = fabs(m_agentCaptal[agent_i] - m_agentCaptal[agent_j]);
            if (capitalDifference > 0) {
                correlationFactor = pow(capitalDifference, -m_correlationStrength);
            } else {
                correlationFactor = 1.0;
            }
            experienceFactor = pow((m_transactionLog[agent_i][agent_j] + 1),m_experienceStrength);

            //Metropolis test
            metropolis = randomNumber(gen);
            if (correlationFactor*experienceFactor >= metropolis) {

                transactionFactor = randomNumber(gen);
                transactionValue = m_agentSpendingFactor*(transactionFactor*m_agentCaptal[agent_j]-(1-transactionFactor)*m_agentCaptal[agent_i]);

                m_agentCaptal[agent_i] += transactionValue;
                m_agentCaptal[agent_j] -= transactionValue;

                agent_i_inLog = m_agentCaptal[agent_i]/m_distributionResolution;
                agent_j_inLog = m_agentCaptal[agent_j]/m_distributionResolution;
                m_capitalDistribution[agent_i_inLog] += 1;
                m_capitalDistribution[agent_j_inLog] += 1;

                m_transactionLog[agent_i][agent_j] +=1;
                m_transactionLog[agent_j][agent_i] +=1;
            }
        }
    }
}

void Market::writeDistributionToFile(string filename) {
    ofstream distributionFile;
    distributionFile.open(filename, ios_base::app);

    for (int i = 0; i < m_distributionLength; i++) {
        distributionFile << m_capitalDistribution[i] << endl;
    }

    distributionFile.close();
}

void Market::printTransactionLog()
{
    for (int i = 0; i < m_numberOfAgents; i++) {
        for (int j = 0; j < m_numberOfAgents; j++) {
            cout << m_transactionLog[i][j] << " ";
        }
        cout << endl;
    }
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

double Market::correlationStrength() const {
    return m_correlationStrength;
}

double Market::experienceStrength() const {
    return m_experienceStrength;
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


void Market::setCorrelationStrength(double correlationStrength) {
    m_correlationStrength = correlationStrength;
}

void Market::setExperienceStrength(double experienceStrength) {
    m_experienceStrength = experienceStrength;
}








