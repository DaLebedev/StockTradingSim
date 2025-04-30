#include "userportfolio.h"
#include <QDebug>

// Constructor
UserPortfolio::UserPortfolio(float balance)
    : balance(balance) {}

// Getters & Setters
float UserPortfolio::getBalance() {
    return balance;
}

void UserPortfolio::setBalance(float balance) {
    this->balance = balance;
}

map<Stock*, int> UserPortfolio::getUserShares() {
    return userShares;
}

float UserPortfolio::getTotalValue() {
    return totalValue;
}

// Function to purchase shares
void UserPortfolio::buyShares(Stock& stock, int numShares) {
    float cost = stock.getCurrPrice() * numShares;
    if (stock.getNumShares() >= numShares) {
        if (balance >= cost) {
            userShares[&stock] += numShares;
            balance -= cost;
            stock.setNumShares(stock.getNumShares() - numShares);
            qInfo() << "Bought " << numShares << " shares of " << stock.getName() << " for " << cost;
        }
    }
}

// Function to sell user shares
void UserPortfolio::sellShares(Stock& stock, int numShares) {
    float profit = stock.getCurrPrice() * numShares;
    if (userShares.find(&stock) != userShares.end()) {
        if (userShares[&stock] > numShares) {
            userShares[&stock] -= numShares;
            balance += profit;
            stock.setNumShares(stock.getNumShares() + numShares);
            qInfo() << "Sold " << numShares << " shares of " << stock.getName() << " for " << profit;

        } else if (userShares[&stock] == numShares) {
            userShares.erase(&stock);
            balance += profit;
            stock.setNumShares(stock.getNumShares() + numShares);
            qInfo() << "Sold " << numShares << " shares of " << stock.getName() << " for " << profit;
        }
    }
}
