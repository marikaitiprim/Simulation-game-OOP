#include "header.h"

CommonBlock::CommonBlock(char im=Floor): image(im){//constructor of a simple accessible block
    accesible=true;
    battleworthy=true;
    shop=false;
}

CommonBlock::~CommonBlock(){//destructor

}

void CommonBlock::onBlock(){ //when on a common block, check if you have to fight a monster
    int x=rand()%30+1;
    if(x==30){
        battle(0);
    }
    else{
        exit;
    }
}

Market::Market(char im='M'): CommonBlock(im){//constructor of market
    accesible=true;
    battleworthy=false;
    shop=true;
}

Market::~Market(){//destructor

}

void Market::onBlock(){ //when on a market block, print message
    cout<<"Press M to enter market"<<endl;
}

NonAccessible::NonAccessible(char im=Block): CommonBlock(im){// constructor for non accessible block
    accesible=false;
    battleworthy=false;
    shop=false;
}

NonAccessible::~NonAccessible(){//destructor

}

GoalBlock::GoalBlock(char im=Goal): CommonBlock(im){//constructor for reaching goal
    accesible=true;
    battleworthy=false;
    shop=false;
}

GoalBlock::~GoalBlock(){//destructor

}

void GoalBlock::onBlock(){//when reaching goal, update level
    this_thread::sleep_for(chrono::milliseconds(200));
    createmap(Array);
    counter++;
    printMap(Array);
}
