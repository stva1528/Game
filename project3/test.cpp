#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 15; i++){
        cout << rand() % 10 + 1 << " ";
    }
    return 0;
}

