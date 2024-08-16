//
// Created by Sergey Shakhbazyan on 16.08.24.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    Board* board = new Board(this, 10,10, 20);

    layout->addWidget(board);

    QPushButton* resetButton = new QPushButton("Reset", this);
    connect(resetButton, &QPushButton::clicked, board, &Board::reset);
    layout->addWidget(resetButton);

    setCentralWidget(centralWidget);

    connect(board, &Board::gameOver, this, &MainWindow::handleForGameOver);
}

void MainWindow::handleForGameOver(bool won) {
    if (won) {
        QMessageBox::information(this, "Minesweeper", "You won!");
    } else {
        QMessageBox::critical(this, "Minesweeper", "You lost!");
    }
}