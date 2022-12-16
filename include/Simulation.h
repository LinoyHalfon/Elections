#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"

using std::string;
using std::vector;

class Party;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    Agent &getAgent(int index);
    void addAgent(Agent &agent);
    const int getAgentsSize() const;
    Coalition &getCoalition(int coalitionId);
    const Party &getParty(int partyId) const;
    Party &getPartyNC(int partyId);
    const vector<vector<int>> getPartiesByCoalitions() const;
    void getUnjoinedNeighbours(int partyId, vector<int> &unjoinedNeighbours);
   
   
private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> mCoalitions;
};
