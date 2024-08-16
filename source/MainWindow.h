//
// Created by Sergey Shakhbazyan on 16.08.24.
//

#ifndef CP_MAINWINDOW_H
#define CP_MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "Board.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
private:
    void handleForGameOver(bool won);
    Board* board;

};


#endif //CP_MAINWINDOW_H
