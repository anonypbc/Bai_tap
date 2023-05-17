#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseItem;
class BaseKnight;
class Events;
class BaseBag;
enum ItemType { ANTIDOTE, PHOENIX_I, PHOENIX_II, PHOENIX_III, PHOENIX_IV };
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum OpponentType {MadBear = 1, Bandit, LordLupin, Elf, Troll, Tornbery, QueenOfCards, NinaDeRings, DurianGarden, OmegaWeapon, Hades};
class BaseOpponents;
class BaseItem {
protected:
    ItemType Item; 
public:
    ItemType getItem() {
        return Item; 
    }
    void setItem(ItemType item) {
        this ->Item = item; 
    }
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Node {
public:
    BaseItem* item;
    Node* next;
};
class BaseBag {
protected:
    BaseKnight *knight;
    Node *head;
    int count;
    int capacity; 
public:
    BaseBag(BaseKnight *knight, int phoenix, int anti) {
        this ->knight = knight;
        this ->count = 0;
        this ->head = NULL; 
    };
    virtual void remove();
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType); 
    virtual string toString() const;
    ~BaseBag();
};


class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;
    int PhoenixDownI;
    bool isPoisoned = false;
    int excessiveGil;
    int KnightBaseDame; 
public:
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int PhoenixDownI) {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this ->PhoenixDownI = PhoenixDownI;
        this->hp = maxhp;
    }
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI); 
    string toString() const;
    virtual bool fight(BaseOpponents * opnt);
    void setBag(BaseBag *bag){
        this ->bag = bag;
    }
    BaseBag *getBag() {
        return bag; 
    }
    int getID() {
        return id;
    }
    int getMaxHP() {
        return maxhp;
    }
    void setHP(int hp) {
       this ->hp = hp;
    }
    int getHP() {
        return hp; 
    }
    void setGil(int gil) {
        this ->gil = gil;
    }
    int getGil() {
        return gil;
    }
    int getPhoenix() {
        return PhoenixDownI;
    }
    int getAnti() {
        return antidote;
    }
    int getType() {
        return knightType;
    }
    bool getPoison() {
        return isPoisoned; 
    }
    void setPoison(bool Poison) {
        this ->isPoisoned = Poison;
    }
    int getLev() {
        return level;
    }
    void setLev(int lev) {
        this ->level = lev;
    }
    int getExcessiveGil() {
        return excessiveGil;
    }
    void setExcessiveGil(int excessiveGil) {
        this ->excessiveGil = excessiveGil;
    }
    int getBaseDame() {
        return KnightBaseDame;
    }
    ~BaseKnight() {
        delete bag;  
    }
};
class BaseOpponents{
public:
    static bool isWinOmegaWeapon;  
    static bool isWinHades;    
protected:
    int i;     
public:
    static BaseOpponents * create(int i, OpponentType opponentType);
    virtual void KnightStatus(BaseKnight* knight) = 0;
    virtual OpponentType Type() = 0;
};
class MadBearO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class BanditO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class LordLupinO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class ElfO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class TrollO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class TornberyO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class QueenOfCardsO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class NinaDeRingsO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class DurianGardenO: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class OmegaWeaponOpponent: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class HadesOpponent: public BaseOpponents{
public:
    OpponentType Type();
    void KnightStatus(BaseKnight* knight);
};
class NodeTreasure{
public:
    int data;
    NodeTreasure *next;
    NodeTreasure(int d){
        data = d;
        next = NULL;
    };
}; 
struct addNode {
    void static insertHead(NodeTreasure *&head, int data);
    void static print(NodeTreasure *head);
};
struct checkBool {
    bool static checkTreasure(NodeTreasure* head);
    bool static checkPaladinShield(NodeTreasure* head);
    bool static checkLancelot(NodeTreasure* head);
    bool static checkGuinevere(NodeTreasure* head);
};
class ArmyKnights {
protected:
    string *info;
    int count_knight;
    string kn;
    BaseKnight **knight = new BaseKnight*[10000];
    checkBool *check;
    NodeTreasure* head = NULL; 
    addNode *add;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    // bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count () const {
        return count_knight; 
    }
    BaseKnight * lastKnight() const;

    bool hasPaladinShield () const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
    
    bool fight(BaseOpponents * opponent);
};


class Events {
protected:
    int* eventCodes;
    int numEve;
    int event_cnt = 1;
    int cnt = 0; 
    int i; 
    string event_str;
    public:
        Events ( const string & file_events ){
            ifstream file(file_events);
            if(file.is_open()) {
                file >> numEve;
                //cout << numEve; 
                eventCodes = new int[numEve];
                for (i = 0; i < numEve; i++) {
                    file >> eventCodes[i];
                }

            }
            //cout << event_str; 
        };
        int count () const {
            return numEve; 
        };
        string event() const {
            return event_str;
        }
        int get(int k) const {
            return eventCodes[k];
        }
        ~Events() {
            delete[] eventCodes;
        }
};
class KnightAdventure {
private:
    BaseOpponents * opnt; 
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__