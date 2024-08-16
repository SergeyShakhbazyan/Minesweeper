//
// Created by Sergey Shakhbazyan on 16.08.24.
//

#ifndef CP_CELL_H
#define CP_CELL_H

#include <QPushButton>
#include <QMouseEvent>

class Cell : public QPushButton{
    Q_OBJECT
public:
    Cell(QWidget *parent);

    void reset();
    void reveal();
    bool isRevealed();

    void setMine(const bool& isMine);
    bool isMine() const;

    bool isFlagged() const;
    void toggleFlag();


    void adjacentMineCount(const int& count);
    int getAdjacentMineCount() const;

signals:
    void cellClicked(Cell *cell);
    void cellRightClicked(Cell *cell);

private:
    bool mine;
    bool revealed;
    bool flagged;
    int adjacentMines;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};


#endif //CP_CELL_H
