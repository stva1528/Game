// CS1300 Spring 2021
// Author: Stella Vannier and Wren Hoertdoerfer
// Recitation 108 Ani 
// Project 3

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Dungeon.h"
using namespace std;

Dungeon::Dungeon()
{
    keyFound = false;
    angerLvl = 0;
    partySize = 5;

    Room r1 = Room("Red Room");
    Room r2 = Room("Blue Room");
    Room r3 = Room("Green Room");
    Room r4 = Room("Yellow Room");
    Room r5 = Room("Final Room");
    rooms[0] = r1;
    rooms[1] = r2;
    rooms[2] = r3;
    rooms[3] = r4;
    rooms[4] = r5;
}
 
void Dungeon::start()
{
   string name;

   cout << endl;
   cout << "===== DUNGEONS AND DRAGONS =====" << endl;
   cout << endl;
   cout << "You and your team of 5 are about to enter the Dungeon! The goal of the game is to successfully" << endl;
   cout << "navigate through all the rooms in the Dungeon. Each room needs a key to enter. The sorcerer's anger" << endl;
   cout << "level starts at 0. But beware, as you traverse through the Dungeon his anger level will rise! If the" << endl;
   cout << "sorcerer's anger level reaches 100, then the game is over! Good luck!" << endl; // this needs more maybe
   cout << endl;
   cout << "Please enter your first name: " << endl;
   cin >> name;
   teamParty[0] = PartyMember(name, true);
   cout << "Please enter the names of your teammates: " << endl;
   for (int i = 1; i < 5; i++){
      cin >> name;
      teamParty[i] = PartyMember(name, false);
    }
    cout << endl;
    cout << "Before your journey can begin your party must visit the Merchant to purchase supplies." << endl;
    merchant.startMerchant();
    int c = 0;
    do{
        merchant.displayMenu();
        cin >> c;
        switch(c)
        {
            case 1:
                merchant.displayIngredients();
                break;
            case 2:
                merchant.displayCookware();
                break;
            case 3:
                merchant.displayWeapons();
                break;
            case 4:
                merchant.displayArmor();
                break;
            case 5:
                merchant.subtractFromGoldCoins(merchant.getTotalCost());
                merchant.zeroTotal();
                break;
            default:
                cout << "Please enter a value 1 through 5" << endl;
        }
    }
    while (c <= 4);

    merchant.nextRoom();
    status();
    cout << endl;

    cout << "Welcome to the " << rooms[0].getRoomName() << "! You must navigate through this room and find the room key in order to " << endl;
    cout << "move on. You can find the key in a variety of ways: dropped by a monster, given to you by an NPC, or found when" << endl;
    cout << "exploring a room." << endl;
    cout << endl;

    int choice = 0;
    do{
        menu();
        cout << "Please enter the numerical value of the action you would like to pursue:" << endl;
        cin >> choice;
        switch (choice){
            case 1:
                misfortune(false);
                fightMonster();
                addAngerLvl(2);
                break;
            case 2:
                misfortune(false);
                speakToNPC();
                merchant.zeroTotal();
                addAngerLvl(2);
                break;
            case 3:
                misfortune(false);
                cook();
                addAngerLvl(2);
                break;
            case 4:
                misfortune(false);
                exploreRoom();
                addAngerLvl(2);
                break;
            case 5:
                misfortune(true);
                openDoor();
                addAngerLvl(2);
                break;
            case 6:
                misfortune(false);
                quitGame();
                addAngerLvl(2);
                break;
        }
        for (int i = 0; i < partySize; i++){
            teamParty[i].loseFullness(1);
        }
        for (int i = 1; i < partySize; i++){
            if (teamParty[i].getFullness() == 0){
                cout << "OH NO! " << teamParty[i].getName() << " has died of hunger!" << endl;
                partySize--;
                teamParty[i].loseFullness(teamParty[i].getFullness());
                cout << "Your party has been reduced to " << partySize << " members." << endl;
                teamParty[i] = teamParty[partySize];
            }
        }
        status();
        if (teamParty[0].getFullness() == 0){
            cout << "OH NO! Your leader has died and you can no longer continue on your journey." << endl;
            partySize--;
            cout << "Your party has been reduced to " << partySize << " members." << endl;
            teamParty[0] = teamParty[partySize];
        }
        if (partySize < 3){
            quitGame();
        }
        if (teamParty[0].isLeader() == false){
            cout << "OH NO! Your leader has died and you can no longer continue on your journey." << endl;
            quitGame();
        }
    }
    while(choice < 6 && angerLvl != 100);
    quitGame();
}


