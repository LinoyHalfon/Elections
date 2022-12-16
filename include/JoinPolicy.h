#pragma once

#include "Coalition.h"
#include "Party.h"
#include "Simulation.h"

class JoinPolicy 
{

    public:
    virtual const int join(Simulation &s, vector<int> &offers) const = 0;
    virtual ~JoinPolicy() {}
    virtual JoinPolicy* cloneJoinPolicy()=0;
};

class MandatesJoinPolicy : public JoinPolicy {

    public:
    virtual ~MandatesJoinPolicy() {}
    virtual const int join(Simulation &s, vector<int> &offers) const;
    virtual JoinPolicy* cloneJoinPolicy();
    

};

class LastOfferJoinPolicy : public JoinPolicy {

    public:
    virtual ~LastOfferJoinPolicy() {}
    virtual const int join(Simulation &s, vector<int> &offers) const;
    virtual JoinPolicy* cloneJoinPolicy();
};