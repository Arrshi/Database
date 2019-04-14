#ifndef SELLTICKETS_H
#define SELLTICKETS_H

#include <QDialog>
#include <QObject>
#include <QtWidgets>
# include <QtSql/QtSql>
#define BASE_NAME "projectDB"
#define BASE_SEATS "seats"
namespace Ui {
class SellTickets;
}


class QSqlTableModel;

class Tickets:public QObject {
  Q_OBJECT
public:

    Tickets(QTableView* cars, QObject *parent =nullptr);
    ~Tickets();
protected:
  QSqlDatabase m_db;
        //!< база данных
  QSqlTableModel *m_seatsModel;
         //!< модель таблицы посадочных мест


};

class SellTickets : public QDialog
{
    Q_OBJECT
friend Tickets;
public:
    explicit SellTickets(QWidget *parent = nullptr);
    ~SellTickets();

private:
    Tickets *db_seats;
    Ui::SellTickets *ui;
};

#endif // SELLTICKETS_H
