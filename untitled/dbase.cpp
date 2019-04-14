#include "dbase.h"
#include <QTableView>
#include <QtDebug>
#include <QtSql/QSqlError>

/////////////////////////////////CAR
void Train::addCar(QString carname,QString type, QString nSeats,QString cost) {
      exec(tr("INSERT INTO " BASE_CARS " (" NAME_CARS "," TYPE_CARS "," COUNT_CARS "," COST_CAR ") VALUES ('")
      + carname+"','"+type+"',"+nSeats +","+cost+ ")");
    this->m_carsModel->select();

}

void Train::remCar(QString name,QString type) {

 exec(tr("DELETE FROM " BASE_SEATS " WHERE " NAME_SEAT "  = ") +"'"+name+"'"+" AND " TYPE_SEAT " = '"+type+"'");
 exec(tr("DELETE FROM " BASE_CARS " WHERE " NAME_CARS " = ") +"'"+name+"'"+" AND " TYPE_CARS " = '"+type+"'");
 this->m_carsModel->select();
 this->m_seatsModel->select();
}

////////////////////////////////////////////
Train::Train(QTableView* cars, QTableView* seats, QObject *parent)
  : QObject(parent) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(QDir::currentPath()+"/"+BASE_NAME);
QString PathToDb = QCoreApplication::applicationDirPath() + BASE_NAME;
qDebug()<<PathToDb;
  if (false == m_db.open())
    throw "can't open/create DB";

  m_query = new QSqlQuery(m_db);
  if (false == m_db.tables().contains(BASE_SEATS))
    exec("CREATE TABLE " BASE_SEATS " ("  // таблица посадочных мест
     NAME_SEAT" VARCHAR(250) NOT NULL , "// маршрут поезда
      TYPE_SEAT" VARCHAR(250) NOT NULL,"
      COUNT_SEAT" INTEGER, "// номер посадочного места
      "PRIMARY KEY (" NAME_SEAT "," TYPE_SEAT "," COUNT_SEAT ")"
      ");"
    );
  if (false == m_db.tables().contains(BASE_CARS))
    exec("CREATE TABLE " BASE_CARS " ("  // таблица вагонов
        NAME_CARS" VARCHAR(250) NOT NULL , "// маршрут поезда
         TYPE_CARS" VARCHAR(250) NOT NULL , "
       COUNT_CARS" INTEGER, " // количество посадочных мест
         COST_CAR" INTEGER, "
       "PRIMARY KEY (" NAME_CARS "," TYPE_CARS ")"
      ");"
    );

  m_carsModel = new QSqlTableModel(this, m_db);
  m_carsModel->setTable(BASE_CARS);

  m_carsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
  m_carsModel->setHeaderData(0,Qt::Horizontal, tr("Маршрут"));
  m_carsModel->setHeaderData(1,Qt::Horizontal,tr("Тип Мест"));
  m_carsModel->setHeaderData(2,Qt::Horizontal,tr("Кол-во Мест"));
  m_carsModel->setHeaderData(3,Qt::Horizontal,tr("Стоимость билета"));
  m_carsModel->select();
  cars->setModel(m_carsModel);
  cars->resizeColumnsToContents();

  m_seatsModel = new QSqlTableModel(this, m_db);
  m_seatsModel->setTable(BASE_SEATS);
  m_seatsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
  m_seatsModel->setHeaderData(0,Qt::Horizontal,tr("Маршрут"));
  m_seatsModel->setHeaderData(1,Qt::Horizontal,tr("Тип места"));
  m_seatsModel->setHeaderData(2,Qt::Horizontal,tr("Место"));
  m_seatsModel->select();
  seats->setModel(m_seatsModel);

}

Train::~Train() {
  delete m_query;
}


void Train::exec(QString str) {
  this->m_query->clear();
  if (false == this->m_query->exec(str))
    throw tr("DBFacade Error: can't exec : ") + str;
  this->m_rec = m_query->record();

}

void Train::remSeat(QString name,QString type,QString num) {
        exec(tr("DELETE FROM " BASE_SEATS " WHERE " NAME_SEAT " = '") + name +"'"+" AND " TYPE_SEAT " = '"+type+"' AND " COUNT_SEAT " =" + num);
        this->m_seatsModel->select();
}



