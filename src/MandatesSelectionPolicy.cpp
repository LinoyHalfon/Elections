#include "SelectionPolicy.h"
 

const int MandatesSelectionPolicy :: select(vector<int> &options, Simulation &sim, int partyId) const
{
    int max = options[0];
    for (int optionPartyId : options){
        int currPartyMandates = sim.getPartyNC(optionPartyId).getMandates();
        int maxPartyMandates = sim.getPartyNC(max).getMandates();
        if (currPartyMandates > maxPartyMandates)
            max = optionPartyId;
    }
    return max;
}

SelectionPolicy* MandatesSelectionPolicy::cloneSelectionPolicy()
{
    SelectionPolicy* pointer = new MandatesSelectionPolicy();
    return pointer;
}