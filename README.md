# Hospital-Management-system-with-GUI-
A complete Hospital Management System implemented as a desktop GUI application using Qt (C++) with database support via QSqlDatabase. The system is designed to replace a traditional CLI-based workflow with an intuitive graphical interface, supporting all key hospital operations for Admin, Doctor, and Patient roles.


# Features
# Admin

1 - View, add, and remove patients and doctors

2 - Manage appointments: view, cancel, reschedule

3 - Handle billing: print fee, pay bills

4 - View feedback (all or individual for doctors)


# Doctor

1 - View personal details and appointments

2 - Access patient details and disease information

3 - Submit feedback about the hospital

# Patient

1 - Register and view personal details

2 - Book, cancel, and reschedule appointments

3 - Pay bills

4 - Give ratings to doctors

5 - View disease information


# Technical Highlights

1 - Developed using Qt Widgets for a clean and responsive GUI

2 - QSqlDatabase integration for database operations (supports MySQL or SQLite)

3 - Role-based access control with separate windows for Admin, Doctor, and Patient

4 - Modern GUI with color-coded buttons, spacing, and dialogs for better usability

5 - Modular design: Each role has its own window and functionality encapsulated

# System Requirements

1 - Ubuntu / Windows / macOS

2 - Qt 6 or Qt 5 with Widgets and SQL modules

3 - C++17 compatible compiler

4 - MySQL (optional) or SQLite for database backend

# installation Steps :

1. - Clone the Github Repository
     ```bash
     git clone https://github.com/yourusername/HospitalManagementSystem.git
      cd HospitalManagementSystem
     ```
2. install Dependencies :
   ```bash
     sudo apt update
    sudo apt install qt6-base-dev qt6-tools-dev qt6-sql-mysql libmysqlclient-dev build-essential
   ```
3. Configure Database

  i -  Create a database hospital in MySQL or use SQLite.

  ii -  Execute the provided SQL schema (or create tables manually) for:
  
  iii -  pt_list (patients)

  iv -  doc_details (doctors)

  v - appoint_table (appointments)

  vi - pt_fee_details (billing)

  vii - feedback (ratings & comments)

4. Open project in Qt Creator

    i. Open HospitalManagementSystem.pro (QMake) or CMakeLists.txt (CMake)

    ii. Run qmake / CMake

    iii. Build and run the project

# Usage

-> Launch the application.

->  Select a role: Admin, Doctor, or Patient.

-> Use the GUI to perform all operations:

-> Admin: manage patients/doctors, check appointments, handle billing, view feedback

-> Doctor: view appointments and patient info, submit feedback

-> Patient: register, book appointments, pay bills, give ratings

#PROJECT STRUCTURE : 
```BASH
  HospitalManagementSystem/
├── main.cpp                 # Entry point, handles DB connection and role selection
├── dbmanager.h/.cpp         # Database connection manager
├── adminwindow.h/.cpp       # GUI and functions for Admin
├── doctorwindow.h/.cpp      # GUI and functions for Doctor
├── patientwindow.h/.cpp     # GUI and functions for Patient
├── resources.qrc            # Optional icons/resources
├── HospitalManagementSystem.pro # QMake project file
├── README.md
└── sql/                     # Optional SQL scripts for tables

```
