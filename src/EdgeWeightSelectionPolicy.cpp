#include "SelectionPolicy.h"
#include <iostream>
#include <vector>
using std::string;


const int EdgeWeightSelectionPolicy :: select(vector<int> &options, Simulation &sim, int partyId) const  
{
    int max = options[0];
    for (int optionPartyId : options){
        Graph graph = sim.getGraph();
        if (graph.getEdgeWeight(optionPartyId, partyId) > graph.getEdgeWeight(max, partyId))
            max = optionPartyId;
    }
    return max;
}

SelectionPolicy* EdgeWeightSelectionPolicy::cloneSelectionPolicy()
{
    SelectionPolicy* pointer = new EdgeWeightSelectionPolicy();
    return pointer;
}