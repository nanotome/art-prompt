//
// Created by Ifeanyi Oraelosi on 20.12.21.
//

#ifndef RPGDB_QT_RESOURCECONTAINER_H
#define RPGDB_QT_RESOURCECONTAINER_H

#include <QWidget>

#include "actorform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ResourceContainer; }
QT_END_NAMESPACE

class ResourceContainer : public QWidget {
Q_OBJECT

public:
  explicit ResourceContainer(QWidget *parent = nullptr);
  ~ResourceContainer() override;

private:
  Ui::ResourceContainer *ui;
  void setupUiInteraction();
  void setupTabs();

  ActorForm *_actorForm;
};

#endif //RPGDB_QT_RESOURCECONTAINER_H
