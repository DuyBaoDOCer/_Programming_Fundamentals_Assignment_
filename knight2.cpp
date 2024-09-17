#include "knight2.h"

/* * * BEGIN implementation of class BaseItem * * */
Antidote::Antidote()
{
    link=NULL;
    itemType=ANTIDOTE;
}
PhoenixDownI::PhoenixDownI()
{
    link=NULL;
    itemType=PHOENIXDOWNI;
}
bool PhoenixDownI::canUse ( BaseKnight * knight )
{
    if(knight->hp <=0) return true;
    return false;
}
void PhoenixDownI::use ( BaseKnight * knight )
{
    knight->hp=knight->maxhp;
}
PhoenixDownII::PhoenixDownII()
{
    link=NULL;
    itemType=PHOENIXDOWNII;
}
bool PhoenixDownII::canUse ( BaseKnight * knight )
{
    if(knight->hp < int(knight->maxhp/4)) return true;
    return false;
}
void PhoenixDownII::use ( BaseKnight * knight )
{
    knight->hp=knight->maxhp;
}
PhoenixDownIII::PhoenixDownIII()
{
    link=NULL;
    itemType=PHOENIXDOWNIII;
}
bool PhoenixDownIII::canUse ( BaseKnight * knight )
{
    if(knight->hp < int(knight->maxhp/3)) return true;
    return false;
}
void PhoenixDownIII::use ( BaseKnight * knight )
{
    if(knight->hp <= 0) knight->hp=int(knight->maxhp/3);
    else knight->hp+=int(knight->maxhp/4);
}
PhoenixDownIV::PhoenixDownIV()
{
    link=NULL;
    itemType=PHOENIXDOWNIV;
}
bool PhoenixDownIV::canUse ( BaseKnight * knight )
{
    if(knight->hp < int(knight->maxhp/2)) return true;
    return false;
}
void PhoenixDownIV::use ( BaseKnight * knight )
{
    if(knight->hp <= 0) knight->hp=int(knight->maxhp/2);
    else knight->hp+=int(knight->maxhp/5);
}








