#pragma once

#include <vector>

using std::vector;

class Simulation;
class Party;

class Coalition
{
public:
    Coalition(int id, int partyId, int mandates);

    const int getId() const;
    const int getMandates() const;
    const vector<int> &getParties() const;
    void addToCoalition(int partyId, int numOfMandates);
    

private:
    int mId;
    vector<int> mParties;
    int mMandates;
};
