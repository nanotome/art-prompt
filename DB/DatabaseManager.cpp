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
    _database.setDatabaseName("RPGDB.db");

	bool isOpen = _database.open();

	if (!isOpen) {
	  throw std::runtime_error{"Couldn't open database..."};
	}
  } catch (std::exception &e) {
	(void)(e);
	return false;
  }

  createTables();
  qDebug() << "Database: connection ok";
  return true;
}

bool DatabaseManager::isDatabaseOpen() const {
  return _database.isOpen();
}

QSqlDatabase DatabaseManager::getDatabase() {
  return _database;
}

bool DatabaseManager::createTables() {
  QSqlQuery query(_database);

  query.exec(
    "CREATE TABLE IF NOT EXISTS actor_type( "
    "  actor_type_id INTEGER PRIMARY KEY, "
    "  name TEXT, "
    "  description TEXT"
    ")"
  );

  return true;
}
