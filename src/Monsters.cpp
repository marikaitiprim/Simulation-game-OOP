#include "header.h"


Monster::Monster(const string nam, const int level, int hp):Living(nam, level, hp){} // constructor

Monster::~Monster(){} //destructor

void Monster::print(){
    cout<<"name: "<<this->getname()<<endl<<"level: "<<this->level<<endl<<"Health power: "<<this->healthPower<<endl<<"defence: "<<this->defense<<endl<<"avoid attack: "<<this->avoidAttack<<endl<<"range of damage from: "<<this->Min<<" to "<<this->Max<<endl;
}

Exoskeleton::Exoskeleton(const int lvl, int hp):Monster("Exoskeleton", lvl, hp){//constructor
    this->image=makeimage("asciiart//exoskeleton.txt");
    this->clrnum=34;
    this->defense=3*lvl;
    this->avoidAttack=2*lvl;
    this->Min=2*lvl;
    this->Max=4*lvl;
}

Exoskeleton::~Exoskeleton(){}//destructor

void Exoskeleton::normalize(int lvl){   //normalizes the characteristics of the monster
    this->defense=3*lvl;
    this->avoidAttack=2*lvl;
    this->Min=2*lvl;
    this->Max=4*lvl;
}

Dragon::Dragon(const int lvl, int hp):Monster("Dragon", lvl, hp){//constructor
    this->image=makeimage("asciiart//dragon.txt");
    this->clrnum=31;
    this->defense=2*lvl;
    this->avoidAttack=2*lvl;
    this->Min=3*lvl;
    this->Max=6*lvl;
}

Dragon::~Dragon(){//destructor

}

void Dragon::normalize(int lvl){//normalizes the characteristics of the monster
    this->defense=2*lvl;
    this->avoidAttack=2*lvl;
    this->Min=3*lvl;
    this->Max=6*lvl;
}

Spirit::Spirit(const int lvl, int hp):Monster("Spirit", lvl, hp){//constructor
    this->image=makeimage("asciiart//spirit.txt");
    this->clrnum=35;
    this->defense=2*lvl;
    this->avoidAttack=3*lvl;
    this->Min=2*lvl;
    this->Max=4*lvl;
}

Spirit::~Spirit(){//destructor

}

void Spirit::normalize(int lvl){//normalizes the characteristics of the monster
    this->defense=2*lvl;
    this->avoidAttack=3*lvl;
    this->Min=2*lvl;
    this->Max=4*lvl;
}