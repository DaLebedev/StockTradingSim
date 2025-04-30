#include "stock.h"
#include <QDebug>

// Random number gen seeding
random_device rd;
mt19937 gen(rd());

// Constructor
Stock::Stock(string name, string abbreviation, int numShares, float initPrice)
    : name(name), abbreviation(abbreviation), numShares(numShares), initPrice(initPrice), currPrice(initPrice), priceHistory{initPrice} {

    uniform_real_distribution<float> meanDist(0.9, 1.1);
    float meanMod = meanDist(gen);
    meanPrice = initPrice * meanMod;

    uniform_real_distribution<float> volDist (0.75, 1.1);
    float volMod = volDist(gen);
    float scale = 10 / sqrt(meanPrice);
    volatility = ((meanPrice/2) * scale) * volMod;
}

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

void Stock::setNumShares(int numShares) {
    this->numShares = numShares;
}

vector<float> Stock::getPriceHistory() {
    return priceHistory;
}

float Stock::getInitPrice() {
    return initPrice;
}

float Stock::getMeanPrice() {
    return initPrice;
}

float Stock::getVolatility() {
    return initPrice;
}

// Helper function to generate random distribution
float generateRandomDist(float mean, float stdDev) {
    // Move device seeding out
    normal_distribution<float> dist(mean, stdDev);
    return dist(gen);
}

// Function which uses the Ornstein Uhlenbeck means reverting process to determine the price of a stock
float Stock::ornsteinUhlenbeck(float timeStep) {

    // Standard dev. of value after 1 step
    float var = pow(volatility, 2) / (reversionRate * 2) * (1 - exp(-2 * reversionRate * timeStep));
    float stdDev = sqrt(var);

    // Mean of next value
    float mean = initPrice * exp(-reversionRate * timeStep) + meanPrice * (1 - exp(-reversionRate * timeStep));

    // Sample next value from normal dist
    float newPrice = generateRandomDist(mean, stdDev);

    // Round to 2 decimal places
    return round(newPrice * 100.0f) / 100.0f;
}

// Function to update stock price
void Stock::updatePrice() {
    currPrice = ornsteinUhlenbeck(0.01);
    priceHistory.push_back(currPrice);
    qInfo() << abbreviation << "-" << QString::number(currPrice);
}
