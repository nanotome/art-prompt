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
  ui->setupUi(this);

  setupUiInteraction();
  initializeForm();
}

EmojiForm::~EmojiForm() {
  delete ui;
}

void EmojiForm::initializeForm() {
    Emoji newEmoji;
  m_formModel = newEmoji.nextEmoji();

  QSvgWidget *svgWidget = new QSvgWidget(this);
  svgWidget->renderer()->load(m_formModel->svg().toUtf8());
  svgWidget->setFixedSize(512, 512);
  ui->emojiContainer->addWidget(svgWidget);
  ui->emojiContainer->setAlignment(Qt::AlignCenter);
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
