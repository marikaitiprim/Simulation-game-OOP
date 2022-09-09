#include "header.h"


Item::Item(const string n,const double p,const int l):Object(n,p,l){}//constructor

Item::~Item(){}//destructor

void Item::printitem(){
    cout << "Name: " << getname() << endl << "Price: " << getprice() << "$" << endl << "Minimum level required: " << getMinLevel() << endl;
}

Weapon::Weapon(const string n,const double p,const int l,const int d, bool h): Item(n,p,l),damage(d), BothHands(h){}//constructor

Weapon::~Weapon(){}//destructor

//getters
int Weapon::getdamage(){
    return damage;
}

bool Weapon::getBothHands(){
    return BothHands;
}

void Weapon::print(){
    printitem();
    cout<< "Damage: " << damage << endl;
    if(BothHands){
        cout<< "Use both hands!" << endl << endl;
    }
    else{
        cout << "Use one hand!" << endl << endl;
    }
}

void Weapon::buy(Hero* hero){
    if(hero->money>=this->getprice()&&hero->level>=this->getMinLevel()){    //enough money and level required
        hero->money-=this->getprice();
        cout<<"Congratulations, you now own the "<<this->getname()<<endl;
        hero->Inventoryitems1.push_back(this);                              //save weapon to the inventory
    }
    else if (hero->money<this->getprice()){
        cout<<"not enough money"<<endl;
    }
    else{
        cout<<"not enough level"<<endl;
    }
}

Potion::Potion(const string n,const double p,const int l,const int a,const int s): Item(n,p,l), addition(a), statn(s){}//constructor

Potion::~Potion(){}//destructor

//getters
int Potion::getaddition(){
    return addition;
}

int Potion::getstatn(){
    return statn;
}

void Potion::print(){
    printitem();
    if(statn == 1){
        cout<< "Increases health power by ";
    }
    else if(statn == 2){
        cout<< "Increases agility by ";
    }
    else if(statn == 3){
        cout<< "Increases strength by ";
    }
    cout << addition << endl << endl;
}

void Potion::buy(Hero* hero){
    if(hero->money>=this->getprice()&&hero->level>=this->getMinLevel()){
        hero->money-=this->getprice();
        cout<<"Congratulations, you now own the "<<this->getname()<<endl;
        hero->Inventoryitems2.push_back(this);  //save potion to the inventory
    }
    else if (hero->money<this->getprice()){
        cout<<"not enough money"<<endl;
    }
    else{
        cout<<"not enough level"<<endl;
    }
}

Armor::Armor(const string n,const double p,const int l,const int pr): Item(n,p,l), ProtectionPercentage(pr){}//constructor

Armor::~Armor(){}//destructor

int Armor::getProtectionPercentage(){//getter
    return ProtectionPercentage;
}

void Armor::print(){
    printitem();
    cout << "Protection: " << ProtectionPercentage << endl << endl;
}

void Armor::buy(Hero* hero){
    if(hero->money>=this->getprice()&&hero->level>=this->getMinLevel()){
        hero->money-=this->getprice();
        cout<<"Congratulations, you now own the "<<this->getname()<<endl;
        hero->Inventoryitems3.push_back(this);  //save armor to the inventory
    }
    else if (hero->money<this->getprice()){
        cout<<"not enough money"<<endl;
    }
    else{
        cout<<"not enough level"<<endl;
    }
}