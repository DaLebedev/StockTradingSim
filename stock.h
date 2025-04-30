#ifndef STOCK_H
#define STOCK_H
#include <string>
#include <vector>
#include <cmath>
#include <random>
using namespace std;

class Stock {
private:
    // Ornstein-Uhlenbeck price calulation vars
    string name;
    string abbreviation;
    int numShares;
    float initPrice;
    float meanPrice;
    float currPrice;
    vector<float> priceHistory;
    float volatility;
    float reversionRate = 0.95;

    // Static number generator seeding


public:
    // Constructor Declarations
    Stock(string name, string abbreviation, int numShares, float initPrice);

    // Getter & Setter Declarations
    string getName();
    string getAbbreviation();
    int getNumShares();
    void setNumShares(int numShares);
    float getInitPrice();
    float getMeanPrice();
    float getCurrPrice();
    void setCurrPrice(float currPrice);
    vector<float> getPriceHistory();
    float getVolatility();

    // Function Declarations
    float ornsteinUhlenbeck(float timeStep);
    float priceChange();
    void updatePrice();
};

extern random_device rd;
extern mt19937 gen;

#endif // STOCK_H
