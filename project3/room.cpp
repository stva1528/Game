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
#include "Room.h"
using namespace std;

int split2(string words, char delimiter, string arr[], int size){
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

Room::Room()
{
    roomName = "";
    roomNum = 0;
    for(int i = 0; i < 3; i++){
        roomTreasures[i] = "";
    }
    for (int x = 0; x < 4; x++){
        monsters[x] = "";
    }
}

Room::Room(string name, string room_file, string monster_file)
{
    roomName = name;

    ifstream r_file;
    ifstream m_file;
    string line;
    int lineNum = 1;

    r_file.open(room_file);
    if (r_file.fail()){
        cout << "Could not open room file." << endl;
    }
    else{
        while(getline(r_file, line)){
            if (line == roomName){
                roomNum = (lineNum/2 + 1);
                getline(r_file, line);
                split2(line, ',', roomTreasures, 3);
            }
            lineNum++;
        }
    }

    r_file.close();

    int m_line = 0;
    if (roomNum == 1){
        m_line = 0;
    }
    else if (roomNum == 2){
        m_line = 5;
    }
    else if (roomNum == 3){
        m_line = 9;
    }
    else if (roomNum == 4){
        m_line = 13;
    }
    else{
        m_line = 17;
    }

    lineNum = 0;

    m_file.open(monster_file);
    if (m_file.fail()){
        cout << "Could not open monster file." << endl;
    }
    else{
        while(getline(m_file, line)){
            if (lineNum == m_line){
                monsters[0] = line;
                for (int i = 1; i < 4; i++){
                    getline(m_file, line);
                    monsters[i] = line;
                }
            }
            lineNum++;
        }
    }

    m_file.close();
}

string Room::getRoomName()
{
    return roomName;
}

int Room::getRoomNum()
{
    return roomNum;
}

string Room::getTreasure()
{
    srand(time(NULL));
    
    int treasureIndex = rand() % 3;
    return roomTreasures[treasureIndex];
}

string Room::getMonster()
{
    srand(time(NULL));

    int monsterIndex = rand() % 4;
    return monsters[monsterIndex];
}