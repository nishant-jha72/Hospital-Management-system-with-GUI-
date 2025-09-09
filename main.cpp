#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include "dbmanager.h"
#include "adminwindow.h"
#include "doctorwindow.h"
#include "patientwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1️⃣ Connect to Database
    QSqlDatabase db = DBManager::connectDB();
    if(!db.isOpen()) {
        return -1; // Exit if DB connection fails
    }

    // 2️⃣ Choose Role
    QStringList roles;
    roles << "Admin" << "Doctor" << "Patient";
    bool ok;
    QString role = QInputDialog::getItem(nullptr, "Hospital Management", "Select Role:", roles, 0, false, &ok);
    if(!ok) return 0;

    // 3️⃣ Launch the corresponding window
    if(role == "Admin") {
        AdminWindow w;
        w.show();
        return a.exec();
    }
    else if(role == "Doctor") {
        DoctorWindow w;
        w.show();
        return a.exec();
    }
    else if(role == "Patient") {
        PatientWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
