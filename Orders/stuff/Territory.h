#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Territory {
public:
    Territory();
    Territory(const string& name, const int locationX, const int locationY, const string& continent);
    Territory(const string& name, const int locationX, const int locationY, const string& continent, const string& player, int armies);
    Territory(const Territory& territory);
    ~Territory();

    string getName() const;
    void setName(const string& name);

    int getLocationX() const;
    void setLocationX(const int locationX);

    int getLocationY() const;
    void setLocationY(const int locationY);

    string getContinent() const;
    void setContinent(const string& continent);

    string getPlayer() const;
    void setPlayer(const string& player);

    int getArmies() const;
    void setArmies(const int armies);

    bool isNeutral() const;  // method declaration
    void setNeutral(bool neutralStatus);

    Territory& operator=(const Territory& territory);

    friend ostream& operator<<(ostream& os, const Territory& territory);

private:
    string name;
    int locationX;
    int locationY;
    string continent;
    string player;
    int armies;
    bool neutral = true;
};