/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseOpponent * * */
BaseOpponent::BaseOpponent()
{
    lastKnight=NULL;
    rest=0;
}
/*
BaseOpponent::BaseOpponent(int i, int eventID)
{
    this->lastKnight=lastKnight;
    levelO=(i + eventID)%10 + 1;
    rest=0;
}
*/
void BaseOpponent::event1_5(int gil, int baseDamage)//, BaseKnight * lastKnight)
{
    if( (lastKnight->level >= levelO) || lastKnight->knightType==LANCELOT || lastKnight->knightType==PALADIN )
    {
        lastKnight->gil+=gil;//check gil<=999 ??? LAM ROI
        lastKnight->gil=lastKnight->gil >= 999 ? 999 : lastKnight->gil;
        rest=lastKnight->gil-999;
    }
    else lastKnight->hp=lastKnight->hp- baseDamage*(levelO-lastKnight->level);
    if (lastKnight->hp <= 0) negHP();
}
void BaseOpponent::negHP()
{
    lastKnight->bag->negHP=true;
    BaseItem * temp = (lastKnight->bag)->head;
    while(temp!=NULL && !temp->canUse(lastKnight) )
    {
        temp=temp->link;
    }
    if(temp!=NULL)
    {
        temp->use(lastKnight);
        lastKnight->bag->swapDel(temp->itemType);
    }
    if( lastKnight->hp<=0 )
    {
        if( lastKnight->gil >=100 )
        {
            lastKnight->gil -= 100;
            lastKnight->hp = int(lastKnight->maxhp/2);
        }
    }
}
//MadBear::MadBear(BaseKnight * lastKnight, i):BaseKnight(lastKnight) {levelO=(i + 1)%10 + 1;}
MadBear::MadBear(int i, int eventID){levelO=(i + eventID)%10 + 1;}
void MadBear::run(BaseKnight * lastKnight){ this->lastKnight=lastKnight;event1_5(100, 10); }
//Bandit::Bandit(BaseKnight * lastKnight, i):BaseKnight(lastKnight) {levelO=(i + 1)%10 + 1;}
Bandit::Bandit(int i, int eventID){levelO=(i + eventID)%10 + 1;}
void Bandit::run(BaseKnight * lastKnight){ this->lastKnight=lastKnight;event1_5(150, 15); }
//LordLupin::LordLupin(BaseKnight * lastKnight, i):BaseKnight(lastKnight) {levelO=(i + 1)%10 + 1;}
LordLupin::LordLupin(int i, int eventID){levelO=(i + eventID)%10 + 1;}
void LordLupin::run(BaseKnight * lastKnight){ this->lastKnight=lastKnight;event1_5(450, 45); }
//Elf::Elf(BaseKnight * lastKnight, i):BaseKnight(lastKnight) {levelO=(i + 1)%10 + 1;}
Elf::Elf(int i, int eventID){levelO=(i + eventID)%10 + 1;}
void Elf::run(BaseKnight * lastKnight){ this->lastKnight=lastKnight;event1_5(750, 75); }
//Troll::Troll(BaseKnight * lastKnight, i):BaseKnight(lastKnight) {levelO=(i + 1)%10 + 1;}
Troll::Troll(int i, int eventID){levelO=(i + eventID)%10 + 1;}
void Troll::run(BaseKnight * lastKnight){ this->lastKnight=lastKnight;event1_5(800, 95); }
//Tornbery::Tornbery(BaseKnight * lastKnight, i):BaseKnight(lastKnight) {levelO=(i + 1)%10 + 1;}
Tornbery::Tornbery(int i, int eventID){levelO=(i + eventID)%10 + 1;}
void Tornbery::run(BaseKnight * lastKnight)
{
    this->lastKnight=lastKnight;
    if(lastKnight->level >= levelO)
    {
        lastKnight->level+=1;
        if(lastKnight->level>10) lastKnight->level=10;
    }
    else if(lastKnight->knightType!=DRAGON)
         {
             //trung doc
             if( lastKnight->antidote > 0 )
             {
                 --lastKnight->antidote;
                 (lastKnight->bag)->swapDel(ANTIDOTE);//cout << endl<<"ok"<<endl; //lenh nay loi
             }
             else
             {
                 int count6=3;
                 BaseItem * del;
                 while( count6>0 && (lastKnight->bag)->head!=NULL )
                 {
                     --count6;
                     del=(lastKnight->bag)->head;
                     (lastKnight->bag)->head=((lastKnight->bag)->head)->link;
                     delete del;
                 }
                 lastKnight->hp-=10;
                 if (lastKnight->hp <= 0) negHP();
             }
         }
    //if (lastKnight->hp <= 0) negHP();
}
//QueenOfCards::QueenOfCards(BaseKnight * lastKnight, i):BaseKnight(lastKnight){ }
QueenOfCards::QueenOfCards(int i, int eventID){levelO=(i + eventID)%10 + 1;}
void QueenOfCards::run(BaseKnight * lastKnight)
{
    this->lastKnight=lastKnight;
    if(lastKnight->level >= levelO)
    {
        lastKnight->gil*=2;
        lastKnight->gil=lastKnight->gil >= 999 ? 999 : lastKnight->gil;
        rest=lastKnight->gil-999;
    }
    else if(lastKnight->knightType!=PALADIN) lastKnight->gil/=2;//check vu lay phan nguyen ???
}
void NinaDeRings::run(BaseKnight * lastKnight)
{
    this->lastKnight=lastKnight;
    if(lastKnight->knightType!=PALADIN){
    if(lastKnight->gil >= 50 && lastKnight->hp <= int((lastKnight->maxhp)/3))
    {
        lastKnight->gil-=50;
        lastKnight->hp+=int((lastKnight->maxhp)/5);
    }
    }
    else if(lastKnight->hp <= int((lastKnight->maxhp)/3))
         {
             lastKnight->hp+=int((lastKnight->maxhp)/5);
         }
}
void DurianGarden::run(BaseKnight * lastKnight){ this->lastKnight=lastKnight;lastKnight->hp = lastKnight->maxhp; }
bool OmegaWeapon::win;
OmegaWeapon::OmegaWeapon(){win=false;}
void OmegaWeapon::run(BaseKnight * lastKnight)
{
    this->lastKnight=lastKnight;
    if(!win)
    {
        if( (lastKnight->level ==10 && lastKnight->hp == lastKnight->maxhp) || lastKnight->knightType==DRAGON )
        {
            win=true;
            lastKnight->level=10;
            lastKnight->gil=999;
        }
        else
        {
            lastKnight->hp=0;
            negHP();
        }
    }
}
bool Hades::win;
Hades::Hades(){win=false;PaladinShield=false;}
void Hades::run(BaseKnight * lastKnight)
{
    this->lastKnight=lastKnight;
    if(!win)
    {
        if( lastKnight->level ==10 || (lastKnight->knightType == PALADIN && lastKnight->level >= 8) )
        {
            win=true;
            PaladinShield=true;/////////////////////////////////
        }
        else
        {
            lastKnight->hp=0;
            negHP();
        }

    }
}
/*
void Ultimecia::run()
{
    if(lastKnight->hasExcaliburSword()) //dang o day
}
*/


