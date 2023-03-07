//
// Created by Ifeanyi Oraelosi on 26.01.22.
//

#ifndef RANMOJI_MODELS_EMOJI_H
#define RANMOJI_MODELS_EMOJI_H

#include <QString>
#include <QDateTime>
#include <QSqlQuery>

class Emoji {
private:
  int m_id;
  QString m_emoji_id;
  QString m_svg;
  QString m_status;
  QDateTime m_startedAt;
  QDateTime m_finishedAt;
public:
  Emoji();
  [[nodiscard]] int id() const;
  QString emojiId() const;
  [[nodiscard]] QString svg() const;
  [[nodiscard]] QString status() const;
  QDateTime startedAt() const;
  QDateTime finishedAt() const;

  Emoji* markAsDone();
  Emoji* skip();
  Emoji* nextEmoji();

  Emoji emojiFromQuery(const QSqlQuery& query);
  Emoji fetchCurrentEmoji();
  Emoji fetchNextEmoji();

  void resetEmoji();
};

#endif //RANMOJI_MODELS_EMOJI_H
