#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "game.h"
#include "userportfolio.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor Declaratios
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString startBalance;
    Game* game;
    QTimer* gameTimer;
    UserPortfolio* userPortfolio;

    // Function Declarations
    void updateGameDay();
    void displayStocks(vector<Stock*> stocks);

private slots:
    void startButtonClicked();
};
#endif // MAINWINDOW_H
