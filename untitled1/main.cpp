#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        QSystemSemaphore semaphore("Evileg Semaphore", 1);  // создаём семафор
               semaphore.acquire(); // Поднимаем семафор, запрещая другим экземплярам работать с разделяемой памятью

           #ifndef Q_OS_WIN32
               // в linux/unix разделяемая память не освобождается при аварийном завершении приложения,
               // поэтому необходимо избавиться от данного мусора
               QSharedMemory nix_fix_shared_memory("Evileg Shared Memory");
               if(nix_fix_shared_memory.attach()){
                   nix_fix_shared_memory.detach();
               }
           #endif

               QSharedMemory sharedMemory("Evileg Shared Memory");  // Создаём экземпляр разделяемой памяти
               bool is_running;            // переменную для проверки ууже запущенного приложения
               if (sharedMemory.attach()){ // пытаемся присоединить экземпляр разделяемой памяти
                                           // к уже существующему сегменту
                   is_running = true;      // Если успешно, то определяем, что уже есть запущенный экземпляр
               }else{
                   sharedMemory.create(1); // В противном случае выделяем 1 байт памяти
                   is_running = false;     // И определяем, что других экземпляров не запущено
               }
               semaphore.release();        // Опускаем семафор

               // Если уже запущен один экземпляр приложения, то сообщаем об этом пользователю
               // и завершаем работу текущего экземпляра приложения
               if(is_running){
                   QMessageBox msgBox;
                   msgBox.setIcon(QMessageBox::Warning);
                   msgBox.setText(QObject::tr("Приложение уже запущено.\n"
                                   "Вы можете запустить только один экземпляр приложения."));
                   msgBox.exec();
                   return 1;
               }

        Dialog w;
        w.show();

        return a.exec();
    } catch (QString err) {
        qDebug()<<err;
    }

}
