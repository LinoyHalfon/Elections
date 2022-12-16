#pragma once

#include <vector>
#include "Graph.h"

class Simulation;
class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent &other);
    Agent(Agent &&other);
    ~Agent();
    Agent &operator=(const Agent &other);
    Agent &operator=(Agent &&other);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setId(int id);
    void setPartyId(int partyId);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
