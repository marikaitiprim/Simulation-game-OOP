#include "header.h"

Living::Living(const string nam, int l, int hp){//constructor
    name = nam;
    level = l;
    healthPower = hp;
}

Living::~Living(){}//destructor

string Living::getname() const{
    return name;
}

void Living::checkHealthPower(){//check if the living being is alive
    if(healthPower == 0 ){
        cout<< getname() <<" , you died!" << endl;
    }
}
