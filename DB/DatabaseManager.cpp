//
// Created by Ifeanyi Oraelosi on 16.12.21.
//

#include "DatabaseManager.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlDriver>
#include <QCoreApplication>

bool DatabaseManager::initDatabase() {
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/ranmoji.db");

    bool isOpen = db.open();

    if (!isOpen) {
      auto mError = db.lastError().text();
      qDebug() << mError;
    }

    qDebug() << "Database: connection ok";
    return isOpen;
}

bool DatabaseManager::isDatabaseOpen() const {
  return _database.isOpen();
}

QSqlDatabase DatabaseManager::getDatabase() {
  return QSqlDatabase::database(QCoreApplication::applicationDirPath() + "/ranmoji.db");
}
