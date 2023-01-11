//
// Created by Ifeanyi Oraelosi on 22.12.21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ActorForm.h" resolved
#include <QDebug>
#include "actorform.h"
#include "ui_actorform.h"

#include "../Models/ActorType.h"

ActorForm::ActorForm(QWidget *parent) :
	QWidget(parent), ui(new Ui::ActorForm) {
  ui->setupUi(this);



  setupUiInteraction();
}

ActorForm::~ActorForm() {
  delete ui;
}

void ActorForm::initializeForm() {
  // TODO: Initialize model from database if available
  m_formModel = new ActorType;
}

void ActorForm::setupUiInteraction() {
  ui->applyButton->setDisabled(true);

  connect(ui->applyButton, &QPushButton::clicked, this, [&]() {
      ActorForm::saveForm();
  });

  connect(ui->actorName, &QLineEdit::textEdited, this, [&]() {
      ActorForm::isFormDirty();
  });

  connect(ui->actorDescription, &QTextEdit::textChanged, this, [&]() {
      ActorForm::isFormDirty();
  });
}

bool ActorForm::saveForm(){
  // get actortype data from the form inputs and save to model
  m_formModel->setName(ui->actorName->text());
  m_formModel->setDescription(ui->actorDescription->toPlainText());

  // TODO: create common resource class that ActorType inherits from
  return m_formModel->save();
}

void ActorForm::isFormDirty() {
  if (!ui->applyButton->isEnabled()) {
    ui->applyButton->setDisabled(false);
  }
}
