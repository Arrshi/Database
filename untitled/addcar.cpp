#include "addcar.h"
#include "ui_addcar.h"
#include "dbase.h"
AddCar::AddCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCar)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
connect(ui->pushButton,SIGNAL(clicked()),SLOT(ADD_CAR()));
}

AddCar::~AddCar()
{
    delete ui;
}

void AddCar::ADD_CAR(){
    Train *adder=new Train();
    adder->addCar(ui->lineEdit->text(),ui->comboBox->currentText(),ui->lineEdit_2->text());
    delete adder;

}
