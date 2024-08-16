//
// Created by Sergey Shakhbazyan on 16.08.24.
//

#include "Board.h"

Board::Board(QWidget *parent, int rows, int cols, int mineCount)
    : QWidget(parent), rows(rows), cols(cols), revealedCells(0), flaggedCells(0), mineCount(mineCount){
    createBoard();
    setMines();
    calculateAdjacentMines();
}

Board::~Board(){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete cells[i][j];
        }
    }
}

void Board::createBoard() {
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);

    cells.resize(rows);
    for(int i = 0; i < rows; i++) {
        cells[i].resize(cols, nullptr);
        for(int j = 0; j < cols; j++) {
            cells[i][j] = new Cell(this);
            gridLayout->addWidget(cells[i][j], i, j);
            connect(cells[i][j], &Cell::clicked, [=]() {
                revealCell(i, j);
            });
            connect(cells[i][j], &Cell::cellRightClicked, [=]() {
                toggleFlag(i, j);
            });
        }
    }
    setLayout(gridLayout);
}

void Board::revealCell(int i, int j) {
    if(cells[i][j]->isRevealed() || cells[i][j]->isFlagged()){
        return;
    }

    cells[i][j]->reveal();
    ++revealedCells;

    if(cells[i][j]->isMine()){
        showAllMines();
        emit gameOver(false);
    }else if(cells[i][j]->getAdjacentMineCount() == 0){
        for (int k = -1; k <= 1; ++k) {
            for (int l = -1; l <= 1; ++l) {
                int newRow = i + k;
                int newCol = j + l;

                if(newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols){
                    revealCell(newRow, newCol);
                }
            }
        }
    }
    if (chackForWin()) {
        emit gameOver(true);
    }
}

void Board::setMines() {
    srand(QTime::currentTime().msecsSinceStartOfDay());
    int minesPlaced = 0;
    while(minesPlaced <= mineCount){
        int row = rand() % rows;
        int col = rand() % cols;

        if (!cells[row][col]->isMine()) {
            cells[row][col]->setMine(true);
            ++minesPlaced;
        }
    }
}

void Board::calculateAdjacentMines() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(!cells[i][j]->isMine()){
                int minCount = 0;
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        int newRow = i + k;
                        int newCol = j + l;

                        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && cells[newRow][newCol]->isMine()) {
                            ++minCount;
                        }
                    }
                }
                cells[i][j]->adjacentMineCount(minCount);
            }
        }
    }
}

void Board::toggleFlag(int row, int col) {
    if (!cells[row][col]->isRevealed()) {
        cells[row][col]->toggleFlag();
        flaggedCells += cells[row][col]->isFlagged() ? 1 : -1;
    }
}

bool Board::chackForWin() {
    return revealedCells + flaggedCells == rows * cols;
}

void Board::reset() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j]->reset();
        }
    }
    flaggedCells = 0;
    revealedCells = 0;
    setMines();
    calculateAdjacentMines();
}

void Board::showAllMines() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(cells[i][j]->isMine()){
                cells[i][j]->reveal();
            }
        }
    }
}