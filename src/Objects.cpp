#include "header.h"

Object::Object(const string nam, const double pr, const int min){   //constructor 
    name = nam;
    price = pr;
    MinimumLevelRequired = min;
} //constructor
        
Object::~Object(){} //destructor

//getters
string Object::getname() const{ 
    return name;
}
        
double Object::getprice() const{    
    return price;
}
        
int Object::getMinLevel() const{
    return MinimumLevelRequired;
}

void Object::sell(Hero* hero){
    hero->money = hero->money + price/2;    //sell an object in the half price
    cout << "You sold the " << name << " and you earned +" << price/2 << "$" << endl;
}