//
// Created by Ifeanyi Oraelosi on 22.12.21.
//

#ifndef RPGDB_QT_ACTORFORM_H
#define RPGDB_QT_ACTORFORM_H

#include <QWidget>
#include "../Models/ActorType.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ActorForm; }
QT_END_NAMESPACE

class ActorForm : public QWidget {
Q_OBJECT

public:
  explicit ActorForm(QWidget *parent = nullptr);
  ~ActorForm() override;

  bool saveForm();

private:
  Ui::ActorForm *ui;
  void setupUiInteraction();
  void initializeForm();

  ActorType *m_formModel;

private slots:
  void isFormDirty();

};

#endif //RPGDB_QT_ACTORFORM_H
