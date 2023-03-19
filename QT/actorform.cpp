//
// Created by Ifeanyi Oraelosi on 22.12.21.
//
#include <QDebug>
#include <QSvgRenderer>
#include <QSvgWidget>
#include "actorform.h"
#include "ui_actorform.h"

#include "../Models/Emoji.h"

EmojiForm::EmojiForm(QWidget *parent) :
    QWidget(parent) {
  ui = std::make_unique<Ui::EmojiForm>();
  m_formModel = std::make_unique<Emoji>();
    m_formModel->initialEmoji();
  ui->setupUi(this);

  setupUiInteraction();
  initializeForm();
}

EmojiForm::~EmojiForm() = default;

void EmojiForm::initializeForm() {
    emojiView = std::make_unique<QSvgWidget>(this);
  emojiView->renderer()->load(m_formModel->svg().toUtf8());
  emojiView->setFixedSize(512, 512);
  ui->emojiContainer->addWidget(emojiView.get());
  ui->emojiContainer->setAlignment(Qt::AlignCenter);
}

void EmojiForm::setupUiInteraction() {
  connect(ui->emojiDoneButton, &QPushButton::clicked, this, [this]() {
      // TEMP: debugging
      skipEmoji();
  });
  connect(ui->emojiSkipButton, &QPushButton::clicked, this, [this]() {
      // TEMP: debugging
      markEmojiAsDone();
  });
}

void EmojiForm::markEmojiAsDone(){
    m_formModel->markAsDone();
    emojiView->renderer()->load(m_formModel->svg().toUtf8());
    emojiView->update();
}

void EmojiForm::skipEmoji() {
    m_formModel->skip();
    emojiView->renderer()->load(m_formModel->svg().toUtf8());
    emojiView->update();
}
