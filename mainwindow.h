#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "autoclick.h"
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void setupSerialPort();

    void on_pushButton_5_clicked();

private:
    QSerialPort serial;
    Ui::MainWindow *ui;
    AutoClick autoClicker;
     bool autoClickArmed = false;   // 👈 controls execution

};

#endif // MAINWINDOW_H
