#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"

//CONSTRUCTOR
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}

//COPY CONSTRUCTOR
Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy()
{
    mSelectionPolicy = other.mSelectionPolicy->cloneSelectionPolicy();
}

//MOVE CONSTRUCTOR
Agent::Agent(Agent &&other)  : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy)
{ 
    other.mSelectionPolicy = nullptr;
}

//DESTRUCTOR
Agent::~Agent()
{
    if (mSelectionPolicy) 
        delete mSelectionPolicy;
}

//ASSIGNMENT OPERATOR
Agent& Agent::operator=(const Agent &other)
{
    if (this != &other){
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        if(mSelectionPolicy)
            delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy->cloneSelectionPolicy();  
    }
    return *this;
}

//MOVE ASSIGNMENT OPERATOR
Agent& Agent::operator=(Agent &&other)
{
    if (this != &other){
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        if(mSelectionPolicy)
            delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy; 
        other.mSelectionPolicy = nullptr;
    }
    return *this;
}

int Agent::getId() const
{
    return mAgentId;
}

void Agent::setId(int id)
{
    mAgentId = id;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::setPartyId(int partyId)
{
    mPartyId = partyId;
}

void Agent::step(Simulation &sim) 
{
    vector<int> options;
    vector<int> unjoinedNeighbours;
    sim.getUnjoinedNeighbours(mPartyId, unjoinedNeighbours);
    for (int partyId : unjoinedNeighbours){
        if (sim.getParty(partyId).getState() == CollectingOffers){
            vector<int> offers = sim.getPartyNC(partyId).getOffers();
            bool flag = true;
            int offersSize = offers.size();
            for (int index = 0; (index<offersSize) & flag; index++){
                Party thisAgentParty = sim.getParty(mPartyId); 
                int thisCoalitionId = thisAgentParty.getCoalitionId();
                int otherOfferCoalitionId = offers[index];
                if (otherOfferCoalitionId == thisCoalitionId)
                    flag = false;
            }
            if (flag)
                options.push_back(partyId);
        }
        else{
                options.push_back(partyId);
            }
    }

    if (options.size() != 0){
        int selectedPartyId = mSelectionPolicy->select(options, sim, mPartyId);
        int coalitionId = sim.getParty(mPartyId).getCoalitionId();
        Party &selectedParty = sim.getPartyNC(selectedPartyId);
        selectedParty.addOffer(coalitionId);
        if (selectedParty.getState() == Waiting)
            selectedParty.setState(CollectingOffers);
    }   
}
