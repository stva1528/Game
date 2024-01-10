// CS1300 Spring 2021
// Author: Stella Vannier and Wren Hoertdoerfer
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
#include "PartyMember.h"
using namespace std;

PartyMember::PartyMember()
{
    name = "";
    leader = false;
    fullness = 10;
}

PartyMember::PartyMember(string n, bool l)
{
    name = n;
    leader = l;
    fullness = 10;
}

string PartyMember::getName()
{
    return name;
}

int PartyMember::getFullness()
{
    return fullness;
}

void PartyMember::loseFullness(int points)
{
    fullness -= points;
}

void PartyMember::gainFullness(int points)
{
    fullness += points;
}

bool PartyMember::isLeader()
{
    return leader;
}