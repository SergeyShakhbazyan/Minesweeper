//
// Created by Sergey Shakhbazyan on 16.08.24.
//

#include "Cell.h"

Cell::Cell(QWidget *parent) : QPushButton(parent), mine(false), revealed(false), flagged(false), adjacentMines(0){
    setFixedSize(40,40);
}

void Cell::reset() {
    this->mine = false;
    this->revealed = false;
    this->flagged = false;
    this->adjacentMines = 0;
    setText(" ");
}

void Cell::reveal() {
    revealed = true;
    if(!isMine()){
        setText(QString::number(adjacentMines));
    }else{
        setText("*");
    }
}

bool Cell::isRevealed() {
    return revealed;
}

void Cell::setMine(const bool &isMine) {
    this->mine = isMine;
}

bool Cell::isMine() const {
    return mine;
}

void Cell::toggleFlag() {
    if(!revealed){
        this->flagged = !this->flagged;
        setText(flagged ? "F" : " ");
    }
}

bool Cell::isFlagged() const {
    return this->flagged;
}

void Cell::adjacentMineCount(const int& count){
    this->adjacentMines = count;
}

int Cell::getAdjacentMineCount() const {
    return this->adjacentMines;
}

void Cell::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit cellRightClicked(this);
    } else {
        QPushButton::mousePressEvent(event);
    }
}