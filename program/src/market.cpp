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
    m_equalityLimit = 0.001;
    m_capitalDistribution = 0;
    m_distributionLength = 0;
    m_agentCaptal = 0;
    m_transactionLog = 0;
    m_transactionLogNorm = 0;
}

Market::Market(int numberOfAgents, double agentCapital) {
    if (numberOfAgents < 2) { // Ensure valid system size
        cout << "********** ERROR ***********" << endl;
        cout << "*  Need 2 or more agents!  *" << endl;
        cout << "****************************" << endl;
        terminate();
    } else ;
    m_numberOfAgents = numberOfAgents;
    m_averageCapital = agentCapital;
    m_marketCapital = m_numberOfAgents * m_averageCapital;
    m_agentCaptal = new double[m_numberOfAgents];
    for (int i = 0; i < m_numberOfAgents; i++) {
        m_agentCaptal[i] = agentCapital;
    }
}

void Market::initialzeMarket(int numberOfAgents, double agentCapital) {
    if (numberOfAgents < 2) { // Ensure valid system size
        cout << "*************** ERROR ***************" << endl;
        cout << "*       Need 2 or more agents!      *" << endl;
        cout << "*************************************" << endl;
        terminate();
    } else ;
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
    m_transactionLogNorm = new unsigned long int[m_numberOfAgents];
    m_transactionLog = new unsigned long int*[m_numberOfAgents];
    for (int i = 0; i < m_numberOfAgents; i++) {
        m_transactionLog[i] = new unsigned long int[m_numberOfAgents];
        for (int j = 0; j < m_numberOfAgents; j++) {
            m_transactionLog[i][j] = 1;
        }
        m_transactionLogNorm[i] = 1;
    }
}

void Market::resetTransactionLog() {
    for (int i = 0; i < m_numberOfAgents; i++) {
        for (int j = 0; j < m_numberOfAgents; j++) {
            m_transactionLog[i][j] = 1;
        }
        m_transactionLogNorm[i] = 1;
    }
}

int Market::calculateEquilibriumState(string filename) {
    filename.append("_EqHist.txt");
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    //Write the distribution of calculated equlibrium states
    ofstream ofile;
    ofile.open(filename, ofstream::app);

    //Transaction variables
    double transactionFactor, transactionValue; //,agent_i_newCapital,agent_j_newCapital;
    int agent_i,agent_j;

    double metropolis;
    //Financial equality
    double capitalDifference, correlationFactor;

    //Financial history
    double experienceFactor_i,experienceFactor_j, experienceFactor;

    //Equilibrium variables
    int cycle;
    double variance, differance;
    double totalVariance, lastTotalVariance;

    totalVariance = 0;
    lastTotalVariance = 1;
    cycle = 1;

    while (fabs(totalVariance-lastTotalVariance)/cycle  >= 0.1*totalVariance/cycle) {
        //for (int cycle = 1; cycle < 1e3 ; cycle++) {
        lastTotalVariance = totalVariance;
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }

            //Calculate probability of an transaction

            //Financial equality
            capitalDifference = fabs(m_agentCaptal[agent_i] - m_agentCaptal[agent_j]);
            if (capitalDifference > 0) {
                correlationFactor = pow(capitalDifference/m_equalityLimit, -m_correlationStrength);
            } else {
                correlationFactor = 1.0;
            }

            //Financial history
            experienceFactor_i = pow((m_transactionLog[agent_i][agent_j]/m_transactionLogNorm[agent_i]),m_experienceStrength);
            experienceFactor_j = pow((m_transactionLog[agent_i][agent_j]/m_transactionLogNorm[agent_j]),m_experienceStrength);
            experienceFactor = experienceFactor_i*experienceFactor_j;

            //Metropolis test
            metropolis = randomNumber(gen);
            if (correlationFactor*experienceFactor >= metropolis) {

                //Calculate transaction value with a spending factor
                transactionFactor = randomNumber(gen);
                transactionValue = m_agentSpendingFactor*(transactionFactor*m_agentCaptal[agent_j]-(1-transactionFactor)*m_agentCaptal[agent_i]);

                //Perform the transaction
                m_agentCaptal[agent_i] += transactionValue;
                m_agentCaptal[agent_j] -= transactionValue;

                //Log the transaction
                m_transactionLog[agent_i][agent_j] +=1;
                m_transactionLog[agent_j][agent_i] +=1;

                //Update local normalization of transaction log
                if (m_transactionLog[agent_i][agent_j] > m_transactionLogNorm[agent_i]) {
                    m_transactionLogNorm[agent_i] = m_transactionLog[agent_i][agent_j];
                }
                if (m_transactionLog[agent_i][agent_j] > m_transactionLogNorm[agent_j]) {
                    m_transactionLogNorm[agent_j] = m_transactionLog[agent_i][agent_j];
                }
            }
        }
        variance = 0;
        for (int i = 0; i < m_numberOfAgents; i++) {
            differance = (m_agentCaptal[i]-m_averageCapital);
            variance += differance*differance;
        }
        variance = variance/m_numberOfAgents;
        totalVariance += variance;
        cycle ++;
    }
    ofile << cycle << endl;
    ofile.close();
    return cycle;
}


