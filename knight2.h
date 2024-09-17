#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType { ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV };

class BaseItem;

class Events;

class BaseKnight;

//struct Node;
class BaseBag {
public://protected //check ###############################??????????????????????
    BaseKnight * knight;
    BaseItem * head;
    int max_num;
    int bagCount;
    bool negHP;
//public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    bool swapDel(ItemType itemType);
    BaseBag();
    ~BaseBag();
};
class PaladinBag:public BaseBag
{
    public:
        PaladinBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num);
        bool insertFirst(BaseItem * item);
};
class LancelotBag:public BaseBag
{
    public:
        LancelotBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num);
};
class DragonBag:public BaseBag
{
    public:
        DragonBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num);
        bool insertFirst(BaseItem * item);
};
class NormalBag:public BaseBag
{
    public:
        NormalBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num);
};

class BaseOpponent
{
    //protected://CHINH SAU ###????
    public:
        BaseKnight * lastKnight;
        int levelO;
        bool PaladinShield;
        int rest;
    //public:
        BaseOpponent();
        //BaseOpponent(int i, int eventID);
        virtual void run(BaseKnight * lastKnight)=0;
        void event1_5(int gil, int baseDamage);//, BaseKnight * lastKnight)
        void negHP();
};
class MadBear:public BaseOpponent//chuyen may ham qua cpp sau ???
{
    public:
        MadBear(int i, int eventID);
        void run(BaseKnight * lastKnight);
};
class Bandit:public BaseOpponent
{
    public:
        Bandit(int i, int eventID);
        void run(BaseKnight * lastKnight);
};
class LordLupin:public BaseOpponent
{
    public:
        LordLupin(int i, int eventID);
        void run(BaseKnight * lastKnight);
};
class Elf:public BaseOpponent
{
    public:
        Elf(int i, int eventID);
        void run(BaseKnight * lastKnight);
};
class Troll:public BaseOpponent
{
    public:
        Troll(int i, int eventID);
        void run(BaseKnight * lastKnight);
};
class Tornbery:public BaseOpponent
{
    public:
        Tornbery(int i, int eventID);
        void run(BaseKnight * lastKnight);
};
class QueenOfCards:public BaseOpponent
{
    public:
        QueenOfCards(int i, int eventID);
        void run(BaseKnight * lastKnight);
};
class NinaDeRings:public BaseOpponent
{
    public:
        //NinaDeRings();
        void run(BaseKnight * lastKnight);
};
class DurianGarden:public BaseOpponent
{
    public:
        //DurianGarden();
        void run(BaseKnight * lastKnight);
};
class OmegaWeapon:public BaseOpponent
{
    private:
        static bool win;
    public:
        OmegaWeapon();
        void run(BaseKnight * lastKnight);
};
class Hades:public BaseOpponent
{
    private:
        static bool win;
    public:
        Hades();
        void run(BaseKnight * lastKnight);
};
/*
class  Ultimecia:public BaseOpponent
{
    public:
        Ultimecia(BaseKnight * lastKnight):BaseOpponent(lastKnight){}
        void run();

};
*/

bool prime_num(int n);

bool pythagoras(int maxhp);

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
//protected://CHINH LAI PROTECTED SAU ####################??????????????????
public:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;//thua ??????
    BaseBag * bag;
    KnightType knightType;

//public:
    //static BaseKnight * temp;
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
//BaseKnight * BaseKnight::temp=new BaseKnitght();
class PaladinKnight:public BaseKnight //check private hay protected hay public, cái nào cũng được ???
{
    public:
        PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class LancelotKnight:public BaseKnight //check private hay protected hay public, cái nào cũng được ???
{
    public:
        LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class DragonKnight:public BaseKnight //check private hay protected hay public, cái nào cũng được ???
{
    public:
        DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class NormalKnight:public BaseKnight //check private hay protected hay public, cái nào cũng được ???
{
    public:
        NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class ArmyKnights {
public://check private// de private sau ###########???????????????? chinh may ham lay HAY DE PUBLIC LUON
    //const int max_knights_num;//sua trong cpp
    int knights_count;//cap nhat trong cpp
    int knights_num;
    bool PaladinShield;// coi co can static ko, chi 1 doi tuong ArmyKnights ??? thi ko can
    bool LancelotSpear;// coi co can static ko, chi 1 doi tuong ArmyKnights ??? thi ko can
    bool GuinevereHair;// coi co can static ko, chi 1 doi tuong ArmyKnights ??? thi ko can
    bool ExcaliburSword;// coi co can static ko, chi 1 doi tuong ArmyKnights ??? thi ko can
    BaseKnight ** armyKnights;
//public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const; //temporary
    BaseKnight * lastKnight() const; //temporary

    bool hasPaladinShield() const; //temporary
    bool hasLancelotSpear() const; //temporary
    bool hasGuinevereHair() const; //temporary
    bool hasExcaliburSword() const; //temporary

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public://protected
    BaseItem * link;
    ItemType itemType;
//public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};
class Antidote:public BaseItem
{
public:
    bool canUse ( BaseKnight * knight ){return 0;}//ko dung luon
    void use ( BaseKnight * knight ){}//ko dung luon
    Antidote();
};
class PhoenixDownI:public BaseItem
{
public:
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
    PhoenixDownI();
};
class PhoenixDownII:public BaseItem
{
public:
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
    PhoenixDownII();
};
class PhoenixDownIII:public BaseItem
{
public:
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
    PhoenixDownIII();
};
class PhoenixDownIV:public BaseItem
{
public:
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
    PhoenixDownIV();
};

class Events {
private://check private hay protected hay public ???
    int * eventsArray;
    int events_num;
public:
    Events ( const string & file_events );
    int count() const;
    int get(int i) const;
    ~Events();
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); //temporary

    void loadArmyKnights(const string &file_armyknights); //temporary
    void loadEvents(const string &file_events); //temporary
    void run(); //temporary //class nay chi con run() chua hien thuc HET
};

#endif // __KNIGHT2_H__
