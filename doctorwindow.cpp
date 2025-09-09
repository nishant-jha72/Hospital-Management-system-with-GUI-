#include "doctorwindow.h"
#include "dbmanager.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DoctorWindow::DoctorWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(450, 350);

    QWidget *central = new QWidget(this);
    central->setStyleSheet("background-color: #2ecc71;"); // green
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setSpacing(15);
    layout->setContentsMargins(20,20,20,20);

    QPushButton *btn1 = new QPushButton("View Appointments", this);
    QPushButton *btn2 = new QPushButton("View Patient Details", this);
    QPushButton *btn3 = new QPushButton("View Patient Disease", this);
    QPushButton *btn4 = new QPushButton("Submit Feedback", this);

    QString buttonStyle =
        "QPushButton { background-color: #27ae60; color: white; font-size: 14px; padding: 8px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #1e8449; }";

    btn1->setStyleSheet(buttonStyle);
    btn2->setStyleSheet(buttonStyle);
    btn3->setStyleSheet(buttonStyle);
    btn4->setStyleSheet(buttonStyle);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);

    setCentralWidget(central);

    connect(btn1, &QPushButton::clicked, this, &DoctorWindow::viewAppointments);
    connect(btn2, &QPushButton::clicked, this, &DoctorWindow::viewPatientDetails);
    connect(btn3, &QPushButton::clicked, this, &DoctorWindow::viewPatientDisease);
    connect(btn4, &QPushButton::clicked, this, &DoctorWindow::submitFeedback);
}

// View all pending appointments for this doctor
void DoctorWindow::viewAppointments() {
    bool ok;
    int doc_id = QInputDialog::getInt(this,"View Appointments","Enter Your Doctor ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QSqlQuery query;
    query.prepare("SELECT app_id, p_id, app_date, status FROM appoint_table WHERE doc_id=:docid");
    query.bindValue(":docid", doc_id);

    if(!query.exec()) {
        QMessageBox::critical(this,"Error","Query Failed: "+query.lastError().text());
        return;
    }

    QString result;
    while(query.next()) {
        result += QString("AppID: %1 | PatientID: %2 | Date: %3 | Status: %4\n")
                      .arg(query.value(0).toInt())
                      .arg(query.value(1).toInt())
                      .arg(query.value(2).toString())
                      .arg(query.value(3).toString());
    }
    QMessageBox::information(this,"Appointments",result);
}

// View patient full details
void DoctorWindow::viewPatientDetails() {
    bool ok;
    int p_id = QInputDialog::getInt(this,"Patient Details","Enter Patient ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QSqlQuery query;
    query.prepare("SELECT * FROM pt_list WHERE p_id=:pid");
    query.bindValue(":pid", p_id);

    if(!query.exec()) {
        QMessageBox::critical(this,"Error","Query Failed: "+query.lastError().text());
        return;
    }

    if(query.next()) {
        QString info = QString("ID: %1\nName: %2\nAddress: %3\nPhone: %4\nDisease: %5")
                           .arg(query.value("p_id").toInt())
                           .arg(query.value("p_name").toString())
                           .arg(query.value("p_address").toString())
                           .arg(query.value("p_phone_number").toInt())
                           .arg(query.value("p_diesease").toString());
        QMessageBox::information(this,"Patient Info",info);
    } else {
        QMessageBox::information(this,"Patient Info","Patient not found.");
    }
}

// View patient disease only
void DoctorWindow::viewPatientDisease() {
    bool ok;
    int p_id = QInputDialog::getInt(this,"Patient Disease","Enter Patient ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QSqlQuery query;
    query.prepare("SELECT p_diesease FROM pt_list WHERE p_id=:pid");
    query.bindValue(":pid", p_id);

    if(!query.exec()) {
        QMessageBox::critical(this,"Error","Query Failed: "+query.lastError().text());
        return;
    }

    if(query.next()) {
        QMessageBox::information(this,"Disease","Patient Disease: "+query.value(0).toString());
    } else {
        QMessageBox::information(this,"Disease","Patient not found.");
    }
}

// Submit feedback about hospital
void DoctorWindow::submitFeedback() {
    bool ok;
    int doc_id = QInputDialog::getInt(this,"Submit Feedback","Enter Your Doctor ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QString feedback = QInputDialog::getText(this,"Submit Feedback","Feedback:",QLineEdit::Normal,"",&ok);
    if(!ok || feedback.isEmpty()) return;

    if(feedback.length()>1000) {
        QMessageBox::warning(this,"Warning","Feedback too long (max 1000 chars)");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO feedback_hospital(doc_id,feedback) VALUES(:docid,:fb)");
    query.bindValue(":docid", doc_id);
    query.bindValue(":fb", feedback);

    if(!query.exec()) QMessageBox::critical(this,"Error","Insert Failed: "+query.lastError().text());
    else QMessageBox::information(this,"Success","Feedback Submitted!");
}
