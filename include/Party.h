#pragma once
#include <string>
#include <vector>
#include "Coalition.h"

using std::string;
using std::vector;

class JoinPolicy;
class Simulation;


enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *jp); 
    Party(const Party &other);
    Party(Party &&other);
    ~Party();
    Party& operator=(const Party &other);
    Party &operator=(Party &&other);

    State getState() const;
    int getCoalitionId() const;
    vector <int> &getOffers();
    int getTimer() const;
    void setTimer();
    void addOffer(int coalitionId);
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    void setCoalition(int coalitionId);
    const int getId() const;

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mCoalitionId;
    int mTimer;
    vector<int> mOffers;
};
