#ifndef CARDS_H
#define CARDS_H
#include <string>
#include <vector>


class Cards
{
    public:
        Cards();
        std::vector<std::string> defaultShoe;
        void buildShoe();
        void shuffleShoe();

};

#endif // CARDS_H
