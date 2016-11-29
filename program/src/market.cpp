#include "market.h"

Market::Market() {
    m_numberOfAgents = 0;
    m_marketCapital = 0;

}

void Market::initialzeMarket(int numberOfAgents, double agentInitalCapital) {
    m_numberOfAgents = numberOfAgents;
    m_marketCapital = numberOfAgents * agentInitalCapital;
    //Initialize list of capitals
    m_agents = new double[m_numberOfAgents];
    for ( int i = 0; i < m_numberOfAgents; i++) {
        m_agents[i] = agentInitalCapital;
    }
    //Initialize transaction log
    m_transactionLog = new int*[m_numberOfAgents];
    for ( int i = 0; i < m_numberOfAgents; i++) {
        m_transactionLog[i] = new int[m_numberOfAgents];
        for ( int j = 0; j < m_numberOfAgents; j++) {
            m_transactionLog[i][j] = 0;
        }
    }
}

//void Market::initialzeMarket(int numberOfAgents, double agentInitalCapital) {
//    m_numberOfAgents = numberOfAgents;
//    m_marketCapital = numberOfAgents * agentInitalCapital;
//    m_marketGrid = new double*[m_numberOfAgents];
//    for ( int i = 1; i <= m_numberOfAgents; i++) {
//        m_marketGrid[i] = new double[m_numberOfAgents];
//        for ( int j = 1; j <= m_numberOfAgents; j++) {
//            m_marketGrid[i][j] = agentInitalCapital;
//        }
//    }
//}

void Market::simulateTransactions(int numberOfTransactions,int equilibriumNumberOfTransactions,double smallesTransactionSize) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    int possibleCapitalValues = m_marketCapital/smallesTransactionSize;
    m_CapitalOccurencies = new long int[possibleCapitalValues];

    double transactionFactor,agentCapitalCombined,agent1_newCapital,agent2_newCapital;
    int i,j;
    //Calculate equilibrium
    for (int cycle = 0; cycle < equilibriumNumberOfTransactions; cycle++) {

        i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
        j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
        while(j==i) {
            j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
        }
        transactionFactor = randomNumber(gen);
        agentCapitalCombined = m_agents[i] + m_agents[j];
        agent1_newCapital = transactionFactor * agentCapitalCombined;
        agent2_newCapital = agentCapitalCombined - agent1_newCapital;
        if (agent1_newCapital > 0 && agent2_newCapital > 0) {
            m_agents[i] = agent1_newCapital;
            m_agents[j] = agent2_newCapital;
        }
    }
    //Start logging in histogram
    int agent1_inLog,agent2_inLog;
    for (int cycle = 0; cycle < numberOfTransactions; cycle++) {

        i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
        j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
        while(j==i) {
            j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
        }
        transactionFactor = randomNumber(gen);
        agentCapitalCombined = m_agents[i] + m_agents[j];
        agent1_newCapital = transactionFactor * agentCapitalCombined;
        agent2_newCapital = agentCapitalCombined - agent1_newCapital;
        if (agent1_newCapital > 0 && agent2_newCapital > 0) {
            m_agents[i] = agent1_newCapital;
            m_agents[j] = agent2_newCapital;
        }
        agent1_inLog = agent1_newCapital/smallesTransactionSize;
        agent2_inLog = agent2_newCapital/smallesTransactionSize;
        m_CapitalOccurencies[agent1_inLog] += 1;
        m_CapitalOccurencies[agent2_inLog] += 1;
    }
}

void Market::writeLogToFile(string fileName) {
    string outputFile = fileName;
    outputFile.append(".txt");
    std::ofstream ofile;
    ofile.open(outputFile);//, std::ios_base::app);
    int arrayLength = m_marketCapital/0.01;
    for(int i = 1; i <= arrayLength ; i+=10) {
        ofile << m_CapitalOccurencies[i] << "\n" ;
    }
    ofile << std::endl;
    ofile.close();
}




/************************************/
/*        Setters & Getters         */
/************************************/
void Market::setNumberOfAgents(int numberOfAgents) {
    m_numberOfAgents = numberOfAgents;
}

void Market::setMarketCapital(double marketCapital) {
    m_marketCapital = marketCapital;
}

void Market::setAgents(double *agents) {
    m_agents = agents;
}

void Market::setOccurencies(long *occurencies) {
    m_CapitalOccurencies = occurencies;
}

int Market::numberOfAgents() const {
    return m_numberOfAgents;
}

double Market::marketCapital() const {
    return m_marketCapital;
}

double *Market::agent() const {
    return m_agents;
}

long *Market::occurencies() const {
    return m_CapitalOccurencies;
}


