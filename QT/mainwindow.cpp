//
// Created by Ifeanyi Oraelosi on 20.12.21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    ui = std::make_unique<Ui::MainWindow>();
  ui->setupUi(this);
  _emojiForm = std::make_unique<EmojiForm>();
  setCentralWidget(_emojiForm.get());
}

MainWindow::~MainWindow() = default;

