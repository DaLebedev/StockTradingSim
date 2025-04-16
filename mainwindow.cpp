#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stock.h"
#include <QTimer>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Stock Trading Sim");

    // Initialize game and market
    vector<Stock*> market = {
        new Stock("Apple", "APL", 150.25, 1000),
        new Stock("Tesla", "TSLA", 280.15, 5000),
        new Stock("Microssoft", "MSFT", 360.07, 5000),
    };

    game = new Game(market);
    gameTimer = new QTimer(this);

    QRegularExpressionValidator* numValidator = new QRegularExpressionValidator(QRegularExpression("^\\d{0,7}$"));
    ui->startEdit->setValidator(numValidator);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to handle starting game
void MainWindow::startButtonClicked() {
    startBalance = ui->startEdit->text();

    // Hide start screen widgets
    ui->startButton->hide();
    ui->startEdit->hide();
    ui->startLabel->hide();

    // TESTING INFO - DELETE LATER
    qInfo() << "Balance: " << startBalance;
    displayStocks(game->getMarket());

    // Create new userPortfolio with selected balance
    userPortfolio = new UserPortfolio(startBalance.toFloat());
    // Start game timer, when time runs out, update day
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGameDay);
    gameTimer->start(1000);
}

// Helper function to call advanceDay
void MainWindow::updateGameDay() {
    game->advanceDay();
}

// TODO: Complete function to dynamically display each stock
void MainWindow::displayStocks(vector<Stock*> stocks) {

    QWidget* gamePage = ui->stackedWidget->widget(1);

    // Create new layout for gamePage
    QVBoxLayout* layout = new QVBoxLayout(gamePage);
    gamePage->setLayout(layout);

    // Add labels for each stock
    for (const auto& stock : stocks) {
        QLabel* stockLabel = new QLabel(QString::fromStdString(stock->getName()), gamePage);
        layout->addWidget(stockLabel);
    }

    // Show game page
    ui->stackedWidget->setCurrentWidget(gamePage);
}
