#include "dialog.h"
#include <QMessageBox>
#include <QtDebug>
#include <QKeyEvent>
#include <QShortcut>
#include <QtSql/QSqlError>
#include "ui_dialog.h"
#include "dbase.h"
#include "carexep.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
   this->setFixedSize(770,525);
   keyCtrl_Dell=new QShortcut(this);
   keyCtrl_Dell->setKey(Qt::CTRL+Qt::Key_Delete);
   keyDell=new QShortcut(this);
   keyDell->setKey(Qt::Key_Delete);
   ui->FAQ->setIcon(QIcon(":/new/images/question"));
      m_db = new Train(ui->tableView,ui->tableView_2, this);
      connect(ui->carAdd,SIGNAL(clicked()),SLOT(on_carAdd()));
      connect(ui->pushButton,SIGNAL(clicked()),SLOT(on_carDell()));
      connect(ui->FAQ,SIGNAL(clicked()),SLOT(chcekform()));
      connect(ui->ReSize,SIGNAL(clicked()),SLOT(Resize()));
      connect(keyDell,SIGNAL(activated()),SLOT(Slot_Del()));
      connect(keyCtrl_Dell,SIGNAL(activated()),SLOT(Seat_Dell()));
}

Dialog::~Dialog()
{
    delete keyDell;
    delete m_db;
    delete ui;
}

void Dialog::on_carAdd()
{
    if(ui->lineEdit->text().isEmpty()&&ui->checkBox->isChecked()==false&&ui->checkBox_2->isChecked()==false&&ui->spinBox->value()==0)
    {
        QMessageBox empty;
       empty.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        empty.setWindowTitle("Ошибка!");
        empty.setText("Требуется ввести данные запонения");
        empty.setStandardButtons(QMessageBox::Ok);
        empty.setIcon(QMessageBox::Critical);
        empty.exec();
        return;
    }
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox text_empty(QMessageBox::Critical,tr("Внимание!"),tr("Введите маршрут поезда"),QMessageBox::Ok);
        text_empty.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        text_empty.exec();
        return;
    }
    if(!ui->checkBox->isChecked()&&!ui->checkBox_2->isChecked())
    {
        QMessageBox type_empty(QMessageBox::Critical,tr("Внимание!"),tr("Виберите тип места!"),QMessageBox::Ok);
        type_empty.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        type_empty.exec();
        return;
    }
    /*if (this->ui->checkBox->isChecked()&&this->ui->checkBox_2->isChecked())
    {
        QMessageBox Type_error;
        Type_error.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        Type_error.setWindowTitle(tr("Внимание!"));
        Type_error.setText("Ошибка заполнения!");
        Type_error.setInformativeText("Выберите тип места!");
        Type_error.setStandardButtons(QMessageBox::Ok);
        Type_error.setIcon(QMessageBox::Critical);
        Type_error.setGeometry(745,443,190,125);
        Type_error.exec();

        return;
    }*/
    if (this->ui->spinBox->value()==0||this->ui->spinBox->text().isEmpty())
    {
        QMessageBox message;
        message.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        message.setWindowTitle("Внимание!");
        message.setText("Ошибка заполнения!");
        message.setInformativeText("Введите количество мест в вагоне!");
        message.setStandardButtons(QMessageBox::Ok);
        message.setIcon(QMessageBox::Critical);
        message.setGeometry(745,443,250,125);
        message.exec();
        return;
    }
    if(this->ui->spinBox_2->value()==0||this->ui->spinBox_2->text().isEmpty())
    {
        QMessageBox empty_cost;
        empty_cost.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        empty_cost.setWindowTitle("Внимание!");
        empty_cost.setText("Ошибка заполнения!");
        empty_cost.setInformativeText("Введите цену места!");
        empty_cost.setStandardButtons(QMessageBox::Ok);
        empty_cost.setIcon(QMessageBox::Critical);
        empty_cost.setGeometry(745,443,250,125);
        empty_cost.exec();
        return;
    }
    if (this->ui->checkBox->isChecked()&&this->ui->checkBox_2->isChecked())
    {
        QMessageBox checked_all(QMessageBox::Warning,tr("Внимание!"),tr("Вы хотите купить оба типа места?"),QMessageBox::Yes|QMessageBox::No);
        if(checked_all.exec()==QMessageBox::Yes)
        {
            TRY_BEGIN
                 this->m_db->addCar(this->ui->lineEdit->text(),this->ui->checkBox->text(),this->ui->spinBox->text(),this->ui->spinBox_2->text());
                CATCH_BEGIN...CATCH_ARG
                     QMessageBox addexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Возможно поезд уже присутствует!"),QMessageBox::Ok);
                      addexep.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
                     addexep.exec();
                       return;
            CATCH_END
              QMessageBox succses(QMessageBox::Information,tr("Успешено!"),"Маршрут "+this->ui->lineEdit->text()+" "+this->ui->checkBox->text()+" "+"добавлен!",QMessageBox::Ok);
              succses.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
              succses.exec();
             TRY_BEGIN
                     this->m_db->addCar(this->ui->lineEdit->text(),this->ui->checkBox_2->text(),this->ui->spinBox->text(),this->ui->spinBox_2->text());
                CATCH_BEGIN...CATCH_ARG
                       QMessageBox addexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Возможно поезд уже присутствует!"),QMessageBox::Ok);
                       addexep.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
                        addexep.exec();
                        return;
              CATCH_END
              QMessageBox succses_2(QMessageBox::Information,tr("Успешено!"),"Маршрут "+this->ui->lineEdit->text()+" "+this->ui->checkBox_2->text()+" "+ "добавлен!",QMessageBox::Ok);
              succses_2.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
              succses_2.exec();
        }
    this->Resize();
        return;
    }
    if(this->ui->checkBox->isChecked())
    {
        TRY_BEGIN
             this->m_db->addCar(this->ui->lineEdit->text(),this->ui->checkBox->text(),this->ui->spinBox->text(),this->ui->spinBox_2->text());
            CATCH_BEGIN...CATCH_ARG
                 QMessageBox addexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Возможно поезд уже присутствует!"),QMessageBox::Ok);
                  addexep.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
                 addexep.exec();
                 return;
            CATCH_END
    }
    if(this->ui->checkBox_2->isChecked())
    {
        TRY_BEGIN
            this->m_db->addCar(this->ui->lineEdit->text(),this->ui->checkBox_2->text(),this->ui->spinBox->text(),this->ui->spinBox_2->text());
            CATCH_BEGIN...CATCH_ARG
                QMessageBox addexep(QMessageBox::Critical,tr("Внимание!"),tr("Введены некорректные данные.Возможно поезд уже присутствует!"),QMessageBox::Ok);
                 addexep.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
                addexep.exec();
                return;
            CATCH_END
    }
    QMessageBox succses(QMessageBox::Information,tr("Успешено!"),tr("Маршрут добавлен!"),QMessageBox::Ok);
    succses.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
    succses.exec();
    this->Resize();
}

