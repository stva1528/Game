// CS1300 Spring 2021
// Author: Stella Vannier and Wren Hoertdoerfer
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Merchant.h"
using namespace std;

Merchant::Merchant()
{
   totalCost = 0;
   goldCoins = 100;
   currentRoom = 0;

   price1 = 2;
   price2 = 5;
   price3 = 10;
   price4 = 20;
}

void Merchant::startMerchant(string filename)
{
   ifstream infile;
   string line;

   cout << endl;
   infile.open(filename);
   if (infile.fail()){
      cout << "Could not open file." << endl;
   }
   else{
      while(getline(infile, line)){
         cout << line << endl;
      }
   }
}

void Merchant::displayMenu()
{
   cout << endl;
   cout << "====== Main Menu ======" << endl;
   cout << "Choose a numerical value: " << endl;
   cout << "1. Ingredients" << endl;
   cout << "2. Cookware" << endl;
   cout << "3. Weapons" << endl;
   cout << "4. Armor" << endl;
   cout << "5. Complete purchase and continue into the dungeon!" << endl;
   cout << endl;
}

void Merchant::displayIngredients()
{
   switch (currentRoom){
      case 1:
         price1 = 2;
         price2 = 6;
         price3 = 12;
         price4 = 25;
         break;
      case 2:
         price1 = 3;
         price2 = 7;
         price3 = 15;
         price4 = 30;
         break;
      case 3:
         price1 = 3;
         price2 = 8;
         price3 = 17;
         price4 = 35;
         break;
      case 4:
         price1 = 4;
         price2 = 10;
         price3 = 20;
         price4 = 40;
         break;
      case 5:
         price1 = 4;
         price2 = 11;
         price3 = 22;
         price4 = 45;
         break;
      default:
         price1 = 2;
         price2 = 5;
         price3 = 10;
         price4 = 20;
         break;
   }

   int kg = 0;

   cout << endl;
   cout << "I sell ingredients at 1 gold coin per kilogram of food. I suggest you purchase at least" << endl;
   cout << "10 kilograms of ingredients per party member to ensure no one in your party dies of starvation!" << endl;
   cout << endl;
   cout << "Please enter how many kilograms of ingredients you would like to purchase: " << endl;
   cin >> kg;

   if (totalCost + kg > goldCoins){
      cout << "You do not have enough gold coins! Please choose an amount you can afford." << endl;
      cin >> kg;
   }
   else{
      totalCost += kg;
      cout << "Current total cost: " << totalCost << " gold coins." << endl;
   }

   ingredients += kg;
   
}
 
void Merchant::displayCookware()
{
   switch (currentRoom){
      case 1:
         price1 = 2;
         price2 = 6;
         price3 = 12;
         price4 = 25;
         break;
      case 2:
         price1 = 3;
         price2 = 7;
         price3 = 15;
         price4 = 30;
         break;
      case 3:
         price1 = 3;
         price2 = 8;
         price3 = 17;
         price4 = 35;
         break;
      case 4:
         price1 = 4;
         price2 = 10;
         price3 = 20;
         price4 = 40;
         break;
      case 5:
         price1 = 4;
         price2 = 11;
         price3 = 22;
         price4 = 45;
         break;
      default:
         price1 = 2;
         price2 = 5;
         price3 = 10;
         price4 = 20;
         break;
   }

   int choice = 0;

   cout << endl;
   cout << "COOKWARE:" << endl;
   cout << "Cauldron (" << price4 << " gold coins): used to stew and boil ingredients. Chance of breaking during use: 2%" << endl;
   cout << "Cast Iron Pan (" << price3 << " gold coins): Used to fry ingredients. Chance of breaking during use: 10%" << endl;
   cout << "Ceramic Pot (" << price2 << " gold coins): Used to stew and boil ingredients. Chance of breaking during use: 25%" << endl;
   cout << endl;
   do {
      cout << "Enter a number corresponding to the cookware you woud like to choice:" << endl;
      cout << "1. Cauldron" << endl;
      cout << "2. Cast Iron Pan" << endl;
      cout << "3. Ceramic Pot" << endl;
      cout << "4. I'm done looking at cookware" << endl;
      cin >> choice;

      switch (choice){
         case 1: 
            if (totalCost + price4 > goldCoins){
               cout << "You do not have enough gold coins! Please choose cookware you can afford." << endl;
            }
            else{
               totalCost += price4;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               cookware.push_back("Cauldron");
            }
            break;
         case 2:
            if (totalCost + price3 > goldCoins){
               cout << "You do not have enough gold coins! Please choose cookware you can afford." << endl;
            }
            else{
               totalCost += price3;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               cookware.push_back("Cast Iron Pan");
            }
            break;
         case 3:
            if (totalCost + price2 > goldCoins){
               cout << "You do not have enough gold coins! Please choose cookware you can afford." << endl;
            }
            else{
               totalCost += price2;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               cookware.push_back("Ceramic Pot");
            }
            break;
         case 4:
            cout << "Current total cost: " << totalCost << " gold coins." << endl;
            break;
      }
      cout << endl;
   }
   while (choice != 4);
}
 
