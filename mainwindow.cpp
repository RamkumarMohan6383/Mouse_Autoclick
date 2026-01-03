#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCursor>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint,true);
    setWindowTitle("Mouse Auto Click");
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
              ui->comboBox->addItem(portInfo.portName());  // Add each available port
          }
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
    if (autoClicker.getClickPosition().isNull()) {
        ui->statusbar->showMessage("Mark position first!");
        return;
    }
    else
    {
    if (!serial.isOpen()) {
        ui->statusbar->showMessage("Serial port not connected!");
        return;
    }

    autoClickArmed = true;   // ✅ ARM
    ui->pushButton->setDisabled(true);

    ui->statusbar->showMessage("Auto-click armed. Waiting for sensor...");
    }
}



void MainWindow::on_pushButton_3_clicked()
{
    //Stop
    autoClickArmed = false;   // ❌ DISARM
    ui->pushButton->setDisabled(false);
    ui->statusbar->showMessage("Auto-click stopped.");
}


void MainWindow::on_pushButton_4_clicked()
{
    setupSerialPort();
}

void MainWindow::setupSerialPort()
{
    if (serial.isOpen()) {
        serial.close();
    }

    serial.setPortName(ui->comboBox->currentText());
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!serial.open(QIODevice::ReadOnly)) {
        ui->statusbar->showMessage("Serial open failed!");
        ui->pushButton->setEnabled(false);
        qDebug() << serial.errorString();
        return;
    }

    ui->statusbar->showMessage("Serial connected");
    ui->pushButton->setEnabled(true);

    // 🔐 Prevent duplicate connections
    disconnect(&serial, nullptr, this, nullptr);

    connect(&serial, &QSerialPort::readyRead, this, [this]()
    {
        static QByteArray buffer;
        buffer.append(serial.readAll());

        while (buffer.contains('\n')) {
            int index = buffer.indexOf('\n');
            QByteArray line = buffer.left(index);
            buffer.remove(0, index + 1);

            line = line.trimmed().toUpper();

            qDebug() << "Received:" << line;

            if (line == "CLICK" && autoClickArmed) {
                autoClicker.performClick();
                ui->statusbar->showMessage("Sensor trigger → Mouse click");
            }
        }
    });
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->comboBox->clear();
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
              ui->comboBox->addItem(portInfo.portName());  // Add each available port
          }
}