void Market::runEquilibrium(int numberOfCycles) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    //Transaction variables
    double transactionFactor, transactionValue; //,agent_i_newCapital,agent_j_newCapital;
    int agent_i,agent_j;

    double metropolis;
    //Financial equality
    double capitalDifference, correlationFactor;

    //Financial history
    double experienceFactor_i,experienceFactor_j, experienceFactor;

    for (int cycle = 0; cycle < numberOfCycles; cycle++) {
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }

            //Calculate probability of an transaction

            //Financial equality
            capitalDifference = fabs(m_agentCaptal[agent_i] - m_agentCaptal[agent_j]);
            if (capitalDifference > 0) {
                correlationFactor = pow(capitalDifference/m_equalityLimit, -m_correlationStrength);
            } else {
                correlationFactor = 1.0;
            }

            //Financial history
            experienceFactor_i = pow(((double) m_transactionLog[agent_i][agent_j]/(double) m_transactionLogNorm[agent_i]),m_experienceStrength);
            experienceFactor_j = pow(((double) m_transactionLog[agent_i][agent_j]/(double) m_transactionLogNorm[agent_j]),m_experienceStrength);
            experienceFactor = experienceFactor_i*experienceFactor_j;

            //Metropolis test
            metropolis = randomNumber(gen);
            if (correlationFactor*experienceFactor >= metropolis) {

                //Calculate transaction value with a spending factor
                transactionFactor = randomNumber(gen);
                transactionValue = m_agentSpendingFactor*(transactionFactor*m_agentCaptal[agent_j]-(1-transactionFactor)*m_agentCaptal[agent_i]);

                //Perform the transaction
                m_agentCaptal[agent_i] += transactionValue;
                m_agentCaptal[agent_j] -= transactionValue;

                //Log the transaction
                m_transactionLog[agent_i][agent_j] +=1;
                m_transactionLog[agent_j][agent_i] +=1;

                //Update local normalization of transaction log
                if (m_transactionLog[agent_i][agent_j] > m_transactionLogNorm[agent_i]) {
                    m_transactionLogNorm[agent_i] = m_transactionLog[agent_i][agent_j];
                }
                if (m_transactionLog[agent_i][agent_j] > m_transactionLogNorm[agent_j]) {
                    m_transactionLogNorm[agent_j] = m_transactionLog[agent_i][agent_j];
                }
            }
        }
    }
}


