#include "header.h"

CommonBlock* Array[MAXROWS][MAXCOLLUMNS];   //creating the grid of the game

int counter;    //??

void clearscreen(){ //clearing screen when running the program
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

CommonBlock* common= new CommonBlock(Floor);//creating a simple accessible block
NonAccessible* blocked=new NonAccessible(Block);//creating a non accessible block
Market* M=new Market('M');//creating the blocks where you can access the shop
Market* A=new Market('A');
Market* R=new Market('R');
Market* K=new Market('K');
Market* E=new Market('E');
Market* T=new Market('T');
GoalBlock* goal=new GoalBlock(Goal);//creating a goal block

struct player{  //heroes' team, holds the current possition of the Player and the pointers to the three heroes
    int i;
    int j=MAXCOLLUMNS/2-1;
    Hero* hero1;
    Hero* hero2;
    Hero* hero3;

}Plr;

struct object{ //obstacles
    int i;
    int j;
}obj1, obj2, obj3, shop;

struct monsteicon{ //Struct for the monsters, holds their current possition, their direction, how much they have gone to that direction, and their health state
    bool alive;
    int i;
    int j;
    int steps;
    bool plus;
    void checkplayer(int x){    //function to check if Player is at the vicinity of a monster (same block, or infront of them)
        if(this->alive){
            int Pi=Plr.i;
            int Pj=Plr.j;
            if(this->i==Pi){
                if(this->j>1){
                    if(this->j%2==0){
                        if(this->j-1==Pj){
                            this->alive=battle(x);
                        }
                    }
                }
                if(this->j==Pj||this->j+1==Pj||this->j+2==Pj||this->j+3==Pj||this->j+4==Pj||this->j+5==Pj){
                    this->alive=battle(x);
                }
            }
            else if(this->plus&&(j==53||j==1)){
                if(this->i+1==Pi){
                    if(this->j-1==Pj||this->j==Pj||this->j+1==Pj||this->j+2==Pj||this->j+3==Pj||this->j+4==Pj||this->j+5==Pj){
                        this->alive=battle(x);
                    }
                }
            }
            else if(!this->plus&&(j==53||j==1)){
                if(this->i-1==Pi){
                    if(this->j-1==Pj||this->j==Pj||this->j+1==Pj||this->j+2==Pj||this->j+3==Pj||this->j+4==Pj||this->j+5==Pj){
                        this->alive=battle(x);
                    }
                }
            }
        }
    }
}dragon, spirit, exoske;    //(used to showcase monsters and to make the map more interesting)


int listchooseitem(Item** array, float money){   //to buy an item you have to choose it
    int n=-1;
    int max=12;
    int i=0;
    char c='a';
    int ascii=c;
    int pcounter=0;
    string sword=" o--[}========>    ";
    clearscreen();
    cout<<"Use w to scroll up, use s to scroll down, use x to leave, press Enter to choose"<<endl;
    cout<<"current money: "<<money<<"$"<<endl<<endl;
    for(i=0;i<max;i++){
                cout<<endl;
                if(pcounter==i){
                    cout<<"\033[33m"<<sword<<"\033[0m";
                    array[i]->print();  //show the characteristics of this item
                }
                else{
                    cout<<" "<<i+1<<" ."<<array[i]->getname()<<"   level: "<<array[i]->getMinLevel()<<" money: "<<array[i]->getprice()<<"$"<<endl;
                }
            }
    while( (c!='x') && (c!='X') ){ //while not exiting the buy section of items in the shop
        c=getch();
        ascii=c;
        if(c=='w'||c=='W'||c=='s'||c=='S'||ascii==13){
            clearscreen();
            cout<<"Use w to scroll up, use s to scroll down, use x to leave, press Enter to choose"<<endl;
            cout<<"current money: "<<money<<"$"<<endl<<endl;
            if(c=='w'||c=='W'){ // show the previous item
                if(pcounter>0){
                    pcounter--;}
                else pcounter=max-1;    //show the last item
            }
            else if(c=='s'||c=='S'){ //show the next item
                if(pcounter<max-1){
                    pcounter++;}
                else pcounter=0;    //show the first item
            }
            for(i=0;i<max;i++){
                cout<<endl;
                if(pcounter==i){
                    cout<<"\033[33m"<<sword<<"\033[0m";
                    array[i]->print();//show details of the item, when pointed at
                }
                else{
                    cout<<" "<<i+1<<" ."<<array[i]->getname()<<"   level: "<<array[i]->getMinLevel()<<" money: "<<array[i]->getprice()<<"$"<<endl;
                }

            }
            if(ascii==13){ //If you press enter, this will return the number of the item you choose
                cout<<"\nYou choose: "<<array[pcounter]->getname()<<endl;
                n= pcounter;
                break;
            }
            if(ascii==27||c=='x'||c=='X'){//exit from item choosing
                n= -1;
                break;
            }
        }
    }
    return n;
}

int listchoosespell(Spell** array, float money){//to buy a spell you have to choose it
    int n=-1;
    int max=6;
    int i=0;
    char c='a';
    int ascii=c;
    int pcounter=0;
    string wand=" -~==~~====~~=[+]>    ";
    clearscreen();
    cout<<"Use w to scroll up, use s to scroll down, use x to leave, press Enter to choose"<<endl;
    cout<<"current money: "<<money<<"$"<<endl<<endl;
    for(i=0;i<max;i++){
                cout<<endl;
                if(pcounter==i){
                    cout<<"\033[36m"<<wand<<"\033[0m";
                    array[i]->print();//show spell's details
                }
                else{
                    cout<<" "<<i+1<<" ."<<array[i]->getname()<<"   level: "<<array[i]->getMinLevel()<<" money: "<<array[i]->getprice()<<"$"<<endl;
                }
            }
    while( (c!='x') && (c!='X') ){  //while not exiting 
        c=getch();
        ascii=c;
        if(c=='w'||c=='W'||c=='s'||c=='S'||ascii==13){
            clearscreen();
            cout<<"Use w to scroll up, use s to scroll down, use x to leave, press Enter to choose"<<endl;
            cout<<"current money: "<<money<<"$"<<endl<<endl;
            if(c=='w'||c=='W'){     //move up to the list of spells
                if(pcounter>0){
                    pcounter--;}
                else pcounter=max-1;
            }
            else if(c=='s'||c=='S'){ //move down 
                if(pcounter<max-1){
                    pcounter++;}
                else pcounter=0;
            }
            for(i=0;i<max;i++){
                    cout<<endl;
                    if(pcounter==i){
                        cout<<"\033[36m"<<wand<<"\033[0m";
                        array[i]->print();  //print the details of the current spell
                    }
                    else{
                        cout<<" "<<i+1<<" ."<<array[i]->getname()<<"   level: "<<array[i]->getMinLevel()<<" money: "<<array[i]->getprice()<<"$"<<endl;
                    }
                }
            if(ascii==13){//when enter is used, return where it was used
                cout<<"\nYou choose: "<<array[pcounter]->getname()<<endl;
                n= pcounter;
                break;
            }
            if(ascii==27||c=='x'||c=='X'){ //exit spell choice
                n=-1;
                break;
            }
        }
    }
    return n; //returns the number of the spell in the array
}

string makeimage(string textname){  //images for monsters an heroes
    string o;   //string that holds the current line (from first letter till \n)
    string full;    //string that combines all the lines
    ifstream file(textname);
    if(file.is_open ()){
        while(!file.eof()){     //until the end copy the line on o
            getline(file,o);
            full +=o+"\n";      //patch o to the end of full
        }
    }
    file.close();
    return full;        //return the string, now attached with an image
}

void animation(Hero* curhero, Monster* curmonster){///arrange images of monsters and heroes so that it seems like a video game
    cout<<"____________________________________________________________________________________________________________________________________________"<<endl<<endl;
    cout<<"\t\t\t\t\t\t\t\t"<<curmonster->getname()<<": ";
    for(int i=1; i<=curmonster->healthPower;i+=curmonster->level){
        cout<<"|";
    }
    cout<<endl;
    cout<<"\033["<<curmonster->clrnum<<"m"<<curmonster->image<<"\033[0m"<<endl;
    cout<<"\033["<<curhero->clrnum<<"m"<<curhero->image<<"\033[0m"<<endl;
    cout<<"\t"<<curhero->getname()<<": ";
    for(int i=1; i<=curhero->healthPower;i+=curhero->level){
        cout<<"|";
    }
    cout<<endl;
    cout<<"_____________________________________________________________________________________________________________________________________________"<<endl<<endl;
}

Monster* createMonsterType(){   //creating monsters
    int i=rand()%3+1;   //choosing randomly which type of monster it will be created 
    Monster* randomMonster;
    int level=(counter)+1;
    switch(i){
        case 1:
        randomMonster=new Dragon(level,level*10);   //creating a boss dragon   used for the moving monsters of the map
        break;
        case 2:
        randomMonster=new Exoskeleton(level,level*10);  //creating a boss exoskeleton
        break;
        case 3:
        randomMonster=new Spirit(level,level*10);   //creating a boss spirit
        break;
    }
    return randomMonster;
}

vector<Monster*> createRandomMonsters(vector<Monster*> randomMonstersVector){   //store monsters in an array
    int x=rand()%5+1;
    for(int i=0;i<x;i++){
        randomMonstersVector.push_back(createMonsterType());
    }
    return randomMonstersVector;
}

bool heroAvoidAttack(Monster* monster, Hero* hero){ 
    int x=rand()%(monster->level*8);    //possibility a hero can avoid an attack depending on the level of the monster
    if(x>=hero->dexterity){ //and hero's dexterity
        return false;
    }
    else{
        cout<<hero->getname()<<" avoided the attack from "<<monster->getname()<<endl;
        return true;
    }
}

bool checkmonster(int curround, int spellrounds, int monsternumber, int monsterwithspell){//check if a monster has a spell on it
    if(monsternumber==monsterwithspell){
        if(curround!=spellrounds){
            return false;
        }
        else{
            cout<<"the spell is lifted from the monster"<<endl; //if a monster is enchanted, after enough rounds lift the spell
            return true;
        }
    }
    else{
        return false;
    }
}

void Monsterattack(Monster* monster,Hero*hero){
    bool flag=heroAvoidAttack(monster,hero);
    if(!flag){  //hero does not avoid attack
        int y=(monster->Max-monster->Min); //range of damage

        int damage=(monster->Min+rand()%(y+1)); 
        cout<<monster->getname()<<" attacks with "<<damage<<" damage"<<endl;
        if((hero->protection/2)<=damage){   //not enough protection
            hero->healthPower-=damage-(hero->protection/2); //loses healthpower
        }
        else{
            cout<<"hero protected himself from the attack"<<endl;
        }
        if(hero->healthPower<0){
            hero->healthPower=0;
        }
        cout<<hero->getname()<<" was attacked his health is now: "<<hero->healthPower<<endl;
    }
}

bool battleTheMonsters(vector<Monster*> curMonster){
    int i=0;
    int j;
    int rounds=1;
    Spell* s;
     int spellrounds=0;
    int numofmonsterwithspell;
    while(i<curMonster.size()){
        if(Plr.hero1->healthPower>0){   //hero 1 alive
            clearscreen();
            cout<<"Round: "<<rounds<<endl;
            cout<<Plr.hero1->getname()<<"'s turn"<<endl;
            cout<<"\tPress 1 to attack, 2 to use spell, 3 to use potion, 4 to equip weapons or armor and 0 to view Stats, 9 to forfeit (your score will become 0)"<<endl;
            animation(Plr.hero1,curMonster.at(i));
            char v;
            cin>>v;
            if(v>='0'&&v<='9'){
                j=v-'0';
            }
            while(j==0){    //showing details of heroes and monsters
                clearscreen();
                cout<<"Monsters:\n"<<endl;
                for(int num=0; num<curMonster.size();num++){
                    cout<<num+1<<". ";
                    curMonster.at(num)->print();
                    cout<<endl;
                }
                cout<<"\nHeroes:\n"<<endl;
                Plr.hero1->print();
                cout<<endl;
                Plr.hero2->print();
                cout<<endl;
                Plr.hero3->print();
                cout<<endl;
                pressanybutton();
                cout<<endl;
                clearscreen();
                cout<<"Round: "<<rounds<<endl;
                cout<<Plr.hero1->getname()<<"'s turn"<<endl;
                cout<<"\tPress 1 to attack, 2 to use spell, 3 to use potion, 4 to equip weapons or armor and 0 to view Stats, 9 to forfeit (your score will become 0)"<<endl;
                animation(Plr.hero1,curMonster.at(i));
                char v;
                cin>>v;
                if(v>='0'&&v<='9'){
                    j=v-'0';
                }
            }
            while(j<1||(j>4&&j!=9)){//not valid
                cout<<"please choose from 1,2,3"<<endl;
                char v;
                cin>>v;
                if(v>='0'&&v<='9'){
                    j=v-'0';
                }
            }
            switch(j){
                case 1: 
                i=Plr.hero1->Heroattack(curMonster.at(i), i); //hero's attack 
                break;
                case 2:
                s = Plr.hero1->checkInventory(2);   //use spell
                if(s==NULL){
                    break;
                }
                spellrounds = rounds + 2;   //duration of spell
                i=Plr.hero1->castSpell(curMonster.at(i),s, i);  //apply spell
                numofmonsterwithspell = i;
                break;
                case 3: 
                Plr.hero1->checkInventory(3); //use potion
                break;
                case 4:
                Plr.hero1->checkInventory(1); //equip/unequip
                break;
                case 9://skip battle
                Plr.hero1->healthPower=0;
                Plr.hero2->healthPower=0;
                Plr.hero3->healthPower=0;
                counter=0;  //lose scor
                break;
            }
                if(i==curMonster.size()){
                    return true;
                }
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
        if(Plr.hero2->healthPower>0){// the same for hero 2
            clearscreen();
            cout<<"Round: "<<rounds<<endl;
            cout<<Plr.hero2->getname()<<"'s turn"<<endl;
            cout<<"\tPress 1 to attack, 2 to use spell, 3 to use potion, 4 to equip weapons or armor and 0 to view Stats, 9 to forfeit (your score will become 0)"<<endl;
            animation(Plr.hero2,curMonster.at(i));
            char v;
                cin>>v;
                if(v>='0'&&v<='9'){
                    j=v-'0';
                }
            while(j==0){
                clearscreen();
                cout<<"Monsters:\n"<<endl;
                for(int num=0; num<curMonster.size();num++){
                    cout<<num+1<<". ";
                    curMonster.at(num)->print();
                    cout<<endl;
                }
                cout<<"\nHeroes:\n"<<endl;
                Plr.hero1->print();
                cout<<endl;
                Plr.hero2->print();
                cout<<endl;
                Plr.hero3->print();
                cout<<endl;
                pressanybutton();
                cout<<endl;
                clearscreen();
                cout<<"Round: "<<rounds<<endl;
                cout<<Plr.hero2->getname()<<"'s turn"<<endl;
                cout<<"\tPress 1 to attack, 2 to use spell, 3 to use potion, 4 to equip weapons or armor and 0 to view Stats, 9 to forfeit (your score will become 0)"<<endl;
                animation(Plr.hero2,curMonster.at(i));
                char v;
                cin>>v;
                if(v>='0'&&v<='9'){
                    j=v-'0';
                }
            }
            while(j<1||(j>4&&j!=9)){
                cout<<"please choose from 1,2,3"<<endl;
                char v;
                cin>>v;
                if(v>='0'&&v<='9'){
                    j=v-'0';
                }
            }
            switch(j){
                case 1:
                i=Plr.hero2->Heroattack(curMonster.at(i), i);
                break;
                case 2:
                s = Plr.hero2->checkInventory(2);
                if(s==NULL){
                    break;
                }
                spellrounds = rounds + 2;
                i=Plr.hero2->castSpell(curMonster.at(i),s, i);
                numofmonsterwithspell = i;
                break;
                case 3:
                Plr.hero2->checkInventory(3);
                break;
                case 4:
                Plr.hero2->checkInventory(1);
                break;
                case 9:
                Plr.hero1->healthPower=0;
                Plr.hero2->healthPower=0;
                Plr.hero3->healthPower=0;
                counter=0;
                break;
            }
                if(i==curMonster.size()){
                    return true;
                }
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
        if(Plr.hero3->healthPower>0){// the same for hero 3
            clearscreen();
            cout<<"Round: "<<rounds<<endl;
            cout<<Plr.hero3->getname()<<"'s turn"<<endl;
            cout<<"\tPress 1 to attack, 2 to use spell, 3 to use potion, 4 to equip weapons or armor and 0 to view Stats, 9 to forfeit (your score will become 0)"<<endl;
            animation(Plr.hero3,curMonster.at(i));
            char v;
                cin>>v;
                if(v>='0'&&v<='9'){
                    j=v-'0';
                }
            while(j==0){
                clearscreen();
                cout<<"Monsters:\n"<<endl;
                for(int num=0; num<curMonster.size();num++){
                    cout<<num+1<<". ";
                    curMonster.at(num)->print();
                    cout<<endl;
                }
                cout<<"\nHeroes:\n"<<endl;
                Plr.hero1->print();
                cout<<endl;
                Plr.hero2->print();
                cout<<endl;
                Plr.hero3->print();
                cout<<endl;
                pressanybutton();
                cout<<endl;
                clearscreen();
                cout<<"Round: "<<rounds<<endl;
                cout<<Plr.hero3->getname()<<"'s turn"<<endl;
                cout<<"\tPress 1 to attack, 2 to use spell, 3 to use potion, 4 to equip weapons or armor and 0 to view Stats, 9 to forfeit (your score will become 0)"<<endl;
                animation(Plr.hero3,curMonster.at(i));
                char v;
                cin>>v;
            if(v>='0'&&v<='9'){
                j=v-'0';
            }
            }
            while(j<1||(j>4&&j!=9)){
                cout<<"please choose from 1,2,3"<<endl;
                char v;
                cin>>v;
            if(v>='0'&&v<='9'){
                j=v-'0';
            }
            }
            switch(j){
                case 1:
                i=Plr.hero3->Heroattack(curMonster.at(i), i);
                break;
                case 2:
                s = Plr.hero3->checkInventory(2);
                if(s==NULL){
                    break;
                }
                spellrounds = rounds + 2;
                i=Plr.hero3->castSpell(curMonster.at(i),s, i);
                numofmonsterwithspell = i;
                break;
                case 3:
                Plr.hero3->checkInventory(3);
                break;
                case 4:
                Plr.hero3->checkInventory(1);
                break;
                case 9:
                Plr.hero1->healthPower=0;
                Plr.hero2->healthPower=0;
                Plr.hero3->healthPower=0;
                counter=0;
                break;
            }
            if(i==curMonster.size()){
                return true;;
            }
            this_thread::sleep_for(chrono::milliseconds(1500));
        }
        clearscreen();
        if(i==curMonster.size()){
                    return true;
                }
        cout<<"Round: "<<rounds<<"\n\t"<<curMonster.at(i)->getname()<<" attacks"<<endl<<endl; //monster's turn
        if(Plr.hero1->healthPower>0){ // attack on hero 1 if alive
            animation(Plr.hero1,curMonster.at(i));
            Monsterattack(curMonster.at(i),Plr.hero1);
            this_thread::sleep_for(chrono::milliseconds(1500));
            clearscreen();
            cout<<"Round: "<<rounds<<endl<<endl<<"everyone regenerates some health"<<endl;
            animation(Plr.hero1,curMonster.at(i));
            }
        else if(Plr.hero2->healthPower>0){//attack on hero 2 if alive
            animation(Plr.hero2,curMonster.at(i));
            Monsterattack(curMonster.at(i),Plr.hero2);
            this_thread::sleep_for(chrono::milliseconds(1500));
            clearscreen();
            cout<<"Round: "<<rounds<<endl<<endl<<"everyone regenerates some health"<<endl;
            animation(Plr.hero2,curMonster.at(i));
            }
        else if(Plr.hero3->healthPower>0){//attack on hero 3 if alive
            animation(Plr.hero3,curMonster.at(i));
            Monsterattack(curMonster.at(i),Plr.hero3);
            this_thread::sleep_for(chrono::milliseconds(1500));
            clearscreen();
            cout<<"Round: "<<rounds<<endl<<endl<<"everyone regenerates some health"<<endl;
            animation(Plr.hero3,curMonster.at(i));
            }
        else{
                return false;
            }
            cout<<"next round"<<endl;
            rounds++;   //next round
        if(checkmonster(rounds, spellrounds, i, numofmonsterwithspell)){//check if the monster has a spell 
            curMonster.at(i)->normalize(curMonster.at(i)->level);
            spellrounds=0;
        }//give each hero and monster some health( equal to their level) at the end of a round
        if(Plr.hero1->healthPower>0){
            if(Plr.hero1->healthPower<5*Plr.hero1->level){
                Plr.hero1->healthPower+=Plr.hero1->level;
                if(Plr.hero1->healthPower>5*Plr.hero1->level){
                    Plr.hero1->healthPower=5*Plr.hero1->level;
                }
            }
            if(Plr.hero1->magicPower<5*Plr.hero1->level){
                Plr.hero1->magicPower+=Plr.hero1->level;
                if(Plr.hero1->magicPower>5*Plr.hero1->level){
                    Plr.hero1->magicPower=5*Plr.hero1->level;
            }
            }
        }
        if(Plr.hero2->healthPower>0){
            if(Plr.hero2->healthPower<5*Plr.hero2->level){
                Plr.hero2->healthPower+=Plr.hero2->level;
                if(Plr.hero2->healthPower>5*Plr.hero2->level){
                    Plr.hero2->healthPower=5*Plr.hero2->level;
            }
            }
            if(Plr.hero2->magicPower<5*Plr.hero2->level){
                Plr.hero2->magicPower+=Plr.hero2->level;
                if(Plr.hero2->magicPower>5*Plr.hero2->level){
                    Plr.hero2->magicPower=5*Plr.hero2->level;
            }
            }
        }
        if(Plr.hero3->healthPower>0){
            if(Plr.hero3->healthPower<5*Plr.hero3->level){
                Plr.hero3->healthPower+=Plr.hero3->level;
                if(Plr.hero3->healthPower>5*Plr.hero3->level){
                    Plr.hero3->healthPower=5*Plr.hero3->level;
            }
            }
            if(Plr.hero3->magicPower<5*Plr.hero3->level){
                Plr.hero3->magicPower+=Plr.hero3->level;
                if(Plr.hero3->magicPower>5*Plr.hero3->level){
                    Plr.hero3->magicPower=5*Plr.hero3->level;
            }
            }
        }
        if(curMonster.at(i)->healthPower<10*curMonster.at(i)->level){
            curMonster.at(i)->healthPower+=curMonster.at(i)->level;
        }
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
        return true;
}

void checkforLvlup(){
    if(Plr.hero1->experience>=50+(Plr.hero1->level*10)){ //enough experience to level up
        cout<<endl<<Plr.hero1->getname()<<" Levels up to Level "<<Plr.hero1->level+1<<endl;
        Plr.hero1->experience=Plr.hero1->experience%(50+(Plr.hero1->level*10));
        Plr.hero1->levelUp();
    }
    cout<<Plr.hero1->getname()<<" has "<<Plr.hero1->experience<<" experience and "<<Plr.hero1->money<<"$ money!"<<endl;
    if(Plr.hero2->experience>=50+(Plr.hero2->level*10)){
        cout<<endl<<Plr.hero2->getname()<<" Levels up to Level "<<Plr.hero2->level+1<<endl;
        Plr.hero2->experience=Plr.hero2->experience%(50+(Plr.hero2->level*10));        
        Plr.hero2->levelUp();
    }
    cout<<Plr.hero2->getname()<<" has "<<Plr.hero2->experience<<" experience and "<<Plr.hero2->money<<"$ money!"<<endl;
    if(Plr.hero3->experience>=50+(Plr.hero3->level*10)){
        cout<<endl<<Plr.hero3->getname()<<" Levels up to Level "<<Plr.hero3->level+1<<endl;
        Plr.hero3->experience=Plr.hero3->experience%(50+(Plr.hero3->level*10));
        Plr.hero3->levelUp();
    }
    cout<<Plr.hero3->getname()<<" has "<<Plr.hero3->experience<<" experience and "<<Plr.hero3->money<<"$ money!"<<endl;
}

bool battle(int i){
    //string a;
    vector<Monster *> battleMonsterVector; 
    clearscreen();
    cout<<"\n\n\n\n\n\tTHIS IS BATTLE MENU "<<endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    fflush(stdin);
    if (i==0){
    battleMonsterVector=createRandomMonsters(battleMonsterVector); //create monsters and store them in an array
    }
    else if(i==1){
        battleMonsterVector.push_back(new Dragon((counter+2),(counter+2)*30));
        battleMonsterVector.at(0)->image=makeimage("asciiart//dragonboss.txt");
    }
    else if(i==2){
        battleMonsterVector.push_back(new Exoskeleton((counter+2),(counter+2)*30));
        battleMonsterVector.at(0)->image=makeimage("asciiart//exoskeletonboss.txt");
    }
    else if(i==3){
        battleMonsterVector.push_back(new Spirit((counter+2),(counter+2)*30));
        battleMonsterVector.at(0)->image=makeimage("asciiart//spiritboss.txt");
    }
    int monstercount;
    if(i==0){
        monstercount=battleMonsterVector.size();
    }
    else{
        monstercount=5;
    }
    cout<<"Your Enemies are:\n"<<endl;
    for(int i=0; i<battleMonsterVector.size();i++){
        cout<<i+1<<".     ";
        battleMonsterVector.at(i)->print();
    }
    pressanybutton();
    bool flag=battleTheMonsters(battleMonsterVector); //battle

     for(int i=battleMonsterVector.size()-1; i>=0;i--){
        delete battleMonsterVector.at(i);
    }
    battleMonsterVector.clear();
    pressanybutton();
    if(flag){           //heroes win
    cout<<"Congratulations, you won the fight"<<endl;
    Plr.hero1->experience+=10*monstercount+rand()%11; //earn experience
    Plr.hero2->experience+=10*monstercount+rand()%11;
    Plr.hero3->experience+=10*monstercount+rand()%11;
    Plr.hero1->money+=5*monstercount+rand()%11; //earn money
    Plr.hero2->money+=5*monstercount+rand()%11;
    Plr.hero3->money+=5*monstercount+rand()%11;
    if(Plr.hero1->healthPower==0){ //if hero dead
        Plr.hero1->healthPower=(5*Plr.hero1->level)/2;//reset to the half of the health power, if dead
        if((Plr.hero1->level*5)%2==1){
            Plr.hero1->healthPower++;
        }
    }
    if(Plr.hero2->healthPower==0){
        Plr.hero2->healthPower=(5*Plr.hero2->level)/2;
        if((Plr.hero2->level*5)%2==1){
            Plr.hero2->healthPower++;
        }
    }
    if(Plr.hero2->healthPower==0){
        Plr.hero2->healthPower=(5*Plr.hero2->level)/2;
        if((Plr.hero3->level*5)%2==1){
            Plr.hero3->healthPower++;
        }
    }
    checkforLvlup();
    pressanybutton();
    printMap(Array);
    return false;}
    else {
        clearscreen();
        cout<<"You lost!"<<endl;
        Plr.i=MAXROWS-2;
        Plr.j=MAXCOLLUMNS/2-1;
        Plr.hero1->healthPower=5*Plr.hero1->level/2;//reset power health to the half
        if((Plr.hero1->level*5)%2==1){
            Plr.hero1->healthPower++;
        }
        Plr.hero2->healthPower=5*Plr.hero1->level/2;
        if((Plr.hero2->level*5)%2==1){
            Plr.hero2->healthPower++;
        }
        Plr.hero3->healthPower=5*Plr.hero1->level/2;
        if((Plr.hero3->level*5)%2==1){
            Plr.hero3->healthPower++;
        }
        Plr.hero1->money=Plr.hero1->money/2;//hero loses half of his money
        Plr.hero2->money=Plr.hero2->money/2;
        Plr.hero3->money=Plr.hero3->money/2;
        printMap(Array);
        return true;
    }
}


//guide when displaying map
string text[]={"__________________________________________________________",
                "|PRESS X to Exit Map                                     |",
                "|                                                        |",
                "|Use W   to move around                                  |",
                "|   ASD                                                  |",
                "|                                                        |",
                "|Enter MARKET and press M to buy items or spells         |",
                "|                                                        |",
                "|Press I to see inventory                                |",
                "|                                                        |",
                "|Press E to equip                                        |",         
                "|                                                        |",
                "|Press U to use potion                                   |",    
                "|                                                        |",
                "|Reach the goal at the top of the map to raise your score|",
                "|                                                        |",
                "|There are three bosses on each floor but you better gear|",
                "|up before you face them. They give more exp and money   |",
                "|________________________________________________________|"
                };

void createobjects(){//create the 3 random objects, that look like a credit card, the greek letter (ex) and a fat exclamation point, and the possition of the market
    int x=(rand()%(MAXROWS-12))+4;
    int y=(rand()%(MAXCOLLUMNS-21))+8;          //use rand to give each object a different place each round
    if(y%2==0){
        y++;
    }
    obj1.i=x;
    obj1.j=y;
    x=(rand()%(MAXROWS-16))+4;
    y=(rand()%(MAXCOLLUMNS-24))+8;
    
    while(!(obj1.i+5<=x||x+5<=obj1.i)){         //make sure that 2 objects dont overlap too much
        x=(rand()%(MAXROWS-16))+4;
    }
    while(!(obj1.j+5<=y||y+7<=obj1.j)){
        y=(rand()%(MAXCOLLUMNS-26))+8;
    }
    if(y%2==0){
        y++;
    }
    obj2.i=x;
    obj2.j=y;
    x=(rand()%(MAXROWS-12))+6;
    y=(rand()%(MAXCOLLUMNS-26))+8;
    while((!(obj1.i+5<=x||x+3<=obj1.i))&&(!(obj2.i+5<=x||x+3<=obj2.i))){
        x=(rand()%(MAXROWS-12))+6;
    }
    while((!(obj1.j+5<y||y+7<obj1.j))&&(!(obj2.i+7<=y||y+7<=obj2.i))){
        y=(rand()%(MAXCOLLUMNS-26))+8;
    }
    if(y%2==0){
        y++;
    }
    obj3.i=x;
    obj3.j=y;

    int f=rand()%2;                //shop is either at the left or right bottom corner of the map, this function desided where on each level
    if(f==0){
        shop.i=MAXROWS-3;          //shop has a "wall" infront of it, this is used to set the wall and according to the wall the shop is set
        shop.j=1;
    }
    else{
        shop.i=MAXROWS-3;
        shop.j=MAXCOLLUMNS-7;
    }
}

void createmonsters(){//this creates the three movable monsters (bosses) and places them on the map
    dragon.alive=true;
    dragon.i=1;
    dragon.j=19;
    dragon.steps=0;
    dragon.plus=true;
    spirit.alive=true;
    spirit.i=1;
    spirit.j=1;
    spirit.steps=0;
    spirit.plus=true;
    exoske.alive=true;
    exoske.i=1;
    exoske.j=53;
    exoske.steps=0;
    exoske.plus=true;
}

void movemonsters(){//each time the player moves the monsters move
    if(dragon.alive){
        if(dragon.steps<16){
            if(dragon.plus==true){
                dragon.steps++;
                dragon.j++;
            }
            else if(dragon.plus==false){    //dragon goes left and right 16 steps, moving 1 step at a time from the top centre-left of the map
                dragon.steps++;
                dragon.j--;
            }
        }
        else{
            dragon.steps=0;
            if(dragon.plus==true){
                dragon.plus=false;
            }
            else{dragon.plus=true;}
        }
    }
    else{
        dragon.i=-1;
        dragon.j=-1;
    }
    if(spirit.alive){               //spirit goes 20 steps down and up, starting from the top left
        if(spirit.steps<20){
            if(spirit.plus==true){
                spirit.steps++;
                spirit.i++;
            }
            else if(spirit.plus==false){
                spirit.steps++;
                spirit.i--;
            }
        }
        else{
            spirit.steps=0;
            if(spirit.plus==true){
                spirit.plus=false;
            }
            else{spirit.plus=true;}
        }
    }
    else{
        spirit.i=-1;
        spirit.j=-1;
    }
    if(exoske.alive){       //exoskeleton goes 20 steps down and up, starting from the top right
        if(exoske.steps<20){
            if(exoske.plus==true){
                exoske.steps++;
                exoske.i++;
            }
            else if(exoske.plus==false){
                exoske.steps++;
                exoske.i--;
            }
        }
        else{
            exoske.steps=0;
            if(exoske.plus==true){
                exoske.plus=false;
            }
            else{exoske.plus=true;}
        }
    }
    else{
        exoske.i=-1;
        exoske.j=-1;
    }
}


void printMap(CommonBlock* blockArray[MAXROWS][MAXCOLLUMNS]){ //this prints the map, along with the entities (Player, moveable monsters) on it
    char Array[MAXROWS][MAXCOLLUMNS];
    for(int i=0;i<MAXROWS;i++){
        for(int j=0;j<MAXCOLLUMNS;j++){
            Array[i][j]=blockArray[i][j]->getchar();        //copy the block map on a char map, this way only the part that we care (the icon of each block) is used
        }
    }
    clearscreen();
    int aftertext=0;
    int i=0,j=0, textnum=0;
    for(i=0; i<MAXROWS; i++){                               //while the entities are on a different line, print the whole line of the map (quickest method, faster than cout)
        if(i!=Plr.i&&i!=dragon.i&&i!=spirit.i&&i!=exoske.i){    //makes the map print faster
            fwrite(&Array[i], sizeof(char), MAXCOLLUMNS, stdout);
            if(i>0){
                if(i>=1&&(!(text[textnum].empty()))){       //also print the quide next to the map
                    cout<<"\033[32m"<<text[textnum]<<"\033[0m";
                    textnum++;
                }
                else if(aftertext==0&&i>1){
                    cout<<"\033["<<Plr.hero1->clrnum<<"m"<<Plr.hero1->getname()<<"'s health: "<<Plr.hero1->healthPower<<"/"<<Plr.hero1->level*5<<"    mana: "<<Plr.hero1->magicPower<<"\033[0m";    //print info about the
                    aftertext++;
                }
                else if(aftertext==1&&i>1){
                    cout<<"\033["<<Plr.hero2->clrnum<<"m"<<Plr.hero2->getname()<<"'s health: "<<Plr.hero2->healthPower<<"/"<<Plr.hero2->level*5<<"    mana: "<<Plr.hero2->magicPower<<"\033[0m";    //heroes at the bottom
                    aftertext++;
                }
                else if(aftertext==2&&i>1){
                    cout<<"\033["<<Plr.hero3->clrnum<<"m"<<Plr.hero3->getname()<<"'s health: "<<Plr.hero3->healthPower<<"/"<<Plr.hero3->level*5<<"    mana: "<<Plr.hero3->magicPower<<"\033[0m";
                    aftertext++;
                }
            }
            else{
                cout<<"Your score: "<<counter;  //print score
            }
        }
        else{
            for(j=0; j<MAXCOLLUMNS; j++){                   //print entities, according to their coordinates on the map
                if(i==Plr.i&&j==Plr.j){
                    cout<<"\033[32m";
                    fwrite("P", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(i==Plr.i&&j==Plr.j+1){
                    cout<<"\033[32m";
                    fwrite("l", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(dragon.alive==true&&i==dragon.i&&j==dragon.j){
                    cout<<"\033[31m";
                    fwrite("D", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(dragon.alive&&i==dragon.i&&j==dragon.j+1){
                    cout<<"\033[31m";
                    fwrite("r", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(dragon.alive&&i==dragon.i&&j==dragon.j+2){
                    cout<<"\033[31m";
                    fwrite("a", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(dragon.alive&&i==dragon.i&&j==dragon.j+3){
                    cout<<"\033[31m";
                    fwrite("g", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(dragon.alive&&i==dragon.i&&j==dragon.j+4){
                    cout<<"\033[31m";
                    fwrite("o", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(dragon.alive&&i==dragon.i&&j==dragon.j+5){
                    cout<<"\033[31m";
                    fwrite("n", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(spirit.alive==true&&i==spirit.i&&j==spirit.j){
                    cout<<"\033[35m";
                    fwrite("S", sizeof(char), 1, stdout);
                    
                }
                else if(spirit.alive&&i==spirit.i&&j==spirit.j+1){
                    cout<<"\033[35m";
                    fwrite("p", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(spirit.alive&&i==spirit.i&&j==spirit.j+2){
                    cout<<"\033[35m";
                    fwrite("i", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(spirit.alive&&i==spirit.i&&j==spirit.j+3){
                    cout<<"\033[35m";
                    fwrite("r", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(spirit.alive&&i==spirit.i&&j==spirit.j+4){
                    cout<<"\033[35m";
                    fwrite("i", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(spirit.alive&&i==spirit.i&&j==spirit.j+5){
                    cout<<"\033[35m";
                    fwrite("t", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(exoske.alive==true&&i==exoske.i&&j==exoske.j){
                    cout<<"\033[34m";
                    fwrite("E", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(exoske.alive&&i==exoske.i&&j==exoske.j+1){
                    cout<<"\033[34m";
                    fwrite("x", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(exoske.alive&&i==exoske.i&&j==exoske.j+2){
                    cout<<"\033[34m";
                    fwrite("o", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(exoske.alive&&i==exoske.i&&j==exoske.j+3){
                    cout<<"\033[34m";
                    fwrite("s", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(exoske.alive&&i==exoske.i&&j==exoske.j+4){
                    cout<<"\033[34m";
                    fwrite("k", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else if(exoske.alive&&i==exoske.i&&j==exoske.j+5){
                    cout<<"\033[34m";
                    fwrite("e", sizeof(char), 1, stdout);
                    cout<<"\033[0m";
                }
                else{
                    fwrite(&Array[i][j], sizeof(char), 1, stdout);
                }
            }
            if(i>=1&&(!(text[textnum].empty()))){
                cout<<"\033[32m"<<text[textnum]<<"\033[0m";
                textnum++;
            }
            else if(aftertext==0&&i>1){
                cout<<"\033["<<Plr.hero1->clrnum<<"m"<<Plr.hero1->getname()<<"'s health: "<<Plr.hero1->healthPower<<"/"<<Plr.hero1->level*5<<"    mana: "<<Plr.hero1->magicPower<<"\033[0m";
                aftertext++;
            }
            else if(aftertext==1&&i>1){
                cout<<"\033["<<Plr.hero2->clrnum<<"m"<<Plr.hero2->getname()<<"'s health: "<<Plr.hero2->healthPower<<"/"<<Plr.hero2->level*5<<"    mana: "<<Plr.hero2->magicPower<<"\033[0m";
                aftertext++;
            }
            else if(aftertext==2&&i>1){
                cout<<"\033["<<Plr.hero3->clrnum<<"m"<<Plr.hero3->getname()<<"'s health: "<<Plr.hero3->healthPower<<"/"<<Plr.hero3->level*5<<"    mana: "<<Plr.hero3->magicPower<<"\033[0m";
                aftertext++;
            }
        }
	 fwrite("\n", sizeof(char), 1, stdout);
    }
}

void inventorymenu(){
    bool flag=true;
    while (flag)
    {
        clearscreen();
        cout<<"Choose the heroes inventory you want to see."<<endl;
        cout<<"press 1 for the first hero"<<endl;
        cout<<"press 2 for the second hero"<<endl;
        cout<<"press 3 for the third hero"<<endl;
        cout<<"press 0 to exit"<<endl;
        int i;
        char v;
        cin>>v;
            if(v>='0'&&v<='9'){
                i=v-'0';
            }
        clearscreen();
        switch(i){
            case 0:
                flag=false;
                break;
            case 1:
                cout<<"Displaying Hero no1 inventory"<<endl;
                Plr.hero1->checkInventory(0);   //just printing inventory things
                break;
            case 2:
                cout<<"Displaying Hero no2 inventory"<<endl;
                Plr.hero2->checkInventory(0);   
                break;
            case 3:
                cout<<"Displaying Hero no3 inventory"<<endl;
                Plr.hero3->checkInventory(0);   
                break;
            default:
                cout<<"Please choose a number from 0-3"<<endl;
                fflush(stdin);
                break;
        }
        if(i!=0){
            pressanybutton();
        }
    }
    printMap(Array);
}

void equipmenu(){
    bool flag=true;
    while (flag)
    {
        clearscreen();
        cout<<"Choose the hero you want to equip:"<<endl;
        cout<<"press 1 for the first hero"<<endl;
        cout<<"press 2 for the second hero"<<endl;
        cout<<"press 3 for the third hero"<<endl;
        cout<<"press 0 to exit"<<endl;
        int i;
        char v;
                cin>>v;
            if(v>='0'&&v<='9'){
                i=v-'0';
            }
        clearscreen();
        switch(i){
            case 0:
                flag=false;
                break;
            case 1:
                cout<<"Equip hero 1:"<<endl;
                Plr.hero1->checkInventory(1); //equip/unequip
                break;
            case 2:
                cout<<"Equip hero 2: "<<endl;
                Plr.hero2->checkInventory(1);
                break;
            case 3:
                cout<<"Equip hero 3"<<endl;
                Plr.hero3->checkInventory(1);
                break;
            default:
                cout<<"Please choose a number from 0-3"<<endl;
                fflush(stdin);
                break;
        }
        string a;
        if(i!=0){
            pressanybutton();
        }
    }
    printMap(Array);
}

void potionmenu(){
    bool flag=true;
    while (flag)
    {
        clearscreen();
        cout<<"Choose the hero you want to use potion."<<endl;
        cout<<"press 1 for the first hero"<<endl;
        cout<<"press 2 for the second hero"<<endl;
        cout<<"press 3 for the third hero"<<endl;
        cout<<"press 0 to exit"<<endl;
        int i;
        char v;
                cin>>v;
            if(v>='0'&&v<='9'){
                i=v-'0';
            }
        clearscreen();
        switch(i){
            case 0:
                flag=false;
                break;
            case 1:
                cout<<"Using potion on hero 1:"<<endl;
                Plr.hero1->checkInventory(3); //use potion
                break;
            case 2:
                cout<<"Using potion on hero 2"<<endl;
                Plr.hero2->checkInventory(3);
                break;
            case 3:
                cout<<"Using potion on hero 3"<<endl;
                Plr.hero3->checkInventory(3);
                break;
            default:
                cout<<"Please choose a number from 0-3"<<endl;
                fflush(stdin);
                break;
        }
        string a;
        if(i!=0){
            pressanybutton();
        }
    }
    printMap(Array);
}

void shopmenu(Item** array1,Spell** array2,Hero* h){
    bool flag = true;
    clearscreen();
    while(1){
        char inp,choose;
        cout<<"\n\n\n\n\n\tTHIS IS SHOP MENU\n\nPress b to buy an object, s to sell,x to exit"<<endl;
        cout << "\n\tBUY " << "\t\tSELL " << endl;
        cin>>inp;
        if(inp=='x'){ //exiting
            fflush(stdin);
            return;
        }
        while(inp!='b'&&inp!='s'){
            cout << "Please,press b to buy an object, s to sell" << endl;
            cin>>inp;
        }
        while(1){
            if(inp == 'b'){//buy
                clearscreen();
                cout<< "\n\n\n\n\n\tBUY\n\nPress i to see items, s to see spells, x to exit"<< endl << endl;
                cin>>choose;
                while(choose!='i'&&choose!='s'&&choose!='x'){
                    cout << "Please,press i to see items, s to see spells, x to exit" << endl;
                    cin>>choose;
                }
                if(choose=='x'){ //exiting
                    clearscreen();
                    break;
                }
                while(1){
                    flag = true;
                    if(choose=='i'){
                        int in=-1;
                        clearscreen();
                        cout << "Items: " << endl << endl;
                        cout<<"\n"<<h->getname()<<"'s money: "<<h->money<<"$"<<endl<<endl;
                        in=listchooseitem(array1, h->money); //choosing items
                        if(in==-1){
                            clearscreen();
                            break;
                        }
                        if(in>=0 &&in<=5){
                            for(int i=0; i<h->Inventoryitems1.size(); i++){
                                if(array1[in]==h->Inventoryitems1.at(i)){ //check if you already have this item
                                    cout << "You already have this item" << endl;
                                    this_thread::sleep_for(chrono::milliseconds(2000));
                                    flag = false;
                                }
                            }
                            if(flag==true){
                                array1[in]->buy(h); //buy item
                                this_thread::sleep_for(chrono::milliseconds(2000));
                            }
                        }
                        else if(in<=9 && in>5){
                            for(int i=0; i<h->Inventoryitems2.size(); i++){
                                if(array1[in]==h->Inventoryitems2.at(i)){
                                    cout << "You already have this item" << endl;
                                    this_thread::sleep_for(chrono::milliseconds(2000));
                                    flag = false;
                                }
                            }
                            if(flag==true){
                                array1[in]->buy(h);
                                this_thread::sleep_for(chrono::milliseconds(2000));
                                
                            }
                        }   
                        else if(in<=11 && in>9){
                            for(int i=0; i<h->Inventoryitems3.size(); i++){
                                if(array1[in]==h->Inventoryitems3.at(i)){
                                    cout << "You already have this item" << endl;
                                    this_thread::sleep_for(chrono::milliseconds(2000));
                                    flag = false;
                                    
                                }
                            }
                            if(flag==true){
                                array1[in]->buy(h);
                                this_thread::sleep_for(chrono::milliseconds(2000));
                                
                            }
                        }
                    }
                    else if(choose=='s'){
                        int in=-1;
                        clearscreen();
                        cout << "Spells: " << endl << endl;
                        cout<<"\n"<<h->getname()<<"'s money: "<<h->money<<"$"<<endl<<endl;
                        in=listchoosespell(array2, h->money); //choose spell from the store
                        if(in==-1){
                            clearscreen();
                            break;
                        }
                        if(in>=0&& in<=5){
                            for(int i=0; i<h->Inventoryspells.size(); i++){
                                if(array2[in]==h->Inventoryspells.at(i)){ //checking if you already have this spell
                                    cout << "You already have this spell" << endl;
                                    this_thread::sleep_for(chrono::milliseconds(2000));
                                    flag = false;
                                }
                            }
                            if(flag == true){
                                array2[in]->buy(h); //buy
                                this_thread::sleep_for(chrono::milliseconds(2000));
                            }
                        }
                    }
                }
            }
            else if(inp == 's'){ //sell
                int in;
                clearscreen();
                cout<<"\n"<<h->getname()<<"'s money: "<<h->money<<"$"<<endl;
                cout<< "\n\n\n\n\n\tSELL\n\nPress the number of the object you want to sell, press 0 to exit"<< endl << endl;
                h->checkInventory(0);
                string v;
                cin>>v;
                in=stoi(v);
                if(in==0){ //exiting
                    clearscreen();
                    break;
                }
                if(h->Inventoryitems1.size()+h->Inventoryitems2.size()+h->Inventoryitems3.size()+h->Inventoryspells.size()==0){ //empty inventory
                    cout << "Your inventory is empty, you can't sell anything" << endl;
                    this_thread::sleep_for(chrono::milliseconds(2000));
                    clearscreen();
                    break;
                }
                while(in>h->Inventoryitems1.size()+h->Inventoryitems2.size()+h->Inventoryitems3.size()+h->Inventoryspells.size()){ //out of the bounds
                    cout << "Not valid, try again: " << endl;
                    string v;
                    cin>>v;
                    in=stoi(v);
                }
                if(in<=h->Inventoryitems1.size()+h->Inventoryitems2.size()+h->Inventoryitems3.size() && h->Inventoryitems1.size()+h->Inventoryitems2.size()+h->Inventoryitems3.size()!=0){
                    if(in<=h->Inventoryitems1.size()){
                        h->Inventoryitems1.at(in-1)->sell(h); //sell weapon
                        h->Inventoryitems1.erase(h->Inventoryitems1.begin() + (in-1)); //delete weapon from inventory
                    }
                    else if(in<=h->Inventoryitems2.size()+h->Inventoryitems1.size()){
                        h->Inventoryitems2.at(in-1-h->Inventoryitems1.size())->sell(h); //sell potion
                        h->Inventoryitems2.erase(h->Inventoryitems2.begin() + (in-1-h->Inventoryitems1.size())); //delete potion from inventory
                    }
                    else if(in<=h->Inventoryitems1.size()+h->Inventoryitems2.size()+h->Inventoryitems3.size()){
                        h->Inventoryitems3.at(in-1-h->Inventoryitems1.size()+h->Inventoryitems2.size())->sell(h); //sell armor
                        h->Inventoryitems3.erase(h->Inventoryitems3.begin() + (in-1-h->Inventoryitems1.size()+h->Inventoryitems2.size())); //delete armor from inventory
                    }
                }
                else{
                    h->Inventoryspells.at(in-(h->Inventoryitems1.size()+h->Inventoryitems2.size()+h->Inventoryitems3.size()+1))->sell(h); //sell spell
                    h->Inventoryspells.erase(h->Inventoryspells.begin() + (in-(h->Inventoryitems1.size()+h->Inventoryitems2.size()+h->Inventoryitems3.size()+1))); //delete spell from inventory
                }
                this_thread::sleep_for(chrono::milliseconds(2000));
            }
        }
    }
}

void createmap(CommonBlock* Array[MAXROWS][MAXCOLLUMNS]){ //on each level create a new map

    createmonsters();
    createobjects();
    Plr.i=MAXROWS-2;    //place player at the bottom of the map

    for(int i=0; i<MAXROWS; i++){
        for(int j=0; j<MAXCOLLUMNS; j++){
            if(i==0){
                if(j>=MAXCOLLUMNS/2-5&&j<=MAXCOLLUMNS/2+4){         //create the goal (top mid)
                   Array[i][j]=goal;
                }
                else{
                    Array[i][j]=blocked;        //create the walls
                    }
            }
            else if(i==MAXROWS-1){
                Array[i][j]=blocked;
            }
            else if(j==0||j==MAXCOLLUMNS-1){
                Array[i][j]=blocked;
            }
            else if((obj1.i==i||obj1.i+1==i||obj1.i+2==i||obj1.i+4==i||obj1.i+5==i)&&(obj1.j==j||obj1.j+1==j||obj1.j+2==j||obj1.j+3==j||obj1.j+4==j||obj1.j+5==j)){
                Array[i][j]=blocked;                    //create the three obstacles (the many conditions give them their unique shape)
            }                                           //plane rectangles and squares would be borring
            else if((obj2.i==i||obj2.i+1==i||obj2.i+3==i||obj2.i+5==i)&&(obj2.j==j||obj2.j+1==j||obj2.j+2==j||obj2.j+3==j||obj2.j+4==j||obj2.j+5==j||obj2.j+6==j||obj2.j+7==j)){
                Array[i][j]=blocked;
            }
            else if((obj3.i==i||obj3.i+1==i||obj3.i+2==i||obj3.i+3==i)&&(obj3.j==j||obj3.j+1==j||obj3.j+2==j||obj3.j+3==j||obj3.j+6==j||obj3.j+7==j)){
                Array[i][j]=blocked;
            }
            else if(shop.i==i&&(shop.j==j||shop.j+1==j||shop.j+2==j||shop.j+3==j||shop.j+4==j||shop.j+5==j)){
                Array[i][j]=blocked;
            }
            else if(shop.i+1==i){               //place the wall on top of market (bottom left or right)
                if(j==shop.j){
                    Array[i][j]=M;
                }                               //create the market blocks
                else if(j==shop.j+1){
                    Array[i][j]=A;
                }
                else if(j==shop.j+2){
                    Array[i][j]=R;
                }
                else if(j==shop.j+3){
                    Array[i][j]=K;
                }
                else if(j==shop.j+4){
                    Array[i][j]=E;
                }
                else if(j==shop.j+5){
                    Array[i][j]=T;
                }
                else{
                    Array[i][j]=common;         //make anythign else a common block
                }
            }
            else{
                Array[i][j]=common;
            }
        }

    }
}

void createshop(Item** array1,Spell** array2){
    //create items
    //weapons
    array1[0] = new Weapon("Knight sword",5.50,1,5,false); 
    array1[1] = new Weapon("Fire bow",10.00,3,7,true);
    array1[2] = new Weapon("Spiked Rod",6.50,4,5,true);
    array1[3] = new Weapon("Death wand",14.50,5,8,false);
    array1[4] = new Weapon("Bomb",14.00,5,10,false);
    array1[5] = new Weapon("Punisher",25.00,7,12,true);
    //potions
    array1[6] = new Potion("Stamina tonic",6.00,2,5,1);
    array1[7] = new Potion("Speed Distiller",7.50,3,5,2);
    array1[8] = new Potion("Strong tablet",10.00,4,10,3);
    array1[9] = new Potion("Mega potion",20.00,5,15,1);
    //armors
    array1[10] = new Armor("Metal shield",4.00,1,5);
    array1[11] = new Armor("Crystal shield",15.00,4,10);

    //create spells
    //Icespells
    array2[0] = new IceSpell("Staff of ice",10.00,1,5,8,5,2);
    array2[1] = new IceSpell("Freeze Wave",14.50,5,10,14,9,5);
    //Firespells
    array2[2] = new FireSpell("Flame",12.50,4,7,12,8,4);
    array2[3] = new FireSpell("Fireball",16.00,6,9,15,11,7);
    //lightningspells
    array2[4] = new LightningSpell("Bolt",18.50,4,13,18,17,10);
    array2[5] = new LightningSpell("Light",22.00,7,17,20,20,12);
}

#ifndef WIN32   //for windows we use conio.h to utilize getch (gets a char without waiting for the operator to press enter)
char getch(){       //but for linux, we utilize the system(raw) functions to turn system back to a state where it didn't need enter, get the char
	char c;         //this way and then return the system back to normal
    int ascii;
    fflush(stdin);
    system ("/bin/stty raw");
    c=getchar();
    ascii=c;
    while(ascii==10){       //if character is \n, left by some cout, skip it
        c=getchar();
        ascii=c;
    }
	system ("/bin/stty cooked");
    fflush(stdin);
    return c;
}
#endif

void pressanybutton(){      //a nice way to pause the screen for the appropriet amount of time
    cout<<"\n\n\tPress any button to continue..."<<endl;
    char a=getch();
}

void move(CommonBlock* Array[MAXROWS][MAXCOLLUMNS],Item** array1, Spell** array2){//this allows the player to move in the map
    char key;
    int ascii;

    while(1){
        this_thread::sleep_for(chrono::milliseconds(100));
        key=getch();
        fflush(stdin);
        ascii=key;

        if(ascii==27||key=='x'||key=='X'){  //if esc or x is printed go to main menu
            break;
        }

        if(key=='w'||key=='W'||key=='a'||key=='A'||key=='s'||key=='S'||key=='d'||key=='D'||key=='i'||key=='I'||key=='e'||key=='E'||key=='m'||key=='M'||key=='u'||key=='U'){
            if(key=='w'||key=='W'){     //UP
                if(Array[Plr.i-1][Plr.j]->accesible){
                    Plr.i--;
                }
            }
            else if(key=='s'||key=='S'){        //DOWN
                if(Array[Plr.i+1][Plr.j]->accesible){
                    Plr.i++;
                }
            }
            else if(key=='a'||key=='A'){        //LEFT( by two blocks because the grid is 2 as wide)
                if(Array[Plr.i][Plr.j-1]->accesible&&Array[Plr.i][Plr.j-2]->accesible){
                    Plr.j-=2;
                }
            }
            else if(key=='d'||key=='D'){        //RIGHT (by two)
                if(Array[Plr.i][Plr.j+1]->accesible&&Array[Plr.i][Plr.j+2]->accesible){
                    Plr.j+=2;
                }
            }
            movemonsters();
            printMap(Array);
            if(dragon.alive==true){
            dragon.checkplayer(1);}
            if(spirit.alive==true){
            spirit.checkplayer(3);}
            if(exoske.alive==true){
            exoske.checkplayer(2);}
            if(key=='M'||key=='m'){     //Market
                if(Array[Plr.i][Plr.j]->shop){
                    cout<<"Choose the hero you want for the shop."<<endl;
                    cout<<"press 1 for the first hero"<<endl;
                    cout<<"press 2 for the second hero"<<endl;
                    cout<<"press 3 for the third hero"<<endl;
                    cout<<"press 0 to exit"<<endl;
                    int i;
                    char v;
                    cin>>v;
                    if(v>='0'&&v<='9'){
                        i=v-'0';
                    }
                    clearscreen();
                    while(i!=0){
                        switch(i){
                        case 0:
                            break;
                        case 1:
                            cout<<"\n\nHero no 1 "<<endl;
                            shopmenu(array1,array2,Plr.hero1);
                            break;
                        case 2:
                            cout<<"\n\nHero no 2 "<<endl;
                            shopmenu(array1,array2,Plr.hero2);
                            break;
                        case 3:
                            cout<<"\n\nHero no 3 "<<endl;
                            shopmenu(array1,array2,Plr.hero3);
                            break;
                        default:
                            cout<<"Please choose a number from 0-3"<<endl;
                            fflush(stdin);
                            break;
                        }
                        clearscreen();
                        printMap(Array);
                        cout<<"Choose the hero you want for the shop."<<endl;
                        cout<<"press 1 for the first hero"<<endl;
                        cout<<"press 2 for the second hero"<<endl;
                        cout<<"press 3 for the third hero"<<endl;
                        cout<<"press 0 to exit"<<endl;
                        cin>>v;
                        if(v>='0'&&v<='9'){
                            i=v-'0';
                        }
                        clearscreen();
                    }
                    printMap(Array);
                }
                else{
                    cout<<"this is not the market"<<endl;
                    this_thread::sleep_for(chrono::milliseconds(300));
                }
            }
            else if(key=='I'||key=='i'){
                inventorymenu();
            }
            else if(key=='E'||key=='e'){
                equipmenu();
            }
            else if(key=='U'||key=='u'){
                potionmenu();
            }
            Array[Plr.i][Plr.j]->onBlock();
            if(Plr.i==0){
                Plr.i=MAXROWS-2;
            }
            fflush(stdin);
        }
        else{
            cout<<"invalid input, please make sure you are using English."<<endl<<"Check the box next to the map to see your moves."<<endl;
            continue;
        }
    }
}

void heroinfo(Hero* hero){ //info for heroes
    hero->print();
    cout<<endl<<endl;
    cout<<"\033["<<hero->clrnum<<"m"<<hero->image<<"\033[0m"<<endl;
    pressanybutton();
    clearscreen();
}

void displayheroes(){ //displayng stats of heroes
    bool flag=true;
    while (flag)
    {
        clearscreen();
        cout<<"Choose the heroes stats you want to see."<<endl;
        cout<<"press 1 for the first hero"<<endl;
        cout<<"press 2 for the second hero"<<endl;
        cout<<"press 3 for the third hero"<<endl;
        cout<<"press 0 to exit"<<endl;
        int i;
        char v;
        cin>>v;
        if(v>='0'&&v<='9'){
            i=v-'0';
        }
        clearscreen();
        switch(i){
            case 0:
                flag=false;
                break;
            case 1:
                cout<<"Displaying Hero no1 info"<<endl;
                heroinfo(Plr.hero1);
                break;
            case 2:
                cout<<"Displaying Hero no2 info"<<endl;
                heroinfo(Plr.hero2);
                break;
            case 3:
                cout<<"Displaying Hero no3 info"<<endl;
                heroinfo(Plr.hero3);
                break;
            default:
                cout<<"Please choose a number from 0-3"<<endl;
                fflush(stdin);
                break;
        }
       
    }
}

void startingscreen( CommonBlock* Array[MAXROWS][MAXCOLLUMNS],Item** array1,Spell** array2){
    bool flag=true;
    char c;
    while(flag){
        clearscreen();
        cout<<"\nplease choose your action"<<endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        cout<<"Press H to view heroes"<<endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        cout<<"Press M to Display Map"<<endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        cout<<"Press X to Quit Game"<<endl;
        c=getch();
        int ascii=c;
        if(ascii==27){
            break;
        }
        switch (c){
            case 'H': case 'h':
                displayheroes();
                break;
            case 'M': case 'm':
                printMap(Array);
                move(Array,array1,array2);
                break;
            case 'X': case 'x':
                clearscreen();
                cout<<"Goodbye"<<endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                flag=false;
                break;
            default:
                cout<<"please choose a character from those mentioned above"<<endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                continue;
        }
    }
}
void herochoice(char type, int i){
    string name;
    if(type=='s'||type=='S'){
        cout<<"choose the name of your Sorcerer: "; //give name to your hero
        cin>>name;
        if(i==1){
        Plr.hero1=new Sorcerer(name);
        cout<<"\033["<<Plr.hero1->clrnum<<"m"<<Plr.hero1->image<<"\033[0m"<<endl;
        pressanybutton();}
        else if(i==2){
        Plr.hero2=new Sorcerer(name);
        cout<<"\033["<<Plr.hero2->clrnum<<"m"<<Plr.hero2->image<<"\033[0m"<<endl;
        pressanybutton();}
        else {
        Plr.hero3=new Sorcerer(name);
        cout<<"\033["<<Plr.hero3->clrnum<<"m"<<Plr.hero3->image<<"\033[0m"<<endl;
        pressanybutton();}
    }
    else if(type=='w'||type=='W'){
        cout<<"choose the name of your Warrior: ";
        cin>>name;
        if(i==1){
        Plr.hero1=new Warrior(name);
        cout<<"\033["<<Plr.hero1->clrnum<<"m"<<Plr.hero1->image<<"\033[0m"<<endl;
        pressanybutton();}
        else if(i==2){
        Plr.hero2=new Warrior(name);
        cout<<"\033["<<Plr.hero2->clrnum<<"m"<<Plr.hero2->image<<"\033[0m"<<endl;
        pressanybutton();}
        else {
        Plr.hero3=new Warrior(name);
        cout<<"\033["<<Plr.hero3->clrnum<<"m"<<Plr.hero3->image<<"\033[0m"<<endl;
        pressanybutton();}
    }
    else if(type=='p'||type=='P'){
        cout<<"choose the name of your Paladin: ";
        cin>>name;
        if(i==1){
        Plr.hero1=new Paladin(name);
        cout<<"\033["<<Plr.hero1->clrnum<<"m"<<Plr.hero1->image<<"\033[0m"<<endl;
        pressanybutton();}
        else if(i==2){
        Plr.hero2=new Paladin(name);
        cout<<"\033["<<Plr.hero2->clrnum<<"m"<<Plr.hero2->image<<"\033[0m"<<endl;
        pressanybutton();}
        else {
        Plr.hero3=new Paladin(name);
        cout<<"\033["<<Plr.hero3->clrnum<<"m"<<Plr.hero3->image<<"\033[0m"<<endl;
        pressanybutton();}
    }
    else{
        cout<<"not a valid letter please choose again. Remember w for Warrior, s for Sorcerer, p for Paladin"<<endl;
        cin>>type;
        herochoice(type,i);
    }
    cout<<endl<<"Congratulations, you now have the hero "<<name<<"!"<<endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

void createheroes(){
    char a;
    clearscreen();
    cout<<" Choose your first hero's type."<<endl<<"type w for Warrior, s for Sorcerer, p for Paladin"<<endl;
    cin>>a;
    herochoice(a,1); //creating hero depending on the choice a
    clearscreen();
    cout<<" Choose your second hero's type."<<endl<<"type w for Warrior, s for Sorcerer, p for Paladin"<<endl;
    cin>>a;
    herochoice(a,2);
    clearscreen();
    cout<<" Choose your third hero's type."<<endl<<"type w for Warrior, s for Sorcerer, p for Paladin"<<endl;
    cin>>a;
    herochoice(a,3);
}

void herostart(){ //start menu for heroes
    createheroes();
    clearscreen();
    cout<<"Now that your party is, ready, please enjoy this adventure"<<endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
}


int main(void){
    clearscreen();
    srand(time(NULL));
    Item** item_array = new Item*[12];  //array for storing items of the shop
    Spell** spell_array = new Spell*[6]; //array for storing spells of the shop

    createmap(Array);
    createshop(item_array,spell_array);
    counter=0;
    cout<<"Welcome to endless dungeons!"<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    herostart();
    startingscreen(Array,item_array,spell_array);
    
    
    for(int i=11;i>=0;i--){
        delete item_array[i];
    }
    for(int i=5;i>=0;i--){
        delete spell_array[i];
    }
    delete[] item_array;
    delete[] spell_array;
    delete Plr.hero1;
    delete Plr.hero2;
    delete Plr.hero3;
    delete common;
    delete blocked;
    delete M;
    delete A;
    delete R;
    delete K;
    delete E;
    delete T;
    delete goal;

    clearscreen();
    string a;
    cout<<"Congratulations, your score was "<<counter<<endl;
    pressanybutton();
    return 0;
}