void Dungeon::menu()
{
   cout << endl;
   cout << "====== ACTIONS ======" << endl;
   cout << "1. Fight a monster" << endl;
   cout << "2. Speak to NPC" << endl;
   cout << "3. Cook and eat" << endl;
   cout << "4. Explore the room" << endl;
   cout << "5. Open door to next room" << endl;
   cout << "6. Quit game" << endl;
   cout << endl;
}   
 
void Dungeon::status()
{
    cout << endl;
    cout << "----STATUS UPDATE ----" << endl;
    cout << "CURRENT ROOM: " << rooms[merchant.getCurrentRoom()-1].getRoomName() << endl;
    cout << "ROOM KEY FOUND: " << keyFound << endl;
    cout << "SORCERER ANGER LEVEL: " << angerLvl << " OUT OF 100" << endl;
    cout << "GOLD COINS: " << merchant.getGoldCoins() << endl;
    cout << "----PARTY MEMBERS ----" << endl;
    cout << "(LEADER) ME: " << teamParty[0].getFullness() << " FULLNESS POINTS" << endl;
    cout << "MEMBER 2: " << teamParty[1].getFullness() << " FULLNESS POINTS" << endl;
    cout << "MEMBER 3: " << teamParty[2].getFullness() << " FULLNESS POINTS" << endl;
    cout << "MEMBER 4: " << teamParty[3].getFullness() << " FULLNESS POINTS" << endl;
    cout << "MEMBER 5: " << teamParty[4].getFullness() << " FULLNESS POINTS" << endl;
    cout << "----MATERIALS ----" << endl;
    cout << "INGREDIENTS: " << merchant.getIngredients() << " KG" << endl;
    cout << "COOKWARE: ";
    merchant.getCookware();
    cout << "WEAPONS: ";
    merchant.getWeapons();
    cout << "ARMOR: " << merchant.getArmor() << " SETS"<< endl;
    cout << "TREASURE ITEMS: ";
    merchant.getTreasures();
    cout << endl;

    int first = teamParty[0].getFullness();
    int second = 0;
    int third = 0;
    int fourth = 0;
    int fifth = 0;
    string one = teamParty[0].getName();
    string two;
    string three;
    string four;
    string five;
    int arr[5] = {teamParty[0].getFullness(), teamParty[1].getFullness(), teamParty[2].getFullness(), teamParty[3].getFullness(), teamParty[4].getFullness()};
    for (int i = 1; i < partySize; i++)
    {
        if (arr[i] > first)
        {
            fifth = fourth;
            fourth = third;
            third = second;
            second = first;
            first = arr[i];
 
            five = four;
            four = three;
            three = two;
            two = one;
            one = teamParty[i].getName();
        }
        else
        {
            if (i == 1)
            {
                fifth = fourth;
                fourth = third;
                third = second;
                second = arr[i];
    
                five = four;
                four = three;
                three = two;
                two = teamParty[i].getName();
            }
            else if (i == 2)
            {
                fifth = fourth;
                fourth = third;
                third = arr[i];
                five = four;
                four = three;
                three = teamParty[i].getName();
            }
            else if (i == 3)
            {
                fifth = fourth;
                fourth = arr[i];
    
                five = four;
                four = teamParty[i].getName();
            }
            else if (i == 4)
            {
                fifth = arr[i];
                five = teamParty[i].getName();
            }
        }
    }

    cout << "----LEADERBOARD ----" << endl;
    cout << "(based on fullness points)" << endl;
    cout << "1. " << one << endl;
    cout << "2. " << two << endl;
    cout << "3. " << three << endl;
    cout << "4. " << four << endl;
    cout << "5. " << five << endl;
    cout << endl;

}
 
