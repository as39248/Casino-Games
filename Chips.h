#ifndef CHIPS_H
#define CHIPS_H


class Chips
{
    public:
        Chips();
        double balance;
        void setBalance(int chips);
        void bet();
        void winBet();
        void pushBet();
        void winBjBet();
    private:
        double betAmount;
};

#endif // CHIPS_H
