// CS1300 Spring 2021
// Author: Stella Vannier
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef NPC_H
#define NPC_H

class NPC
{
   public:
   NPC();                      // default constructor sets the NPC to either good, bad, or neutral
   void NPCread(string);                // reads the NPC text file
   int getRiddle();            // selects a ramdon riddle from the array of riddles to ask
   int checkAnswer(string);   // checks that the players answer is correct
 
   private:
   string riddles[10];
   string answers[10];
   int r = 0;
   bool NPCgood = false;
   bool NPCneutral = false;
   bool NPCevil = false;
};


#endif