/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class Evetns * * */
Events::Events ( const string & file_events )
{
    string str;
    ifstream input(file_events);
    getline(input,str);
    stringstream strstream_1(str);
    strstream_1 >> events_num;
    //cout << events_num <<endl;

    eventsArray=new int[events_num];
    for(int i=0;i<=events_num-2;i++)
    {
        getline(input,str,' ');
        stringstream strstream_2(str);
        strstream_2 >> eventsArray[i];
    }
    getline(input,str);
    stringstream strstream_2(str);
    strstream_2 >> eventsArray[events_num-1];
    input.close();
    //for(int i=0;i<=events_num-1;i++){cout << events[i] <<endl;}
}
int Events::count() const {    return events_num;}
int Events::get( int i) const {    return eventsArray[i];}
Events::~Events() {    delete[] eventsArray;}
/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class BaseBag * * */
/*
struct Node
{
    ItemType itemType;
    Node * link;
};
*/
bool BaseBag::insertFirst(BaseItem * item)
{
    if(bagCount<max_num)
    {
        item -> link = head;
        head = item;
        ++bagCount;
        return true;
    }
    else return false;
}
bool PaladinBag::insertFirst(BaseItem * item)
{
    item -> link = head;
    head = item;
    ++bagCount;
    return true;
}
bool DragonBag::insertFirst(BaseItem * item)
{
    if(item->itemType != ANTIDOTE && bagCount<max_num)
    {
        item -> link = head;
        head = item;
        ++bagCount;
        return true;
    }
    else return false;
}
BaseItem * BaseBag::get(ItemType itemType)
{
    BaseItem * temp = head;
    while(temp!=NULL && temp->itemType!=itemType){ temp = temp->link;}
    return temp;
}
string BaseBag::toString() const
{
    string s="Bag[count="+to_string(bagCount)+";";
    BaseItem * temp = head;
    for(int i=0; i<bagCount; i++)
    {
        if(temp->itemType==ANTIDOTE) s+="Antidote";
        else if(temp->itemType==PHOENIXDOWNI) s+="PhoenixI";
             else if(temp->itemType==PHOENIXDOWNII) s+="PhoenixII";
                  else if(temp->itemType==PHOENIXDOWNIII) s+="PhoenixIII";
                       else if(temp->itemType==PHOENIXDOWNIV) s+="PhoenixIV";
        if(i!=bagCount-1) s+=",";
        temp=temp->link;
    }
    s+="]";
    return s;
}
bool BaseBag::swapDel(ItemType itemType)
{
    if(get(itemType)!=NULL)
    {
        BaseItem * pre=NULL, * cur=head;
        while(cur!=get(itemType))
        {
            pre=cur;
            cur=cur->link;
        }

        //xoa node
        if(pre!=NULL)
        {
        pre->link=head;
        head->link=cur->link;
        head=head->link;
        delete cur;
        --bagCount;
        return true;
        }
        else
        {
            head=head->link;
            delete cur;
        --bagCount;
        return true;
        }
    }
    else return false;
}



