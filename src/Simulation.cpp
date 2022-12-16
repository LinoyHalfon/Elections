#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions()
{
    // You can change the implementation of the constructor, but not the signature!
    int index = 0;
    for (Agent agent : agents){
        int partyId = agent.getPartyId();
        mCoalitions.push_back(Coalition(index, partyId, getParty(partyId).getMandates()));
        Party &party = getPartyNC(partyId);
        party.setCoalition(index);
        index++;
    }
}

//TODO
void Simulation::step()
{
    int numOfParties = mGraph.getNumVertices();
    for (int i = 0; i<numOfParties; i++){
        Party &party = mGraph.getPartyNC(i);
        party.step(*this);
    }

    for (Agent agent : mAgents){
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    for (Coalition coalition : mCoalitions){
        if (coalition.getMandates() >= 61)
        return true;
    }
    int numOfParties = mGraph.getNumVertices();
    for (int index = 0; index<numOfParties; index++ ){
        if (getParty(index).getState() != Joined){
            return false;
        }
    }
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

Agent &Simulation::getAgent(int index)
{
    return mAgents.at(index);
}

void Simulation::addAgent(Agent &agent)
{
    return mAgents.push_back(agent);
}

const int Simulation::getAgentsSize() const
{
    return mAgents.size();
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getPartyNC(int partyId)
{
    return mGraph.getPartyNC(partyId);
}

Coalition &Simulation::getCoalition(int CoalitionId)
{
    return mCoalitions.at(CoalitionId);
}

void Simulation::getUnjoinedNeighbours(int partyId, vector<int> &unjoinedNeighbours) 
{
    //vector<int> unjoinedNeighbours;
    int numOfParties = mGraph.getNumVertices();
    for (int v = 0; v < numOfParties; v++ ){
        if (mGraph.containsEdge(partyId,v) && getParty(v).getState() != Joined)
            unjoinedNeighbours.push_back(v);
    }
    //return unjoinedNeighbours;
        
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    vector<vector<int>> partiesByCoalitions;
    for (Coalition coalition : mCoalitions){
        partiesByCoalitions.push_back(coalition.getParties());
    }
    return partiesByCoalitions;
}