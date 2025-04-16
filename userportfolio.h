#ifndef USERPORTFOLIO_H
#define USERPORTFOLIO_H
#include <string>
#include <map>
#include "stock.h"
using namespace std;

class UserPortfolio{
private:
    float balance;
    map<Stock*, int> userShares;
    float totalValue;

public:
    // Constructor
    UserPortfolio(float balance);

    // Getter & Setter Declarations
    float getBalance();
    void setBalance(float balance);
    map<Stock*, int> getUserShares();
    float getTotalValue();

    // Function Declarations
    void buyShares(Stock& stock, int numShares);
    void sellShares(Stock& stock, int numShares);
};

#endif // USERPORTFOLIO_H
