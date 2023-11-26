#pragma once
#include "../Player/Player.h"

//Free function
void testPlayerStrategies();

//Abstract Strategy Class
class PlayerStrategy{
    public:
        PlayerStrategy();
        PlayerStrategy(Player* player);
        PlayerStrategy(const PlayerStrategy& other);
        virtual ~PlayerStrategy();
        PlayerStrategy& operator=(const PlayerStrategy& other);
        friend ostream& operator<<(ostream& out, const PlayerStrategy& playerStrategy);
        virtual void issueOrder()=0;
       virtual vector<Territory *> toAttack()=0;
       virtual vector<Territory *> toDefend()=0;
       
    protected:
       Player* p;
       
};

//5 Concrete Strategy Classes
class HumanPlayer : public PlayerStrategy{
    public:
        HumanPlayer(Player* player);
        HumanPlayer(const HumanPlayer& other);
        ~HumanPlayer();
        HumanPlayer& operator=(const HumanPlayer& other);
        friend ostream& operator<<(ostream& out, const HumanPlayer& humanPlayer);
        virtual void issueOrder() override;
        virtual vector<Territory *> toAttack() override;
        virtual vector<Territory *> toDefend() override;
};

class AggressivePlayer : public PlayerStrategy{
    public:
        AggressivePlayer(Player* player);
        AggressivePlayer(const AggressivePlayer& other);
        ~AggressivePlayer();
        AggressivePlayer& operator=(const AggressivePlayer& other);
        friend ostream& operator<<(ostream& out, const AggressivePlayer& aggressivePlayer);
        virtual void issueOrder() override;
        virtual vector<Territory *> toAttack() override;
        virtual vector<Territory *> toDefend() override;
};

class BenevolentPlayer : public PlayerStrategy{
    public:
        BenevolentPlayer(Player* player);
        BenevolentPlayer(const BenevolentPlayer& other);
        ~BenevolentPlayer();
        BenevolentPlayer& operator=(const BenevolentPlayer& other);
        friend ostream& operator<<(ostream& out, const BenevolentPlayer& benevolentPlayer);
        virtual void issueOrder() override;
        virtual vector<Territory *> toAttack() override;
        virtual vector<Territory *> toDefend() override;
};

class NeutralPlayer : public PlayerStrategy{
    public:
        NeutralPlayer(Player* player);
        NeutralPlayer(const NeutralPlayer& other);
        ~NeutralPlayer();
        NeutralPlayer& operator=(const NeutralPlayer& other);
        friend ostream& operator<<(ostream& out, const NeutralPlayer& neutralPlayer);
        virtual void issueOrder() override;
        virtual vector<Territory *> toAttack() override;
        virtual vector<Territory *> toDefend() override;
};

class CheaterPlayer : public PlayerStrategy{
    public:
        CheaterPlayer(Player* player);
        CheaterPlayer(const CheaterPlayer& other);
        ~CheaterPlayer();
        CheaterPlayer& operator=(const CheaterPlayer& other);
        friend ostream& operator<<(ostream& out, const CheaterPlayer& cheaterPlayer);
        virtual void issueOrder() override;
        virtual vector<Territory *> toAttack() override;
        virtual vector<Territory *> toDefend() override;
};