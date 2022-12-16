#pragma once

#include <vector>
#include "Party.h"
#include "Graph.h"
#include "Simulation.h"

using std::vector;

class SelectionPolicy 
{
    public:
    virtual const int select(vector<int> &options, Simulation &sim, int partyId) const = 0;
    virtual ~SelectionPolicy() {}
    virtual SelectionPolicy* cloneSelectionPolicy()=0;
 };

class MandatesSelectionPolicy: public SelectionPolicy
{
    public:
    virtual ~MandatesSelectionPolicy() {}
    virtual const int select(vector<int> &options, Simulation &sim, int partyId) const;
    virtual SelectionPolicy* cloneSelectionPolicy();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{ 
    public:
    virtual ~EdgeWeightSelectionPolicy() {}
    virtual const int select(vector<int> &options, Simulation &sim, int partyId) const; 
    virtual SelectionPolicy* cloneSelectionPolicy();
};