void Merchant::displayWeapons()
{
   switch (currentRoom){
      case 1:
         price1 = 2;
         price2 = 6;
         price3 = 12;
         price4 = 25;
         break;
      case 2:
         price1 = 3;
         price2 = 7;
         price3 = 15;
         price4 = 30;
         break;
      case 3:
         price1 = 3;
         price2 = 8;
         price3 = 17;
         price4 = 35;
         break;
      case 4:
         price1 = 4;
         price2 = 10;
         price3 = 20;
         price4 = 40;
         break;
      case 5:
         price1 = 4;
         price2 = 11;
         price3 = 22;
         price4 = 45;
         break;
      default:
         price1 = 2;
         price2 = 5;
         price3 = 10;
         price4 = 20;
         break;
   }

   int choice = 0;

   cout << endl;
   cout << "You need weapons to be able to fend off monsters, otherwise, you can only run! Equipping" << endl;
   cout << "your team with the maximum number of weapons and buying upgraded weapons will maximize your" << endl;
   cout << "chances of survival during an attack. You can have a maximum of 5 weapons." << endl;
   cout << endl;
   do{
      cout << "WEAPONS:" << endl;
      cout << "1. Club: " << price1 << " gold coins" << endl;
      cout << "2. Spear: " << price1 << " gold coins" << endl;
      cout << "3. Crossbow: " << price2 << " gold coins" << endl;
      cout << "4. Battle-axe: " << price2 << " gold coins" << endl;
      cout << "5. Longsword: " << price2 << " gold coins" << endl;
      cout << "6. I'm done looking at weapons" << endl;
      cin >> choice;

      switch (choice)
      {
         case 1:
            if (totalCost + price1 > goldCoins){
               cout << "You do not have enough gold coins! Please choose a weapon you can afford." << endl;
            }
            else{
               totalCost += price1;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               weapons.push_back("Club");
            }
            break;
         case 2:
            if (totalCost + price1 > goldCoins){
               cout << "You do not have enough gold coins! Please choose a weapon you can afford." << endl;
            }
            else{
               totalCost += price1;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               weapons.push_back("Spear");
            }
            break;
         case 3: 
            if (totalCost + price2 > goldCoins){
               cout << "You do not have enough gold coins! Please choose a weapon you can afford." << endl;
            }
            else{
               totalCost += price2;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               weapons.push_back("Crossbow");
            }
            break;
         case 4:
            if (totalCost + price2 > goldCoins){
               cout << "You do not have enough gold coins! Please choose a weapon you can afford." << endl;
            }
            else{
               totalCost += price2;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               weapons.push_back("Battle-axe");
            }
            break;
         case 5:
            if (totalCost + price2 > goldCoins){
               cout << "You do not have enough gold coins! Please choose a weapon you can afford." << endl;
            }
            else{
               totalCost += price2;
               cout << "Current total cost: " << totalCost << " gold coins." << endl;
               weapons.push_back("Longsword");
            }
            break;
         case 6: 
            cout << "Current total cost: " << totalCost << " gold coins." << endl;
            break;
      }
      cout << endl;
   }
   while (choice != 6);
}
 
