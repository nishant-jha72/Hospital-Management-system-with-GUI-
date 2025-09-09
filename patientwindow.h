#ifndef PATIENTWINDOW_H
#define PATIENTWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class PatientWindow : public QMainWindow {
    Q_OBJECT
public:
    PatientWindow(QWidget *parent = nullptr);

private slots:
    void registerPatient();
    void bookAppointment();
    void payBill();
    void viewDetails();
};

#endif // PATIENTWINDOW_H
