#ifndef GAME_H
#define GAME_H
#include <QDate>
#include "stock.h"

class Game {
private:
    vector<Stock*> market;
    QDate startDate;
    QDate currDay;
    int timeStep;

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
