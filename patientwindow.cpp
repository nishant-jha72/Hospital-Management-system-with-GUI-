#include "patientwindow.h"
#include "dbmanager.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

PatientWindow::PatientWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(450, 350);

    QWidget *central = new QWidget(this);
    central->setStyleSheet("background-color: #e74c3c;"); // red
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setSpacing(15);
    layout->setContentsMargins(20,20,20,20);

    QPushButton *btn1 = new QPushButton("Register Patient", this);
    QPushButton *btn2 = new QPushButton("Book Appointment", this);
    QPushButton *btn3 = new QPushButton("Pay Bill", this);
    QPushButton *btn4 = new QPushButton("View Details", this);

    QString buttonStyle =
        "QPushButton { background-color: #c0392b; color: white; font-size: 14px; padding: 8px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #922b21; }";

    btn1->setStyleSheet(buttonStyle);
    btn2->setStyleSheet(buttonStyle);
    btn3->setStyleSheet(buttonStyle);
    btn4->setStyleSheet(buttonStyle);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);

    setCentralWidget(central);

    connect(btn1, &QPushButton::clicked, this, &PatientWindow::registerPatient);
    connect(btn2, &QPushButton::clicked, this, &PatientWindow::bookAppointment);
    connect(btn3, &QPushButton::clicked, this, &PatientWindow::payBill);
    connect(btn4, &QPushButton::clicked, this, &PatientWindow::viewDetails);
}

// ---------------- Register Patient ----------------
void PatientWindow::registerPatient() {
    bool ok;
    QString name = QInputDialog::getText(this,"Register","Patient Name:",QLineEdit::Normal,"",&ok);
    if(!ok || name.isEmpty()) return;

    QString address = QInputDialog::getText(this,"Register","Address:",QLineEdit::Normal,"",&ok);
    if(!ok || address.isEmpty()) return;

    int phone = QInputDialog::getInt(this,"Register","Phone Number:",0,0,999999999,1,&ok);
    if(!ok) return;

    QString disease = QInputDialog::getText(this,"Register","Disease:",QLineEdit::Normal,"",&ok);
    if(!ok || disease.isEmpty()) return;

    QSqlQuery query;
    query.prepare("INSERT INTO pt_list(p_name, p_address, p_phone_number, p_diesease) "
                  "VALUES(:name,:addr,:phone,:disease)");
    query.bindValue(":name", name);
    query.bindValue(":addr", address);
    query.bindValue(":phone", phone);
    query.bindValue(":disease", disease);

    if(!query.exec()) {
        QMessageBox::critical(this,"Error","Insert Failed: "+query.lastError().text());
    } else {
        int p_id = query.lastInsertId().toInt();
        QMessageBox::information(this,"Registered","Patient ID: "+QString::number(p_id));
    }
}

// ---------------- Book Appointment ----------------
void PatientWindow::bookAppointment() {
    bool ok;
    int doc_id = QInputDialog::getInt(this,"Book Appointment","Doctor ID:",0,0,10000,1,&ok);
    if(!ok) return;

    int p_id = QInputDialog::getInt(this,"Book Appointment","Patient ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QString date = QInputDialog::getText(this,"Book Appointment","Date (YYYY-MM-DD):",QLineEdit::Normal,"",&ok);
    if(!ok || date.isEmpty()) return;

    QSqlQuery query;
    query.prepare("INSERT INTO appoint_table(doc_id,p_id,app_date,status) "
                  "VALUES(:docid,:pid,:date,'pending')");
    query.bindValue(":docid", doc_id);
    query.bindValue(":pid", p_id);
    query.bindValue(":date", date);

    if(!query.exec()) {
        QMessageBox::critical(this,"Error","Booking Failed: "+query.lastError().text());
    } else {
        int app_id = query.lastInsertId().toInt();
        QMessageBox::information(this,"Success","Appointment ID: "+QString::number(app_id));
    }
}

// ---------------- Pay Bill ----------------
void PatientWindow::payBill() {
    bool ok;
    int p_id = QInputDialog::getInt(this,"Pay Bill","Enter Patient ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QSqlQuery query;
    query.prepare("SELECT SUM(p_fee_unpaid) FROM pt_fee_details WHERE p_id=:pid");
    query.bindValue(":pid", p_id);
    if(!query.exec() || !query.next()) {
        QMessageBox::critical(this,"Error","Query Failed: "+query.lastError().text());
        return;
    }

    int fee = query.value(0).toInt();
    int pay = QInputDialog::getInt(this,"Pay Bill","Total Unpaid Fee: "+QString::number(fee)+"\nEnter Amount to Pay:",0,0,fee,1,&ok);
    if(!ok) return;

    int remaining = fee - pay;
    query.prepare("UPDATE pt_fee_details SET p_fee_unpaid=:rem WHERE p_id=:pid");
    query.bindValue(":rem", remaining);
    query.bindValue(":pid", p_id);

    if(!query.exec()) QMessageBox::critical(this,"Error","Update Failed: "+query.lastError().text());
    else QMessageBox::information(this,"Success","Payment Successful! Remaining Fee: "+QString::number(remaining));
}

// ---------------- View Patient Details ----------------
void PatientWindow::viewDetails() {
    bool ok;
    int p_id = QInputDialog::getInt(this,"View Details","Enter Patient ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QSqlQuery query;
    query.prepare("SELECT * FROM pt_list WHERE p_id=:pid");
    query.bindValue(":pid", p_id);
    if(!query.exec() || !query.next()) {
        QMessageBox::information(this,"Details","Patient not found.");
        return;
    }

    QString info = QString("ID: %1\nName: %2\nAddress: %3\nPhone: %4\nDisease: %5")
                       .arg(query.value("p_id").toInt())
                       .arg(query.value("p_name").toString())
                       .arg(query.value("p_address").toString())
                       .arg(query.value("p_phone_number").toInt())
                       .arg(query.value("p_diesease").toString());

    QMessageBox::information(this,"Patient Details",info);
}