void Dungeon :: fightMonster()
{
    int choice = 0;
    string monster = rooms[merchant.getCurrentRoom()-1].getMonster();
    cout << monster << " ahead! THEY LOOK HOSTILE!" << endl;
    cout << "You have 2 options: " << endl << "1. Attack " << endl << "2. Surrender " << endl
    << "Please enter the numerical value of the action you wish to pursue" << endl;
    cin >> choice;
 
    if (choice == 1 && merchant.getNumWeapons() > 0 && merchant.getArmor() > 0) // if party has at least one weapon and set of armor
    {
        int w = 0; 
        for (int i = 0; i < merchant.getNumWeapons(); i++){
            if (merchant.getWeaponAtIndex(i) == "Club" || merchant.getWeaponAtIndex(i) == "Spear"){
                w += 1;
            }
            else{
                w += 2;
            }
        }
        int d = 0;
        if (merchant.hasAllWeapons() == true){
            d = 1;
        }
        int a = merchant.getArmor();
        int c = merchant.getCurrentRoom();
        srand (time(NULL));
        int r1 = rand() % 7 +1;
        int r2 = rand() % 7 +1;
        while (r1 == r2)
        {
            r2 = rand() % 7 +1;
        }
        int battle = (r1*w + d) - (r2*c*(1/a));
 
        if (battle > 0)
        {
            cout << "CONGRATULATIONS! Your party has successfully defeated the " << monster << endl;
            cout << "Since you won the battle your party has been rewarded 50 gold pieces and 20 kg of ingredients." << endl;
            merchant.addToGoldCoins(50); // add 50 gold pieces
            merchant.addToIngredients(20); // add 20 kg of ingredients
            srand (time(NULL));
            int r = rand() % 4 +1;
            if (r == 1)
            {
                keyFound = true;
                cout << "The monster has dropped the room key!" << endl;
            }
            for (int i = 0; i < partySize; i++) // decrement each players fullness by 1 point
            {
                teamParty[i].loseFullness(1);
            }
        }
        else
        {
            int lose = merchant.getGoldCoins() / 4; 
            merchant.subtractFromGoldCoins(lose);  // lose 1/4 of gold
            merchant.takeFromIngredients(30);   // lose 30 kg of ingredients
            
            int r = merchant.getArmor();
            int prob = 0;
           // individually each party member has a 10% (5% with armor) chance of getting slain by the monster, if a party member is lost: update the total party size
            for (int i = 0; i < partySize; i++){
                if (i < r){
                    prob = rand() % 100 + 1;
                    if (prob <= 5){
                        if (i == 0){
                            cout << "Oh No! " << teamParty[i].getName() << ", the leader, has been slain by the " << monster << "!" << endl;
                            quitGame();
                        }
                        else{
                            cout << teamParty[i].getName() << " has been slain by the " << monster << "!" << endl;
                            partySize--;
                            teamParty[i].loseFullness(teamParty[i].getFullness());
                            merchant.loseArmor(1);
                            teamParty[i] = teamParty[partySize];
                        }
                    }
                }
                else{
                    prob = rand() % 100 + 1;
                    if (prob <= 10){
                        cout << teamParty[i].getName() << " has been slain by the " << monster << "!" << endl;
                        partySize--;
                        teamParty[i].loseFullness(teamParty[i].getFullness());
                        teamParty[i] = teamParty[partySize];
                    }
                }
            }
            for (int i = 0; i < 5; i++) // decrement each players fullness by 1 point
            {
                teamParty[i].loseFullness(1);
            }
        }
    }
    else if (choice == 1) // if party doesn't have weapons or armor
    {
        cout << "You must have at least 1 weapon and 1 armor to attack the monster." << endl;
        if (partySize > 2)
        {
            partySize--; // decrement party size
            for (int i = 0; i < 5; i++) // decrement each players fullness by 1 point
            {
                teamParty[i].loseFullness(1);
            }
            cout << "Because of this you must surrender and " << teamParty[partySize].getName() << " was unable to escape the wrath of the " << monster;
            cout << ". Your party must now contine without them." << endl;
            teamParty[partySize].loseFullness(teamParty[partySize].getFullness());
        }
        else
        {
            partySize--;
            cout << "Because of this you must surrender and unfortunately you don’t have a large enough party size to continue." << endl;
            quitGame(); // call quit
        }
    }
    else if (choice == 2)
    {
        cout << "You have chosen to surrender!" << endl;
        if (partySize > 2)
        {
            partySize--;
            cout << "Because of this " << teamParty[partySize].getName() << " was unable to escape the wrath of the " << monster;
            cout << ". Your party must now contine without them." << endl;
            teamParty[partySize].loseFullness(teamParty[partySize].getFullness());
        }
        else
        {
            partySize--;
            cout << "Because of this you don’t have a large enough party size to continue." << endl;
            teamParty[partySize].loseFullness(teamParty[partySize].getFullness());
            quitGame();  // call quit
        }
    }
}

