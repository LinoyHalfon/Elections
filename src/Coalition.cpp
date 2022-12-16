#include "Coalition.h"

Coalition::Coalition(int id, int partyId, int mandates) : mId(id), mParties(), mMandates(mandates)
{
    vector<int> parties;
    parties.push_back(partyId);
    mParties = parties;
}

const int Coalition::getId() const
{
    return mId;
}
    
const int Coalition::getMandates() const
{
    return mMandates;
}

const vector<int> &Coalition::getParties() const
{
    return mParties;
}

void Coalition::addToCoalition(int partyId, int numOfMandates) 
{
   mParties.push_back(partyId);
   mMandates = mMandates + numOfMandates;
}