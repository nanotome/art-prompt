//
// Created by Ifeanyi Oraelosi on 26.01.22.
//
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <utility>

#include "Emoji.h"

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

void Emoji::markAsDone() {
    m_status = "FINISHED";
    m_finishedAt = QDateTime::currentDateTimeUtc();
  QSqlQuery query(m_dbManager.getDatabase());

  query.prepare("UPDATE jobs SET finishedAt = :finishedAt, status = :status WHERE id = :id");
  query.bindValue(":id", this->id());
  query.bindValue(":status", this->status());
  query.bindValue(":finishedAt", this->finishedAt());

  if (!query.exec()) {
    qWarning() << __func__ << ": " << query.lastError();
  } else {
    nextEmoji();
  }
}

void Emoji::skip() {
    nextEmoji();
}

/**
 * Get the first emoji with a status of RUNNING. If none can be found, get
 * the first random emoji with a status of NEW.
 *
 * @brief Emoji::nextEmoji
 * @return
 */
void Emoji::nextEmoji() {
    fetchCurrentEmoji();

    if (this->emojiId() == "") {
        fetchNextEmoji();
    }

    m_status = "RUNNING";
    m_startedAt = QDateTime::currentDateTimeUtc();

    QSqlQuery query(m_dbManager.getDatabase());

    query.prepare("UPDATE jobs SET startedAt = :startedAt, status = :status WHERE id = :id");
    query.bindValue(":id", this->id());
    query.bindValue(":status", this->status());
    query.bindValue(":startedAt", this->startedAt());
}

void Emoji::fetchCurrentEmoji() {
  QSqlQuery query(m_dbManager.getDatabase());

  query.prepare("SELECT * FROM jobs WHERE id != :id AND status = :status LIMIT 1");
  query.bindValue(":id", this->id());
  query.bindValue(":status", "RUNNING");

  if (!query.exec()) {
	qWarning() << __func__ << ": " << query.lastError();
  } else {
	if (query.first()) {
      emojiFromQuery(query);
    } else {
        resetEmoji();
    }
  }
}

void Emoji::fetchNextEmoji() {
    QSqlQuery query(m_dbManager.getDatabase());

    query.prepare("SELECT * FROM jobs WHERE status = :status ORDER BY random() LIMIT 1");
    query.bindValue(":status", "NEW");

    if (!query.exec()) {
      qWarning() << __func__ << ": " << query.lastError();
    } else {
      if (query.first()) {
        emojiFromQuery(query);
      }
    }
}

void Emoji::emojiFromQuery(const QSqlQuery& query) {
  m_id = query.value("id").toInt();
  m_emoji_id = query.value("emoji_id").toString();
  m_svg = query.value("svg").toString();
  m_status = query.value("status").toString();

  if (QString startedAtFromDb = query.value("startedAt").toString(); startedAtFromDb != "") {
    m_startedAt = QDateTime::fromString(query.value("startedAt").toString());
  }

  if (QString finishedAtFromDb = query.value("finishedAt").toString(); finishedAtFromDb != "") {
     m_finishedAt = QDateTime::fromString(query.value("finishedAt").toString());
  }
}

void Emoji::resetEmoji() {
    m_id = 0;
    m_emoji_id = "";
    m_svg = "";
    m_status = "NEW";
    m_startedAt = QDateTime();
    m_finishedAt = QDateTime();
}
