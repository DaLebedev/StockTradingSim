#ifndef STOCK_H
#define STOCK_H
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Stock {
private:
    string name;
    string abbreviation;
    float currPrice;
    int numShares;
    vector<float> priceHistory;

public:
    // Constructor Declaration
    Stock(string name, string abbreviation, float currPrice, int numShares);

    // Getter & Setter Declarations
    string getName();

    string getAbbreviation();

    float getCurrPrice();
    void setCurrPrice(float currPrice);

    int getNumShares();

    vector<float> getPriceHistory();

    // Function Declarations
    float priceChange();
    void updatePrice();

};

#endif // STOCK_H
