#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    double equity = calculatePotEquity(outs, potSize, betSize);
    ui->potEquityLabel->setText(QString::number(equity, 'f', 2));
}

double MainWindow::calculatePotEquity(int outs, double potSize, double betSize)
{
    double totalOuts = outs + 2; // Assuming 2 cards are seen (simplification)
    double winProbability = outs / totalOuts;
    double betToPotRatio = betSize / potSize;

    return winProbability / (winProbability + betToPotRatio);
}
