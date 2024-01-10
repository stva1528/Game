// CS1300 Spring 2021
// Author: Stella Vannier and Wren Hoertdoerfer
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
#include "PartyMember.h"
#include "Merchant.h"
#include "Room.h"
#include "NPC.h"
using namespace std;

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon 
{
    private:
    PartyMember teamParty[5];
    int partySize;
    bool keyFound;
    int angerLvl;
    Merchant merchant;
    Room rooms[5];

    public:
    Dungeon();
    void start();
    void quitGame();
    void finishGame();

    void menu();
    void status();
    void fightMonster();
    void speakToNPC();
    void cook();
    void exploreRoom();
    void openDoor();

    void misfortune(bool);

    // Getters
    int getAngerLvl();

    // Setters
    void addAngerLvl(int); // adds int to the anger level
};

#endif