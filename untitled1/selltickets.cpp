#include "selltickets.h"
#include "ui_selltickets.h"
SellTickets::SellTickets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellTickets)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    db_seats=new Tickets(ui->tableView,this);
}

SellTickets::~SellTickets()
{
    delete db_seats;
    delete ui;
}

Tickets::Tickets(QTableView *seats,QObject *parent):QObject(parent)
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName("../untitled/" BASE_NAME);
    if (false == m_db.open())
     throw "can't open/create DB";

    m_seatsModel = new QSqlTableModel(this, m_db);
    m_seatsModel->setTable(BASE_SEATS);
    m_seatsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_seatsModel->setHeaderData(0,Qt::Horizontal,tr("Маршрут"));
    m_seatsModel->setHeaderData(1,Qt::Horizontal,tr("Тип места"));
    m_seatsModel->setHeaderData(2,Qt::Horizontal,tr("Место"));
    m_seatsModel->select();
    seats->setModel(m_seatsModel);
}

Tickets::~Tickets()
{
    QSqlDatabase::removeDatabase("QSQLITE");
}