void Dungeon :: speakToNPC()
{
   string ans;
   NPC person = NPC();
   person.NPCread("riddles.txt");
   int r = person.getRiddle();
   if (r == 1)
   {
       cin >> ans;
       int a = person.checkAnswer(ans);
       if (a == 1)
       {
           cout << "CONGRATULATIONS! You solved the riddle and you now have a chance to purchase more goods." << endl;
           status();
           int c =0;
           do
           {
               merchant.displayMenu();
               cin >> c;
               switch(c)
               {
                   case 1:
                       merchant.displayIngredients();
                       break;
                   case 2:
                       merchant.displayCookware();
                       break;
                   case 3:
                       merchant.displayWeapons();
                       break;
                   case 4:
                       merchant.displayArmor();
                       break;
                   case 5:
                       break;
               }
           }
           while (c != 5);
       }
   }
   else
   {
       cout << endl;
       fightMonster();
   }
}
 
void Dungeon::cook()
{
   int choice = 0;
   int kg = 0;
   string utensil;
   int points = 0;

   srand (time(NULL));
   int prob = rand() % 100 +1;

   if (merchant.getIngredients() == 0){
      cout << "You don't have any ingredients!" << endl;
   }
   else if (merchant.getNumCookware() == 0){
      cout << "You don't have any cookware!" << endl;
   }
   else{
      cout << "Here's your current cookware: " << endl;
      merchant.getCookware();
      cout << "Current amount of ingredients: " << merchant.getIngredients() << " kg" << endl;
      cout << endl;
      cout << "Enter the number corresponding to the cookware you'd like to use (first is 1, second is 2, etc.): " << endl;
      cin >> choice;
      cout << "Enter the amount of ingredients you'd like to use." << endl;
      cin >> kg;
      merchant.takeFromIngredients(kg);

      utensil = merchant.getCookwareAtIndex(choice - 1);
      if (utensil == "Cauldron"){
         if (prob <= 2){
            cout << "Oh No! Your Cauldron broke... All the ingredients went to waste." << endl;
            merchant.removeCookware("Cauldron");
         }
         else{
            points = kg / 5;
            for (int i = 0; i < partySize; i++){
               teamParty[i].gainFullness(points);
            }
         }
      }
      else if (utensil == "Cast Iron Pan"){
         if (prob <= 10){
            cout << "Oh No! Your Cast Iron Pan broke... All the ingredients went to waste." << endl;
            merchant.removeCookware("Cast Iron Pan");
         }
         else{
            points = kg / 5;
            for (int i = 0; i < partySize; i++){
               teamParty[i].gainFullness(points);
            }
         }
      }
      else{
         if (prob <= 25){
            cout << "Oh No! Your Ceramic Pot broke... All the ingredients went to waste." << endl;
            merchant.removeCookware("Ceramic Pot");
         }
         else{
            points = kg / 5;
            for (int i = 0; i < partySize; i++){
               teamParty[i].gainFullness(points);
            }
         }
      }
   }
}
 
void Dungeon::exploreRoom()
{
   srand(time(NULL));
   int prob = rand() % 100 + 1;
   string treasure;

   if (prob <= 20){
        cout << endl;
        cout << "Key found!" << endl;
        keyFound = true;
    }
    else if (prob > 20 && prob <= 40){
        cout << endl;
        cout << "Treasure found!" << endl;
        treasure = rooms[merchant.getCurrentRoom()-1].getTreasure();
        cout << "You found a " << treasure << "!" << endl;
        merchant.addTreasure(treasure);
    }
    else if (prob > 40 && prob <= 60){
        fightMonster();
    }
    else{
        cout << endl;
        cout << "You didn't have any luck searching the room." << endl;
    }
}
 
