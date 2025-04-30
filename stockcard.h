#ifndef STOCKCARD_H
#define STOCKCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QChartView>
#include <QRegularExpressionValidator>
#include "stock.h"
#include "stockgraph.h"
#include "userportfolio.h"

class StockCard : public QWidget {
    Q_OBJECT

public:
    explicit StockCard(Stock* stock, UserPortfolio* portfolio);

private:
    Stock* stock;
    UserPortfolio* userPortfolio;
    QLabel* priceLabel;
    QLabel* sharesLabel;
    StockGraph* stockGraph;
public:
    void updateCard();
};

#endif // STOCKCARD_H
