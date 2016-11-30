#include "market.h"

Market::Market() {
    m_numberOfAgents = 0;
    m_marketCapital = 0;
    m_averageCapital = 0;
    m_agentSavingFactor = 0;
    m_agentSpendingFactor = 0;
}

void Market::initialzeMarket(int numberOfAgents, double agentCapital) {
    m_numberOfAgents = numberOfAgents;
    m_averageCapital = agentCapital;
    m_marketCapital = m_numberOfAgents*m_averageCapital;

    m_agentCaptal = new double[m_numberOfAgents];
    for (int i = 0; i < m_numberOfAgents; i++) {
        m_agentCaptal[i] = agentCapital;
    }
}

void Market::calculateEquilibriumState() {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    //TEST FILE
    std::ofstream ofile;
    string filename = "testEquilibrium.txt";
    ofile.open(filename);//, std::ios_base::app);

    double transactionFactor,agentCapitalCombined,agent1_newCapital,agent2_newCapital;
    int agent_i,agent_j;
    //Calculate equilibrium
    for (int cycle = 0; cycle < 1e4; cycle++) {

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

        double variance, differance;
        for (int i = 0; i < m_numberOfAgents; i++) {
            differance = (m_agentCaptal[i]-m_averageCapital);
            variance += differance*differance;
        }
        variance = variance/m_numberOfAgents;

        //TEST FILE
        ofile << variance << "\n" ;

    }
    //TEST FILE
    ofile << std::endl;
    ofile.close();
}





/************************************/
/*        Setters & Getters         */
/************************************/


