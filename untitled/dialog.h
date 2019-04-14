#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
class Train;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();   
public slots:
void Slot_Del();
void on_carDell();
void chcekform();
void on_carAdd();
void Resize();
void Seat_Dell();
private:
    Train *m_db;
    Ui::Dialog *ui;
    QShortcut* keyDell,* keyCtrl_Dell;
};

#endif // DIALOG_H
