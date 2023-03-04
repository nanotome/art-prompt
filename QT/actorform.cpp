//
// Created by Ifeanyi Oraelosi on 22.12.21.
//
#include <QDebug>
#include "actorform.h"
#include "ui_actorform.h"

#include "../Models/Emoji.h"

EmojiForm::EmojiForm(QWidget *parent) :
    QWidget(parent), ui(new Ui::EmojiForm) {
  ui->setupUi(this);

  setupUiInteraction();
  initializeForm();
}

EmojiForm::~EmojiForm() {
  delete ui;
}

void EmojiForm::initializeForm() {
  m_formModel = Emoji().nextEmoji();
  qDebug() << m_formModel->svg();
}

void EmojiForm::setupUiInteraction() {
  connect(ui->emojiDoneButton, &QPushButton::clicked, this, [&]() {
      EmojiForm::markEmojiAsDone();
  });
}

bool EmojiForm::markEmojiAsDone(){
    return m_formModel->markAsDone();
}

void EmojiForm::isFormDirty() {

}
