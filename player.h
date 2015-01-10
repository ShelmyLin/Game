//! Player class defines the states and activities of a player
#ifndef _PLAYER_H
#define _PLAYER_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "random.h"
#include "global.h"
using namespace std;
class Player{
public:
    Player();
    ~Player();
public:
    unsigned int    id;                  ///< each player has its own id
    unsigned int    level;
    bool            gender;              ///< the gender of player, it can be MALE or FEMALE
    bool            live;                ///< to mark whether a player live(LIVING) or not(DEAD)
    unsigned int    money;
    unsigned int    hp;
    unsigned int    mp;
    unsigned int    hp_max;
    unsigned int    mp_max;
    unsigned int    intelligence;        ///< intelligence of a player
    unsigned int    strength;            ///< strength of a player
    unsigned int    experience;          ///< when a male succeed hunting, his experience will increase.
    unsigned int    phy_attack;          ///< attack value per second
    unsigned int    phy_armor;
    unsigned int    mag_armor;
    struct Point    position;     ///< a player's position
    struct Point    dest;         ///< a task destination
    Random Crandom;             /// Random class was uesd to generate a random number
public:
    void   Show();                           ///< show the states of a player
    bool   move();                           ///< when a player get a new destinion, he/she will move every day

};

#endif

