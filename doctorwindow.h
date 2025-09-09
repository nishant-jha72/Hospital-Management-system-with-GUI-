#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class DoctorWindow : public QMainWindow {
    Q_OBJECT
public:
    DoctorWindow(QWidget *parent = nullptr);

private slots:
    void viewAppointments();
    void viewPatientDetails();
    void viewPatientDisease();
    void submitFeedback();
};

#endif // DOCTORWINDOW_H
