#include "JoinPolicy.h"


const int MandatesJoinPolicy:: join(Simulation &s, vector<int> &offers) const
{
    int max = offers[0];
    for (int coalitionId : offers){
        int currCoalitionMandates = s.getCoalition(coalitionId).getMandates();
        int maxCoalitionMandates = s.getCoalition(max).getMandates();
        if (currCoalitionMandates > maxCoalitionMandates)
            max = coalitionId;
    }
    return max;
}

JoinPolicy* MandatesJoinPolicy:: cloneJoinPolicy()
{
    JoinPolicy* pointer = new MandatesJoinPolicy();
    return pointer;
}
