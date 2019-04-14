#include "carexep.h"
#include "ui_carexep.h"
#include "dbase.h"
CarExep::CarExep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarExep)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

CarExep::~CarExep()
{
    delete ui;
}