void Dungeon::openDoor()
{
    if (keyFound == false)
    {
        int i = 0;
        cout << "YOU ARE STUCK IN A DOOR PUZZLE!" << endl << "You must play a game of rock-paper-scissors against the door in order to escape the door puzzle." << endl <<
        "You must beat the door in three attempts or you will lose a party member." << endl;
        while(i < 3)
        {
            int choice = 0;
            cout << "Please enter the numerical value of your choice:" << endl << "1. rock" << endl << "2. paper" << endl << "3. scissors" << endl;
            cin >> choice;
    
            srand(time(NULL));
            int ran = rand() % 4 + 1;
            int rad = rand() % 4 + 1;
            int compC = (ran + rad) / 2;
    
            if (choice == 1)
            {
                if (compC == 1)
                {
                    cout << "You tied try again!" << endl;
                }
                else if (compC == 2)
                {
                    cout << "You lost try again!" << endl;
                }
                else
                {
                    cout << "Congradulations you have beaten the door puzzle!" << endl;
                    if (merchant.getCurrentRoom() <= 4){
                        merchant.nextRoom();
                        cout << "Welcome to the " << rooms[merchant.getCurrentRoom()].getRoomName() << "! You must navigate through this";
                        cout << " room and find the room key in order to move on. You can find the key in a variety of ways: dropped by a";
                        cout << " monster, given to you by an NPC, or found when exploring a room." << endl;
                        cout << endl;
                        keyFound = false;
                        break;
                    }
                    else{
                        finishGame();
                    }
                }
            }
            else if (choice == 2)
            {
                if (compC == 1)
                {
                    cout << "Congradulations you have beaten the door puzzle!" << endl;
                    if (merchant.getCurrentRoom() <= 4){
                        merchant.nextRoom();
                        cout << "Welcome to the " << rooms[merchant.getCurrentRoom()].getRoomName() << "! You must navigate through this";
                        cout << " room and find the room key in order to move on. You can find the key in a variety of ways: dropped by a";
                        cout << " monster, given to you by an NPC, or found when exploring a room." << endl;
                        cout << endl;
                        keyFound = false;
                        break;
                    }
                    else{
                        finishGame();
                    }
                }
                else if (compC == 2)
                {
                    cout << "You tied try again!" << endl;
                }
                else
                {
                    cout << "You lost try again!" << endl;
                }
            }
            else
            {
                if (compC == 1)
                {
                    cout << "You lost try again!" << endl;
                }
                else if (compC == 2)
                {
                    cout << "Congradulations you have beaten the door puzzle!" << endl;
                    if (merchant.getCurrentRoom() <= 4){
                        merchant.nextRoom();
                        cout << "Welcome to the " << rooms[merchant.getCurrentRoom()].getRoomName() << "! You must navigate through this";
                        cout << " room and find the room key in order to move on. You can find the key in a variety of ways: dropped by a";
                        cout << " monster, given to you by an NPC, or found when exploring a room." << endl;
                        cout << endl;
                        keyFound = false;
                        break;
                    }
                    else{
                        finishGame();
                    }
                }
                else
                {
                    cout << "You tied try again!" << endl;
                }
            }
            i++;
        }
        if (i == 3){
            if (partySize > 2)
            {
                cout << "You lost to the door. Party member " << teamParty[partySize - 1].getName() << " is now removed from your party!" << endl;
                partySize--;
                teamParty[partySize].loseFullness(teamParty[partySize].getFullness());
            }
            else
            {
                cout << "You lost to the door and the last member of your party has died." << endl;
                quitGame();
            }
        }
    }
    else
    {
        if (merchant.getCurrentRoom() <= 4){
            merchant.nextRoom();
            cout << "Welcome to the " << rooms[merchant.getCurrentRoom()].getRoomName() << "! You must navigate through this";
            cout << " room and find the room key in order to move on. You can find the key in a variety of ways: dropped by a";
            cout << " monster, given to you by an NPC, or found when exploring a room." << endl;
            cout << endl;
            keyFound = false;
        }
        else{
            finishGame();
        }
    }
}

