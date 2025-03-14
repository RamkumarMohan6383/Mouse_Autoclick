#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Mark
    QPoint pos = QCursor::pos();
    autoClicker.setClickPosition(pos.x(), pos.y());
    ui->statusbar->showMessage("Marked position: " + QString::number(pos.x()) + "," + QString::number(pos.y()));
}


void MainWindow::on_pushButton_2_clicked()
{
   //Start
    autoClicker.startClicking();
    ui->statusbar->showMessage("Auto-click started.");
}


void MainWindow::on_pushButton_3_clicked()
{
    //Stop
    autoClicker.stopClicking();
    ui->statusbar->showMessage("Auto-click stopped.");
}

