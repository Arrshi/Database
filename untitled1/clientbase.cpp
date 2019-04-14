#include "clientbase.h"
#include <QTableView>
#include <QtDebug>
#include <QApplication>
#include <QtSql/QSqlError>
Train::Train(QTableView* cars,  QObject *parent)
  : QObject(parent) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");

  m_db.setDatabaseName("../untitled/" BASE_NAME);

  if (false == m_db.open())
  throw "can't open/create DB";

  qDebug() << QDir::toNativeSeparators(QApplication::applicationDirPath());
    m_query = new QSqlQuery(m_db);
  m_carsModel = new QSqlTableModel(this, m_db);
  m_carsModel->setTable(BASE_CARS);
  m_carsModel->select();
  m_carsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
  m_carsModel->setHeaderData(0,Qt::Horizontal, tr("Маршрут"));
  m_carsModel->setHeaderData(1,Qt::Horizontal,tr("Тип Мест"));
  m_carsModel->setHeaderData(2,Qt::Horizontal,tr("Кол-во Мест"));
  m_carsModel->setHeaderData(3,Qt::Horizontal,tr("Стоимость билета"));
  cars->setModel(m_carsModel); 
  m_seatsModel = new QSqlTableModel(this, m_db);
  m_seatsModel->setTable(BASE_SEATS);
  m_seatsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
  m_seatsModel->setHeaderData(0,Qt::Horizontal,tr("Маршрут"));
  m_seatsModel->setHeaderData(1,Qt::Horizontal,tr("Тип места"));
  m_seatsModel->setHeaderData(2,Qt::Horizontal,tr("Место"));
  m_seatsModel->select();
}

Train::~Train() {
  delete m_query;
}


void Train::exec(QString str) {
  this->m_query->clear();
  if (false == this->m_query->exec(str))
    throw tr("DB Error: can't exec : ") + str;
 this->m_rec = this->m_query->record();
}

void Train::addSeat(QString name,QString type,QString num) {
        exec(tr("SELECT * FROM " BASE_CARS " WHERE " NAME_CARS " = ")+"'"+name+"'"+" AND " TYPE_CARS " = "+"'"+type+"'");
          this->m_query->first();
          if (this->m_query->value(this->m_rec.indexOf(COUNT_CARS)).toString().toInt() < num.toInt())
           throw 1;
              exec(tr("INSERT INTO " BASE_SEATS " (" NAME_SEAT "," TYPE_SEAT "," COUNT_SEAT ") VALUES('") + name+ "','"+type+"'," + num + ")");
          this->m_seatsModel->select();
}



