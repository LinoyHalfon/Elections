#include "Party.h"
#include "JoinPolicy.h"

//CONSTRUCTOR
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mCoalitionId(-1), mTimer(0), mOffers()
{
     // You can change the implementation of the constructor, but not the signature!
}


//COPY CONSTRUCTOR
Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(), mState(other.mState), mCoalitionId(other.mCoalitionId), mTimer(other.mTimer), mOffers(other.mOffers)
{
    mJoinPolicy = other.mJoinPolicy->cloneJoinPolicy();   
}

//MOVE CONSTRUCTOR
Party::Party(Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mCoalitionId(other.mCoalitionId), mTimer(other.mTimer), mOffers(other.mOffers)
{ 
    other.mJoinPolicy = nullptr;
}

//DESTRUCTOR
Party::~Party()
{
    if (mJoinPolicy)
        delete mJoinPolicy;
}

//ASSIGNMENT OPERATOR
Party& Party::operator=(const Party &other)
{
    if (this != &other){
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;
        mCoalitionId = other.mCoalitionId;
        mTimer = other.mTimer;
        mOffers = other.mOffers;
        if(mJoinPolicy)
            delete mJoinPolicy;
        mJoinPolicy = other.mJoinPolicy->cloneJoinPolicy();   
    }
    return *this;
}

//MOVE ASSIGNMENT OPERATOR
Party& Party::operator=(Party &&other)
{
    if (this != &other){
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;
        mCoalitionId = other.mCoalitionId;
        mTimer = other.mTimer;
        mOffers = other.mOffers;
        if(mJoinPolicy)
                delete mJoinPolicy;
        mJoinPolicy = other.mJoinPolicy; 
        other.mJoinPolicy = nullptr;
    }
    return *this;
}

State Party::getState() const
{
    return mState;
}

int Party::getCoalitionId() const
{
    return mCoalitionId;
}

int Party::getTimer() const
{
    return mTimer;
}

void Party::setTimer()
{
    mTimer = mTimer+1;
}

vector<int> &Party::getOffers() 
{
    return mOffers;
}

void Party::addOffer(int coalitionId)
{
    mOffers.push_back(coalitionId);
}

void Party::setState(State state)
{
    mState = state;
}

void Party::setCoalition(int coalitionId)
{
    mCoalitionId = coalitionId;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

const int Party:: getId() const
{   
    return mId;
}

void Party::step(Simulation &s)
{
    if (mState == CollectingOffers){
        setTimer();
        if (mTimer == 3){
            int selectedCoalitionId = mJoinPolicy->join(s, mOffers);
            setState(Joined);
            mCoalitionId = selectedCoalitionId;
            Coalition &selectedCoalition = s.getCoalition(selectedCoalitionId);
            selectedCoalition.addToCoalition(mId, mMandates);
            //COPY AGENT
            Agent &originalAgent = s.getAgent(selectedCoalitionId);
            Agent newAgent(originalAgent);
            //SET ID & PARTYID
            newAgent.setId(s.getAgentsSize());
            newAgent.setPartyId(mId);
            //ADD AGENT TO AGNENTS VECTOR
            s.addAgent(newAgent);
        }
    }
}
