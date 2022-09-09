#include "header.h"

Hero::Hero(const string nam, int st=2,int de=2 ,int ag=2):Living(nam,1,5){//constructor
    magicPower = 5;
    strength = st;
    dexterity = de;
    agility = ag;
    protection = 2;
    money = 20.0;
    experience = 2;
}

Hero::~Hero(){//destructor
}

void Hero::print(){
    cout << "Name: " << getname() << endl << "Level: " << level << endl << "Health power: " << healthPower << endl;
    cout << "Magic power: " << magicPower << endl << "Strength: " << strength << endl << "Dexterity: " << dexterity << endl;
    cout << "Agility: " << agility << endl << "Protection: " << protection << endl << "Money: " << money << endl << "Experience: " << experience << endl << endl;
}

//depending of the value of x, the function does the appropriate use
Spell* Hero::checkInventory(int x){ //check inventory or equip or use potion or use spell
    int a;
    char q,h;
    int num=1;
    if(Inventoryitems1.size()+Inventoryitems2.size()+Inventoryitems3.size()+Inventoryspells.size()==0){
            cout << "Your inventory is empty" << endl;
            return NULL;
    }
    //printing the whole inventory
    if(x==1||x==0){
        cout << "Your items: " << endl<< endl;
        for(int i=0;i<Inventoryitems1.size();i++){
            cout << num << ") ";
            Inventoryitems1.at(i)->print();
            num++;
        }
    }
    if(x==3||x==0){
        for(int i=0;i<Inventoryitems2.size();i++){
            cout << num << ") ";
            Inventoryitems2.at(i)->print();
            num++;
        }
    }
    if(x==1||x==0){
        for(int i=0;i<Inventoryitems3.size();i++){
            cout << num << ") ";
            Inventoryitems3.at(i)->print();
            num++;
        }
    }
    if(x==2||x==0){
        cout << "\nYour spells: " << endl << endl;
        for(int i = 0;i<Inventoryspells.size();i++){
            cout << i+1 << ") ";
            Inventoryspells.at(i)->print();
        }
    }
    if(x==1){                                                              //equip & unequip
        cout << "Do you want to equip or to unequip? Press e to equip, u to unequip, press x to exit" << endl;
        cin >> q;
        while(q!='x'&&q!='X'){
            if(q =='u' || q == 'U'){//unequip
                if(lefthand == NULL && righthand == NULL && arm==NULL){
                    cout << "Your hands are empty, you cannot unequip" << endl;
                }
                else{
                    if(lefthand == NULL){
                        cout << "Left hand is empty"<<endl;
                    }
                    else{
                    cout << "Left hand: " << lefthand->getname()<<endl; 
                    }
                    if(righthand == NULL){
                        cout <<endl<<"Right hand is empty " << endl;
                    }
                    else{
                        cout <<endl<< "Right hand: " << righthand->getname() <<endl;
                    }
                    if(arm==NULL){
                        cout<<endl<<"You are not wearing any Armor"<<endl;
                    }
                    else{
                        cout <<endl<<"You are wearing: "<< arm->getname() <<endl<<endl;
                    }
                    cout << "Which item do you want to remove? Press l for the one on the left hand, r for the one on the right hand, a for armor, any other character to exit" << endl;
                    cin >> h;
                    if(h == 'l'||h == 'L'){
                        if(lefthand == NULL){
                            cout << "Your left hand is empty, you cannot unequip" << endl;
                        }
                        else{
                            lefthand = NULL;
                        }
                    }
                    else if(h == 'r'||h == 'R'){
                        if(righthand == NULL){
                            cout << "Your right hand is empty, you cannot unequip" << endl;
                        }
                        else{
                            righthand= NULL;
                        }
                    }
                    else if(h=='a'||h=='A'){
                        if(arm==NULL){
                            cout<<"You are not wearing any armor, you cannot unequip"<<endl<<endl;
                        }
                        else{
                            arm=NULL;
                        }
                    }
                }
            }
            else if(q == 'E' || q == 'e'){  //equip
                if(Inventoryitems1.size()+Inventoryitems3.size()==0){
                    cout << "Your inventory is empty" << endl;
                    return NULL;
                }
                cout << "Choose the item you want to equip:" << endl;
                cin >> a;
                while(a<1 || a>Inventoryitems1.size()+Inventoryitems3.size()){
                    cout << "Please try again" << endl;
                    cin >> a;
                }
                if(a<=Inventoryitems1.size()){
                    Weapon* s = Inventoryitems1.at(a-1);
                    equip(s);
                   //return NULL;
                }
                if(a>Inventoryitems1.size()){
                    Armor* s = Inventoryitems3.at(a-1-Inventoryitems1.size());
                    equip(NULL,s);
                    //return NULL;
                }
            }
        cout << "Do you want to equip or to unequip? Press e to equip, u to unequip, press x to exit" << endl;
        cin >> q;
        }
    }
    if(x==2){                                                                   //use spell
        if(Inventoryspells.size()==0){
            cout << "Your inventory is empty" << endl;
            return NULL;
        }
        cout << "Choose the spell you want to use:" << endl;
        cin >> a;
        while(a<1||a>Inventoryspells.size()){
            cout << "Please try again" << endl;
            cin >> a;
        }
        Spell* s = Inventoryspells.at(a-1);
        return s;
    }
    if(x==3){                                                                            //use potion
        if(Inventoryitems2.size()==0){
            cout << "Your inventory is empty" << endl;
            return NULL;
        }
        cout << "Choose the potion you want to use: " << endl;
        cin >> a;
        while(a<1||a>Inventoryitems2.size()){
            cout << "Please try again" << endl;
            cin >> a;
        }
        Potion* s = Inventoryitems2.at(a-1);
        use(s);
        Inventoryitems2.erase(Inventoryitems2.begin()+a-1);
        return NULL;
    }
    return NULL;
}

