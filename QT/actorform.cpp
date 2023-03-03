//
// Created by Ifeanyi Oraelosi on 22.12.21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_actorform.h" resolved
#include <QDebug>
#include "actorform.h"
#include "ui_actorform.h"

#include "../Models/ActorType.h"

EmojiForm::EmojiForm(QWidget *parent) :
    QWidget(parent), ui(new Ui::EmojiForm) {
  ui->setupUi(this);

  setupUiInteraction();
}

EmojiForm::~EmojiForm() {
  delete ui;
}

void EmojiForm::initializeForm() {
  // TODO: Initialize model from database if available
  m_formModel = new ActorType;
}

void EmojiForm::setupUiInteraction() {
  connect(ui->emojiDoneButton, &QPushButton::clicked, this, [&]() {
      EmojiForm::saveForm();
  });
}

bool EmojiForm::saveForm(){

}

void EmojiForm::isFormDirty() {

}
