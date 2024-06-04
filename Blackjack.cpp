#include "Blackjack.h"
#include "Cards.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <cstring>
#include <list>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

Blackjack::Blackjack()
{

}
string split(string str){

    char arr[5];
    strcpy(arr, str.c_str());
    char *temp = strtok(arr, " ");

    return temp;
}

tuple<string, int, bool> Blackjack::dealCards(int playerSum){ //update cards

    if(defaultShoe.empty()){
        cout << "\nNew shoe shuffled. \n" << endl;
        buildShoe();
    }
    string cardInfo;
    string token;
    int cardValue;
    bool ace;

    cardInfo = defaultShoe.back();
    defaultShoe.pop_back();
    token = split(cardInfo);

    if (token == "J" || token == "Q" ||token == "K"){
         cardValue = 10;
         ace = false;
    }
    else if (token == "A" && playerSum < 11) {
         cardValue = 11;
         ace = true;
    }
    else if (token == "A" && playerSum > 10) {
         cardValue = 1;
         ace = true;
    }
    else {
         cardValue = stoi(token);
         ace = false;
    }
    return make_tuple(cardInfo, cardValue, ace);
}


void Blackjack::gameStart() {
    cout << "Enter S to start the game.\n"<< endl;
    string gameType;
    getline(cin, gameType);

    if (gameType != "S" && gameType != "s") {
        cout << "\nInvalid key:" << endl;
        gameStart();
    }
}


bool Blackjack::checkBust(string player, int cardSum){
    if (cardSum > 21 && player == "player"){
        cout << "Player Bust. Dealer Win" << endl;
        if (balance == 0){
            cout << "\nGame Over" << endl;
            cout << "Restart?  Y/N" << endl;
        }
        return true;
    }
    else if (cardSum > 21 && player == "dealer") {
        winBet();
        cout << "Dealer Bust. Player Win" << endl;
        return true;
    }
    return false;
}


void Blackjack::checkWin(int dealerSum, int playerSum){
    if(dealerSum > playerSum){
        cout << "Dealer Win" << endl;
        if (balance == 0){
            cout << "\nGame Over" << endl;
            cout << "Restart?  Y/N" << endl;
        }
    }
    else if(dealerSum < playerSum) {
        winBet();
        cout << "Player Win" << endl;
    }
    else{
        pushBet();
        cout << "Push" << endl;
    }
}


bool Blackjack::checkBlackjack(int playerSum, int dealerSum){

    string cardInfo = defaultShoe.back();
    string token = split(cardInfo);

    if(playerSum == 21 && dealerSum == 21){
        pushBet();
        cout << "Push"<< endl;
        return true;
    }
    else if (playerSum == 21 && token != "10" && token != "J" && token != "Q" && token != "K" && token != "A"){
        winBjBet();
        cout << "Player Blackjack"<< endl;
        return true;
    }
    else if (dealerSum == 21){
        cout << "Dealer Blackjack"<< endl;
        if (balance == 0){
            cout << "\nGame Over" << endl;
            cout << "Restart?  Y/N" << endl;
        }
        return true;
    }
    return false;
}


void Blackjack::play(){

    string input;
    tuple<string, int, bool> cardInfo;
    string dealerLine;
    string playerLine;
    string dealerNew;
    string playerNew;
    int dealerSum;
    int playerSum;
    bool bust;
    bool blackjack;
    int hitCount;
    int dealerCount;
    bool ace;
    string bets;

    string LINE = "=====================================================";
    string NEWLINE = "\n";
    string DEALER = "Dealer: ";
    string UNKNOWN ="?     ";
    string SPACE = "     ";
    string LAST = NEWLINE + NEWLINE + LINE;
    string PLAYER = "Player: ";

    //start game
    setBalance(1000); //set initial balance
    cout << "\nWelcome to 6 Deck Blackjack!\n" << endl;
    gameStart();

    for(;;){
        if (balance == 0){
            break;
        }

        bet();
        cout << "\n-----------------------------------------------------------------------"<< endl;

        // first deal
        dealerCount = 0;
        hitCount = 0;
        dealerSum = 0;
        playerSum = 0;
        ace = false;

        //dealer's hand
        cardInfo = dealCards(dealerSum);
        dealerSum += get<1>(cardInfo);
        dealerNew = get<0>(cardInfo);

        dealerLine = LINE + NEWLINE + DEALER + dealerNew + SPACE;

        cout << dealerLine << UNKNOWN << dealerSum << LAST << endl;


        // player's hand
        for (int i = 0; i < 2; i++){

            cardInfo = dealCards(playerSum);
            playerSum += get<1>(cardInfo);
            playerNew = get<0>(cardInfo);

            if(i == 0){
                playerLine = PLAYER + playerNew + SPACE;
            }
            else{
                playerLine += playerNew + SPACE;
            }
        }
        cout << playerLine << playerSum << LAST << endl;
        blackjack = checkBlackjack(playerSum, dealerSum);

        for(;;){
            if(blackjack){
                break;
            }
            if (hitCount == 0){
                cout << "Stand: S  Hit: H                              Exit: E \n" << endl;
                getline(cin, input);
            }
            hitCount = 0;

            //stand
            if(input == "s" || input == "S") {
                //dealer's hand
                cardInfo = dealCards(dealerSum);
                dealerSum += get<1>(cardInfo);

                dealerNew = get<0>(cardInfo);
                ace = get<2>(cardInfo);
                dealerCount++;

                if (dealerSum > 21 && ace){
                    dealerSum -= 10;
                    ace = false;
                    cardInfo = {dealerNew, dealerSum, ace};
                }

                dealerLine += dealerNew + SPACE;
                if(dealerSum > 16){
                    cout << dealerLine << dealerSum << LAST << endl;
                    cout << playerLine << playerSum << LAST << endl;
                    bust = checkBust("dealer", dealerSum);
                    if (dealerCount == 1){
                        blackjack = checkBlackjack(playerSum, dealerSum);
                        if(blackjack){
                            break;
                        }
                    }
                    if (!bust){
                        checkWin(dealerSum, playerSum);
                    }
                    break;
                }
                else{
                    hitCount = 1;
                }
            }
            else if (input == "h" || input == "H"){

                // player's hand
                cardInfo = dealCards(playerSum);
                playerSum += get<1>(cardInfo);

                playerNew = get<0>(cardInfo);
                ace = get<2>(cardInfo);

                if (playerSum > 21 && ace){
                    playerSum -= 10;
                    ace = false;
                    cardInfo = {playerNew, playerSum, ace};
                }

                playerLine += playerNew + SPACE;
                cout << dealerLine << UNKNOWN << dealerSum << LAST << endl;
                cout << playerLine << playerSum << LAST << endl;
                bust = checkBust("player", playerSum); // check bust

                if(bust){
                    break;
                }
            }
            else if  (input == "e" || input == "E") {
                exit(0);
            }

            else {
                cout << "Invalid Key" << endl;
            }
        }
    }
}

