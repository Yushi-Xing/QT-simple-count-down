#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QTimer"
#include <QMainWindow>
#include "QDebug"
#include "QDateTime"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer0=new QTimer;
    QTimer *timer1=new QTimer;
    int iscounting=0;
    int sec_count=-1;
    QDateTime countdown= QDateTime::fromString( "10:00", "mm:ss");
    void timeUpdate();
public slots:
    void Timecountdown();
    void chTime();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
