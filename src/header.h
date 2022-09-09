#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#ifdef _WIN32
#include <conio.h>
#define Block -37
#define Floor -80
#define Goal -79
#else
#include <stdio.h>
#define Block '#'
#define Floor ' '
#define Goal '='
#endif
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <stdlib.h>
#define MAXROWS 30
#define MAXCOLLUMNS 60

using namespace std;

class Item;

class Spell;

class Weapon;

class Armor;

class Potion;

class Monster;

class Object;

class Living{       //class for living beings
    private:
        string name;
    public:
        string image;
        int clrnum;
        int level;
        int healthPower;
        Living(const string,int,int);   //constructor
        ~Living();                      //destructor
        string getname() const;
        void checkHealthPower();
};

class Hero: public Living{      //class for heroes
    public:
        int magicPower;
        int strength;
        int dexterity;
        int agility;
        int protection;
        double money;
        int experience;
        vector<Weapon*> Inventoryitems1;    //array for saving the weapons of the hero
        vector<Potion*> Inventoryitems2;    //array for saving the potions of the hero
        vector<Armor*> Inventoryitems3;     //array for saving the armors of the hero
        vector<Spell*> Inventoryspells;     //array for saving the spells of the hero
        Weapon* lefthand=NULL;
        Weapon* righthand=NULL;
        Armor* arm=NULL;

        Hero(const string, int,int,int);    //constructor
        virtual ~Hero();                    //destructor
        void print();
        virtual void levelUp()=0;
        Spell* checkInventory(int);
        void equip(Weapon*w=NULL, Armor*a=NULL);
        void remove(Weapon* w=NULL,Armor* a = NULL);
        int Heroattack(Monster* ,int);
        int castSpell(Monster* , Spell*,int );
        void use(Potion* );

};

class Monster: public Living{           //class for monsters
    public:
        int Max;    //range of damage
        int Min;
        int defense;
        int avoidAttack;
        Monster(const string, const int , int); //constructor
        ~Monster();                             //destructor
        void print();
        virtual void normalize(int)=0;
};

class Warrior: public Hero{ //class for warriors
    public:
        Warrior(const string);
        ~Warrior();
        void levelUp();
};

class Paladin: public Hero{     //class for paladins
    public:
        Paladin(const string);
        ~Paladin();
        void levelUp();
};

class Sorcerer: public Hero{    //class for sorcerers
    public:
        Sorcerer(const string);
        ~Sorcerer();
        void levelUp();
};

class Exoskeleton: public Monster{  //class for exoskeletons
    public:
        Exoskeleton(const int, int);
        ~Exoskeleton();
        void normalize(int);
};

class Dragon: public Monster{   //class for dragons
    public:
        Dragon(const int, int);
        ~Dragon();
         void normalize(int);
};

class Spirit: public Monster{   //class for spirits
    public:
        Spirit(const int, int);
        ~Spirit();
        void normalize(int);

};


class Object{  //general base class for items and spells
    private:
        string name;
        double price;
        int MinimumLevelRequired;
    public:
        Object(const string , const double , const int ); //constructor
        ~Object(); //destructor
        string getname() const;
        double getprice() const;
        int getMinLevel() const;
        virtual void print()=0;
        virtual void buy(Hero*)=0;
        void sell(Hero*);
};

class Item: public Object{  //class for items
    public:
        Item(const string,const double,const int);
        virtual ~Item();
        void printitem();
};

class Weapon: public Item{  //class for weapons
    private:
        int damage; //value of damage to the opponent
        bool BothHands; //one or two hands
    public:
        Weapon(const string,const double,const int,const int, bool);
        ~Weapon();
        int getdamage();
        bool getBothHands();
        void print();
        void buy(Hero*);
};

class Armor: public Item{   //class for armors
    private:
        int ProtectionPercentage;   //value of protection offer
    public:
        Armor(const string,const double,const int,const int);
        ~Armor();
        int getProtectionPercentage();
        void print();
        void buy(Hero*);
};

class Potion: public Item{  //class for potions
    private:
        int addition;
        int statn;  //value deciding which characteristic of the hero will be increased
    public:
        Potion(const string,const double,const int,const int,const int);
        ~Potion();
        int getaddition();
        int getstatn();
        void print();
        void buy(Hero*);
};


class Spell: public Object{ //class for spells
    private:
        int Min;    //bounds of damage
        int Max;
        int MagicPower; //magic power needed
    protected:
        int amount; // for decreasing in each case
    public:
        Spell(const string , const double, const int,const int ,const int ,const int );
        virtual ~Spell();
        void RemoveMagicPower(Hero*);
        int LevelOfDamage(Hero* );
        int getMin() const;
        int getMax() const;
        int getMagicPower() const;
        void print();
        void buy(Hero*);
        virtual int Decrease(Monster* )=0;
};


class FireSpell: public Spell{  //class for firespells
    public:
        FireSpell(const string , const double , const int, int , int , int , const int );
        ~FireSpell();
        int Decrease(Monster* );
};

class IceSpell: public Spell{   //class for icespells
    public:
        IceSpell(const string , const double , const int , int , int , int , const int );
        ~IceSpell();
        int Decrease(Monster* );
};

class LightningSpell: public Spell{ //class for lightningspells
    public:
        LightningSpell(const string , const double , const int , int , int , int , const int );
        ~LightningSpell();
        int Decrease(Monster* );
};


string makeimage(string);

class CommonBlock{  //class for common accesible blocks
    private:
        char image;
    public:
        CommonBlock(char);
        ~CommonBlock();
        char getchar(){return image;}
        virtual void onBlock();
        bool accesible;
        bool battleworthy;
        bool shop;
};

class Market: public CommonBlock{   //class for Market blocks
    public:
        Market(char);
        ~Market();
        void onBlock();
};

class NonAccessible: public CommonBlock{    //class for unaccessible blocks
    public:
        NonAccessible(char);
        ~NonAccessible();
};

class GoalBlock: public CommonBlock{    //class for goal blocks( added to showcase block potential)
    public:
        GoalBlock(char);
        ~GoalBlock();
        void onBlock();
};

void clearscreen();

extern CommonBlock* Array[MAXROWS][MAXCOLLUMNS];

extern int counter;

void printMap(CommonBlock*[MAXROWS][MAXCOLLUMNS]);

void pressanybutton();

#ifndef WIN32
char getch();
#endif

int listchooseitem(Item**, float);

int listchoosespell(Spell**, float);

string makeimage(string);

void animation(Hero*, Monster*);

Monster* createMonsterType();

vector<Monster*> createRandomMonsters(vector<Monster*>);

bool heroAvoidAttack(Monster*, Hero*);

bool checkmonster(int, int, int, int);

void Monsterattack(Monster*,Hero*);

bool battleTheMonsters(vector<Monster*>);

void checkforLvlup();

bool battle(int);

void randombattle();

void createobjects();

void createmonsters();

void movemonsters();

void inventorymenu();

void equipmenu();

void potionmenu();

void shopmenu(Item**,Spell**,Hero*);

void createmap(CommonBlock*[MAXROWS][MAXCOLLUMNS]);

void nextlevel();

void createshop(Item**,Spell**);

void move(CommonBlock*[MAXROWS][MAXCOLLUMNS],Item**, Spell**);

void heroinfo(Hero*);

void displayheroes();

void startingscreen( CommonBlock*[MAXROWS][MAXCOLLUMNS],Item**,Spell**);

void herochoice(char, int);

void createheroes();

void herostart();