#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QSpinBox>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Stock Trading Sim");
    setFixedSize(1200, 700);

    // Initialize game and market
    vector<Stock*> market = {
        new Stock("Intel", "INTC", 4500, 35),
        new Stock("Coca-Cola", "KO", 5000, 62),
        new Stock("Uber", "UBER", 4500, 65),
        new Stock("Starbucks", "SBUX", 3500, 95),
        new Stock("Nike", "NKE", 4000, 92),
        new Stock("Disney", "DIS", 2000, 105),
        new Stock("Amazon", "AMZN", 5000, 120),
        new Stock("Google", "GOOGL", 4000, 140),
        new Stock("AMD", "AMD", 4000, 145),
        new Stock("Apple", "AAPL", 5000, 170),
        new Stock("Tesla", "TSLA", 3000, 180),
        new Stock("PepsiCo", "PEP", 4000, 180),
        new Stock("Visa", "V", 3000, 270),
        new Stock("McDonald's", "MCD", 3000, 285),
        new Stock("Microsoft", "MSFT", 4000, 320),
        new Stock("Meta Platforms", "META", 3500, 430),
        new Stock("Berkshire Hathaway", "BRK.B", 1000, 410),
        new Stock("Mastercard", "MA", 2500, 460),
        new Stock("Adobe", "ADBE", 2000, 500),
        new Stock("Netflix", "NFLX", 3000, 560),
        new Stock("Nvidia", "NVDA", 2500, 760),
    };

    // Initialize game object and game timer
    game = new Game(market);
    gameTimer = new QTimer(this);

    // Ensures only numbers up to 9999999 are entered in balance
    ui->startEdit->setValidator(new QIntValidator(100, 1000000, ui->startEdit));
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to handle starting game
void MainWindow::startButtonClicked() {
    int balance = ui->startEdit->text().toInt();

    // Check if the input is valid and within range
    if (balance < 1000 || balance > 1000000) {
        return;
    }

    // Set user str
    startBalance = ui->startEdit->text();

    // Hide start screen widgets
    ui->startButton->hide();
    ui->startEdit->hide();
    ui->startLabel->hide();

    // TESTING INFO - DELETE LATER
    qInfo() << "Balance: " << startBalance;

    // Create userPortfolio with selected balance
    userPortfolio = new UserPortfolio(startBalance.toFloat());

    // Display game screen
    displayStocks(game->getMarket());

    // Start game timer to update day
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGameDay);
    gameTimer->start(1000);
}

// Function to advance the day
void MainWindow::updateGameDay() {
    game->advanceDay();
    for (auto it = stockCards.begin(); it != stockCards.end(); ++it) {
        StockCard* stockCard = it.value();
        stockCard->updateCard();
    }
}

// Helper for buying stock
void MainWindow::buyStock(Stock* stock, int quantity) {
    userPortfolio->buyShares(*stock, quantity);
}

// Helper for selling stock
void MainWindow::sellStock(Stock* stock, int quantity) {
    userPortfolio->sellShares(*stock, quantity);
}

// Function to generate and display stock cards for each stock
void MainWindow::displayStocks(vector<Stock*> stocks) {

    // Set up scroll area with grid layout
    QWidget* gamePage = ui->stackedWidget->widget(1);
    QScrollArea* scrollArea = new QScrollArea(gamePage);
    QWidget* container = new QWidget();
    QGridLayout* gridLayout = new QGridLayout(container);
    scrollArea->setWidgetResizable(true);
    container->setLayout(gridLayout);
    scrollArea->setWidget(container);

    // Create card for each stock
    for (int i = 0; i < static_cast<int>(stocks.size()); ++i) {
        Stock* stock = stocks[i];
        StockCard* stockCard = new StockCard(stock, userPortfolio);
        gridLayout->addWidget(stockCard, i / 3, i % 3);
        stockCards[stock] = stockCard;
    }

    // Add the scroll area to the game page's layout
    QVBoxLayout* gamePageLayout = new QVBoxLayout(gamePage);
    gamePageLayout->addWidget(scrollArea);
    gamePage->setLayout(gamePageLayout);

    // Show game page
    ui->stackedWidget->setCurrentWidget(gamePage);
}