void Market::runTransactions(int numberOfCycles) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    //Transaction variables
    double transactionFactor, transactionValue; //,agent_i_newCapital,agent_j_newCapital;
    int agent_i,agent_j;

    double metropolis;
    //Financial equality
    double capitalDifference, correlationFactor;


    //Financial history
    double experienceFactor_i,experienceFactor_j, experienceFactor;

    //Distribution variables
    int agent_i_inLog, agent_j_inLog;

    for (int cycle = 0; cycle < numberOfCycles; cycle++) {
        for (int transaction = 0; transaction < m_numberOfAgents; transaction++) {

            agent_i = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);

            while(agent_j==agent_i) {
                agent_j = (int) (randomNumber(gen)*(double)m_numberOfAgents);
            }

            //Calculate probability of an transaction

            //Financial equality
            capitalDifference = fabs(m_agentCaptal[agent_i] - m_agentCaptal[agent_j]);
            if (capitalDifference > 0) {
                correlationFactor = pow(capitalDifference/m_equalityLimit, -m_correlationStrength);
            } else {
                correlationFactor = 1.0;
            }

            //Financial history
            experienceFactor_i = pow((m_transactionLog[agent_i][agent_j]/m_transactionLogNorm[agent_i]),m_experienceStrength);
            experienceFactor_j = pow((m_transactionLog[agent_i][agent_j]/m_transactionLogNorm[agent_j]),m_experienceStrength);
            experienceFactor = experienceFactor_i*experienceFactor_j;

            //Metropolis test
            metropolis = randomNumber(gen);
            if (correlationFactor*experienceFactor >= metropolis) {
                //Calculate transaction value with a spending factor
                transactionFactor = randomNumber(gen);
                transactionValue = m_agentSpendingFactor*(transactionFactor*m_agentCaptal[agent_j]-(1-transactionFactor)*m_agentCaptal[agent_i]);

                //Perform the transaction
                m_agentCaptal[agent_i] += transactionValue;
                m_agentCaptal[agent_j] -= transactionValue;

                //Log the transaction
                m_transactionLog[agent_i][agent_j] +=1;
                m_transactionLog[agent_j][agent_i] +=1;

                //Update local normalization of transaction log
                if (m_transactionLog[agent_i][agent_j] > m_transactionLogNorm[agent_i]) {
                    m_transactionLogNorm[agent_i] = m_transactionLog[agent_i][agent_j];
                }
                if (m_transactionLog[agent_i][agent_j] > m_transactionLogNorm[agent_j]) {
                    m_transactionLogNorm[agent_j] = m_transactionLog[agent_i][agent_j];
                }

                //Save to the distribution
                agent_i_inLog = m_agentCaptal[agent_i]/m_distributionResolution;
                agent_j_inLog = m_agentCaptal[agent_j]/m_distributionResolution;
                m_capitalDistribution[agent_i_inLog] += 1;
                m_capitalDistribution[agent_j_inLog] += 1;
            }
        }
    }
}

void Market::writeDistributionToFile(string filename) {
    filename.append("_CapitalDistribution.txt");

    writeHeader(filename);

    ofstream distributionFile;
    distributionFile.open(filename, ios_base::app);

    for (int i = 0; i < m_distributionLength; i++) {
        distributionFile << m_capitalDistribution[i] << endl;
    }

    distributionFile.close();
}

void Market::writeHeader(string filename) {
    ofstream ofile;
    ofile.open(filename);
    ofile << "****** Stock market simulation ******" << endl;
    ofile << "*************************************" << endl;
    ofile << m_numberOfAgents << "\t" << "# Number of agens" << endl;
    ofile << m_averageCapital << "\t" << "# Agent capital" << endl;
    ofile << m_distributionResolution << "\t" << "# Distribution resolution" <<  endl;
    ofile << m_agentSavingFactor << "\t" << "# Agent saving factor"  << endl;
    ofile << m_correlationStrength << "\t" << "# Correlation strength" << endl;
    ofile << m_experienceStrength <<  "\t" << "# Experience strength" << endl;
    ofile << "*************************************" << endl;
    ofile.close();
}

void Market::printTransactionLog() {
    for (int i = 0; i < m_numberOfAgents; i++) {
        for (int j = 0; j < m_numberOfAgents; j++) {
            cout << m_transactionLog[i][j] << " ";
        }
        cout << endl;
    }
}

void Market::createFileName() {
    m_fileName = "market_";
    m_fileName.append(to_string( m_numberOfAgents ));
    m_fileName.append( "_" );
    m_fileName.append(to_string( m_averageCapital ));
    m_fileName.append( "_" );
    m_fileName.append(to_string( m_distributionResolution ));
    m_fileName.append( "_" );
    m_fileName.append(to_string( m_agentSavingFactor ));
    m_fileName.append( "_" );
    m_fileName.append(to_string( m_correlationStrength ));
    m_fileName.append( "_" );
    m_fileName.append(to_string( m_experienceStrength ));
    m_fileName.append( "_" );
    m_fileName.append(to_string( m_averageCapital ));
}




/************************************/
/*        Setters & Getters         */
/************************************/

int Market::numberOfAgents() const {
    return m_numberOfAgents;
}

double Market::distributionResolution() const {
    return m_distributionResolution;
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

double Market::equalityLimit() const {
    return m_equalityLimit;
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

void Market::setDistributionResolution(double distributionResolution) {
    m_distributionResolution = distributionResolution;
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

void Market::setEqualityLimit(double equalityLimit) {
    m_equalityLimit = equalityLimit;
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


