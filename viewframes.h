#ifndef VIEWFRAMES_H
#define VIEWFRAMES_H

#include <QMainWindow>

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QSpinBox>
#include <QComboBox>


// QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
// QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString mGetInputLoginEmail();
    QString mGetInputLoginPassword();
    QString mGetInputRegisterEmail();
    QString mGetInputRegisterFirstName();
    QString mGetInputRegisterLastName();
    QString mGetInputRegisterPassword();
    int     mGetInputRegisterAge();
    QString mGetInputRegisterGender();
    QString mGetInputRegisterAddress();
    QString mGetInputRegisterRegisteredCourse();
    QString mGetInputRegisterTeacherCourse();
    QString mGetInputRegisterBackground();
    void mShowStudentFrame(QString email, QString firstName);
    void mShowTeacherFrame(QString email, QString firstName);
    void mShowInsertState(bool state);
    void mShowLoginState(bool state);
    void mShowModifyState(bool state);
    void mShowDeleteState(bool state);
    void mShowRegisterCourseState(bool state);
    void mLoadUsersGui(QMap<QString,QString> xEmployees);
    void mLoadAdminGui();
    void mLoadTeachersGui();
    void mLoadStudentsGui(QList<QMap<QString, QString>> students);


    QPushButton *studentsButton;
    QPushButton *teachersButton;
    QPushButton *subjectsButton;
    QPushButton *loginButton;

    QLabel *loginEmailLabel;
    QLineEdit *loginEmailLineEdit;
    QLabel *loginPasswordLabel;
    QLineEdit *loginPasswordLineEdit;

    QLineEdit *registerEmailLineEdit;
    QLineEdit *registerFirstNameLineEdit;
    QLineEdit *registerLastNameLineEdit;
    QLineEdit *registerPasswordLineEdit;
    QSpinBox *registerAgeSpinBox;
    QComboBox *registerGenderComboBox;
    QLineEdit *registerStudentCourseLineEdit;
    QLineEdit *registerTeacherCourseLineEdit;
    QLineEdit *registerTeacherBackgroundLineEdit;
    QLineEdit *registerTeacherAddressLineEdit;
private slots:
    void on_LoginButton_clicked();

//     void on_LogoutPB_clicked();

//     void on_AddUserPB_clicked();

private:
//     // Ui::MainWindow * ui;
    // QString dCurrentUserEmail;

    void mCreateGui();

signals:
    void LoginAttempt();
    void AddNewStudentAttempt();
    void AddNewTeacherAttempt();
};

#endif // VIEWFRAMES_H
