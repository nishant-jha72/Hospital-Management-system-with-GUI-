#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>

class DBManager {
public:
    static QSqlDatabase connectDB() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("hsm");
        db.setUserName("cppuser");
        db.setPassword("Nishant@123");
        if(!db.open()) {
            QMessageBox::critical(nullptr, "Database Connection",
                                  "Failed to connect: " + db.lastError().text());
        }
        return db;
    }
};

#endif // DBMANAGER_H
