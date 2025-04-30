#include "stockgraph.h"

StockGraph::StockGraph(Stock* stock) : stock(stock) {
    series = new QLineSeries();

    // // Add the initial price
    series->append(0, stock->getCurrPrice());

    // Create QChart and add series
    chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    // X-axis setup
    axisX = new QValueAxis();
    axisX->setRange(0, 5);
    axisX->setTickInterval(1);
    axisX->setLabelFormat("%d");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisX->setTitleText("Day");

    // Y-axis setup
    axisY = new QValueAxis();
    qreal initialPrice = stock->getCurrPrice();
    axisY->setRange(initialPrice - 5, initialPrice + 5);
    axisY->setTickInterval(axisY->max()/10);
    axisY->setLabelFormat("%.2f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setTitleText("Price");

    // Create chart view
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedHeight(250);
    chartView->setFixedWidth(325);
    chart->setMargins(QMargins(0, 0, 0, 0));
}

void StockGraph::updateGraph(){
    // Update QLineSeries using priceHistory
    const auto& priceHistory = stock->getPriceHistory();
    int lastIndex = static_cast<int>(priceHistory.size()) - 1;
    series->append(lastIndex, priceHistory[lastIndex]);

    // Dynamic X-axis (days) scrolling
    int day = stock->getPriceHistory().size();
    int startDay = max(0, day - 30);
    startDay = max(0, startDay);
    axisX->setRange(startDay, max(5, day + 1));
    axisX->setLabelFormat("%d");

    // Dynamic Y-axis (price) range expansion
    qreal currPrice = stock->getCurrPrice();
    qreal minY = axisY->min();
    qreal maxY = axisY->max();
    qreal buffer = (maxY - minY) * 0.5;
    if ((currPrice - minY) < buffer) {
        minY = currPrice - (currPrice * 0.1);
    }
    if ((maxY - currPrice) < buffer) {
        maxY = currPrice + (currPrice * 0.1);
    }
    minY = floor(min(minY, axisY->min()) / 5.0) * 5.0;
    maxY = ceil(max(maxY, axisY->max()) / 5.0) * 5.0;
    axisY->setRange(minY, maxY);
    axisY->setLabelFormat("%.2f");
}

QChartView* StockGraph::getChartView() {
    return chartView;
}
