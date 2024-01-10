// CS1300 Spring 2021
// Author: Stella Vannier
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef ROOM_H
#define ROOM_H

class Room
{
    // Data members
    private:
    string roomName;
    int roomNum;
    string roomTreasures[3];
    string monsters[4];

    // Member functions
    public:
    Room();
    Room(string, string = "Room.txt", string = "Monster.txt"); 

    // Getters 
    string getRoomName();
    int getRoomNum();
    string getTreasure();
    string getMonster();
    
};

#endif