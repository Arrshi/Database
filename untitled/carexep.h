#ifndef CAREXEP_H
#define CAREXEP_H

#include <QDialog>
#include "dbase.h"
namespace Ui {
class CarExep;
}

class CarExep : public QDialog
{
    Q_OBJECT

public:
    explicit CarExep(QWidget *parent = nullptr);
    ~CarExep();
  public slots:
private:
    Ui::CarExep *ui;
};

#endif // CAREXEP_H
