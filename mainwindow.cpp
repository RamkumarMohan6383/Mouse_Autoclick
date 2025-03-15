#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint,true);
    setWindowTitle("Mouse Auto Click");
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Mark

    QPoint pos = QCursor::pos();
    autoClicker.setClickPosition(pos.x(), pos.y());
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->statusbar->showMessage("Marked position: " + QString::number(pos.x()) + "," + QString::number(pos.y()));
}

void MainWindow::on_pushButton_2_clicked()
{
   //Start
    ui->pushButton->setDisabled(true);
    autoClicker.startClicking();
    ui->statusbar->showMessage("Auto-click started.");
}


void MainWindow::on_pushButton_3_clicked()
{
    //Stop
    ui->pushButton->setDisabled(false);
    autoClicker.stopClicking();
    ui->statusbar->showMessage("Auto-click stopped.");
}

