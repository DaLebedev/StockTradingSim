#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QtCharts/QLineSeries>
#include "game.h"
#include "userportfolio.h"
#include "stockgraph.h"
#include "stockcard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor Declarations
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString startBalance;
    Game* game;
    QTimer* gameTimer;
    UserPortfolio* userPortfolio;
    QMap<Stock*, StockCard*> stockCards;
    QMap<Stock*, StockGraph*> stockGraphs;

    // Function Declarations
    QWidget* createStockCard(Stock* stock);
    QWidget* createGraph(Stock* stock);
    void displayStocks(vector<Stock*> stocks);    
    void displayPortfolio(UserPortfolio portfolio);

private slots:
    void startButtonClicked();
    void updateGameDay();
    void buyStock(Stock* stock, int quantity);
    void sellStock(Stock* stock, int quantity);
};
#endif // MAINWINDOW_H
