//
// Created by Ifeanyi Oraelosi on 16.12.21.
//

#include "DatabaseManager.h"

#include <QSqlQuery>
#include <QDebug>

DatabaseManager::DatabaseManager() {
  connectDatabase();
}

DatabaseManager::~DatabaseManager() {
  _database.close();
}

bool DatabaseManager::connectDatabase() {
  try {
	_database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName("ranmoji.db");

	bool isOpen = _database.open();

	if (!isOpen) {
	  throw std::runtime_error{"Couldn't open database..."};
	}
  } catch (std::exception &e) {
	(void)(e);
	return false;
  }

  qDebug() << "Database: connection ok";
  return true;
}

bool DatabaseManager::isDatabaseOpen() const {
  return _database.isOpen();
}

QSqlDatabase DatabaseManager::getDatabase() {
  return _database;
}
