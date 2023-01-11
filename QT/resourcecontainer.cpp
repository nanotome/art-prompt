//
// Created by Ifeanyi Oraelosi on 20.12.21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ResourceContainer.h" resolved

#include "resourcecontainer.h"
#include "ui_resourcecontainer.h"

#include "actorform.h"

ResourceContainer::ResourceContainer(QWidget *parent) :
	QWidget(parent), ui(new Ui::ResourceContainer) {
  ui->setupUi(this);

  _actorForm = new ActorForm;

  setupUiInteraction();
  setupTabs();
}

ResourceContainer::~ResourceContainer() {
  delete ui;
}

void ResourceContainer::setupUiInteraction() {

}

void ResourceContainer::setupTabs() {
  	QVBoxLayout *vBoxLay = new QVBoxLayout;
    vBoxLay->addWidget(_actorForm);
	ui->actorTab->setLayout(vBoxLay);
}
