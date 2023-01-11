//
// Created by Ifeanyi Oraelosi on 17.12.21.
//

#include "DatabaseUtils.h"

DatabaseUtils::DatabaseUtils(std::shared_ptr<DatabaseManager> manager) : QObject() {
  _manager = manager;
}
