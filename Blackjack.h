#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Cards.h"
#include "Chips.h"
#include <string>



class Blackjack : public Cards, public Chips {
    public:
        Blackjack();
        void play();

    private:
        void gameStart();
        std::tuple<std::string, int, bool> dealCards(int playerSum);
        bool checkBust(std::string player, int cardSum);
        void checkWin(int dealerSum, int playerSum);
        bool checkBlackjack(int playerSum, int dealerSum);
};

#endif // BLACKJACK_H