void Hero::equip(Weapon* w, Armor* a){  //actual equip
    if(w!=NULL){//equip with a weapon
        if(this->lefthand!=w&&this->righthand!=w){
            cout<< getname() <<" Using Weapon: "<< w->getname()<<endl;
            strength += w->getdamage();
            if(w->getBothHands()){
                if(lefthand==NULL && righthand==NULL){//empty hands
                    lefthand = w;
                    righthand = w;
                }
                else{
                    cout<<"you can't equip this weapon, it needs two hands"<<endl;
                    remove(w);
                }
            }
            else{
                if(lefthand==NULL){
                    lefthand=w;
                }
                else if(righthand==NULL){
                    righthand=w;
                }
                else {
                    cout<<"please remove a weapon"<<endl;
                    remove(w);
                }
            }
        }
        else{
            cout<<"You already equiped this weapon"<<endl;
        }
    }
    if(a!=NULL){//equip with an armor
        if(arm!=a){
            cout<<getname()<<" Equiped the Armor: "<<a->getname()<<endl;
            protection+=a->getProtectionPercentage();
            cout<<getname()<<" protection was raised by "<<a->getProtectionPercentage()<<endl;
            if(arm!=NULL){//arm full
                remove(NULL,a);
            }
            arm=a;
        }
        else{
            cout<<"You already equiped this armor"<<endl;
        }
    }

}

void Hero::remove(Weapon* w, Armor* a){ //remove item
    if(w!=NULL){//remove weapon
        cout<<getname()<<" Removing Weapon: "<<w->getname()<<endl;
        strength -= w->getdamage();
        if(lefthand==w){
            lefthand=nullptr;
        }
        if(righthand==w){
            righthand=nullptr;
        }
    }

    if(a!=NULL){//remove armor
        cout<<getname()<<" Unequiped the Armor: "<<a->getname()<<endl;
        protection-=a->getProtectionPercentage();
        arm=nullptr;
    }
}

