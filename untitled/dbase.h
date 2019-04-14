#ifndef DBASE_H
#define DBASE_H

# include <QtSql/QtSql>
# include <QObject>
#define BASE_NAME "projectDB"
#define BASE_SEATS "seats"
#define BASE_CARS "cars"
#define NAME_CARS "carname"
#define TYPE_CARS "typeofseats"
#define COUNT_CARS "nseats"
#define NAME_SEAT "carnm"
#define TYPE_SEAT "typeofseat"
#define COUNT_SEAT "nseat"
#define COST_CAR "cost"
#define TRY_BEGIN try {
#define CATCH_BEGIN } catch(
#define CATCH_ARG ) {
#define CATCH_END }

class QTableView;
class QSqlTableModel;
class Train : public QObject {
  Q_OBJECT
public:
  Train();
  Train(QTableView* cars, QTableView* seats, QObject *parent =nullptr);
  virtual ~Train();
void addCar(QString carname,QString type, QString nSeats,QString cost);
          //!< добавляет вагон
void remSeat(QString name,QString type,QString num);
void remCar(QString name,QString type);
          //!< удаляет вагон
private:
  void exec(QString);
        //!< пытается выполнить запрос
  QSqlDatabase m_db;
        //!< база данных
  QSqlQuery *m_query;
        //!< запрос к базе
  QSqlRecord m_rec;
        //!< строка таблицы (ответ на запрос)
 public:
  QSqlTableModel *m_carsModel;
        //!< модель таблицы автомобилей
  QSqlTableModel *m_seatsModel;
        //!< модель таблицы посадочных мест
};

#endif // DBASE_H