void Dialog::on_carDell()
{
    if(this->ui->lineEdit->text().isEmpty()&&this->ui->checkBox->isChecked()==false&&this->ui->checkBox_2->isChecked()==false&&this->ui->spinBox->value()==0)
    {
        QMessageBox empty;
        empty.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        empty.setWindowTitle("Ошибка!");
        empty.setText("Требуется ввести данные удаления или же удалите через выделение!");
        empty.setStandardButtons(QMessageBox::Ok);
        empty.setIcon(QMessageBox::Critical);
        empty.exec();
        return;
    }
    if (this->ui->checkBox->isChecked()&&this->ui->checkBox_2->isChecked())
    {
        QMessageBox Dell_message;
        Dell_message.setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
        Dell_message.setWindowTitle("Внимание!");
        Dell_message.setText("Ошибка удаления");
        Dell_message.setInformativeText("Выберите один тип места");
        Dell_message.setIcon(QMessageBox::Critical);
        Dell_message.setStandardButtons(QMessageBox::Ok);
        Dell_message.setGeometry(745,443,300,125);
        Dell_message.width();
        Dell_message.exec();
        return;
    }
    QMessageBox * dell_question=new QMessageBox(QMessageBox::Question,"Вы уверены?","Действительно удалить?",QMessageBox::Yes|QMessageBox::No);
    dell_question->setWindowIcon(QIcon(":/new/images/images/icon.jpg"));
    if(dell_question->exec()==QMessageBox::Yes)
    {

        if(this->ui->checkBox->isChecked())

            this->m_db->remCar(ui->lineEdit->text(),ui->checkBox->text());

        if (this->ui->checkBox_2->isChecked())

           this->m_db->remCar(ui->lineEdit->text(),ui->checkBox_2->text());

        this->Resize();
    }
    else
    {
        delete dell_question;
        return;
    }

}
void Dialog::chcekform(){
    CarExep *add=new CarExep(this);
    add->show();
    if(!add->isWindow())
    {
        delete add;
    }
}

void Dialog::Resize(){
    this->ui->tableView->resizeColumnsToContents();
}

void Dialog::Slot_Del(){
   QMessageBox* quest=new QMessageBox(QMessageBox::Question,"Вы уверены?","Дейсвительно удалить?",QMessageBox::Yes|QMessageBox::No);

   if(quest->exec()==QMessageBox::Yes)
{
    QItemSelectionModel *selectModel;
    QModelIndexList indexes;
    QModelIndex index;
    selectModel= this->ui->tableView->selectionModel();
    indexes=selectModel->selection().indexes();
    foreach(index,indexes)
    {

        if (this->m_db->m_carsModel->rowCount()==0)
        {
            //qDebug()<<m_db->m_carsModel->lastError().text();
            break;
        }
        else
        {

            //QModelIndex current = ui->tableView->currentIndex();
            QString id = index.sibling(index.row(), 0).data ().toString();
            QString type=index.sibling(index.row(),1).data().toString();
            this->m_db->remCar(id,type);
           // m_db->m_carsModel->removeRows(index.row(),0);
        }

    }
   this->m_db->m_carsModel->select();
}
delete quest;
}

void Dialog::Seat_Dell()
{
     QMessageBox* quest=new QMessageBox(QMessageBox::Question,"Вы уверены?","Дейсвительно удалить?",QMessageBox::Yes|QMessageBox::No);

   if(quest->exec()==QMessageBox::Yes)
   {
       QItemSelectionModel *selected;
       QModelIndexList indexes;
       QModelIndex index;
       selected=this->ui->tableView_2->selectionModel();
       indexes=selected->selection().indexes();
       foreach(index,indexes)
        {
           if(this->m_db->m_seatsModel->rowCount()==0)
           {
               break;
           }
           else
           {
               QString id = index.sibling(index.row(), 0).data ().toString();
               QString type=index.sibling(index.row(),1).data().toString();
               QString num=index.sibling(index.row(),2).data().toString();
               this->m_db->remSeat(id,type,num);
           }
        }
    }
   delete quest;
}





