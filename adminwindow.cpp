#include "adminwindow.h"
#include "dbmanager.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(450, 350);

    QWidget *central = new QWidget(this);
    central->setStyleSheet("background-color: #f1c40f;");
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setSpacing(15);
    layout->setContentsMargins(20,20,20,20);

    QPushButton *btn1 = new QPushButton("Show Patient List", this);
    QPushButton *btn2 = new QPushButton("Add Doctor", this);
    QPushButton *btn3 = new QPushButton("Remove Doctor", this);
    QPushButton *btn4 = new QPushButton("Show Feedback", this);
    QPushButton *btn5 = new QPushButton("Show Doctor", this);

    QString buttonStyle =
        "QPushButton { background-color: #34495e; color: white; font-size: 14px; padding: 8px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #2c3e50; }";

    btn1->setStyleSheet(buttonStyle);
    btn2->setStyleSheet(buttonStyle);
    btn3->setStyleSheet(buttonStyle);
    btn4->setStyleSheet(buttonStyle);
    btn5->setStyleSheet(buttonStyle);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);
    layout->addWidget(btn5);

    setCentralWidget(central);

    connect(btn1, &QPushButton::clicked, this, &AdminWindow::showPatients);
    connect(btn2, &QPushButton::clicked, this, &AdminWindow::addDoctor);
    connect(btn3, &QPushButton::clicked, this, &AdminWindow::removeDoctor);
    connect(btn4, &QPushButton::clicked, this, &AdminWindow::showFeedback);
    connect(btn5, &QPushButton::clicked, this, &AdminWindow::showDoctor);
}

void AdminWindow::showDoctor() {
    QSqlQuery query;
    if(!query.exec("SELECT id, doc_name, doc_sal FROM doc_details")) {
        QMessageBox::critical(this, "Error", "Query Failed: " + query.lastError().text());
        return;
    }

    QString result;
    while(query.next()) {
        result += QString("ID: %1 | Name: %2 | SALARY : %3\n")
                      .arg(query.value(0).toInt())
                      .arg(query.value(1).toString())
                      .arg(query.value(2).toInt());
    }
    QMessageBox::information(this, "Doctor List", result);
}

void AdminWindow::showPatients() {
    QSqlQuery query;
    if(!query.exec("SELECT p_id, p_name, p_address FROM pt_list")) {
        QMessageBox::critical(this, "Error", "Query Failed: " + query.lastError().text());
        return;
    }

    QString result;
    while(query.next()) {
        result += QString("ID: %1 | Name: %2 | Fee: %3\n")
                      .arg(query.value(0).toInt())
                      .arg(query.value(1).toString())
                      .arg(query.value(2).toString());
    }
    QMessageBox::information(this, "Patient List", result);
}

void AdminWindow::addDoctor() {
    bool ok;
    QString name = QInputDialog::getText(this,"Add Doctor","Doctor Name:",QLineEdit::Normal,"",&ok);
    if(!ok || name.isEmpty()) return;

    QString spec = QInputDialog::getText(this,"Add Doctor","Specialization:",QLineEdit::Normal,"",&ok);
    if(!ok || spec.isEmpty()) return;

    int salary = QInputDialog::getInt(this,"Add Doctor","Salary:",0,0,1000000,1,&ok);
    if(!ok) return;

    QString phone = QInputDialog::getText(this,"Add Doctor","Phone Number:",QLineEdit::Normal,"",&ok);
    if(!ok || phone.isEmpty()) return;

    QSqlQuery query;
    query.prepare("INSERT INTO doc_details(doc_name, doc_spec, doc_sal, doc_phonr) "
                  "VALUES(:name,:spec,:sal,:phone)");
    query.bindValue(":name", name);
    query.bindValue(":spec", spec);
    query.bindValue(":sal", salary);
    query.bindValue(":phone", phone);

    if(!query.exec()) QMessageBox::critical(this,"Error","Insert Failed: " + query.lastError().text());
    else QMessageBox::information(this,"Success","Doctor Added Successfully!");
}

void AdminWindow::removeDoctor() {
    bool ok;
    int id = QInputDialog::getInt(this,"Remove Doctor","Doctor ID:",0,0,10000,1,&ok);
    if(!ok) return;

    QSqlQuery query;
    query.prepare("DELETE FROM doc_details WHERE id = :id");
    query.bindValue(":id", id);
    if(!query.exec()) QMessageBox::critical(this,"Error","Delete Failed: "+query.lastError().text());
    else QMessageBox::information(this,"Success","Doctor Removed Successfully!");
}

void AdminWindow::showFeedback() {
    QSqlQuery query;
    if(!query.exec("SELECT doc_name, p_feedback, ratings FROM feedback")) {
        QMessageBox::critical(this,"Error","Query Failed: "+query.lastError().text());
        return;
    }

    QString result;
    while(query.next()) {
        result += QString("Doctor: %1 | Feedback: %2 | Ratings: %3\n")
                      .arg(query.value(0).toString())
                      .arg(query.value(1).toString())
                      .arg(query.value(2).toInt());
    }
    QMessageBox::information(this,"Feedback",result);
}
