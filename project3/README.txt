Project 3 - READMECSCI 
1300 Spring 21

Project Name - Dungeons and Dragons

This is a user input text game that can be played in the terminal. It stores results of the game 
in a seperate results.txt text file. 

Required Text 
Merchant.txt Room.txt Monster.txt riddles.txt results.txt

Required Libraries
To run this application you need to install:
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h> 

Compile and Run
g++ -std=c++11 Dungeon.cpp merchant.cpp NPC.cpp partyMember.cpp room.cpp unity.cpp
(Make sure that all the files are present in the directory)

Notes
You can exit the game at any time by entering 6. At the end of each game you should clear your 
results text file.

Authors: Stella Vannier and Wren Hoertdoerfer
