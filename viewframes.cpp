#include "viewframes.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{


    mCreateGui();
    // mLoadAdminGui();
}
void MainWindow::mCreateGui(){
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    loginEmailLabel       = new QLabel("Email:",this);
    loginEmailLineEdit    = new QLineEdit(this);
    loginPasswordLabel    = new QLabel("Password:",this);
    loginPasswordLineEdit = new QLineEdit(this);
    //passwordInput->setEchoMode(QLineEdit::Password); // Hide password input

    loginButton = new QPushButton("Login",this);

    mainLayout->addWidget(loginEmailLabel);
    mainLayout->addWidget(loginEmailLineEdit);
    mainLayout->addWidget(loginPasswordLabel);
    mainLayout->addWidget(loginPasswordLineEdit);
    mainLayout->addWidget(loginButton);

    setCentralWidget(centralWidget);
}

void MainWindow::mShowInsertState(bool state)
{
    if(state)
        QMessageBox::information(this,"Success", "Added Successfully");
    else
        QMessageBox::critical(this,"Error", "Error while adding employee");
}

void MainWindow::mShowLoginState(bool state)
{
    if(!state)
        QMessageBox::information(this,"Error", "Incorrect Email or Password");
}
void mLoadUsersGui(QMap<QString,QString> xEmployees);
void MainWindow::mLoadAdminGui(){
    QWidget *centralWidget = new QWidget(this);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QWidget *sideNav = new QWidget(this);
    QVBoxLayout *sideLayout = new QVBoxLayout(sideNav);

    // Buttons for navigation
    studentsButton = new QPushButton("Students", this);
    teachersButton = new QPushButton("Teachers", this);
    subjectsButton = new QPushButton("Subjects", this);
    sideLayout->addWidget(studentsButton);
    sideLayout->addWidget(teachersButton);
    sideLayout->addWidget(subjectsButton);
    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(3); // Change according to the data you need to display
    table->setHorizontalHeaderLabels({"#", "Name", "Details"}); // Set column headers

    // Set a placeholder row as an example
    table->setRowCount(1);
    table->setItem(0, 0, new QTableWidgetItem("1"));
    table->setItem(0, 1, new QTableWidgetItem("John Doe"));
    table->setItem(0, 2, new QTableWidgetItem("Some details"));

    // Connect button clicks to load specific data
    // connect(studentsButton, &QPushButton::clicked, this, &MainWindow::loadStudentsData);
    // connect(teachersButton, &QPushButton::clicked, this, &MainWindow::loadTeachersData);
    // connect(subjectsButton, &QPushButton::clicked, this, &MainWindow::loadSubjectsData);

    // Add side nav and table to the main layout
    mainLayout->addWidget(sideNav);
    mainLayout->addWidget(table);

    setCentralWidget(centralWidget);
}

void MainWindow::mShowDeleteState(bool state) {
    if (state)
        QMessageBox::information(this, "Success", "Deleted Successfully");
    else
        QMessageBox::critical(this, "Error", "Error while deleting person");
}

void MainWindow::mShowModifyState(bool state) {
    if (state)
        QMessageBox::information(this, "Success", "Modified Successfully");
    else
        QMessageBox::critical(this, "Error", "Error while modifying person");
}

void MainWindow::mShowRegisterCourseState(bool state) {
    if (state)
        QMessageBox::information(this, "Success", "Registered for the course successfully");
    else
        QMessageBox::critical(this, "Error", "Error while registering for the course");
}
// void MainWindow::mShowAddSubjectState(bool state) {
//     if (state)
//         QMessageBox::information(this, "Success", "Subject Added Successfully");
//     else
//         QMessageBox::critical(this, "Error", "Error while adding subject");
// }

void MainWindow::mLoadStudentsGui(QList<QMap<QString, QString>> students) {
    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(3); // Change according to the data you need to display
    table->setHorizontalHeaderLabels({"#", "First Name", "Last Name", "Registered Course"}); // Set column headers

    table->setRowCount(students.size());
    for (int i = 0; i < students.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(students[i]["student_id"]));
        table->setItem(i, 1, new QTableWidgetItem(students[i]["first_name"]));
        table->setItem(i, 2, new QTableWidgetItem(students[i]["last_name"]));
        table->setItem(i, 3, new QTableWidgetItem(students[i]["registered_course"]));
    }

    // Replace the existing central widget with the table view
    setCentralWidget(table);
}

void MainWindow::mLoadTeachersGui(){}





QString MainWindow::mGetInputLoginEmail() {
    return loginEmailLineEdit->text();
}

QString MainWindow::mGetInputLoginPassword() {
    return loginPasswordLineEdit->text();
}
QString MainWindow::mGetInputRegisterEmail() {
    return registerEmailLineEdit->text();
}
QString MainWindow::mGetInputRegisterFirstName() {
    return registerFirstNameLineEdit->text();
}

QString MainWindow::mGetInputRegisterLastName() {
    return registerLastNameLineEdit->text();
}
QString MainWindow::mGetInputRegisterPassword() {
    return registerPasswordLineEdit->text();
}
int MainWindow::mGetInputRegisterAge() {
    return registerAgeSpinBox->value();
}
QString MainWindow::mGetInputRegisterGender() {
    return registerGenderComboBox->currentText();
}
QString MainWindow::mGetInputRegisterRegisteredCourse() {
    return registerStudentCourseLineEdit->text();
}

QString MainWindow::mGetInputRegisterTeacherCourse() {
    return registerTeacherCourseLineEdit->text();
}
QString MainWindow::mGetInputRegisterBackground() {
    return registerTeacherBackgroundLineEdit->text();
}
QString MainWindow::mGetInputRegisterAddress(){
    return registerTeacherAddressLineEdit->text();
}
MainWindow::~MainWindow()
{
}
