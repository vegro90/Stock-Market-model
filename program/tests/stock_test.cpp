#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/market.h"

SCENARIO ("Constructor test" ) {
    WHEN ("Creating instance of Market") {
        Market market;
        THEN ("Initial conditions is initialized") {
            REQUIRE (market.numberOfAgents() == 0);
            REQUIRE (market.averageCapital() == 0);
            REQUIRE (market.marketCapital() == 0);
            REQUIRE (market.agentSavingFactor() == 0);
            REQUIRE (market.agentSpendingFactor() == 1);
            REQUIRE (market.distributionResolution() == 0.01);
            REQUIRE (market.correlationStrength() == 0);
            REQUIRE (market.experienceStrength() == 0);
            REQUIRE (market.equalityLimit() == 0.001);
//            REQUIRE (market.capitalDistribution() == 0);  // create getter
//            REQUIRE (market.distributionLength() == 0);   // create getter
            REQUIRE (market.agentCaptal() == 0);
//            REQUIRE (market.transactionLog() == 0);       // create getter
//            REQUIRE (market.transactionLogNorm() == 0);   // create getter
        }
    }
}

SCENARIO ("Overload Constructor test") {
    WHEN ("Creating Market of 10 agents with 100 money") {
        Market market(10, 100);
        THEN ("Updates values in Market") {
            REQUIRE (market.numberOfAgents() == 10);
            REQUIRE (market.averageCapital() == 100);
            REQUIRE (market.marketCapital() == 1000);
            for (int i = 0; i < 10; i++) {
                REQUIRE (market.agentCaptal()[i] == 100);
            }
            REQUIRE_FALSE (market.agentCaptal()[-1] == 100);
            REQUIRE_FALSE (market.agentCaptal()[10] == 100);
        }
    }
}

SCENARIO ("InitializeMarket test") {
    WHEN ("Initializing market of 200 agents with 100 money") {
        Market market;
        market.initialzeMarket(20, 100);
        THEN ("Updates values in Market") {
            REQUIRE (market.numberOfAgents() == 20);
            REQUIRE (market.averageCapital() == 100);
            REQUIRE (market.marketCapital() == 2000);
            for (int i = 0; i < 20; i++) {
                REQUIRE (market.agentCaptal()[i] == 100);
            }
            REQUIRE_FALSE (market.agentCaptal()[-1] == 100);
            REQUIRE_FALSE (market.agentCaptal()[20] == 100);
        }
    }
}








