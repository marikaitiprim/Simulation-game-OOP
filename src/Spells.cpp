#include "header.h"

Spell::Spell(const string nam, const double pr, const int min,const int low,const int up,const int mp):Object(nam,pr,min){  //constructor
    Min = low;
    Max = up;
    MagicPower = mp;
}

Spell::~Spell(){}//destructor

void Spell::RemoveMagicPower(Hero* h){    //remove amount of magic power
    h->magicPower = h->magicPower - MagicPower;
}

int Spell::LevelOfDamage(Hero* h){
    int x=Max-Min+(h->dexterity/3);
	int y=rand()%(x)+Min;
	if(y<0){
		y=0;
	}
	return y;
}

//getters
int Spell::getMin() const{
    return Min;
}

int Spell::getMax() const{
    return Max;
}

int Spell::getMagicPower() const{
    return MagicPower;
}

void Spell::print(){
    cout << "Name: " << getname() << endl << "Price: " << getprice() << "$" << endl << "Minimum level required: " << getMinLevel() << endl;
    cout << "Range of damage: " << getMin() << "-" << getMax() << endl << "Magic power required: " << getMagicPower() << endl << endl;
}

void Spell::buy(Hero* hero){
    if(hero->money>=this->getprice()&&hero->level>=this->getMinLevel()){
        hero->money-=this->getprice();
        cout<<"Congratulations, you now own the "<<this->getname()<<endl;
        hero->Inventoryspells.push_back(this);  //save spell to the inventory of the hero
    }
    else if (hero->money<this->getprice()){
        cout<<"not enough money"<<endl;
    }
    else{
        cout<<"not enough level"<<endl;
    }
}


IceSpell::IceSpell(const string nam, const double pr, const int min,const int low,const int up,const int mp, const int am):Spell(nam,pr,min,low,up,mp){//constructor
    amount = am;    //initialize amount of decreasing opponent's defense
}

IceSpell::~IceSpell(){}//destructor

int IceSpell::Decrease(Monster* m){  //decrease range of damage of the monster
    m->Max = m->Max - amount;
    return m->Max;
}



FireSpell::FireSpell(const string nam, const double pr, const int min,const int low,const int up,const int mp, const int am):Spell(nam,pr,min,low,up,mp){//constructor
    amount = am;    //initialize amount of decreasing opponent's defense
}
FireSpell::~FireSpell(){}//destructor

int FireSpell::Decrease(Monster* m){ //decrease defense
    m->defense = m->defense - amount;
    return m->defense;
}


LightningSpell::LightningSpell(const string nam, const double pr, const int min,const int low,const int up,const int mp, const int am):Spell(nam,pr,min,low,up,mp){//constructor
    amount = am;    //initialize amount of decreasing opponent's defense
}

LightningSpell::~LightningSpell(){}//destructor

int LightningSpell::Decrease(Monster* m){  //decrease possibility of avoiding attack
    m->avoidAttack = m->avoidAttack - amount;
    return m->avoidAttack;
}