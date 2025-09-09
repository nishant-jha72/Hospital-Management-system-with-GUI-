#include "mainwindow.h"
#include "adminwindow.h"
#include "doctorwindow.h"
#include "patientwindow.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(400, 350);

    QWidget *central = new QWidget(this);
    central->setStyleSheet("background-color: #ecf0f1;");

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setSpacing(15);
    layout->setContentsMargins(30,30,30,30);

    QLabel *title = new QLabel("Hospital Management System", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #2c3e50;");
    layout->addWidget(title);

    QPushButton *adminBtn = new QPushButton("Admin", this);
    QPushButton *doctorBtn = new QPushButton("Doctor", this);
    QPushButton *patientBtn = new QPushButton("Patient", this);

    QString buttonStyle =
        "QPushButton { background-color: #3498db; color: white; font-size: 16px; padding: 10px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #2980b9; }";

    adminBtn->setStyleSheet(buttonStyle);
    doctorBtn->setStyleSheet(buttonStyle);
    patientBtn->setStyleSheet(buttonStyle);

    layout->addWidget(adminBtn);
    layout->addWidget(doctorBtn);
    layout->addWidget(patientBtn);

    setCentralWidget(central);

    connect(adminBtn, &QPushButton::clicked, this, &MainWindow::openAdmin);
    connect(doctorBtn, &QPushButton::clicked, this, &MainWindow::openDoctor);
    connect(patientBtn, &QPushButton::clicked, this, &MainWindow::openPatient);
}

void MainWindow::openAdmin() {
    AdminWindow *aw = new AdminWindow(this);
    aw->show();
}

void MainWindow::openDoctor() {
    DoctorWindow *dw = new DoctorWindow(this);
    dw->show();
}

void MainWindow::openPatient() {
    PatientWindow *pw = new PatientWindow(this);
    pw->show();
}
