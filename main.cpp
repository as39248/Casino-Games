#include "Cards.h"
#include "Chips.h"
#include "Blackjack.h"
#include <iostream>

using namespace std;

void gameSelection() {
    cout << "Enter P to play Blackjack.\n" << endl;
    string gameType;
    getline(cin, gameType);

    if (gameType == "P" || gameType == "p") {
        Blackjack blackjack;
        blackjack.play();
    }
    else {
        cout << "\nInvalid key:" << endl;

        gameSelection();
    }
}
void restartGame(){
    string input;

    getline(cin, input);
    if (input == "y" || input == "Y"){
        cout << "" << endl;

    }
    else if (input == "n" || input == "N"){
        exit(0);
    }
    else {
        cout << "\nInvalid Input" << endl;
        restartGame();
    }
}

int main()
{
    cout << "Welcome to Casino Games!" << endl;
    cout << "========================\n" << endl;
    for(;;){
        gameSelection();
        restartGame();
    }
    return 0;
}
