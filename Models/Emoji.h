//
// Created by Ifeanyi Oraelosi on 26.01.22.
//

#ifndef RANMOJI_MODELS_EMOJI_H
#define RANMOJI_MODELS_EMOJI_H

#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include "../DB/DatabaseManager.h"

class Emoji {
private:
  int m_id = 0;
  QString m_emoji_id = "";
  QString m_svg = "";
  QString m_status = "NEW";
  QDateTime m_startedAt;
  QDateTime m_finishedAt;
  DatabaseManager m_dbManager;
public:
  [[nodiscard]] int id() const;
  QString emojiId() const;
  [[nodiscard]] QString svg() const;
  [[nodiscard]] QString status() const;
  QDateTime startedAt() const;
  QDateTime finishedAt() const;

  void markAsDone();
  void skip();
  void nextEmoji();
  void initialEmoji();

  void emojiFromQuery(const QSqlQuery& query);
  void fetchCurrentEmoji();
  void fetchNextEmoji();

  void resetEmoji();
};

#endif //RANMOJI_MODELS_EMOJI_H
