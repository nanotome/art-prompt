//
// Created by Ifeanyi Oraelosi on 26.01.22.
//
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <utility>
#include "../DB/DatabaseManager.h"

#include "ActorType.h"

ActorType::ActorType() {
  m_id = 0;
  m_name = "";
  m_description = "";
}

int ActorType::id() const {
  return m_id;
}

void ActorType::setId(int id) {
  m_id = id;
}

QString ActorType::name() const {
  return m_name;
}

void ActorType::setName(QString name) {
  m_name = std::move(name);
}

QString ActorType::description() const {
  return m_description;
}

void ActorType::setDescription(QString description) {
  m_description = description;
}

bool ActorType::save() {
  DatabaseManager dbManager;
  QSqlQuery query(dbManager.getDatabase());

  query.prepare("INSERT INTO actor_type (name, description) VALUES (:name, :description)");
  query.bindValue(":name", this->name());
  query.bindValue(":description", this->description());
  return query.exec();
}

ActorType ActorType::fetchById(int id) {
  DatabaseManager dbManager;
  QSqlQuery query(dbManager.getDatabase());

  query.prepare("SELECT * FROM actor_type WHERE 'id' = :id");
  query.bindValue(":id", id);

  if (!query.exec()) {
	qWarning() << __func__ << ": " << query.lastError();
  } else {
	if (query.first()) {
	  return actorTypeFromQuery(query);
	}
  }

  return {};
}

ActorType ActorType::actorTypeFromQuery(const QSqlQuery& query) {
  return ActorType().fillFromQuery(query);
}

ActorType ActorType::fillFromQuery(const QSqlQuery& query) {
  m_id = query.value("id").toInt();
  m_name = query.value("name").toString();
  m_description = query.value("description").toString();

  return *this;
}

