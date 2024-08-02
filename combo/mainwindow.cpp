#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::on_calculateButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculateButton_clicked()
{
    int outs = ui->outsSpinBox->value();
    double potSize = ui->potSizeSpinBox->value();
    double betSize = ui->betSizeSpinBox->value();
    int totalCards = 52 - 2; // Assuming 2 cards are known (simplification)

    double equity = calculatePotEquity(outs, potSize, betSize, totalCards);
    ui->potEquityLabel->setText(QString::number(equity, 'f', 2));
}

double MainWindow::calculatePotEquity(int outs, double potSize, double betSize, int totalCards)
{
    int unseenCards = totalCards - 2; // Assuming 2 cards are known
    long long favorableOutcomes = combination(outs, 1); // Number of favorable outcomes

    long long totalOutcomes = combination(unseenCards, 1); // Total possible outcomes
    double winProbability = static_cast<double>(favorableOutcomes) / totalOutcomes;
    double betToPotRatio = betSize / potSize;

    return winProbability / (winProbability + betToPotRatio);
}

long long MainWindow::combination(int n, int k)
{
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    long long result = 1;
    for (int i = 1; i <= k; ++i)
    {
        result *= (n - (k - i));
        result /= i;
    }
    return result;
}
