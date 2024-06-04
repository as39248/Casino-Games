#include "Cards.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <random>

using namespace std;

Cards::Cards()
{

}

void Cards::shuffleShoe()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(defaultShoe.begin(), defaultShoe.end(), default_random_engine(seed));
}


void Cards::buildShoe()
{

    string suit[] = {" S", " D", " H", " C"};
    string special[] = {"A", "J", "Q", "K"};
    string card;
    for(int i = 2; i < 11; i++){
        for(int j = 0; j < 24; j++){ // append 6 times each card
            card = to_string(i) + suit[j % 4];
            defaultShoe.push_back(card);
        }

    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 24; j++){ // append 6 times each card
            card = special[i] + suit[j % 4];
            defaultShoe.push_back(card);
        }
    }
    shuffleShoe();
}


