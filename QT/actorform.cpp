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
    QWidget(parent), ui(new Ui::EmojiForm) {
    Emoji* newEmoji = new Emoji();
  m_formModel = newEmoji->nextEmoji();
  ui->setupUi(this);

  setupUiInteraction();
  initializeForm();
}

EmojiForm::~EmojiForm() {
  delete ui;
}

void EmojiForm::initializeForm() {
  emojiView = new QSvgWidget(this);
  emojiView->renderer()->load(m_formModel->svg().toUtf8());
  emojiView->setFixedSize(512, 512);
  ui->emojiContainer->addWidget(emojiView);
  ui->emojiContainer->setAlignment(Qt::AlignCenter);
}

void EmojiForm::setupUiInteraction() {
  connect(ui->emojiDoneButton, &QPushButton::clicked, this, [&]() {
      markEmojiAsDone();
  });
  connect(ui->emojiSkipButton, &QPushButton::clicked, this, [&]() {
      skipEmoji();
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
