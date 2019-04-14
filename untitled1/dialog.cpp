#include "dialog.h"
#include "ui_dialog.h"
#include "clientbase.h"
#include "selltickets.h"
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QTimer>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    time_counter=new QTimer();
    time_counter->start(1000);
    QPixmap icon(":/new/client/images/Add_Action.png");
    QIcon Add_Icon(icon);
    ui->pushButton->setIcon(Add_Icon);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_db = new Train(ui->cars,this);
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(addSeat()));
    connect(time_counter,SIGNAL(timeout()),SLOT(timer()));
    connect(ui->commandLinkButton,SIGNAL(clicked()),SLOT(show_seats()));


}

Dialog::~Dialog()
{
    delete time_counter;
    delete ui;
    delete m_db;
}

void Dialog::addSeat(){
   if(this->ui->travel->text().isEmpty()&&!this->ui->checkBox->isChecked()&&!this->ui->checkBox_2->isChecked()&&this->ui->spinBox->value()==0)
    {
        QMessageBox empty_all(QMessageBox::Critical,tr("Внимание!"),tr("Заполните поля для ввода!"),QMessageBox::Ok);
        empty_all.exec();
        return;
    }
   if(this->ui->travel->text().isEmpty())
   {
       QMessageBox text_empty(QMessageBox::Critical,tr("Внимание!"),tr("Введите желаемый маршрут!"),QMessageBox::Ok);
       text_empty.exec();
       return;
   }
   if(this->ui->spinBox->value()==0)
   {
       QMessageBox null(QMessageBox::Critical,tr("Внимание!"),tr("Введнено нулевое место!"),QMessageBox::Ok);
       null.exec();
       return;
   }
   if(this->ui->checkBox->isChecked()&&this->ui->checkBox_2->isChecked())
   {
       QMessageBox checked_all(QMessageBox::Warning,tr("Внимание!"),tr("Вы хотите купить оба типа места?"),QMessageBox::Yes|QMessageBox::No);
       if(checked_all.exec()==QMessageBox::Yes)
       {

           TRY_BEGIN
            this->m_db->addSeat(this->ui->travel->text(),this->ui->checkBox->text(),this->ui->spinBox->text());
           CATCH_BEGIN int CATCH_ARG
                   QMessageBox selectexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Проверьте правильность заполнения!"),QMessageBox::Ok);
                  selectexep.exec();
                  return;
           CATCH_BEGIN...CATCH_ARG
                   QMessageBox addexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Возможно место уже занято!"),QMessageBox::Ok);
                   addexep.exec();
                   return;
           CATCH_END
                QMessageBox succsesful(QMessageBox::Information,tr("Успешно"),"Место "+this->ui->travel->text()+" "+this->ui->checkBox->text()+" № "+this->ui->spinBox->text()+" куплено!",QMessageBox::Ok);
                succsesful.exec();
           TRY_BEGIN
                  this->m_db->addSeat(this->ui->travel->text(),this->ui->checkBox_2->text(),this->ui->spinBox->text());
           CATCH_BEGIN int CATCH_ARG
                    QMessageBox selectexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Проверьте правильность заполнения!"),QMessageBox::Ok);
                    selectexep.exec();
                    return;
           CATCH_BEGIN...CATCH_ARG
                     QMessageBox addexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Возможно место уже занято!"),QMessageBox::Ok);
                     addexep.exec();
                     return;
           CATCH_END
                   QMessageBox succsesful_2(QMessageBox::Information,tr("Успешно"),"Место "+this->ui->travel->text()+" "+this->ui->checkBox_2->text()+" № "+this->ui->spinBox->text()+" куплено!",QMessageBox::Ok);
                    succsesful_2.exec();

       }
       else
       {
           QMessageBox checked_all(QMessageBox::Warning,tr("Внимание!"),tr("Вам следуте выбрать один тип места!"),QMessageBox::Ok);
           checked_all.exec();
       }
       return;
   }
   TRY_BEGIN
    this->m_db->addSeat(this->ui->travel->text(),this->ui->checkBox->text(),this->ui->spinBox->text());
   CATCH_BEGIN int CATCH_ARG
           QMessageBox selectexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Проверьте правильность заполнения!"),QMessageBox::Ok);
          selectexep.exec();
          return;
   CATCH_BEGIN...CATCH_ARG
           QMessageBox addexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Возможно место уже занято!"),QMessageBox::Ok);
           addexep.exec();
           return;
   CATCH_END
           QMessageBox succsesful(QMessageBox::Information,tr("Успешно"),tr("Место куплено!"),QMessageBox::Ok);
            succsesful.exec();
}

void Dialog::timer()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str=time.toString("hh:mm:ss");
    this->ui->lcdNumber->setDigitCount(8);
    this->ui->lcdNumber->display(str);
}

void Dialog::show_seats()
{
    delete this->m_db;
    QSqlDatabase::removeDatabase("QSQLITE");
    SellTickets *sell=new SellTickets(this);
    sell->show();
    QSqlDatabase::removeDatabase("QSQLITE");
    this->m_db = new Train(ui->cars,this);
}
