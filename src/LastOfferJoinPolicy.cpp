#include "JoinPolicy.h"


const int LastOfferJoinPolicy:: join(Simulation &s, vector<int> &offers) const
{
    return offers.at(offers.size()-1);                             
}

JoinPolicy* LastOfferJoinPolicy:: cloneJoinPolicy()
{
    JoinPolicy* pointer = new LastOfferJoinPolicy();
    return pointer;
}