void Dungeon :: quitGame()
{
   cout << endl;
   cout << "GAME OVER!!" << endl;
   cout << "Sorry you and your team did not make it out of the dungeon." << endl;
   cout << "Here are your final stats: " << endl;
   status();
 
   ofstream out_file("results.txt");
   if (out_file.is_open())
   {
        out_file << "----STATUS UPDATE ----" << endl;
        out_file << "CURRENT ROOM: " << rooms[merchant.getCurrentRoom()-1].getRoomName() << endl;
        out_file << "ROOM KEY FOUND: " << keyFound << endl;
        out_file << "SORCERER ANGER LEVEL: " << angerLvl << " OUT OF 100" << endl;
        out_file << "GOLD COINS: " << merchant.getGoldCoins() << endl;
        out_file << "----PARTY MEMBERS ----" << endl;
        out_file << "(LEADER) ME: " << teamParty[0].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 2: " << teamParty[1].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 3: " << teamParty[2].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 4: " << teamParty[3].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 5: " << teamParty[4].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "----MATERIALS ----" << endl;
        out_file << "INGREDIENTS: " << merchant.getIngredients() << " KG" << endl;
        out_file << "COOKWARE: ";
        for (int i = 0; i < merchant.getNumCookware(); i++){
            out_file << merchant.getCookwareAtIndex(i) << " ";
        }
        out_file << "WEAPONS: ";
        for (int i = 0; i < merchant.getNumWeapons(); i++){
            out_file << merchant.getWeaponAtIndex(i) << " ";
        }
        out_file << "ARMOR: " << merchant.getArmor() << " SETS"<< endl;
        out_file << "TREASURE ITEMS: ";
        for (int i = 0; i < merchant.getNumTreasures(); i++){
            out_file << merchant.getTreasureAtIndex(i) << " ";
        }
    
        int first = teamParty[0].getFullness();
        int second = 0;
        int third = 0;
        int fourth = 0;
        int fifth = 0;
        string one = teamParty[0].getName();
        string two;
        string three;
        string four;
        string five;
        int arr[5] = {teamParty[0].getFullness(), teamParty[1].getFullness(), teamParty[2].getFullness(), teamParty[3].getFullness(), teamParty[4].getFullness()};
        for (int i = 1; i < 6; i++)
        {
            if (arr[i] > first)
            {
                fifth = fourth;
                fourth = third;
                third = second;
                second = first;
                first = arr[i];
    
                five = four;
                four = three;
                three = two;
                two = one;
                one = teamParty[i].getName();
                
            }
            else
            {
                if (i == 2)
                {
                    second = arr[i];
                    two = teamParty[i].getName();
                }
                else if (i == 3)
                {
                    third = arr[i];
                    three = teamParty[i].getName();
                }
                else if (i == 4)
                {
                    fourth = arr[i];
                    four = teamParty[i].getName();
                }
                else if (i == 5)
                {
                    fifth = arr[i];
                    five = teamParty[i].getName();
                }
            }
        }
    
        out_file << "----LEADERBOARD ----" << endl;
        out_file << "(based on fullness points)" << endl;
        out_file << "1. " << one << endl;
        out_file << "2. " << two << endl;
        out_file << "3. " << three << endl;
        out_file << "4. " << four << endl;
        out_file << "5. " << five << endl;
        out_file << endl;
    
        out_file.close();
    
        cout << "Your final results have been saved to 'results.txt'. " << endl;
    }
    else
    {
        cout << "Unable to open file";
    }
    
    abort();
}

void Dungeon::misfortune(bool door)
{
    srand(time(NULL));
    int mis = rand() % 10 + 1;
 
    if (mis == 1)
    {
        int r = rand() % 4 + 1;
        if (r == 1)
        {
            cout << endl;
            merchant.takeFromIngredients(merchant.getIngredients());
            cout << "OH NO! Your team was robbed by dungeon bandits! You have no food left!" << endl;
            cout << endl;
        }
        else if (r == 2)
        {
            merchant.removeAllCookware();
            cout << endl;
            cout << "OH NO! Your team was robbed by dungeon bandits! You have no cookware left!" << endl;
            cout << endl;
        }
        else
        {
            merchant.loseArmor(merchant.getArmor());
            cout << endl;
            cout << "OH NO! Your team was robbed by dungeon bandits! You have no armor left!" << endl;
            cout << endl;
        }
    }
    else if (mis == 2)
    {
        int r = rand() % 2;
        if (r == 1)
        {
            cout << endl;
            cout << "OH NO! Your " << merchant.getWeaponAtIndex(0) << " broke!" << endl;
            cout << endl;
            merchant.removeWeaponAtIndex(0);
        }
        else
        {
            cout << endl;
            cout << "OH NO! One of your armor broke!" << endl;
            cout << endl;
            merchant.loseArmor(1);
        }
    }
    else if (mis == 3)
    {
        partySize--;
        cout << endl;
        cout << "OH NO! " << teamParty[1].getName() << " has died of hunger! Your party size has reduced to ";
        cout << partySize << " members." << endl;
        cout << endl;
        teamParty[1] = teamParty[partySize];
        teamParty[1].loseFullness(teamParty[1].getFullness());
        merchant.loseArmor(1);
    }
    else if (mis == 4 && door == true)
    {
        partySize--;
        cout << endl;
        cout << "OH NO! Your teammate " << teamParty[1].getName() << " is trapped in the previous room, and is";
        cout << " unable to get through. You must continue without them. Your party size has reduced to " << partySize << " members." << endl;
        cout << endl;
        teamParty[1] = teamParty[partySize];
        teamParty[1].loseFullness(teamParty[1].getFullness());
        merchant.loseArmor(1);
    }
    else if (mis == 5)
    {
        merchant.addToGoldCoins(100);
        cout << endl;
        cout << "The family discovered a lost pirate treasure chest. Your gold reserves increase by 100 gold pieces!" << endl;
        cout << endl;
    }
    else if (mis == 6)
    {
        for (int i = 0; i < partySize; i++)
        {
            teamParty[i].gainFullness(3);
        }
        cout << endl;
        cout << "Your team has had time for a nap. Your fullness levels have increase by 3." << endl;
        cout << endl;
    }
}

