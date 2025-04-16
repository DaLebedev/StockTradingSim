#ifndef GAME_H
#define GAME_H
#include <QDate>
#include "stock.h"

class Game {
private:
    QDate startDate;
    QDate currDay;
    int timeStep;
    vector<Stock*> market;

public:
    // Constructor Declaration
    Game(vector<Stock*> market);

    // Getter & Setter Declarations
    QDate getCurrDay();
    void setCurrDay(QDate currDay);

    QDate getStartDate();

    int getTimeStep();
    void setTimeStep(int timeStep);

    vector<Stock*> getMarket();

    // Function Declarations
    void gameLoop();
    void advanceDay();
};

#endif // GAME_H
