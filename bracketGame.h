#ifndef BRACKETGAME_H
#define BRACKETGAME_H

#include <iostream>     //for standard input and output objects
#include <string>       //for strings
#include <vector>       //vectors
#include <cstdlib>      //contatins several general purpose functions including binary search and random num generation
#include <cmath>        //contains a large number of basic math functions: notably exponents, trig, and rounding
#include <time.h>       //this is used for time management (which helps with random number generation)
#include <fstream>      //this allows for file opening and closing
#include <algorithm>    //this contains a large number of basic algorithms such as copy, minmax, and is_sorted
#include <Windows.h>    //for the sleep function
#include <thread>       //for time and sleep relating

using namespace std;

struct contender {
    string contenderName;   //name of the contender
    double powerLevel;      //strength of the contender.  The greater the absolute difference between two people, the greater the chance of winning.
    int stance;             //the current style of fighting used by the contender.  The stance gives direct power bonuses if used against a countering stance.  This also controls how much exhaustion is spent.
    int favoriteStance;
    double quickPower;
    double passionatePower;
    double flowingPower;
    double calmPower;
    double maxExhaustion;   //the amount of exhaustion the contender has to use before passing out.  If it hits 0, the contender will be unable to fight.
    double exhaustion;
    double percentExhaustion;      //how tired the contender is.  Higher exhaustion will impact the effectiveness of different stances while also lowering Power Level.
    //double maxHealth;       //the more macro fitness of the contender.  Health can be lost in fights and if it hits 0, the contender dies.
    //double health;          //the current health of the contender.  Will provide a direct decrease to Power Level based on how low it is relative to the Max Health.
    int roundRobinWins;
    int roundRobinPlace;
    bool player;
};

struct roundResult {
    contender winner;
    contender loser;
    double degreeOfVictory;   
};

struct bracketResults {
    contender winner;
    int numberOfRounds;
};

struct victoryChip {
    bool victory = 0;
    contender victor;
};

struct tournament {     //TODO: impliment this as a thing.
    int numberOfContenders = 1;     //number of contenders generated.
    bool roundRobinYes = true;      //whether or not there is a round robin preceding the bracket.
    int timeBetweenFights = 0;      //amount of time between fights.  Likely something like 0 is no time, 1 is 15 minutes, 2 is 30 minutes, 3 is an hour, and so on and so forth.  Longer times will give exponentially more exhuastion back.
    int winsNeeded = 1;             //how many wins needed to advance to the next stage in the bracket. 
};

roundResult round(contender &alpha, contender &beta);
contender fight(contender &alpha, contender &beta, int &numberOfRounds);
victoryChip checkForVictory(roundResult result, int &numberOfRounds);
void stancePickerManager(contender &alpha, contender &beta);
void playerStancePicker(contender &alpha, contender &beta);
void stancePicker(contender &alpha, contender &beta);
void recoverExhaustion(contender &alpha);
void createContender(contender &Guy);
double stanceAdvantage(int alpha, int beta);
void printContenderInfo(contender);
void printLessContenderInfo(contender Guy);
vector<string> createRandomNameList();
contender createRandomContender(ofstream &contenders);
void stancePointSetter(contender &alpha);
contender roundRobinFight(contender &alpha, contender &beta, int &numberOfRounds);
void bracket();
bracketResults variableBracket(int size, ofstream &contenders);
void printVariableBracket(vector<contender> bracket);
vector<contender> roundRobin(vector<contender> group);

double stanceBonus(contender alpha, contender beta);
void stanceExhaustion(contender &alpha, contender &beta);
void exhaustionChecker (contender &alpha);
void exhaustionPercentSetter(contender &alpha);
double exhaustionPowerLevel(contender alpha);
double passionate(double multiplier, contender alpha, contender beta);
double flowing(double multiplier, contender alpha, contender beta);
bool compareRoundRobinWins(contender alpha, contender beta);
double restBetweenMatches(string time); 
int roundCountController(int mode, int &numberOfRounds);
int gameCounter(int bracketSize);
void createTables(ofstream &contenders, ofstream &roundRobinWinners, ofstream &bracketWinners, int size);
void closeTables(ofstream &contenders, ofstream &roundRobinWinners, ofstream &bracketWinners, int size);
void insertIntoTable(ofstream &fileName, string tableName, contender contenderToEnter);
string nameController(int mode);

const int gamesPlayed = 1000;
const bool playerBracket = 0;
#endif