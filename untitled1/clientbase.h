#ifndef CLIENTBASE_H
#define CLIENTBASE_H


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
#define TRY_BEGIN try {
#define CATCH_BEGIN } catch(
#define CATCH_ARG ) {
#define CATCH_END }

class QTableView;
class QSqlTableModel;
class Train : public QObject {
  Q_OBJECT
public:
  Train(QTableView* cars, QObject *parent =nullptr);
  virtual ~Train();
  void addSeat(QString name,QString type, QString snCar);
            //!< добавляет место
private:
  void exec(QString);
        //!< пытается выполнить запрос
  QString qs(QString);
        //!< выделяет строку одинарными кавычками

  QSqlDatabase m_db;
        //!< база данных
  QSqlQuery *m_query;
        //!< запрос к базе
  QSqlRecord m_rec;
        //!< строка таблицы (ответ на запрос)
  QSqlTableModel *m_carsModel;
        //!< модель таблицы автомобилей
  QSqlTableModel *m_seatsModel;
         //!< модель таблицы посадочных мест

};

#endif // CLIENTBASE_H
