#include "Chips.h"
#include <iostream>

using namespace std;


Chips::Chips()
{

}

void Chips::setBalance(int chips){
    balance = chips;
}

void Chips::bet(){

    string strbets;
    double bets;

    cout << "\nEnter bets.        Balance: $" << balance << endl;
    getline(cin, strbets);

    try{                   //check if the input is a number
        stod(strbets);

        bets = stod(strbets);
        if (balance >= bets){
            balance -= bets;
            betAmount = bets;
        }
        else{
           std::cout << "Invalid amount&" << std::endl;
           bet();
        }
    }
    catch (invalid_argument){
        std::cout << "Invalid input" << std::endl;
        bet();
    }
}

void Chips::winBet(){
    balance += (betAmount * 2);
}


void Chips::pushBet(){
    balance += betAmount;
}

void Chips::winBjBet(){
    balance += (betAmount * 2.5);
}
