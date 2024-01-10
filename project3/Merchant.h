// CS1300 Spring 2021
// Author: Stella Vannier
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef MERCHANT_H
#define MERCHANT_H

class Merchant
{
    // Data members
    private:
    int totalCost;
    int goldCoins;
    int currentRoom;
    int armor;
    int ingredients;
    vector<string> weapons;
    vector<string> cookware;
    vector<string> treasures;

    int price1;
    int price2;
    int price3;
    int price4;

    // Member functions
    public:
    Merchant();

    void startMerchant(string filename = "Merchant.txt");
    void displayMenu();
    void displayIngredients();
    void displayCookware();
    void displayWeapons();
    void displayArmor();

    void nextRoom();  // adds one to the current room
    void subtractFromGoldCoins(int);   // takes int from total gold coins
    void addToGoldCoins(int);
    bool hasAllWeapons();
    
    int getTotalCost();
    int getGoldCoins();
    int getCurrentRoom();
    int getArmor();
    void loseArmor(int);
    int getIngredients();
    void takeFromIngredients(int);
    void addToIngredients(int);
    void getWeapons();
    int getNumWeapons();
    string getWeaponAtIndex(int);
    void removeWeaponAtIndex(int);
    void getCookware();
    string getCookwareAtIndex(int);
    int getNumCookware();
    void removeCookware(string);
    void removeAllCookware();
    void getTreasures();
    void addTreasure(string);
    int getNumTreasures();
    string getTreasureAtIndex(int);
    void zeroTotal();
    
};

#endif