BaseBag::BaseBag()
{
    this->knight=knight;
    head=NULL;
    bagCount=0;
    negHP=false;
}
PaladinBag::PaladinBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num)
{
    max_num=-999;
    for(int i=0; i<phoenixdownI_num; i++)
    {
        //BaseItem * temp = new PhoenixDownI();
        insertFirst(new PhoenixDownI());
        //++bagCount;
    }
    for(int i=0; i<antidote_num; i++)
    {
        insertFirst(new Antidote());
        //++bagCount;
    }
}
LancelotBag::LancelotBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num)
{
    max_num=16;
    while( phoenixdownI_num>0 && bagCount<max_num )
    {
        insertFirst(new PhoenixDownI());
        --phoenixdownI_num;
        //++bagCount;
    }
    while( antidote_num>0 && bagCount<max_num )
    {
        insertFirst(new Antidote());
        --antidote_num;
        //++bagCount;
    }
}
DragonBag::DragonBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num)
{
    max_num=14;
    while( phoenixdownI_num>0 && bagCount<max_num )
    {
        insertFirst(new PhoenixDownI());
        --phoenixdownI_num;
        //++bagCount;
    }
}
NormalBag::NormalBag(BaseKnight * knight, int phoenixdownI_num, int antidote_num)
{
    max_num=19;
    while( phoenixdownI_num>0 && bagCount<max_num )
    {
        insertFirst(new PhoenixDownI());
        --phoenixdownI_num;
        //++bagCount;
    }
    while( antidote_num>0 && bagCount<max_num )
    {
        insertFirst(new Antidote());
        --antidote_num;
        //++bagCount;
    }
}
BaseBag::~BaseBag()
{
    BaseItem * pDel;
    while(head!=NULL)
    {
        pDel=head;
        head=head->link;
        delete pDel;
    }
}






/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id)
        + ",hp:" + to_string(hp)
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

bool prime_num(int n)
{
    if (n==1) return false;
    for(int i=2;i<n;i++){ if(n%i==0) return false; }
    return true;
}
bool pythagoras(int maxhp)
{
    if (maxhp >=100)
    {
        int a=maxhp/100;
        maxhp=maxhp%100;
        int b=maxhp/10;
        maxhp=maxhp%10;
        int c=maxhp;
        if ( (a*a + b*b == c*c) || (a*a + c*c == b*b) || (c*c + b*b == a*a) ) return true;
        return false;
    }
    return false;
}
//BaseKnight * BaseKnight::temp=NULL;
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    //BaseKnight createTemp;

    //BaseKnight * temp = NULL;
    if (prime_num(maxhp))
    {
        //createTemp.
        //temp=
        return new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);//truyen gia tri ???
    }
    else if (maxhp==888)
         {
            //temp=
            return new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
         }
         else if (pythagoras(maxhp))
              {
                  //temp=
                  return new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
              }
              else
                  {
                      //temp=
                      return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
                  }
    //return temp;



}
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id=id;
    this->hp=maxhp;//check
    this->maxhp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;//?????????????????????????????????????????????????????????????????????????????????/
    //bag gan o class con
    //knightType gan o class con
}
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    knightType=PALADIN;
    this->bag=new PaladinBag(this, phoenixdownI, antidote);//check this alone co sai ko ######################?????????????????????????
}
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    knightType=LANCELOT;
    this->bag=new LancelotBag(this, phoenixdownI, antidote);//check this alone co sai ko ######################?????????????????????????
}
DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    knightType=DRAGON;
    this->bag=new DragonBag(this, phoenixdownI, 0);//check this alone co sai ko ######################?????????????????????????
}
NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    knightType=NORMAL;
    this->bag=new NormalBag(this, phoenixdownI, antidote);//check this alone co sai ko ######################?????????????????????????
}



