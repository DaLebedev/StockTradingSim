#include "stockcard.h"

StockCard::StockCard(Stock* stock, UserPortfolio* portfolio) : stock(stock), userPortfolio(portfolio), stockGraph(nullptr) {
    setStyleSheet("background-color: white; border-radius: 10px;");
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Create a container layout for both header and body
    QWidget* containerWidget = new QWidget(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(containerWidget);
    containerWidget->setStyleSheet("background-color: white; border-radius: 10px;");

    // Header layout - name, abbreviation, price
    QWidget* headerWidget = new QWidget(this);
    QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
    headerWidget->setStyleSheet("background-color: #CFCFCF; border-radius: 10px;");

    // Stock name label setup
    QLabel* nameLabel = new QLabel(QString::fromStdString(stock->getName()), headerWidget);
    nameLabel->setStyleSheet("color: black; font-size: 16px; font-weight: bold;");
    nameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    nameLabel->setAlignment(Qt::AlignLeft);

    // Stock abbreviation label setup
    QLabel* abbrLabel = new QLabel(QString::fromStdString(stock->getAbbreviation()), headerWidget);
    abbrLabel->setStyleSheet("color: black; font-size: 12px; font-weight: bold;");
    abbrLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    abbrLabel->setAlignment(Qt::AlignLeft);

    // Stock price label setup
    priceLabel = new QLabel(QString::number(stock->getCurrPrice()), headerWidget);
    priceLabel->setStyleSheet("color: black; font-size: 12px;");
    priceLabel->setAlignment(Qt::AlignRight);

    // Add widgets to header
    headerLayout->addWidget(nameLabel);
    headerLayout->addWidget(abbrLabel);
    headerLayout->addWidget(priceLabel);
    headerWidget->setLayout(headerLayout);

    // Body layout - number of shares, graph, buttonLayout
    QWidget* bodyWidget = new QWidget();
    QVBoxLayout* bodyLayout = new QVBoxLayout(bodyWidget);

    // Share count label setup
    sharesLabel = new QLabel("Number of shares: " + QString::number(stock->getNumShares()), bodyWidget);
    sharesLabel->setStyleSheet("color: black; font-size: 14px; font-weight: bold; background-color: #CFCFCF; border-radius: 5px; padding: 5px;");

    // Create graph for stock
    stockGraph = new StockGraph(stock);
    QChartView* graphWidget = stockGraph->getChartView();


    // Button layout - buy/sell buttons, quantity input, +/- quantity buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(10);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);

    // Buy/Sell Button setup
    QPushButton* buyButton = new QPushButton("Buy", bodyWidget);
    buyButton->setStyleSheet("background-color: green; color: white; font-size: 14px; font-weight: bold; border: none; border-radius: 5px; padding: 5px;");
    QPushButton* sellButton = new QPushButton("Sell", bodyWidget);
    sellButton->setStyleSheet("background-color: red; color: white; font-size: 14px; font-weight: bold; border: none; border-radius: 5px; padding: 5px;");

    // Minus button for quantity
    QPushButton* minusButton = new QPushButton("-", bodyWidget);
    minusButton->setStyleSheet("background-color: #D3D3D3; font-size: 18px; font-weight: bold; border: none; border-radius: 5px; padding: 5px;");
    minusButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Buy/Sell quantity input
    QLineEdit* quantityEdit = new QLineEdit(bodyWidget);
    quantityEdit->setValidator(new QIntValidator(1, 1000, quantityEdit));
    quantityEdit->setText("1");
    quantityEdit->setStyleSheet("background-color: #CFCFCF; color: black; font-size: 14px; font-weight: bold; padding: 5px; border-radius: 5px;");
    quantityEdit->setAlignment(Qt::AlignCenter);
    quantityEdit->setFixedWidth(50);

    // Plus button for quantity
    QPushButton* plusButton = new QPushButton("+", bodyWidget);
    plusButton->setStyleSheet("background-color: #D3D3D3; font-size: 18px; font-weight: bold; border: none; border-radius: 5px; padding: 5px;");
    plusButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Add the buttons and quantity input
    buttonsLayout->addWidget(buyButton);
    buttonsLayout->addWidget(minusButton);
    buttonsLayout->addWidget(quantityEdit);
    buttonsLayout->addWidget(plusButton);
    buttonsLayout->addWidget(sellButton);

    // Add body widgets
    bodyLayout->addWidget(sharesLabel);
    bodyLayout->addWidget(graphWidget);
    bodyLayout->addLayout(buttonsLayout);
    bodyWidget->setLayout(bodyLayout);

    // Add header and body to the container layout
    containerLayout->addWidget(headerWidget);
    containerLayout->addWidget(bodyWidget);
    containerWidget->setLayout(containerLayout);

    // Add container to main layout
    mainLayout->addWidget(containerWidget);
    setLayout(mainLayout);

    // Connect buy/sell buttons to buy/sell stocks
    connect(buyButton, &QPushButton::clicked, this, [=]() {
        portfolio->buyShares(*stock, quantityEdit->text().toInt());
        sharesLabel->setText("Number of shares: " + QString::number(stock->getNumShares()));

    });
    connect(sellButton, &QPushButton::clicked, this, [=]() {
        portfolio->sellShares(*stock, quantityEdit->text().toInt());
        sharesLabel->setText("Number of shares: " + QString::number(stock->getNumShares()));
    });

    // Connect +/- buttons to adjust quantity
    connect(minusButton, &QPushButton::clicked, this, [=]() {
        int currentVal = quantityEdit->text().toInt();
        if (currentVal > 1) {
            quantityEdit->setText(QString::number(currentVal - 1));
        }
    });
    connect(plusButton, &QPushButton::clicked, this, [=]() {
        int currentVal = quantityEdit->text().toInt();
        if (currentVal < 1000) {
            quantityEdit->setText(QString::number(currentVal + 1));
        }
    });
}

void StockCard::updateCard() {
    // Update the stock price label
    priceLabel->setText(QString::number(stock->getCurrPrice()));
    // Update the number of shares label
    sharesLabel->setText("Number of shares: " + QString::number(stock->getNumShares()));
    // Update the stock graph
    stockGraph->updateGraph();
}