void Hero::use(Potion* p){
    cout<<getname()<<" Using Potion: "<<p->getname()<<endl;
    switch(p->getstatn()){//depending on the value of statn, a characteristic is increasing
    case 1:
        healthPower+=p->getaddition();
        cout<<"Hero's "<<getname()<<" health power was raised by "<<p->getaddition()<<endl;
        break;
    case 2:
        agility+=p->getaddition();
        cout<<"Hero's "<<getname()<<" agility was raised by "<<p->getaddition()<<endl;
        break;
    case 3:
        strength+=p->getaddition();
        cout<<"Hero's "<<getname()<<" strength was raised by "<<p->getaddition()<<endl;
        break;
    default:
        cout<<"Potion had no effect on hero's Stats, but it sure was refreshing"<<endl;
        break;}
}

bool monsterAvoidAttack(Monster* monster, Hero* hero){
    int x=rand()%(hero->level*8);   //random possibility for a monster to avoid attack depending on hero's level
    if(x>=monster->avoidAttack){
        return false;
    }
    else{
        cout<<monster->getname()<<" avoided the attack from "<<hero->getname()<<endl;
        return true;
    }
}

int Hero::Heroattack(Monster* monster,int i){   //function for hero to attack to a monster
    bool flag=monsterAvoidAttack(monster,this);
    if(!flag){
        monster->healthPower-=strength-(monster->defense/2);
        if(monster->healthPower<0){
            monster->healthPower=0;
        }
        cout<<getname()<<" attacks "<<monster->getname()<<" and leaves him with "<< monster->healthPower<<" health"<<endl;
    }
                if(monster->healthPower==0){//monster died by the attack
                    cout<<monster->getname()<<" was slayed"<<endl;
                    return i+1;
                }
                else{
                    return i;
                }
}

int Hero::castSpell(Monster* monster, Spell* s,int i){  //function for hero to use spell
    bool flag=monsterAvoidAttack(monster,this);
    if(!flag){
        monster->healthPower-=s->LevelOfDamage(this);
        if(monster->healthPower<0){
            monster->healthPower=0;
        }
        s->Decrease(monster);//decreases monster's defense
        cout<<this->getname()<<" uses the spell: "<<s->getname()<<" on" <<monster->getname()<<" and leaves him with "<< monster->healthPower<<" health"<<endl;
    }
    if(monster->healthPower==0){//monster died
                    cout<<monster->getname()<<" was slayed"<<endl;
                    return i+1;
                }
                else{
                    return i;
                }
    }


Warrior::Warrior(const string nam):Hero(nam,3,2,3){//constructor
    this->image=makeimage("asciiart//warrior.txt");
    clrnum=33;
    print();
    
}
        
Warrior::~Warrior(){//destructor
}

void Warrior::levelUp(){    //increases level and the characteristics of the warrior
    strength = strength + 3;            
    dexterity = dexterity + 2;
    agility = agility + 3;
    magicPower = magicPower + 3;

    level++;
}
    


Paladin::Paladin(const string nam):Hero(nam,3,3){//constructor
    this->image=makeimage("asciiart//paladin.txt");
    clrnum=32;
    print();
}
        
Paladin::~Paladin(){//destructor
}

void Paladin::levelUp(){//increases level and the characteristics of the paladin
    strength = strength + 3;            
    dexterity = dexterity + 3;
    agility = agility + 2;
    magicPower = magicPower + 3;

    level++;
}


Sorcerer::Sorcerer(const string nam):Hero(nam,2,3,3){//constructor
    this->image=makeimage("asciiart//sorcerer.txt");
    clrnum=36;
    print();
}
        
Sorcerer::~Sorcerer(){//destructor
}
    
void Sorcerer::levelUp(){//increases level and the characteristics of the sorcerer
    strength = strength + 2;            
    dexterity = dexterity + 3;
    agility = agility + 3;
    magicPower = magicPower + 3;

    level++;
}