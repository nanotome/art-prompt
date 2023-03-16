//
// Created by Ifeanyi Oraelosi on 22.12.21.
//

#ifndef RPGDB_QT_ACTORFORM_H
#define RPGDB_QT_ACTORFORM_H

#include <QWidget>
#include <QSvgWidget>
#include <memory>
#include "../Models/Emoji.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EmojiForm; }
QT_END_NAMESPACE

class EmojiForm : public QWidget {
Q_OBJECT

public:
  explicit EmojiForm(QWidget *parent = nullptr);
  ~EmojiForm() override;

  void markEmojiAsDone();
  void skipEmoji();

private:
  std::unique_ptr<Ui::EmojiForm> ui;
  std::unique_ptr<QSvgWidget> emojiView;
  void setupUiInteraction();
  void initializeForm();

  std::unique_ptr<Emoji> m_formModel;
};

#endif //RPGDB_QT_ACTORFORM_H
