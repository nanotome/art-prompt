//
// Created by Ifeanyi Oraelosi on 20.12.21.
//

#ifndef RPGDB_QT_MAINWINDOW_H
#define RPGDB_QT_MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "actorform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private:
  std::unique_ptr<Ui::MainWindow> ui;
  std::unique_ptr<EmojiForm> _emojiForm;
};

#endif //RPGDB_QT_MAINWINDOW_H
