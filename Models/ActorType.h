//
// Created by Ifeanyi Oraelosi on 26.01.22.
//

#ifndef RPGDB_MODELS_ACTORTYPE_H
#define RPGDB_MODELS_ACTORTYPE_H

#include <QString>
#include <QSqlQuery>

class ActorType {
private:
  int m_id;
  QString m_name;
  QString m_description;
public:
  ActorType();
  [[nodiscard]] int id() const;
  void setId(int id);
  [[nodiscard]] QString name() const;
  void setName(QString name);
  [[nodiscard]] QString description() const;
  void setDescription(QString description);

  bool save();

  static ActorType actorTypeFromQuery(const QSqlQuery& query);
  ActorType fillFromQuery(const QSqlQuery& query);
  static ActorType fetchById(int id);
};

#endif //RPGDB_MODELS_ACTORTYPE_H
