// CS1300 Spring 2021
// Author: Stella Vannier and Wren Hoertdoerfer
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef PARTYMEMBER_H
#define PARTYMEMBER_H

class PartyMember
{
    // Data members
    private:
    string name;
    int fullness;
    bool leader;

    // Member functions
    public:
    PartyMember();
    PartyMember(string, bool);

    // Getters 
    string getName();
    int getFullness();

    bool isLeader();
    void loseFullness(int);
    void gainFullness(int);
};

#endif