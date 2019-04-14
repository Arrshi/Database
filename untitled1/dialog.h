#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtWidgets>

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
void timer();
void addSeat();
void show_seats();
private:
QTabWidget * tab;
QTimer *time_counter;
    Train *m_db;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
