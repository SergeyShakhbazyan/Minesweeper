//
// Created by Sergey Shakhbazyan on 16.08.24.
//

#ifndef CP_BOARD_H
#define CP_BOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QTime>
#include <cstdlib>
#include "Cell.h"

class Board : public QWidget{
    Q_OBJECT

public:
    explicit Board(QWidget *parent, int rows, int cols, int mineCount);
    ~Board();
    void reset();
    void showAllMines();

signals:
    void gameOver(bool won);

private:
    void createBoard();
    void revealCell(int i, int j);
    void setMines();
    void calculateAdjacentMines();
    void toggleFlag(int row, int col);
    bool chackForWin();

private:
    int rows;
    int cols;
    int revealedCells;
    int flaggedCells;
    int mineCount;
    std::vector<std::vector<Cell*>> cells;
};


#endif //CP_BOARD_H
