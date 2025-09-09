#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>

class AdminWindow : public QMainWindow {
    Q_OBJECT
public:
    AdminWindow(QWidget *parent = nullptr);

private slots:
    void showPatients();
    void addDoctor();
    void removeDoctor();
    void showFeedback();
    void showDoctor();
};

#endif // ADMINWINDOW_H
