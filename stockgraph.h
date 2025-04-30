#ifndef STOCKGRAPH_H
#define STOCKGRAPH_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QWidget>
#include "stock.h"

class StockGraph : public QWidget
{
    Q_OBJECT

public:
    explicit StockGraph(Stock* stock);
    void updateGraph();
    QChartView* getChartView();

private:
    QLineSeries* series;
    QChart* chart;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QChartView* chartView;
    Stock* stock;
};

#endif // STOCKGRAPH_H