void Merchant::displayArmor()
{
   switch (currentRoom){
      case 1:
         price1 = 2;
         price2 = 6;
         price3 = 12;
         price4 = 25;
         break;
      case 2:
         price1 = 3;
         price2 = 7;
         price3 = 15;
         price4 = 30;
         break;
      case 3:
         price1 = 3;
         price2 = 8;
         price3 = 17;
         price4 = 35;
         break;
      case 4:
         price1 = 4;
         price2 = 10;
         price3 = 20;
         price4 = 40;
         break;
      case 5:
         price1 = 4;
         price2 = 11;
         price3 = 22;
         price4 = 45;
         break;
      default:
         price1 = 2;
         price2 = 5;
         price3 = 10;
         price4 = 20;
         break;
   }

   int sets = 0;

   cout << endl;
   cout << "Armor protects you from monsters. Equipping your team with the maximum amount of armor will" << endl;
   cout << "maximize your chances of survival during attack. Maximum amount of armor is 5, one per team member." << endl;
   cout << "Each set of armor costs " << price2 << " gold coins." << endl;
   cout << endl;
   cout << "How many sets of armor would you like to purchase?" << endl;
   cin >> sets;

   while (totalCost + (sets * price2) > goldCoins){
      cout << "You do not have enough gold coins! Please enter a quantity you can afford." << endl;
      cin >> sets;
   }
   
   totalCost += (sets * price2);
   cout << "Current total cost: " << totalCost << " gold coins." << endl;
   armor += sets;
}

void Merchant::nextRoom()
{
   currentRoom++;
}

void Merchant::subtractFromGoldCoins(int cost)
{
   goldCoins -= cost;
}

void Merchant::addToGoldCoins(int coins)
{
   goldCoins += coins;
}

bool Merchant::hasAllWeapons()
{
   int club = 0;
   int s = 0;
   int c = 0;
   int b = 0;
   int l = 0;
   int total = 0;

   for (int i = 0; i < weapons.size(); i++){
      if (weapons[i] == "Club"){
         club++;
      }
      else if (weapons[i] == "Spear"){
         s++;
      }
      else if (weapons[i] == "Crossbow"){
         c++;
      }
      else if (weapons[i] == "Battle-axe"){
         b++;
      }
      else if (weapons[i] == "Longsword"){
         l++;
      }
   }

   total = club + s + c + b + l;

   if (total == 5){
      return true;
   }
   else{
      return false;
   }
}
 
int Merchant::getTotalCost()
{
   return totalCost;
}

int Merchant::getGoldCoins()
{
   return goldCoins;
}

int Merchant::getCurrentRoom()
{
   return currentRoom;
}

int Merchant::getArmor()
{
   return armor;
}

void Merchant::loseArmor(int sets)
{
   armor -= sets;
}

int Merchant::getIngredients()
{
   return ingredients;
}

void Merchant::takeFromIngredients(int kg)
{
   ingredients -= kg;
}

void Merchant::addToIngredients(int kg)
{
   ingredients += kg;
}

void Merchant::getWeapons()
{
   if (weapons.size() > 0){
      for (int i = 0; i < weapons.size() - 1; i++){
         cout << weapons[i] << ", ";
      }
      cout << weapons[weapons.size() - 1] << endl;
   }
}

int Merchant::getNumWeapons()
{
   return weapons.size();
}

string Merchant::getWeaponAtIndex(int index)
{
   return weapons[index];
}

void Merchant::removeWeaponAtIndex(int index)
{
   weapons[index] = weapons[weapons.size() - 1];
}

void Merchant::getCookware()
{
   if (cookware.size() > 0){
      for (int i = 0; i < cookware.size() - 1; i++){
         cout << cookware[i] << ", ";
      }
      cout << cookware[cookware.size() - 1] << endl;
   }
}

string Merchant::getCookwareAtIndex(int index)
{
   return cookware[index];
}

int Merchant::getNumCookware()
{
   return cookware.size();
}

void Merchant::removeCookware(string utensil)
{
   for (int i = 0; i < cookware.size(); i++){
      if (cookware[i] == utensil){
         cookware[i] = cookware[cookware.size() - 1];
      }
   }
}

void Merchant::removeAllCookware()
{
   for (int i = 0; i < cookware.size(); i++){
      cookware.pop_back();
   }
}

void Merchant::getTreasures()
{
   if (treasures.size() > 0){
      for (int i = 0; i < treasures.size() - 1; i++){
         cout << treasures[i] << ", ";
      }
      cout << treasures[treasures.size() - 1] << endl;
   }
   
}

void Merchant::addTreasure(string prize)
{
   treasures.push_back(prize);
}

int Merchant::getNumTreasures()
{
   return treasures.size();
}

string Merchant::getTreasureAtIndex(int index)
{
   return treasures[index];
}

void Merchant::zeroTotal()
{
   totalCost = 0;
}