void Dungeon :: addAngerLvl(int points)
{
   angerLvl += points;
}

void Dungeon :: finishGame()
{
    cout << endl;
    cout << "Congradulations!! You have made it out of the dungeon!!" << endl;
    
    cout << "Here are your final stats: " << endl;
    status();
    
    ofstream out_file("results.txt");
    if (out_file.is_open())
    {
        out_file << "----STATUS UPDATE ----" << endl;
        out_file << "CURRENT ROOM: " << rooms[merchant.getCurrentRoom()-1].getRoomName() << endl;
        out_file << "ROOM KEY FOUND: " << keyFound << endl;
        out_file << "SORCERER ANGER LEVEL: " << angerLvl << " OUT OF 100" << endl;
        out_file << "GOLD COINS: " << merchant.getGoldCoins() << endl;
        out_file << "----PARTY MEMBERS ----" << endl;
        out_file << "(LEADER) ME: " << teamParty[0].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 2: " << teamParty[1].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 3: " << teamParty[2].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 4: " << teamParty[3].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "MEMBER 5: " << teamParty[4].getFullness() << " FULLNESS POINTS" << endl;
        out_file << "----MATERIALS ----" << endl;
        out_file << "INGREDIENTS: " << merchant.getIngredients() << " KG" << endl;
        out_file << "COOKWARE: ";
        for (int i = 0; i < merchant.getNumCookware(); i++){
            out_file << merchant.getCookwareAtIndex(i) << " ";
        }
        out_file << "WEAPONS: ";
        for (int i = 0; i < merchant.getNumWeapons(); i++){
            out_file << merchant.getWeaponAtIndex(i) << " ";
        }
        out_file << "ARMOR: " << merchant.getArmor() << " SETS"<< endl;
        out_file << "TREASURE ITEMS: ";
        for (int i = 0; i < merchant.getNumTreasures(); i++){
            out_file << merchant.getTreasureAtIndex(i) << " ";
        }
    
        int first = teamParty[0].getFullness();
        int second = 0;
        int third = 0;
        int fourth = 0;
        int fifth = 0;
        string one = teamParty[0].getName();
        string two;
        string three;
        string four;
        string five;
        int arr[5] = {teamParty[0].getFullness(), teamParty[1].getFullness(), teamParty[2].getFullness(), teamParty[3].getFullness(), teamParty[4].getFullness()};
        for (int i = 1; i < 6; i++)
        {
            if (arr[i] > first)
            {
                fifth = fourth;
                fourth = third;
                third = second;
                second = first;
                first = arr[i];
    
                five = four;
                four = three;
                three = two;
                two = one;
                one = teamParty[i].getName();
                
            }
            else
            {
                if (i == 2)
                {
                    second = arr[i];
                    two = teamParty[i].getName();
                }
                else if (i == 3)
                {
                    third = arr[i];
                    three = teamParty[i].getName();
                }
                else if (i == 4)
                {
                    fourth = arr[i];
                    four = teamParty[i].getName();
                }
                else if (i == 5)
                {
                    fifth = arr[i];
                    five = teamParty[i].getName();
                }
            }
        }
    
        out_file << "----LEADERBOARD ----" << endl;
        out_file << "(based on fullness points)" << endl;
        out_file << "1. " << one << endl;
        out_file << "2. " << two << endl;
        out_file << "3. " << three << endl;
        out_file << "4. " << four << endl;
        out_file << "5. " << five << endl;
        out_file << endl;
    
        out_file.close();
    
        cout << "Your final results have been saved to 'results.txt'. " << endl;
    }
    else
    {
        cout << "Unable to open file";
    }
    
    abort();
}