/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights (const string & file_armyknights)
{
    PaladinShield=false;
    LancelotSpear=false;
    GuinevereHair=false;
    ExcaliburSword=false;

    string str;
    ifstream input(file_armyknights);
    getline(input,str);
    stringstream strstream_1(str);
    strstream_1 >> knights_num;
    knights_count=knights_num;//cout<<endl<<knights_count<<endl;

    armyKnights=new BaseKnight*[knights_num];
    for(int i=0;i<knights_num;i++)
    {
        int maxhp, level, gil, antidote, phoenixdownI;
        getline(input,str);
        stringstream strstream_2(str);
        strstream_2>>maxhp;
        strstream_2>>level;
        strstream_2>>phoenixdownI;
        strstream_2>>gil;
        strstream_2>>antidote;//getline(
        armyKnights[i]=BaseKnight::create(i+1, maxhp, level, gil, antidote, phoenixdownI);
    }
}
ArmyKnights::~ArmyKnights()
{
    //minh se thu hoi toan bo vung nho heap sau khi chay het chuong trinh chu ko thu hoi le te
    //minh van de dia chi cua hiep si da chet trong mang dong, neu xoa di thi them ham if(armyKnights[i]!=NULL)
    for(int i=0;i<knights_num;i++)
        if(armyKnights[i]!=NULL)  delete armyKnights[i];//event 99
    delete armyKnights;//check dung ko, xoa pointer to pointer
}
/*
void event_1_5 (int hp,int level, int gil, int i, int eventid)
//(int i, int event, int &HP, int &level, bool Lancelot, bool Arthur)
{
    int b= (i+1) % 10 ;
    int levelO = (i+1) > 6?(b > 5?b : 5) : b ;
    double baseDamage[5]={1,1.5,4.5,7.5,9.5};
    int damage = baseDamage[event-1] * levelO * 10;
                if( level>levelO || Lancelot==1 || Arthur==1 ){ level++; }
                else if(level<levelO){ HP=HP-damage; }
                //check level<=10
}
*/
/*
bool ArmyKnights::adventure (Events * events)
{

    for(int i=0;i<(events->count();i++)
    {
        switch(events->get(int i))
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                //event_1_5(i, arr[i], HP, level, Lancelot, Arthur);
                break;
        }
    }


}
*/
//----------------------------BEGIN cach minh nghi-------------------------------------------------
bool ArmyKnights::fight(BaseOpponent * opponent)
{
    //goi lastKnight()
    //lastKnight()->
    //todo
    opponent->run(lastKnight());
    return ( ((opponent->lastKnight)->hp)<=0 ? true : false );//check dung ko ???
    // phai return co hi sinh hay ko #???
}
int ArmyKnights::count() const
{
    //static knights_count=knights_num;
    //if (!fight(//todo)) knights_count-=1;//them tham so ham fight######################
    //cout<<endl<<knights_count<<endl;
    return knights_count;//cout<<endl<<knights_count<<endl;
}
BaseKnight * ArmyKnights::lastKnight() const
{
    //event 99
    int i=knights_num;
    while(armyKnights[i-1]==NULL)
    {
        --i;
    }
    return  armyKnights[i-1];
    //return armyKnights[knights_count-1];//ArmyKnights::count()
}
/*
bool fight ArmyKnights::(BaseOpponent * opponent)
{
    opponent->run();

}*/
bool ArmyKnights::adventure (Events * events)//ham nay co van de ###############???????????? // co ve van dung => check ki
{
    int beforeHP=lastKnight()->hp;
    for(int i=0;i<(events->count());i++)
    {
        BaseOpponent * CurOpponent=NULL;
        //int knights_count_112,knights_count_113,knights_count_114;
        BaseItem * item;
        switch(events->get(i))
        {
        case 1:
            CurOpponent=new MadBear(i, events->get(i));//MadBear(BaseKnight * lastKnight)
            break;
        case 2:
            CurOpponent=new Bandit(i, events->get(i));//MadBear(BaseKnight * lastKnight)
            break;
        case 3:
            CurOpponent=new LordLupin(i, events->get(i));//MadBear(BaseKnight * lastKnight)
            break;
        case 4:
            CurOpponent=new Elf(i, events->get(i));//MadBear(BaseKnight * lastKnight)
            break;
        case 5:
            CurOpponent=new Troll(i, events->get(i));//MadBear(BaseKnight * lastKnight)
            break;
        case 6:
            CurOpponent=new Tornbery(i, events->get(i));//MadBear(BaseKnight * lastKnight)
            break;
        case 7:
            CurOpponent=new QueenOfCards(i, events->get(i));//MadBear(BaseKnight * lastKnight)
            break;
        case 8:
            CurOpponent=new NinaDeRings();
            break;
        case 9:
            CurOpponent=new DurianGarden();
            break;
        case 10:
            CurOpponent=new OmegaWeapon();
            break;
        case 11:
            CurOpponent=new Hades();
            break;
        case 112:
            {

            int knights_count_112=knights_count;
            item = new PhoenixDownII();
            while( knights_count_112 > 0 && !armyKnights[knights_count_112-1]->bag->insertFirst(item) )
            {
                --knights_count_112;
            }
            if(knights_count_112 == 0) delete item;
            break;

            }
        case 113:
            {

            int knights_count_113=knights_count;
            item = new PhoenixDownIII();
            while( knights_count_113 > 0 && !armyKnights[knights_count_113-1]->bag->insertFirst(item) )
            {
                --knights_count_113;
            }
            if(knights_count_113 == 0) delete item;
            break;

            }
        case 114:
            {

            int knights_count_114=knights_count;
            item = new PhoenixDownIV();
            while( knights_count_114 > 0 && !armyKnights[knights_count_114-1]->bag->insertFirst(item) )
            {
                --knights_count_114;
            }
            if(knights_count_114 == 0) delete item;
            break;

            }
        case 95:
            PaladinShield=true;
            break;
        case 96:
            LancelotSpear=true;
            break;
        case 97:
            GuinevereHair=true;
            break;
        case 98:
            if(hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair()) ExcaliburSword=true;
            break;
        case 99:
            break;
        }

        //event 1 -> 11 va 99
        if(events->get(i) >= 1 && events->get(i) <= 11)
        {
        //while ( knights_count!=0 && fight(CurOpponent) ) //knights_count!=0 && ###???????????
        //    --knights_count;
        while ( knights_count!=0 && fight(CurOpponent) ) //knights_count!=0 && ###???????????
        {
            delete armyKnights[knights_count-1]; //event 99 ko lien quan
            --knights_count;
        }


        //event 11
        if(events->get(i)==11) if(CurOpponent->PaladinShield) PaladinShield=true;

        //check gil >999 du = rest :event 1,2,3,4,5,7 //CHECK DE NGOAI VONG WHILE HAY TRONG ##################??????????????????//
        if(CurOpponent->rest > 0)
        {
            int knights_count_gil=knights_count-1;
            while (CurOpponent->rest>0 && knights_count_gil>0 )
            {
                /*
                rest=rest - (999-armyKnights[knights_count_gil-1]->gil);
                armyKnights[knights_count_gil-1]->gil += rest;
                if(armyKnights[knights_count_gil-1]->gil >999) armyKnights[knights_count_gil-1]->gil;
                */
                if( CurOpponent->rest >= (999-armyKnights[knights_count_gil-1]->gil) )
                {
                    CurOpponent->rest -= (999-armyKnights[knights_count_gil-1]->gil);
                    armyKnights[knights_count_gil-1]->gil=999;
                }
                else
                {
                    armyKnights[knights_count_gil-1]->gil += CurOpponent->rest;
                    CurOpponent->rest=0;
                }
                --knights_count_gil;
            }
        }


        if(CurOpponent != NULL) delete CurOpponent;
        }
        else if(events->get(i)==99)
        {
            if(hasExcaliburSword()) ; //return true;///////////////////////////////////////
            else if( hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair() )
                 {
                     int knights_count99=knights_count;
                     //while ( knights_count99!=0 && lastKnight99->knightType == NORMAL ) //cho knights_count99 ve 3 loai hiep si phu hop
                        //--knights_count99;
                     //int * lastKnight99=armyKnights[knights_count99-1];
                     //if(knights_count99!=0){
                     while ( knights_count99!=0 && (armyKnights[knights_count99-1])->knightType == NORMAL )
                        --knights_count99;
                     int hpUltimecia=5000;
                     while( hpUltimecia >0 && knights_count99!=0)
                     {
                     //int * lastKnight99=armyKnights[knights_count99-1];
                     //lastKnight99=armyKnights[knights_count99-1];
                     //--knights_count99; check ki cho nay #############################???????????????????????????????
                     int knightBaseDamage;
                     if((armyKnights[knights_count99-1])->knightType == LANCELOT) knightBaseDamage=0.05;
                     else if((armyKnights[knights_count99-1])->knightType == PALADIN) knightBaseDamage=0.06;
                          else if((armyKnights[knights_count99-1])->knightType == DRAGON) knightBaseDamage=0.075;
                     int damage = (armyKnights[knights_count99-1])->hp * (armyKnights[knights_count99-1])->level * knightBaseDamage;
                     hpUltimecia-=damage;
                     if(hpUltimecia<=0) break;///////////////////////////////////////
                     delete armyKnights[knights_count99-1]; //event 99
                     --knights_count; //event 99
                     --knights_count99;
                     while ( knights_count99!=0 && (armyKnights[knights_count99-1])->knightType == NORMAL )
                        --knights_count99;
                     }
                     if(hpUltimecia <= 0 && knights_count99>0) ; //return true;////////////////////////////////////////////
                     else if(hpUltimecia > 0 && knights_count99==0) knights_count=0;//return false;///////////////////////////////
                 }
                 else knights_count=0; //////////////////return false;
        }


        //thuc hien su dung phoenixdown ở trang 8
        if(lastKnight()->bag->negHP=false && (lastKnight()->hp-beforeHP)<0 )//CHECK KI #################??????????????????
        {
            BaseItem * temp = (lastKnight()->bag)->head;
            while(temp!=NULL && !temp->canUse(lastKnight()) )
            {
                temp=temp->link;
            }
            if(temp!=NULL)
            {
                temp->use(lastKnight());
                lastKnight()->bag->swapDel(temp->itemType);
            }
        }
        lastKnight()->bag->negHP=false;


        //check hp,gil,..........####################################????????????????????????
        //check gil o day
        //if(lastKnight()->gil > 999 ) lastKnight()->gil=999;
        //DU THI TRUYEN LEN #########################################????????????????????????????????

        printInfo();//check may cai return tren
        if(knights_count==0) return false;//chua xet 99 #???? // return 99 riêng ở trên ???
        else if(events->get(i)==99)return true;
        //return true;

    }
    //return ;
}
bool ArmyKnights::hasPaladinShield() const
{
    return PaladinShield;
}
bool ArmyKnights::hasLancelotSpear() const
{
    return LancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const
{
    return GuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const
{
    return ExcaliburSword;
}

//----------------------------END cach minh nghi-------------------------------------------------


/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
void KnightAdventure::loadArmyKnights(const string &file_armyknights)
{
    armyKnights=new ArmyKnights(file_armyknights);//sai thi cap phat tren stack thoi
}
void KnightAdventure::loadEvents(const string &file_events)
{
    events=new Events(file_events);
}
void KnightAdventure::run()
{
    //chua hien thuc HET ?????
    armyKnights-> printResult( armyKnights->adventure(events) );
}
KnightAdventure::~KnightAdventure()
{
    delete armyKnights;
    delete events;
}

/* * * END implementation of class KnightAdventure * * */
