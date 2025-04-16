#include "game.h"
using namespace std;

// Constructor
Game::Game(vector<Stock*> market) : market(market), startDate(QDate::currentDate()), currDay(startDate) { }

// Getters & Setters
QDate Game::getCurrDay() {
    return currDay;
}

void Game::setCurrDay(QDate currDay) {
    this->currDay = currDay;
}

QDate Game::getStartDate() {
    return startDate;
}

int Game::getTimeStep() {
    return timeStep;
}

void Game::setTimeStep(int timeStep) {
    this->timeStep = timeStep;
}

vector<Stock*> Game::getMarket() {
    return market;
}

// Function to increment currDay by 1
void Game::advanceDay() {
    currDay = currDay.addDays(1);
    // TESTING INFO - DELETE LATER
    qInfo() << "Day updated, now: "  << currDay.toString();
    for (auto& stock : market) {
        stock->updatePrice();
    }
}
