// CS1300 Spring 2021
// Author: Stella Vannier and Wren Hoertdoerfer
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "NPC.h"
using namespace std;

int split(string words, char delimiter, string arr[], int size){
    int index = 0;
    string str_word = "";
    int length = words.length();
    int num_elements = 0;

    if (words == ""){
        return 0;
    }

    for (int i = 0; i < length; i++){
        if (words[i] == delimiter){ 
            index++;
            num_elements++;
            str_word = "";
        }
        else{
            str_word += words[i];
            arr[index] = str_word;
        }
    }

    num_elements = index + 1;

    if (arr[0] == words){
        return 1;
    }
    else if (num_elements > size){
        return -1;
    }
    else{
        return num_elements;
    }
}

NPC :: NPC()
{
   srand(time(NULL));
   int ra = rand() % 6;
 
   if (ra < 2)
   {
       NPCgood = true;
   }
   else if (ra <4)
   {
       NPCneutral = true;
   }
   else
   {
       NPCevil = true;
   }
   ra = 0;
}
 
void NPC :: NPCread(string text)
{
   ifstream in_file;
   in_file.open(text);
   string line;
   string arr[2];
   int i = 0;
   if (in_file.is_open())
   {
       while (getline(in_file, line) && i < 10)
       {
           split(line, ',', arr, 2);
           riddles[i] = arr[0];
           answers[i] = arr[1];
           i++;
       }
   }
}
 
int NPC :: getRiddle()
{
   if (NPCevil == true)
   {
       return 0;
   }
   else if (NPCgood == true || NPCneutral == true)
   {
       srand(time(NULL));
       r = rand() % 11;
 
       cout << endl << "Riddle:  ";
       cout << riddles[r] << endl;
       cout << "Whats your partys answer to the riddle? (format your one word answer with all lower case letters)" << endl;
       return 1;
   }
   return 0;
}
 
int NPC :: checkAnswer(string answer)
{
   string a = answers[r];
   if (a == answer)
   {
       if (NPCgood == true)
       {
           return 1;
       }
       else
       {
           return 0;
       }
   }
   else
   {
       cout << endl;
       cout << "The right answer was " << a << ". Since you have failed to enter the right answer to the riddle you will therefore not be offered any goods" << endl;
       return 0;
   }
}
