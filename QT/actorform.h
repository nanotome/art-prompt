//
// Created by Ifeanyi Oraelosi on 22.12.21.
//

#ifndef RPGDB_QT_ACTORFORM_H
#define RPGDB_QT_ACTORFORM_H

#include <QWidget>
#include "../Models/Emoji.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EmojiForm; }
QT_END_NAMESPACE

class EmojiForm : public QWidget {
Q_OBJECT

public:
  explicit EmojiForm(QWidget *parent = nullptr);
  ~EmojiForm() override;

  bool markEmojiAsDone();

private:
  Ui::EmojiForm *ui;
  void setupUiInteraction();
  void initializeForm();

  Emoji *m_formModel;

private slots:
  void isFormDirty();

};

#endif //RPGDB_QT_ACTORFORM_H
