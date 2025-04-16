#include "stock.h"
#include <QDebug>

// Constructor
Stock::Stock(string name, string abbreviation, float currPrice, int numShares)
    : name(name), abbreviation(abbreviation), currPrice(currPrice), numShares(numShares) {}

// Getters & Setters
string Stock::getName() {
    return name;
}

string Stock::getAbbreviation() {
    return abbreviation;
}

float Stock::getCurrPrice() {
    return currPrice;
}

void Stock::setCurrPrice(float currPrice) {
    this->currPrice = currPrice;
}

int Stock::getNumShares() {
    return numShares;
}

vector<float> Stock::getPriceHistory() {
    return priceHistory;
}

// TODO: ADD PROPER PRICE INCREASE/DECREASE FORMULA/ALGORITHM (BROWNIAN MOTION, MEAN REVERTING, JUMP DIFFUSION)
// Function to get price multiplier
float Stock::priceChange() {

    // Random value between 0.005 and 0.03
    float x = (rand() % 300 + 50) / 10000.0f;

    // Generates rand num -0.03 and 0.03
    float y = (rand() % 60 - 30) / 1000.0f;

    // Generates rand num -0.25 to 0.25
    float z = (rand() % 501 - 250) / 1000.0f;

    float marketEvent = (rand() % 100 < 5) ? z : 0.0f;
    return 1 + (x + y + marketEvent);
}

// Function to update stock price
void Stock::updatePrice() {
    float change = priceChange();
    currPrice = max(0.01f, currPrice * change);
    priceHistory.push_back(currPrice);
    qInfo() << QString::number(currPrice);
}
