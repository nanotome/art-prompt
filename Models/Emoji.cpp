//
// Created by Ifeanyi Oraelosi on 26.01.22.
//
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <utility>
#include "../DB/DatabaseManager.h"

#include "Emoji.h"

Emoji::Emoji() {
    m_id = 0;
    m_emoji_id = "";
    m_svg = "";
    m_status = "NEW";
    m_startedAt = QDateTime::currentDateTimeUtc();
    m_finishedAt = QDateTime::currentDateTimeUtc();
}

int Emoji::id() const {
  return m_id;
}

QString Emoji::emojiId() const {
  return m_emoji_id;
}

QString Emoji::svg() const {
  return m_svg;
}

QString Emoji::status() const {
    return m_status;
}

QDateTime Emoji::startedAt() const {
    return m_startedAt;
}

QDateTime Emoji::finishedAt() const {
    return m_finishedAt;
}

bool Emoji::markAsDone() {
    m_status = "FINISHED";
    m_finishedAt = QDateTime::currentDateTimeUtc();
  DatabaseManager dbManager;
  QSqlQuery query(dbManager.getDatabase());

  query.prepare("UPDATE jobs SET 'finishedAt' = :finishedAt, 'status' = :status WHERE 'id' = :id");
  query.bindValue(":id", this->id());
  query.bindValue(":status", this->status());
  query.bindValue(":finishedAt", this->finishedAt().toString());
  return query.exec();
}

Emoji Emoji::skip() {
    fetchNextEmoji();

    m_status = "RUNNING";

    DatabaseManager dbManager;
    QSqlQuery query(dbManager.getDatabase());

    query.prepare("UPDATE jobs SET 'status' = :status WHERE 'id' = :id");
    query.bindValue(":id", this->id());
    query.bindValue(":status", this->status());

    return *this;
}

/**
 * Get the first emoji with a status of RUNNING. If none can be found, get
 * the first random emoji with a status of NEW.
 *
 * @brief Emoji::nextEmoji
 * @return
 */
Emoji Emoji::nextEmoji() {
    fetchCurrentEmoji();

    if (this->emojiId() == "") {
        // no RUNNING emoji was found
        fetchNextEmoji();
    }

    m_status = "RUNNING";

    DatabaseManager dbManager;
    QSqlQuery query(dbManager.getDatabase());

    query.prepare("UPDATE jobs SET 'status' = :status WHERE 'id' = :id");
    query.bindValue(":id", this->id());
    query.bindValue(":status", this->status());

    return *this;
}

Emoji Emoji::fetchCurrentEmoji() {
  DatabaseManager dbManager;
  QSqlQuery query(dbManager.getDatabase());

  query.prepare("SELECT * FROM jobs WHERE 'status' = 'RUNNING' LIMIT 1");

  if (!query.exec()) {
	qWarning() << __func__ << ": " << query.lastError();
  } else {
	if (query.first()) {
      return emojiFromQuery(query);
	}
  }

  return {};
}

Emoji Emoji::fetchNextEmoji() {
    DatabaseManager dbManager;
    QSqlQuery query(dbManager.getDatabase());

    query.prepare("SELECT * FROM jobs WHERE 'status' = 'NEW' ORDER BY random() LIMIT 1");

    if (!query.exec()) {
      qWarning() << __func__ << ": " << query.lastError();
    } else {
      if (query.first()) {
        return emojiFromQuery(query);
      }
    }

    return {};
}

Emoji Emoji::emojiFromQuery(const QSqlQuery& query) {
  m_id = query.value("id").toInt();
  m_emoji_id = query.value("emoji_id").toString();
  m_svg = query.value("svg").toString();
  m_status = query.value("status").toString();
  m_startedAt = QDateTime::fromString(query.value("startedAt").toString());
  m_finishedAt = QDateTime::fromString(query.value("finishedAt").toString());

  return *this;
}
