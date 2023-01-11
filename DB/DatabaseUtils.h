//
// Created by Ifeanyi Oraelosi on 17.12.21.
//

#ifndef RPGDB_DB_DATABASEUTILS_H
#define RPGDB_DB_DATABASEUTILS_H

#include "DatabaseManager.h"

#include <QObject>
#include <memory>

const int CURRENT_DB_VERSION = 1;

class DatabaseUtils : public QObject {
public:
  DatabaseUtils(std::shared_ptr<DatabaseManager> manager);

private:
  std::shared_ptr<DatabaseManager> _manager;
};

#endif //RPGDB_DB_DATABASEUTILS_H
